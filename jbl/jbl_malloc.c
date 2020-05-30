/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_malloc.h"
#if JBL_MALLOC_ENABLE==1
#include "jbl_exception.h"
#define mst jbl_malloc_size_type

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
#endif	

#if JBL_MALLOC_FAST==1
#ifdef __linux__	
	#include <unistd.h>
	#include <sys/mman.h>
#else	
	#include <windows.h>		
	#include <wincrypt.h>
#endif
void*	__jbl_malloc_mmap(mst size);
void	__jbl_malloc_munmap(void *ptr, mst size);
void*	__jbl_malloc_aligned(mst size,mst alignment);
void	__jbl_free_aligned(void* ptr,mst size);
void*	__jbl_malloc_chunk();									//该函数不会操作size              但会操作applied_size
void	__jbl_free_chunk(void *ptr);							//该函数不会操作size              但会操作applied_size
void	__jbl_free_chunks();									//该函数不会操作size和applied_size
void	__jbl_free_cached_chunks();								//该函数不会操作size              但会操作applied_size
void*	__jbl_malloc_page(jbl_uint16 nums,jbl_uint8 type);		//该函数不会操作size和applied_size
void	__jbl_free_page(void *ptr);								//该函数不会操作size和applied_size
void*	__jbl_malloc_large(mst size);							//该函数  会操作size              但不会操作applied_size
void	__jbl_free_large(void *ptr);							//该函数  会操作size              但不会操作applied_size
void*	__jbl_malloc_small(jbl_uint16 size);					//该函数  会操作size              但不会操作applied_size
void	__jbl_free_small(void* ptr);							//该函数  会操作size              但不会操作applied_size
void	__jbl_free_smalls();									//该函数不会操作size和applied_size
void*	__jbl_malloc_huge(mst size);							//该函数  会操作size和applied_size
void	__jbl_free_huge(void* ptr);								//该函数  会操作size和applied_size

static const struct
{
	jbl_uint8 num;
	jbl_uint8 pages;
	jbl_uint16 size;
	jbl_uint16 count;
} jbl_malloc_small_bins[30]={{ 0,1,   8,512},{ 1,1,  16,256},{ 2,1,  24,170},{ 3,1,  32,128},{ 4,1,  40,102}, 
								{ 5,1,  48, 85},{ 6,1,  56, 73},{ 7,1,  64, 64},{ 8,1,  80, 51},{ 9,1,  96, 42},
								{10,1, 112, 36},{11,1, 128, 32},{12,1, 160, 25},{13,1, 192, 21},{14,1, 224, 18}, 
								{15,1, 256, 16},{16,5, 320, 64},{17,3, 384, 32},{18,1, 448,  9},{19,1, 512,  8}, 
								{20,5, 640, 32},{21,3, 768, 16},{22,2, 896,  9},{23,2,1024,  8},{24,5,1280, 16}, 
								{25,3,1536,  8},{26,7,1792, 16},{27,4,2048,  8},{28,5,2560,  8},{29,3,3072,  4}};
#else
#include <malloc.h>	
#endif	
#if JBL_MALLOC_COUNT==1
	jbl_uint64 __jbl_malloc_count[3];
#endif
jbl_malloc_heap_struct jbl_malloc_heap;
void jbl_malloc_start()
{
	jbl_malloc_heap.size=0;
	jbl_malloc_heap.peak=0;
#if JBL_MALLOC_FAST==1
	jbl_malloc_heap.applied_size=0;
	jbl_malloc_heap.applied_peak=0;
	jbl_malloc_heap.cached_chunk_count=0;
	jbl_malloc_heap.huge_list=NULL;
	jbl_malloc_heap.main_chunk=NULL;
	jbl_malloc_heap.cached_chunk=NULL;
#endif	
#if JBL_MALLOC_COUNT==1
	__jbl_malloc_count[0]=0;
	__jbl_malloc_count[1]=0;
	__jbl_malloc_count[2]=0;
#endif
}
void jbl_malloc_stop()
{	
#if JBL_MALLOC_FAST==1
#if JBL_STREAM_ENABLE==1
	jbl_stream_push_chars(jbl_stream_stdout,"\n\n");
	jbl_stream_push_chars(jbl_stream_stdout,"Memory            :");jbl_stream_push_uint64(jbl_stream_stdout,jbl_malloc_heap.size-jbl_malloc_size(jbl_stream_stdout)-(jbl_gc_is_ref(jbl_stream_stdout)?jbl_malloc_size(jbl_refer_pull(jbl_stream_stdout)):0));jbl_stream_push_chars(jbl_stream_stdout,"B\n");	
	jbl_stream_push_chars(jbl_stream_stdout,"Max memory        :");jbl_stream_push_uint64(jbl_stream_stdout,jbl_malloc_heap.peak);jbl_stream_push_chars(jbl_stream_stdout,"B(");jbl_stream_push_double(jbl_stream_stdout,(double)jbl_malloc_heap.peak/1048576);jbl_stream_push_chars(jbl_stream_stdout,"M)\n");	
	jbl_stream_push_chars(jbl_stream_stdout,"Applied max memory:");jbl_stream_push_uint64(jbl_stream_stdout,jbl_malloc_heap.applied_peak>>20);jbl_stream_push_chars(jbl_stream_stdout,"M\n");	
#if JBL_MALLOC_COUNT==1
	jbl_uint64 n=__jbl_malloc_count[0]+__jbl_malloc_count[1]+__jbl_malloc_count[2];
	jbl_stream_push_chars(jbl_stream_stdout,"Small             :");jbl_stream_push_uint64(jbl_stream_stdout,__jbl_malloc_count[0]);jbl_stream_push_chars(jbl_stream_stdout," (");jbl_stream_push_double(jbl_stream_stdout,(double)__jbl_malloc_count[0]*100/n);jbl_stream_push_chars(jbl_stream_stdout,"%)\n");	
	jbl_stream_push_chars(jbl_stream_stdout,"Large             :");jbl_stream_push_uint64(jbl_stream_stdout,__jbl_malloc_count[1]);jbl_stream_push_chars(jbl_stream_stdout," (");jbl_stream_push_double(jbl_stream_stdout,(double)__jbl_malloc_count[1]*100/n);jbl_stream_push_chars(jbl_stream_stdout,"%)\n");	
	jbl_stream_push_chars(jbl_stream_stdout,"Huge              :");jbl_stream_push_uint64(jbl_stream_stdout,__jbl_malloc_count[2]);jbl_stream_push_chars(jbl_stream_stdout," (");jbl_stream_push_double(jbl_stream_stdout,(double)__jbl_malloc_count[2]*100/n);jbl_stream_push_chars(jbl_stream_stdout,"%)\n");	
	
#endif
	jbl_stream_do(jbl_stream_stdout,1);
	jbl_stream_stdout=jbl_stream_free(jbl_stream_stdout);//强推，关闭
#endif
	
	for(;jbl_malloc_heap.huge_list;__jbl_free_huge(jbl_malloc_heap.huge_list->ptr));
	for(void*ptr;jbl_malloc_heap.main_chunk;ptr=jbl_malloc_heap.main_chunk->next,__jbl_free_aligned(jbl_malloc_heap.main_chunk,0X200000),jbl_malloc_heap.main_chunk=ptr,jbl_malloc_heap.applied_size-=0X200000);
	for(void*ptr;jbl_malloc_heap.cached_chunk;ptr=jbl_malloc_heap.cached_chunk->next,__jbl_free_aligned(jbl_malloc_heap.cached_chunk,0X200000),jbl_malloc_heap.cached_chunk=ptr,jbl_malloc_heap.applied_size-=0X200000);

	if(jbl_malloc_heap.huge_list)			jbl_exception(JBL_ERROR_MEMORY_ERROR);
	if(jbl_malloc_heap.main_chunk)			jbl_exception(JBL_ERROR_MEMORY_ERROR);
	if(jbl_malloc_heap.cached_chunk)		jbl_exception(JBL_ERROR_MEMORY_ERROR);
	if(jbl_malloc_heap.applied_size)		jbl_exception(JBL_ERROR_MEMORY_ERROR);
#else
#if JBL_STREAM_ENABLE==1
	jbl_stream_push_chars(jbl_stream_stdout,"Memory    :");jbl_stream_push_uint64(jbl_stream_stdout,jbl_malloc_heap.size-jbl_malloc_size(jbl_stream_stdout));jbl_stream_push_chars(jbl_stream_stdout,"B\n");	
	jbl_stream_push_chars(jbl_stream_stdout,"Max memory:");jbl_stream_push_uint64(jbl_stream_stdout,jbl_malloc_heap.peak);jbl_stream_push_chars(jbl_stream_stdout,"B(");jbl_stream_push_double(jbl_stream_stdout,(double)jbl_malloc_heap.peak/1048576);jbl_stream_push_chars(jbl_stream_stdout,"M)\n");	
	jbl_stream_do(jbl_stream_stdout,1);jbl_stream_stdout=jbl_stream_free(jbl_stream_stdout);//强推，关闭
#endif
#endif
}
#if JBL_MALLOC_FAST==1		
void* __jbl_malloc_mmap(mst size)
{
	#ifdef __linux__
		void* ptr=mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON,-1,0);
		if(ptr==MAP_FAILED)jbl_exception(JBL_ERROR_MEMORY_ERROR);
		return ptr;		
	#else
		void* ptr=VirtualAlloc(NULL,size,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		if(ptr==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);
		return ptr;
	#endif
}
void __jbl_malloc_munmap(void *ptr, mst size)
{
	if(ptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	#ifdef __linux__
		if(munmap(ptr,size)!=0)
			jbl_exception(JBL_ERROR_MEMORY_ERROR);
	#else
		if(VirtualFree(ptr,0,MEM_RELEASE)==0)
			jbl_exception(JBL_ERROR_MEMORY_ERROR);
	#endif
}
void *__jbl_malloc_aligned(mst size,mst alignment)
{
#ifdef __linux__
	void *ptr=__jbl_malloc_mmap(size+alignment-1);
	mst offset=(((mst)(ptr))&((alignment)-1));
	if(offset!=0)
	{
		offset=alignment-offset;
		__jbl_malloc_munmap(ptr,offset);
		ptr=(char*)ptr+offset;
		alignment-=offset;
	}
	if(alignment>0)
		__jbl_malloc_munmap(ptr+size,alignment-1);
#else
	void *ptr=__jbl_malloc_mmap(size+alignment-1);
	mst offset=(((mst)(ptr))&((alignment)-1));
	VirtualFree(ptr,0,MEM_RELEASE);		
	if(offset!=0)
	{
		offset=alignment-offset;
		ptr=VirtualAlloc(ptr+offset,size,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	}
	else
		ptr=VirtualAlloc(ptr,size,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	if(ptr==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);	
#endif
	return ptr;
}
void __jbl_free_aligned(void* ptr,mst size)
{
	if(ptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	__jbl_malloc_munmap(ptr,size);
}
void *__jbl_malloc_chunk()
{
	void *ptr;
	jbl_malloc_chunk_struct *chunk;
	if(jbl_malloc_heap.cached_chunk!=NULL)
	{
		--jbl_malloc_heap.cached_chunk_count;
		ptr=jbl_malloc_heap.cached_chunk;
		chunk=ptr;
		if(chunk->next!=NULL)
			chunk->next->pre=chunk->pre;
		if(chunk->pre==NULL)
			jbl_malloc_heap.cached_chunk=chunk->next;
		else
			chunk->pre->next=chunk->next;
		chunk->next=NULL;
		chunk->pre=NULL;
	}
	else
	{
		ptr=__jbl_malloc_aligned(0X200000,0X200000);//2M
		jbl_malloc_heap.applied_size+=0X200000;jbl_max_update(jbl_malloc_heap.applied_peak,jbl_malloc_heap.applied_size);		
		chunk=ptr;
	}
	for(register jbl_uint16 i=0;i<512;chunk->map[i]=0,++i);
	jbl_bitset_init(chunk->fmap,jbl_malloc_fmap_len);
	chunk->free_pages=511;//第一个page保存chunk_struct
	chunk->map[0]=0X40000000|0X01;//(1<<31)
	jbl_bitset_set(chunk->fmap,0,1);	
	if(jbl_malloc_heap.main_chunk!=NULL)
		jbl_malloc_heap.main_chunk->pre=ptr;
	chunk->next=jbl_malloc_heap.main_chunk;
	chunk->pre=NULL;
	jbl_malloc_heap.main_chunk=ptr;
	return ptr;
}
void __jbl_free_chunk(void *ptr)
{
	if(ptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_malloc_chunk_struct *chunk=ptr;
	if(chunk->next!=NULL)
		chunk->next->pre=chunk->pre;
	if(chunk->pre)
		chunk->pre->next=chunk->next;
	else
		jbl_malloc_heap.main_chunk=chunk->next;
/*TODO:自动决策是否放进缓存 */
//	if(false)
//	{//不用缓存,直接释放
//		__jbl_free_aligned(ptr,0X200000);
//	jbl_malloc_heap.applied_size-=0X200000;
//	}
//	else
//	{
		++jbl_malloc_heap.cached_chunk_count;
		if(jbl_malloc_heap.cached_chunk!=NULL)
			jbl_malloc_heap.cached_chunk->pre=ptr;
		chunk->next=jbl_malloc_heap.cached_chunk;
		chunk->pre=NULL;
		jbl_malloc_heap.cached_chunk=ptr;
//	}
}
void __jbl_free_chunks()
{
	for(jbl_malloc_chunk_struct *chunk=jbl_malloc_heap.main_chunk,*chunk2;chunk;)//遍历表
	{
		if(chunk->fmap[0]!=(1LL<<(jbl_bitset_bits-1)))
			goto not_free;
		for(jbl_uint8 i=1;i<jbl_malloc_fmap_len;++i)
			if(chunk->fmap[i]!=0)
				goto not_free;
		chunk2=chunk->next;
		__jbl_free_chunk(chunk);
		chunk=chunk2;
		continue;
not_free:
		chunk=chunk->next;
	}	
}
void __jbl_free_cached_chunks()
{
	for(void*ptr;jbl_malloc_heap.cached_chunk;ptr=jbl_malloc_heap.cached_chunk->next,__jbl_free_aligned(jbl_malloc_heap.cached_chunk,0X200000),jbl_malloc_heap.cached_chunk=ptr,jbl_malloc_heap.applied_size-=0X200000);
	jbl_malloc_heap.cached_chunk_count=0;
}
void *__jbl_malloc_page(jbl_uint16 nums,jbl_uint8 type)//type为0用于large，type为1用于small
{
	void * ptr=NULL;
	jbl_uint16 cnt0=-1,i0=0;
	jbl_malloc_chunk_struct *chunk0=NULL;
	for(jbl_malloc_chunk_struct *chunk=jbl_malloc_heap.main_chunk;chunk;chunk=chunk->next)//遍历表
	{
		if(chunk->free_pages>=nums)
		{
 			for(jbl_uint16 i=0,cnt1=0,j=0;i<512;++i)
			{
				j=jbl_bitset_find0(chunk->fmap,i,jbl_malloc_fmap_len);
				i=jbl_bitset_find1(chunk->fmap,j,jbl_malloc_fmap_len);
				cnt1=i-j;
				if(cnt1>=nums&&cnt1<cnt0)
					cnt0=cnt1,i0=j,chunk0=chunk;
			}
		}
	}
	if(chunk0==NULL)
		chunk0=__jbl_malloc_chunk(),i0=1;
	chunk0->free_pages-=nums;	
	//在chunk0第i0个位置标记nums个type类型的内存块
	jbl_bitset_set(chunk0->fmap,i0,nums);
	jbl_uint32 tmp;
	if(type==0)
		chunk0->map[i0]=(0X40000000)|nums,	//[31,30]U[9,0] 10b<<29
		tmp=(0X40000000)|nums;
	else
		chunk0->map[i0]=(0X20000000)|(type-1),	//[31,30]U[9,0] 01b<<29
		tmp=(0X60000000)|(type-1);				//				11b<<29
	for(jbl_uint16 i=1;i<nums;++i)
		chunk0->map[i+i0]=tmp|(i<<10);//[31,30]U[19,10]U[9,0]
	
	ptr=chunk0;
	ptr=(char*)ptr+(i0<<12);
	return ptr;
}
void __jbl_free_page(void *ptr)
{
	jbl_malloc_chunk_struct *chunk=(void*)(((mst)ptr)&(~0X1fffff));
	jbl_uint16 i=((mst)(ptr-(void*)chunk))>>12;
	jbl_uint16 n=chunk->map[i]&(0X1FF);
	chunk->free_pages+=n;
	if((chunk->map[i]>>29)&1)//small
		n=jbl_malloc_small_bins[n].pages;	
	jbl_bitset_reset(chunk->fmap,i,n);
}
void* __jbl_malloc_large(mst size)
{
	jbl_uint16 page=((size&(0XFFF))!=0)+(size>>12);//4K对齐
	jbl_malloc_heap.size+=(page<<12);jbl_max_update(jbl_malloc_heap.peak,jbl_malloc_heap.size);
	return __jbl_malloc_page(page,0);
}
void __jbl_free_large(void *ptr)
{
	jbl_malloc_chunk_struct *chunk=(void*)(((mst)ptr)&(~0X1fffff));
	jbl_uint16 i=((mst)(ptr-(void*)chunk))>>12;
	jbl_uint16 n=chunk->map[i]&(0X1FF);	
	chunk->free_pages+=n;
	jbl_malloc_heap.size-=(n<<12);
	jbl_bitset_reset(chunk->fmap,i,n);
}
void* __jbl_malloc_small(jbl_uint16 size)
{	
	jbl_uint8 type=0;
	for(jbl_uint8 i=0;i<30;i++)
		if(jbl_malloc_small_bins[i].size>=size)
			{type=i;break;}
	jbl_malloc_heap.size+=jbl_malloc_small_bins[type].size;jbl_max_update(jbl_malloc_heap.peak,jbl_malloc_heap.size);	
	jbl_uint8 num=jbl_malloc_small_bins[type].num;
	if(jbl_malloc_heap.slot[num].next!=NULL)
	{
		void *ptr=jbl_malloc_heap.slot[num].next;
		jbl_malloc_heap.slot[num].next=jbl_malloc_heap.slot[num].next->next;
		return ptr;
	}
	void *ptr=__jbl_malloc_page(jbl_malloc_small_bins[type].pages,type+1);
	for(jbl_uint16 i=1,n=jbl_malloc_small_bins[type].count,size=jbl_malloc_small_bins[type].size;i<n;++i)
	{
		void *p=(char*)ptr+i*size;
		((jbl_malloc_free_slot*)p)->next=jbl_malloc_heap.slot[num].next;
		jbl_malloc_heap.slot[num].next=p;
	}
	return ptr;
}
void __jbl_free_small(void* ptr)
{
	void *page=(void*)(((mst)ptr)&(~0XFFF));
	jbl_malloc_chunk_struct *chunk=(void*)(((mst)page)&(~0X1fffff));
	jbl_uint16 i=((mst)(page-(void*)chunk))>>12;
	jbl_uint8 type=chunk->map[i]&0X1F;
	
	jbl_uint8 num=jbl_malloc_small_bins[type].num;
	jbl_malloc_heap.size-=jbl_malloc_small_bins[type].size;	
	((jbl_malloc_free_slot*)ptr)->next=jbl_malloc_heap.slot[num].next;
	jbl_malloc_heap.slot[num].next=ptr;
}
void __jbl_free_smalls()
{
	for(jbl_uint8 type=0;type<30;++type)
	{
		for(jbl_malloc_free_slot *ptr=jbl_malloc_heap.slot[type].next;ptr;)
		{
			void *page=(void*)(((mst)ptr)&(~0XFFF));
			jbl_malloc_chunk_struct *chunk=(void*)(((mst)page)&(~0X1fffff));
			jbl_uint16 i=((mst)(page-(void*)chunk))>>12;
			jbl_uint16 fi=i-(jbl_uint32)((chunk->map[i]>>10)&0X1FF);
			jbl_uint16 cnt=(jbl_uint32)((chunk->map[fi]>>20)&0X1FF);
			++cnt;
			//printf("0X%X 0X%X 0X%X %d %d %d %d\n",ptr,page,chunk,i,fi,type,cnt);
			if(cnt==jbl_malloc_small_bins[type].count)
			{
				//printf("FREE 0X%X 0X%X 0X%X %d %d %d\n",ptr,page,chunk,i,fi,type);
				for(jbl_malloc_free_slot *ptr2=jbl_malloc_heap.slot[type].next,*ptr3=NULL;ptr2;)
				{
					void *page2=(void*)(((mst)ptr2)&(~0XFFF));
					jbl_malloc_chunk_struct *chunk2=(void*)(((mst)page2)&(~0X1fffff));
					jbl_uint16 i2=((mst)(page2-(void*)chunk2))>>12;
					jbl_uint16 fi2=i2-(jbl_uint32)((chunk2->map[i2]>>10)&0X1FF);
					//printf("\t0X%X 0X%X 0X%X %d %d\n",ptr2,page2,chunk2,i2,fi2);
					jbl_uint8 flag=0;
					if(ptr2==ptr)
						ptr=ptr2->next,flag=1;
					if(fi2==fi)
						if(ptr3==NULL)
							jbl_malloc_heap.slot[type].next=ptr2->next,ptr2=ptr2->next;//ptr3不动
						else
							(ptr3)->next=ptr2->next,ptr2=ptr2->next;//ptr3不动
					else
						ptr3=ptr2,ptr2=ptr2->next;
					if(flag)
						break;
					
				}
				__jbl_free_page((char*)chunk+(fi<<12));
				continue;
			}
			chunk->map[fi]=0X20000000|type|(cnt<<20);
			ptr=ptr->next;
		}
		for(jbl_malloc_free_slot *ptr=jbl_malloc_heap.slot[type].next;ptr;ptr=ptr->next)
		{
			void *page=(void*)(((mst)ptr)&(~0XFFF));
			jbl_malloc_chunk_struct *chunk=(void*)(((mst)page)&(~0X1fffff));
			jbl_uint16 i=((mst)(page-(void*)chunk))>>12;
			jbl_uint16 fi=i-(jbl_uint32)((chunk->map[i]>>10)&0X1FF);
			chunk->map[fi]=0X20000000|type;
		}			
	}
}

void *__jbl_malloc_huge(mst size)
{
	if(size==0)jbl_exception(JBL_ERROR_MEMORY_ERROR);		
	jbl_malloc_huge_struct* this=jbl_malloc((sizeof (jbl_malloc_huge_struct)));
	this->size=size=(((size&(0XFFF))!=0)+(size>>12))<<12;//4K对齐
	jbl_malloc_heap.size+=size;jbl_max_update(jbl_malloc_heap.peak,jbl_malloc_heap.size);
	jbl_malloc_heap.applied_size+=size;jbl_max_update(jbl_malloc_heap.applied_peak,jbl_malloc_heap.applied_size);
	this->next=jbl_malloc_heap.huge_list;
	jbl_malloc_heap.huge_list=this;
	this->ptr=__jbl_malloc_mmap(size);
//	printf("M %0 16llX\n",this->ptr);
	return this->ptr;
}
void __jbl_free_huge(void* ptr)
{
	for(jbl_malloc_huge_struct *huge=jbl_malloc_heap.huge_list,*pre=NULL;huge!=NULL;pre=huge,huge=huge->next)
		if(ptr==huge->ptr)
		{
//			printf("F %0 16llX\n",huge->ptr);
			if(pre)
				pre->next=huge->next;
			else
				jbl_malloc_heap.huge_list=huge->next;
			__jbl_malloc_munmap(huge->ptr,huge->size);
			jbl_malloc_heap.applied_size-=huge->size;
			jbl_malloc_heap.size-=huge->size;
			jbl_free(huge);
			return;
		}
	jbl_exception(JBL_ERROR_MEMORY_ERROR);
}
#endif	
inline void* jbl_malloc(mst size)
{
	if(size==0)jbl_exception(JBL_ERROR_MEMORY_ERROR);		
#if JBL_MALLOC_FAST==1
	if(size<=3072)//small
	{
#if JBL_MALLOC_COUNT==1		
		++__jbl_malloc_count[0];
#endif
		return __jbl_malloc_small(size);
	}
	else if(size<=2093056)//large 2*1024*1024-4*1024(2M-4K)
	{
#if JBL_MALLOC_COUNT==1		
		++__jbl_malloc_count[1];
#endif
		return __jbl_malloc_large(size);
	}
	else//huge
	{
#if JBL_MALLOC_COUNT==1		
		++__jbl_malloc_count[2];
#endif
		return __jbl_malloc_huge(size);
	}
#else
	void *ptr=malloc(size);
	if(ptr==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);	
	jbl_malloc_heap.size+=jbl_malloc_size(ptr),jbl_max_update(jbl_malloc_heap.peak,jbl_malloc_heap.size);
	return ptr;
#endif	
}
mst jbl_malloc_size(void* ptr)
{
	if(ptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
#if JBL_MALLOC_FAST==1
	void *page=(void*)(((mst)ptr)&(~0XFFF));
	jbl_malloc_chunk_struct *chunk=(void*)(((mst)page)&(~0X1fffff));
	jbl_uint16 i=((mst)(page-(void*)chunk))>>12;
//	printf("%d 0X%X 0X%X 0X%X %d %X\n",__LINE__,ptr,page,chunk,i,chunk->map[i]);
	if(((mst)ptr)&(0XFFF))//没有4k，small
		return jbl_malloc_small_bins[chunk->map[i]&0X1F].size;
	for(jbl_malloc_huge_struct *huge=jbl_malloc_heap.huge_list;huge!=NULL;huge=huge->next)
		if(ptr==huge->ptr)
			return huge->size;
	if(chunk->map[i]&0X20000000)//small
		return jbl_malloc_small_bins[chunk->map[i]&0X1F].size;
	return (chunk->map[i]&0X1ff)<<12;//large
#else
#ifdef __linux__
	return malloc_usable_size(ptr);
#else
	return _msize(ptr);
#endif
#endif
}
void* jbl_realloc(void* ptr,mst size)
{
	if(ptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	if(size==0)jbl_exception(JBL_ERROR_MEMORY_ERROR);		
#if JBL_MALLOC_FAST==1
	mst size_now=jbl_malloc_size(ptr);
	if(size_now>size)
		return ptr;
	
	if(3072<size_now&&size_now<=2093056&&3072<size&&size<=2093056)//全在large
	{
#if JBL_MALLOC_COUNT==1		
		++__jbl_malloc_count[1];
#endif
		jbl_malloc_chunk_struct *chunk=(void*)(((mst)ptr)&(~0X1fffff));
		jbl_uint16 i=((mst)(ptr-(void*)chunk))>>12;
		jbl_uint16 n=chunk->map[i]&(0X1FF);				//有的
		jbl_uint16 page=((size&(0X1FF))!=0)+(size>>12);	//现在需要page个page
		if(jbl_bitset_find1(chunk->fmap,i+n,jbl_malloc_fmap_len)>=i+page)
		{
			jbl_malloc_heap.size+=((page-n)<<12);/*新增page-n个page*/jbl_max_update(jbl_malloc_heap.peak,jbl_malloc_heap.size);
			//在chunk第i个位置标记page个large类型的内存块
			jbl_uint32 tmp=(0X40000000)|page;
			jbl_bitset_set(chunk->fmap,i+n,page-n);
			for(jbl_uint16 j=0;j<page;++j)
				chunk->map[i+j]=tmp|(j<<10);//[30,29]U[19,10]U[9,0]
			return ptr;
		}
	}
	
	void * ptr2=jbl_malloc(size);
	if(ptr2==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);	
	mst size_new=jbl_malloc_size(ptr2);
	jbl_min_update(size_new,size_now);
	jbl_memory_copy(ptr2,ptr,size_new);

//重写free减少查表
	if(size_now<=3072)//small
		__jbl_free_small(ptr);
	else if(size_now<=2093056)//large 2*1024*1024-4*1024(2M-4K)
		__jbl_free_large(ptr);
	else//huge
		__jbl_free_huge(ptr);
		
	return ptr2;	
#else
#ifdef __linux__	
	jbl_malloc_heap.size-=jbl_malloc_size(ptr);
	void *ptr2=realloc(ptr,size);
	if(ptr2==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);
	jbl_malloc_heap.size+=jbl_malloc_size(ptr2),jbl_max_update(jbl_malloc_heap.peak,jbl_malloc_heap.size);
	if(ptr2==NULL)
		jbl_exception(JBL_ERROR_MEMORY_ERROR);
	return ptr2;
#else
	void * ptr2=jbl_malloc(size);
	if(ptr2==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);
	mst size_new=_msize(ptr);
	jbl_min_update(size_new,size);
	jbl_memory_copy(ptr2,ptr,size_new);
	jbl_free(ptr);
	return ptr2;
#endif
#endif
}
inline void jbl_free(void * p)
{
	if(p==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
#if JBL_MALLOC_FAST==1
	mst size=jbl_malloc_size(p);
	if(size<=3072)//small
		__jbl_free_small(p);
	else if(size<=2093056)//large 2*1024*1024-4*1024(2M-4K)
		__jbl_free_large(p);
	else//huge
		__jbl_free_huge(p);
#else	
	jbl_malloc_heap.size-=jbl_malloc_size(p);
	free(p);
#endif
}
void jbl_memory_copy(void *to,const void * from,mst len){for(register mst i=0;i<len;++i)((char*)to)[i]=((char*)from)[i];}
void jbl_memory_copy_reverse(void *to,const void * from,mst len,mst size){for(register mst i=0;i<len;i+=size)for(register mst j=0;j<size;++j)((char*)to)[i+j]=((char*)from)[len-i-size+j];}
#undef mst
#endif
