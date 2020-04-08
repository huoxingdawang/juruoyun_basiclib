/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_malloc.h"
#if JRY_BL_MALLOC_ENABLE==1
#include "jry_bl_exception.h"
#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_stream.h"
#endif	
#if JRY_BL_MALLOC_FAST==1
#ifdef __linux__	
	#include <unistd.h>
	#include <sys/mman.h>
#else	
	#include <windows.h>		
	#include <wincrypt.h>
#endif
void*	__jry_bl_malloc_mmap(jry_bl_malloc_size_type size);
void	__jry_bl_malloc_munmap(void *ptr, jry_bl_malloc_size_type size);
void*	__jry_bl_malloc_aligned(jry_bl_malloc_size_type size,jry_bl_malloc_size_type alignment);
void	__jry_bl_free_aligned(void* ptr,jry_bl_malloc_size_type size);
void*	__jry_bl_malloc_chunk();									//该函数不会操作size				但会操作applied_size
void	__jry_bl_free_chunk(void *ptr);								//该函数不会操作size				但会操作applied_size
void	__jry_bl_free_chunks();										//该函数不会操作size和applied_size
void	__jry_bl_free_cached_chunks();								//该函数不会操作size				但会操作applied_size
void*	__jry_bl_malloc_page(jry_bl_uint16 nums,jry_bl_uint8 type);	//该函数不会操作size和applied_size
void	__jry_bl_free_page(void *ptr);								//该函数不会操作size和applied_size
void*	__jry_bl_malloc_large(jry_bl_malloc_size_type size);		//该函数  会操作size				但不会操作applied_size
void	__jry_bl_free_large(void *ptr);								//该函数  会操作size               但不会操作applied_size
void*	__jry_bl_malloc_small(jry_bl_uint16 size);					//该函数  会操作size				但不会操作applied_size
void	__jry_bl_free_small(void* ptr);								//该函数  会操作size               但不会操作applied_size
void	__jry_bl_free_smalls();										//该函数不会操作size和applied_size
void*	__jry_bl_malloc_huge(jry_bl_malloc_size_type size);			//该函数  会操作size和applied_size
void	__jry_bl_free_huge(void* ptr);								//该函数  会操作size和applied_size

/*

void jry_bl_bitset_set(jry_bl_malloc_fmap_type fmap[jry_bl_malloc_fmap_len],jry_bl_uint16 i,jry_bl_uint16 cnt);
void jry_bl_bitset_reset(jry_bl_malloc_fmap_type fmap[jry_bl_malloc_fmap_len],jry_bl_uint16 i,jry_bl_uint16 cnt);
jry_bl_uint16 jry_bl_bitset_find0(jry_bl_malloc_fmap_type fmap[jry_bl_malloc_fmap_len],jry_bl_uint16 i);
jry_bl_uint16 jry_bl_bitset_find1(jry_bl_malloc_fmap_type fmap[jry_bl_malloc_fmap_len],jry_bl_uint16 i);
#define __jry_bl_malloc_view_fmap(fmap)	for(int i=0;i<jry_bl_malloc_fmap_len;printf("%0 16llX ",fmap[i]),++i);putchar('\n')
*/
static const struct
{
	jry_bl_uint8 num;
	jry_bl_uint8 pages;
	jry_bl_uint16 size;
	jry_bl_uint16 count;
} jry_bl_malloc_small_bins[30]={{ 0,1,   8,512},{ 1,1,  16,256},{ 2,1,  24,170},{ 3,1,  32,128},{ 4,1,  40,102}, 
								{ 5,1,  48, 85},{ 6,1,  56, 73},{ 7,1,  64, 64},{ 8,1,  80, 51},{ 9,1,  96, 42},
								{10,1, 112, 36},{11,1, 128, 32},{12,1, 160, 25},{13,1, 192, 21},{14,1, 224, 18}, 
								{15,1, 256, 16},{16,5, 320, 64},{17,3, 384, 32},{18,1, 448,  9},{19,1, 512,  8}, 
								{20,5, 640, 32},{21,3, 768, 16},{22,2, 896,  9},{23,2,1024,  8},{24,5,1280, 16}, 
								{25,3,1536,  8},{26,7,1792, 16},{27,4,2048,  8},{28,5,2560,  8},{29,3,3072,  4}};
#else
#include <malloc.h>	
#endif	
jry_bl_malloc_heap_struct jry_bl_malloc_heap;
void jry_bl_malloc_start()
{
	jry_bl_malloc_heap.size=0;
	jry_bl_malloc_heap.peak=0;
#if JRY_BL_MALLOC_FAST==1
	jry_bl_malloc_heap.applied_size=0;
	jry_bl_malloc_heap.applied_peak=0;
	jry_bl_malloc_heap.cached_chunk_count=0;
	jry_bl_malloc_heap.huge_list=NULL;
	jry_bl_malloc_heap.main_chunk=NULL;
	jry_bl_malloc_heap.cached_chunk=NULL;
#endif	
}
void jry_bl_malloc_stop()
{	
#if JRY_BL_STREAM_ENABLE==1
	jry_bl_stream_stdout=jry_bl_stream_new(&jry_bl_stream_file_operators,stdout,JRY_BL_STREAM_EXCEED_LENGTH,NULL,0),//重新初始化stdout，因为它已经关了
	jry_bl_stream_push_chars(jry_bl_stream_stdout,"\n\n");
#endif
#if JRY_BL_MALLOC_FAST==1
#if JRY_BL_STREAM_ENABLE==1
	jry_bl_stream_push_chars(jry_bl_stream_stdout,"Memory            :");jry_bl_stream_push_uint64(jry_bl_stream_stdout,jry_bl_malloc_heap.size-jry_bl_malloc_size(jry_bl_stream_stdout));jry_bl_stream_push_chars(jry_bl_stream_stdout,"B\n");	
	jry_bl_stream_push_chars(jry_bl_stream_stdout,"Max memory        :");jry_bl_stream_push_uint64(jry_bl_stream_stdout,jry_bl_malloc_heap.peak);jry_bl_stream_push_chars(jry_bl_stream_stdout,"B(");jry_bl_stream_push_double(jry_bl_stream_stdout,(double)jry_bl_malloc_heap.peak/1048576);jry_bl_stream_push_chars(jry_bl_stream_stdout,"M)\n");	
	jry_bl_stream_push_chars(jry_bl_stream_stdout,"Applied max memory:");jry_bl_stream_push_uint64(jry_bl_stream_stdout,jry_bl_malloc_heap.applied_peak>>20);jry_bl_stream_push_chars(jry_bl_stream_stdout,"M\n");	
	jry_bl_stream_do(jry_bl_stream_stdout,1);
	jry_bl_stream_stdout=jry_bl_stream_free(jry_bl_stream_stdout);//强推，关闭
#endif
	
	for(;jry_bl_malloc_heap.huge_list;__jry_bl_free_huge(jry_bl_malloc_heap.huge_list->ptr));
	for(void*ptr;jry_bl_malloc_heap.main_chunk;ptr=jry_bl_malloc_heap.main_chunk->next,__jry_bl_free_aligned(jry_bl_malloc_heap.main_chunk,0X200000),jry_bl_malloc_heap.main_chunk=ptr,jry_bl_malloc_heap.applied_size-=0X200000);
	for(void*ptr;jry_bl_malloc_heap.cached_chunk;ptr=jry_bl_malloc_heap.cached_chunk->next,__jry_bl_free_aligned(jry_bl_malloc_heap.cached_chunk,0X200000),jry_bl_malloc_heap.cached_chunk=ptr,jry_bl_malloc_heap.applied_size-=0X200000);

	if(jry_bl_malloc_heap.huge_list)			jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	if(jry_bl_malloc_heap.main_chunk)			jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	if(jry_bl_malloc_heap.cached_chunk)			jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	if(jry_bl_malloc_heap.applied_size)			jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
#else
#if JRY_BL_STREAM_ENABLE==1
	jry_bl_stream_push_chars(jry_bl_stream_stdout,"Memory    :");jry_bl_stream_push_uint64(jry_bl_stream_stdout,jry_bl_malloc_heap.size-24);jry_bl_stream_push_chars(jry_bl_stream_stdout,"B\n");	
	jry_bl_stream_push_chars(jry_bl_stream_stdout,"Max memory:");jry_bl_stream_push_uint64(jry_bl_stream_stdout,jry_bl_malloc_heap.peak);jry_bl_stream_push_chars(jry_bl_stream_stdout,"B(");jry_bl_stream_push_double(jry_bl_stream_stdout,(double)jry_bl_malloc_heap.peak/1048576);jry_bl_stream_push_chars(jry_bl_stream_stdout,"M)\n");	
	jry_bl_stream_do(jry_bl_stream_stdout,1);jry_bl_stream_stdout=jry_bl_stream_free(jry_bl_stream_stdout);//强推，关闭
#endif
#endif
}
#if JRY_BL_MALLOC_FAST==1		
void* __jry_bl_malloc_mmap(jry_bl_malloc_size_type size)
{
	#ifdef __linux__
		void* ptr=mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON,-1,0);
		if(ptr==MAP_FAILED)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
		return ptr;		
	#else
		void* ptr=VirtualAlloc(NULL,size,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
		return ptr;
	#endif
}
void __jry_bl_malloc_munmap(void *ptr, jry_bl_malloc_size_type size)
{
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	#ifdef __linux__
		if(munmap(ptr,size)!=0)
			jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	#else
		if(VirtualFree(ptr,0,MEM_RELEASE)==0)
			jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	#endif
}
void *__jry_bl_malloc_aligned(jry_bl_malloc_size_type size,jry_bl_malloc_size_type alignment)
{
#ifdef __linux__
	void *ptr=__jry_bl_malloc_mmap(size+alignment-1);
	jry_bl_malloc_size_type offset=(((jry_bl_malloc_size_type)(ptr))&((alignment)-1));
	if(offset!=0)
	{
		offset=alignment-offset;
		__jry_bl_malloc_munmap(ptr,offset);
		ptr=(char*)ptr+offset;
		alignment-=offset;
	}
	if(alignment>0)
		__jry_bl_malloc_munmap(ptr+size,alignment-1);
#else
	void *ptr=__jry_bl_malloc_mmap(size+alignment-1);
	jry_bl_malloc_size_type offset=(((jry_bl_malloc_size_type)(ptr))&((alignment)-1));
	VirtualFree(ptr,0,MEM_RELEASE);		
	if(offset!=0)
	{
		offset=alignment-offset;
		ptr=VirtualAlloc(ptr+offset,size,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	}
	else
		ptr=VirtualAlloc(ptr,size,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
#endif
	return ptr;
}
void __jry_bl_free_aligned(void* ptr,jry_bl_malloc_size_type size)
{
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	__jry_bl_malloc_munmap(ptr,size);
}
void *__jry_bl_malloc_chunk()
{
	void *ptr;
	jry_bl_malloc_chunk_struct *chunk;
	if(jry_bl_malloc_heap.cached_chunk!=NULL)
	{
		--jry_bl_malloc_heap.cached_chunk_count;
		ptr=jry_bl_malloc_heap.cached_chunk;
		chunk=ptr;
		if(chunk->next!=NULL)
			chunk->next->pre=chunk->pre;
		if(chunk->pre==NULL)
			jry_bl_malloc_heap.cached_chunk=chunk->next;
		else
			chunk->pre->next=chunk->next;
		chunk->next=NULL;
		chunk->pre=NULL;
	}
	else
	{
		ptr=__jry_bl_malloc_aligned(0X200000,0X200000);//2M
		jry_bl_malloc_heap.applied_size+=0X200000;jry_bl_max_update(jry_bl_malloc_heap.applied_peak,jry_bl_malloc_heap.applied_size);		
		chunk=ptr;
	}
	for(register jry_bl_uint16 i=0;i<512;chunk->map[i]=0,++i);
	jry_bl_bitset_init(chunk->fmap,jry_bl_malloc_fmap_len);
	chunk->free_pages=511;//第一个page保存chunk_struct
	chunk->map[0]=0X40000000|0X01;//(1<<31)
	jry_bl_bitset_set(chunk->fmap,0,1);	
	if(jry_bl_malloc_heap.main_chunk!=NULL)
		jry_bl_malloc_heap.main_chunk->pre=ptr;
	chunk->next=jry_bl_malloc_heap.main_chunk;
	chunk->pre=NULL;
	jry_bl_malloc_heap.main_chunk=ptr;
	return ptr;
}
void __jry_bl_free_chunk(void *ptr)
{
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	jry_bl_malloc_chunk_struct *chunk=ptr;
	if(chunk->next!=NULL)
		chunk->next->pre=chunk->pre;
	if(chunk->pre)
		chunk->pre->next=chunk->next;
	else
		jry_bl_malloc_heap.main_chunk=chunk->next;
/*TODO:自动决策是否放进缓存 */
//	if(false)
//	{//不用缓存,直接释放
//		__jry_bl_free_aligned(ptr,0X200000);
//	jry_bl_malloc_heap.applied_size-=0X200000;
//	}
//	else
//	{
		++jry_bl_malloc_heap.cached_chunk_count;
		if(jry_bl_malloc_heap.cached_chunk!=NULL)
			jry_bl_malloc_heap.cached_chunk->pre=ptr;
		chunk->next=jry_bl_malloc_heap.cached_chunk;
		chunk->pre=NULL;
		jry_bl_malloc_heap.cached_chunk=ptr;
//	}
}
void __jry_bl_free_chunks()
{
	for(jry_bl_malloc_chunk_struct *chunk=jry_bl_malloc_heap.main_chunk,*chunk2;chunk;)//遍历表
	{
		if(chunk->fmap[0]!=(1LL<<(jry_bl_bitset_bits-1)))
			goto not_free;
		for(jry_bl_uint8 i=1;i<jry_bl_malloc_fmap_len;++i)
			if(chunk->fmap[i]!=0)
				goto not_free;
		chunk2=chunk->next;
		__jry_bl_free_chunk(chunk);
		chunk=chunk2;
		continue;
not_free:
		chunk=chunk->next;
	}	
}
void __jry_bl_free_cached_chunks()
{
	for(void*ptr;jry_bl_malloc_heap.cached_chunk;ptr=jry_bl_malloc_heap.cached_chunk->next,__jry_bl_free_aligned(jry_bl_malloc_heap.cached_chunk,0X200000),jry_bl_malloc_heap.cached_chunk=ptr,jry_bl_malloc_heap.applied_size-=0X200000);
	jry_bl_malloc_heap.cached_chunk_count=0;
}
void *__jry_bl_malloc_page(jry_bl_uint16 nums,jry_bl_uint8 type)//type为0用于large，type为1用于small
{
	void * ptr=NULL;
	jry_bl_uint16 cnt0=-1,i0=0;
	jry_bl_malloc_chunk_struct *chunk0=NULL;
	for(jry_bl_malloc_chunk_struct *chunk=jry_bl_malloc_heap.main_chunk;chunk;chunk=chunk->next)//遍历表
	{
		if(chunk->free_pages>=nums)
		{
 			for(jry_bl_uint16 i=0,cnt1=0,j=0;i<512;++i)
			{
				j=jry_bl_bitset_find0(chunk->fmap,i,jry_bl_malloc_fmap_len);
				i=jry_bl_bitset_find1(chunk->fmap,j,jry_bl_malloc_fmap_len);
				cnt1=i-j;
				if(cnt1>=nums&&cnt1<cnt0)
					cnt0=cnt1,i0=j,chunk0=chunk;
			}
		}
	}
	if(chunk0==NULL)
		chunk0=__jry_bl_malloc_chunk(),i0=1;
	chunk0->free_pages-=nums;	
	//在chunk0第i0个位置标记nums个type类型的内存块
	jry_bl_bitset_set(chunk0->fmap,i0,nums);
	jry_bl_uint32 tmp;
	if(type==0)
		chunk0->map[i0]=(0X40000000)|nums,	//[31,30]U[9,0] 10b<<29
		tmp=(0X40000000)|nums;
	else
		chunk0->map[i0]=(0X20000000)|(type-1),	//[31,30]U[9,0] 01b<<29
		tmp=(0X60000000)|(type-1);				//				11b<<29
	for(jry_bl_uint16 i=1;i<nums;++i)
		chunk0->map[i+i0]=tmp|(i<<10);//[31,30]U[19,10]U[9,0]
	
	ptr=chunk0;
	ptr=(char*)ptr+(i0<<12);
	return ptr;
}
void __jry_bl_free_page(void *ptr)
{
	jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)ptr)&(~0X1fffff));
	jry_bl_uint16 i=((jry_bl_uint64)(ptr-(void*)chunk))>>12;
	jry_bl_uint16 n=chunk->map[i]&(0X1FF);
	chunk->free_pages+=n;
	if((chunk->map[i]>>29)&1)//small
		n=jry_bl_malloc_small_bins[n].pages;	
	jry_bl_bitset_reset(chunk->fmap,i,n);
}
void* __jry_bl_malloc_large(jry_bl_malloc_size_type size)
{
	jry_bl_uint16 page=((size&(0XFFF))!=0)+(size>>12);//4K对齐
	jry_bl_malloc_heap.size+=(page<<12);jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
	return __jry_bl_malloc_page(page,0);
}
void __jry_bl_free_large(void *ptr)
{
	jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)ptr)&(~0X1fffff));
	jry_bl_uint16 i=((jry_bl_uint64)(ptr-(void*)chunk))>>12;
	jry_bl_uint16 n=chunk->map[i]&(0X1FF);	
	chunk->free_pages+=n;
	jry_bl_malloc_heap.size-=(n<<12);
	jry_bl_bitset_reset(chunk->fmap,i,n);
}
void* __jry_bl_malloc_small(jry_bl_uint16 size)
{	
	jry_bl_uint8 type=0;
	for(jry_bl_uint8 i=0;i<30;i++)
		if(jry_bl_malloc_small_bins[i].size>=size)
			{type=i;break;}
	jry_bl_malloc_heap.size+=jry_bl_malloc_small_bins[type].size;jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);	
	jry_bl_uint8 num=jry_bl_malloc_small_bins[type].num;
	if(jry_bl_malloc_heap.slot[num].next!=NULL)
	{
		void *ptr=jry_bl_malloc_heap.slot[num].next;
		jry_bl_malloc_heap.slot[num].next=jry_bl_malloc_heap.slot[num].next->next;
		return ptr;
	}
	void *ptr=__jry_bl_malloc_page(jry_bl_malloc_small_bins[type].pages,type+1);
	for(jry_bl_uint16 i=1,n=jry_bl_malloc_small_bins[type].count,size=jry_bl_malloc_small_bins[type].size;i<n;++i)
	{
		void *p=(char*)ptr+i*size;
		((jry_bl_malloc_free_slot*)p)->next=jry_bl_malloc_heap.slot[num].next;
		jry_bl_malloc_heap.slot[num].next=p;
	}
	return ptr;
}
void __jry_bl_free_small(void* ptr)
{
	void *page=(void*)(((jry_bl_uint64)ptr)&(~0XFFF));
	jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)page)&(~0X1fffff));
	jry_bl_uint16 i=((jry_bl_uint64)(page-(void*)chunk))>>12;
	jry_bl_uint8 type=chunk->map[i]&0X1F;
	
	jry_bl_uint8 num=jry_bl_malloc_small_bins[type].num;
	jry_bl_malloc_heap.size-=jry_bl_malloc_small_bins[type].size;	
	((jry_bl_malloc_free_slot*)ptr)->next=jry_bl_malloc_heap.slot[num].next;
	jry_bl_malloc_heap.slot[num].next=ptr;
}
void __jry_bl_free_smalls()
{
	for(jry_bl_uint8 type=0;type<30;++type)
	{
		for(jry_bl_malloc_free_slot *ptr=jry_bl_malloc_heap.slot[type].next;ptr;)
		{
			void *page=(void*)(((jry_bl_uint64)ptr)&(~0XFFF));
			jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)page)&(~0X1fffff));
			jry_bl_uint16 i=((jry_bl_uint64)(page-(void*)chunk))>>12;
			jry_bl_uint16 fi=i-(jry_bl_uint32)((chunk->map[i]>>10)&0X1FF);
			jry_bl_uint16 cnt=(jry_bl_uint32)((chunk->map[fi]>>20)&0X1FF);
			++cnt;
			//printf("0X%X 0X%X 0X%X %d %d %d %d\n",ptr,page,chunk,i,fi,type,cnt);
			if(cnt==jry_bl_malloc_small_bins[type].count)
			{
				//printf("FREE 0X%X 0X%X 0X%X %d %d %d\n",ptr,page,chunk,i,fi,type);
				for(jry_bl_malloc_free_slot *ptr2=jry_bl_malloc_heap.slot[type].next,*ptr3=NULL;ptr2;)
				{
					void *page2=(void*)(((jry_bl_uint64)ptr2)&(~0XFFF));
					jry_bl_malloc_chunk_struct *chunk2=(void*)(((jry_bl_uint64)page2)&(~0X1fffff));
					jry_bl_uint16 i2=((jry_bl_uint64)(page2-(void*)chunk2))>>12;
					jry_bl_uint16 fi2=i2-(jry_bl_uint32)((chunk2->map[i2]>>10)&0X1FF);
					//printf("\t0X%X 0X%X 0X%X %d %d\n",ptr2,page2,chunk2,i2,fi2);
					jry_bl_uint8 flag=0;
					if(ptr2==ptr)
						ptr=ptr2->next,flag=1;
					if(fi2==fi)
						if(ptr3==NULL)
							jry_bl_malloc_heap.slot[type].next=ptr2->next,ptr2=ptr2->next;//ptr3不动
						else
							(ptr3)->next=ptr2->next,ptr2=ptr2->next;//ptr3不动
					else
						ptr3=ptr2,ptr2=ptr2->next;
					if(flag)
						break;
					
				}
				__jry_bl_free_page((char*)chunk+(fi<<12));
				continue;
			}
			chunk->map[fi]=0X20000000|type|(cnt<<20);
			ptr=ptr->next;
		}
		for(jry_bl_malloc_free_slot *ptr=jry_bl_malloc_heap.slot[type].next;ptr;ptr=ptr->next)
		{
			void *page=(void*)(((jry_bl_uint64)ptr)&(~0XFFF));
			jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)page)&(~0X1fffff));
			jry_bl_uint16 i=((jry_bl_uint64)(page-(void*)chunk))>>12;
			jry_bl_uint16 fi=i-(jry_bl_uint32)((chunk->map[i]>>10)&0X1FF);
			chunk->map[fi]=0X20000000|type;
		}			
	}
}

void *__jry_bl_malloc_huge(jry_bl_malloc_size_type size)
{
	if(size==0)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);		
	jry_bl_malloc_huge_struct* this=jry_bl_malloc((sizeof (jry_bl_malloc_huge_struct)));
	this->size=size=(((size&(0XFFF))!=0)+(size>>12))<<12;//4K对齐
	jry_bl_malloc_heap.size+=size;jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
	jry_bl_malloc_heap.applied_size+=size;jry_bl_max_update(jry_bl_malloc_heap.applied_peak,jry_bl_malloc_heap.applied_size);
	this->next=jry_bl_malloc_heap.huge_list;
	jry_bl_malloc_heap.huge_list=this;
	this->ptr=__jry_bl_malloc_mmap(size);
//	printf("M %0 16llX\n",this->ptr);
	return this->ptr;
}
void __jry_bl_free_huge(void* ptr)
{
	for(jry_bl_malloc_huge_struct *huge=jry_bl_malloc_heap.huge_list,*pre=NULL;huge!=NULL;pre=huge,huge=huge->next)
		if(ptr==huge->ptr)
		{
//			printf("F %0 16llX\n",huge->ptr);
			if(pre)
				pre->next=huge->next;
			else
				jry_bl_malloc_heap.huge_list=huge->next;
			__jry_bl_malloc_munmap(huge->ptr,huge->size);
			jry_bl_malloc_heap.applied_size-=huge->size;
			jry_bl_malloc_heap.size-=huge->size;
			jry_bl_free(huge);
			return;
		}
	jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
}
#endif	
inline void* jry_bl_malloc(jry_bl_malloc_size_type size)
{
	if(size==0)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);		
#if JRY_BL_MALLOC_FAST==1
	if(size<=3072)//small		
		return __jry_bl_malloc_small(size);
	else if(size<=2093056)//large 2*1024*1024-4*1024(2M-4K)
		return __jry_bl_malloc_large(size);
	else//huge
		return __jry_bl_malloc_huge(size);
#else
	void *ptr=malloc(size);
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
	jry_bl_malloc_heap.size+=jry_bl_malloc_size(ptr),jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
	return ptr;
#endif	
}
jry_bl_malloc_size_type jry_bl_malloc_size(const void* ptr)
{
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
#if JRY_BL_MALLOC_FAST==1
	void *page=(void*)(((jry_bl_uint64)ptr)&(~0XFFF));
	jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)page)&(~0X1fffff));
	jry_bl_uint16 i=((jry_bl_uint64)(page-(void*)chunk))>>12;
//	printf("%d 0X%X 0X%X 0X%X %d %X\n",__LINE__,ptr,page,chunk,i,chunk->map[i]);
	if(((jry_bl_uint64)ptr)&(0XFFF))//没有4k，small
		return jry_bl_malloc_small_bins[chunk->map[i]&0X1F].size;
	for(jry_bl_malloc_huge_struct *huge=jry_bl_malloc_heap.huge_list;huge!=NULL;huge=huge->next)
		if(ptr==huge->ptr)
			return huge->size;
	if(chunk->map[i]&0X20000000)//small
		return jry_bl_malloc_small_bins[chunk->map[i]&0X1F].size;
	return (chunk->map[i]&0X1ff)<<12;//large
#else
#ifdef __linux__
	return malloc_usable_size(ptr);
#else
	return _msize(ptr);
#endif
#endif
}
void* jry_bl_realloc(void* ptr,jry_bl_malloc_size_type size)
{
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	if(size==0)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);		
#if JRY_BL_MALLOC_FAST==1
	jry_bl_malloc_size_type size_now=jry_bl_malloc_size(ptr);
	if(size_now>size)
		return ptr;
	
	if(3072<size_now&&size_now<=2093056&&3072<size&&size<=2093056)//全在large
	{
		jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)ptr)&(~0X1fffff));
		jry_bl_uint16 i=((jry_bl_uint64)(ptr-(void*)chunk))>>12;
		jry_bl_uint16 n=chunk->map[i]&(0X1FF);				//有的
		jry_bl_uint16 page=((size&(0X1FF))!=0)+(size>>12);	//现在需要page个page
		if(jry_bl_bitset_find1(chunk->fmap,i+n,jry_bl_malloc_fmap_len)>=i+page)
		{
			jry_bl_malloc_heap.size+=((page-n)<<12);/*新增page-n个page*/jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
			//在chunk第i个位置标记page个large类型的内存块
			jry_bl_uint32 tmp=(0X40000000)|page;
			jry_bl_bitset_set(chunk->fmap,i+n,page-n);
			for(jry_bl_uint16 j=0;j<page;++j)
				chunk->map[i+j]=tmp|(j<<10);//[30,29]U[19,10]U[9,0]
			return ptr;
		}
	}
	
	void * ptr2=jry_bl_malloc(size);
	if(ptr2==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
	jry_bl_malloc_size_type size_new=jry_bl_malloc_size(ptr2);
	jry_bl_min_update(size_new,size_now);
	jry_bl_memory_copy(ptr2,ptr,size_new);

//重写free减少查表
	if(size_now<=3072)//small
		__jry_bl_free_small(ptr);
	else if(size_now<=2093056)//large 2*1024*1024-4*1024(2M-4K)
		__jry_bl_free_large(ptr);
	else//huge
		__jry_bl_free_huge(ptr);
		
	return ptr2;	
#else
#ifdef __linux__	
	jry_bl_malloc_heap.size-=jry_bl_malloc_size(ptr);
	void *ptr2=realloc(ptr,size);
	if(ptr2==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	jry_bl_malloc_heap.size+=jry_bl_malloc_size(ptr2),jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
	if(ptr2==NULL)
		jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	return ptr2;
#else
	void * ptr2=jry_bl_malloc(size);
	if(ptr2==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	jry_bl_malloc_size_type size_new=_msize(ptr);
	jry_bl_min_update(size_new,size);
	jry_bl_memory_copy(ptr2,ptr,size_new);
	jry_bl_free(ptr);
	return ptr2;
#endif
#endif
}
inline void jry_bl_free(void * p)
{
	if(p==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
#if JRY_BL_MALLOC_FAST==1
	jry_bl_malloc_size_type size=jry_bl_malloc_size(p);
	if(size<=3072)//small
		__jry_bl_free_small(p);
	else if(size<=2093056)//large 2*1024*1024-4*1024(2M-4K)
		__jry_bl_free_large(p);
	else//huge
		__jry_bl_free_huge(p);
#else	
	jry_bl_malloc_heap.size-=jry_bl_malloc_size(p);
	free(p);
#endif
}
void jry_bl_memory_copy(void *to,const void * from,jry_bl_malloc_size_type len){for(register jry_bl_malloc_size_type i=0;i<len;++i)((char*)to)[i]=((char*)from)[i];}
void jry_bl_memory_copy_reverse(void *to,const void * from,jry_bl_malloc_size_type len,jry_bl_malloc_size_type size){for(register jry_bl_malloc_size_type i=0;i<len;i+=size)for(register jry_bl_malloc_size_type j=0;j<size;++j)((char*)to)[i+j]=((char*)from)[len-i-size+j];}
#endif
