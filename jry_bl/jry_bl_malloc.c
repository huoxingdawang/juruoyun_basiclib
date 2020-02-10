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
#include <stdio.h>
jry_bl_malloc_heap_struct jry_bl_malloc_heap;

void jry_bl_malloc_start()
{
	jry_bl_malloc_heap.size=0;
	jry_bl_malloc_heap.peak=0;
#if JRY_BL_MALLOC_FAST==1
	jry_bl_malloc_heap.applied_size=0;
	jry_bl_malloc_heap.applied_peak=0;
	jry_bl_malloc_heap.average_chunk_count=1;
	jry_bl_malloc_heap.cached_chunk_count=0;
	jry_bl_malloc_heap.huge_list=NULL;
	jry_bl_malloc_heap.main_chunk=NULL;
	jry_bl_malloc_heap.cached_chunk=NULL;
#endif	
}
void jry_bl_malloc_stop()
{
#if JRY_BL_MALLOC_FAST==1

#endif
	printf("\nMEMEORY:%lld\nMAX MEMEORY:%lld\n",jry_bl_malloced_size,jry_bl_malloced_peak); 
}
#if JRY_BL_MALLOC_FAST==1
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
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
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
		jry_bl_malloc_heap.applied_size+=0X200000;
		jry_bl_max_update(jry_bl_malloc_heap.applied_peak,jry_bl_malloc_heap.applied_size);
		jry_bl_malloc_heap.average_chunk_count=(jry_bl_malloc_heap.average_chunk_count+1)/2;
		chunk=ptr;
		if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
	}
	for(jry_bl_uint16 i=0;i<512;chunk->map[i]=0,++i);
	chunk->free_pages=511;//第一个page保存chunk_struct
	chunk->map[0]=0X40000000|0X01;//(1<<31)
	
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
//	printf("%f %d\n",(float)jry_bl_malloc_heap.average_chunk_count,jry_bl_malloc_heap.cached_chunk_count);
	if(chunk->next!=NULL)
		chunk->next->pre=chunk->pre;
	if(chunk->pre==NULL)
		jry_bl_malloc_heap.main_chunk=chunk->next;
	else
		chunk->pre->next=chunk->next;
	if(jry_bl_malloc_heap.cached_chunk_count>jry_bl_malloc_heap.average_chunk_count)//不用缓存
	{
//		printf("%d\n",__LINE__);
		__jry_bl_free_aligned(ptr,0X200000);
		jry_bl_malloc_heap.applied_size-=0X200000;
	}
	else
	{
//		printf("%d\n",__LINE__);
		++jry_bl_malloc_heap.cached_chunk_count;
		if(jry_bl_malloc_heap.cached_chunk!=NULL)
			jry_bl_malloc_heap.cached_chunk->pre=ptr;
		chunk->next=jry_bl_malloc_heap.cached_chunk;
		chunk->pre=NULL;
		jry_bl_malloc_heap.cached_chunk=ptr;
	}
}
void *__jry_bl_malloc_page(jry_bl_uint16 nums,jry_bl_uint8 type)//type为0用于large，type为1用于small
{
	if(nums>511||nums==0)
		jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	void * ptr=NULL;
	jry_bl_uint16 cnt0=-1,cnt1=0,i0=0,i1=0;
	jry_bl_malloc_chunk_struct *chunk0=NULL;
	for(jry_bl_malloc_chunk_struct *chunk=jry_bl_malloc_heap.main_chunk;chunk!=NULL;chunk=chunk->next)//遍历表
	{
		if(chunk->free_pages>nums)
		{
			cnt1=0;
			for(jry_bl_uint16 i=0;i<512;++i)
			{
				if(chunk->map[i]==0)
				{
					if(cnt1==0)
						i1=i;
					cnt1++;
				}
				else
				{
					if(cnt1>nums&&cnt1<cnt0)
						cnt0=cnt1,i0=i1,chunk0=chunk;
					cnt1=0;
				}
			}
			if(cnt1>nums&&cnt1<cnt0)
				cnt0=cnt1,i0=i1,chunk0=chunk;
		}
	}
	if(chunk0==NULL)
		chunk0=__jry_bl_malloc_chunk(),i0=1;
	//在chunk0第i0个位置标记nums个type类型的内存块
	jry_bl_uint32 tmp;
	if(type==0)
		chunk0->map[i0]=(0X40000000)|nums,	//[31,30]U[9,0] 10b<<29
		tmp=(0X40000000)|nums;
	else
		chunk0->map[i0]=(0X20000000)|(type-1),	//[31,30]U[9,0] 01b<<29
		tmp=(0X60000000)|(type-1);				//				11b<<29
	for(jry_bl_uint16 i=1;i<nums;++i)
		chunk0->map[i+i0]=tmp|(i<<10);//[30,29]U[19,10]U[9,0]
	ptr=chunk0;
	ptr=(char*)ptr+(i0<<12);
	return ptr;
}
void __jry_bl_free_page(void *ptr)
{
	jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)ptr)&(~0X1fffff));
	jry_bl_uint16 i=((jry_bl_uint64)(ptr-(void*)chunk))>>12;
	jry_bl_uint16 n=chunk->map[i]&(0X1FF);
//	printf("0X%X 0X%X %d %d\n",ptr,chunk,i,n);
	for(n+=i;i<n;++i)
		chunk->map[i]=0;
}
void* __jry_bl_malloc_small(jry_bl_uint16 size)
{
	if(size>3072)
		jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	jry_bl_uint8 type=0;
	for(jry_bl_uint8 i=0;i<30;i++)
		if(jry_bl_malloc_small_bins[i].size>=size)
			{type=i;break;}
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
//	jry_bl_uint16 fi=i-(jry_bl_uint32)((chunk->map[i]>>10)&0X1FF);
	jry_bl_uint8 type=chunk->map[i]&0X1F;
//	printf("0X%X 0X%X 0X%X %d %d\n",ptr,page,chunk,i,type);
	
	jry_bl_uint8 num=jry_bl_malloc_small_bins[type].num;
	((jry_bl_malloc_free_slot*)ptr)->next=jry_bl_malloc_heap.slot[num].next;
	jry_bl_malloc_heap.slot[num].next=ptr;
	
}


#endif	
void* jry_bl_malloc(jry_bl_malloc_size_type size)
{
#if JRY_BL_MALLOC_FAST==1
	if(size<=3072)//small
	{
		jry_bl_malloc_heap.size+=size;jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
		return __jry_bl_malloc_small(size);
	}
	else if(size<=2093056)//large 2*1024*1024-4*1024(2M-4K)
	{
		jry_bl_uint16 page=((size&(0X1FF))!=0)+(size>>12);//4K对齐
		jry_bl_malloc_heap.size+=(page<<12);jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
		return __jry_bl_malloc_page(page,0);
	}
	else//huge
	{
		jry_bl_malloc_huge_struct* this=jry_bl_malloc((sizeof (jry_bl_malloc_huge_struct)));
		this->size=size=(((size&(0X1FF))!=0)+(size>>12))<<12;//4K对齐
		jry_bl_malloc_heap.size+=size;jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
		this->next=jry_bl_malloc_heap.huge_list;
		jry_bl_malloc_heap.huge_list=this;
		return this->ptr=__jry_bl_malloc_mmap(size);
	}
#else
	void *ptr=malloc(size);
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
	jry_bl_malloc_heap.size+=jry_bl_malloc_size(ptr),jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
	return ptr;
#endif	
}
jry_bl_malloc_size_type jry_bl_malloc_size(void* ptr)
{
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
#if JRY_BL_MALLOC_FAST==1
	void *page=(void*)(((jry_bl_uint64)ptr)&(~0XFFF));
	jry_bl_malloc_chunk_struct *chunk=(void*)(((jry_bl_uint64)page)&(~0X1fffff));
	jry_bl_uint16 i=((jry_bl_uint64)(page-(void*)chunk))>>12;
//	printf("0X%X 0X%X 0X%X %d\n",ptr,page,chunk,i);
	if(((jry_bl_uint64)ptr)&(0XFFF))//没有4k，small
		goto small;
	for(jry_bl_malloc_huge_struct *huge=jry_bl_malloc_heap.huge_list;huge!=NULL;huge=huge->next)
		if(ptr==huge->ptr)
			return huge->size;
	
small:
	if(chunk->map[i]&0X40000000)
		return (chunk->map[i]&0X1ff)<<12;
	return jry_bl_malloc_small_bins[chunk->map[i]&0X1F].size;
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
#if JRY_BL_MALLOC_FAST==1
	jry_bl_malloc_size_type size_now=jry_bl_malloc_size(ptr);
	if(size_now>size)
		return ptr;
	void * ptr2=jry_bl_malloc(size);
	if(ptr2==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
	jry_bl_malloc_size_type size_new=jry_bl_malloc_size(ptr2);
	jry_bl_min_update(size_new,size_now);
	jry_bl_memory_copy(ptr2,ptr,size_new);
	jry_bl_free(ptr);
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
	jry_bl_malloc_heap.size-=jry_bl_malloc_size(ptr);
	void * ptr2=jry_bl_malloc(size);
	if(ptr2==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);
	jry_bl_malloc_heap.size+=jry_bl_malloc_size(ptr2),jry_bl_max_update(jry_bl_malloc_heap.peak,jry_bl_malloc_heap.size);
	if(ptr2==NULL)jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
	jry_bl_malloc_size_type size_new=_msize(ptr);
	jry_bl_min_update(size_new,size);
	jry_bl_memory_copy(ptr2,ptr,size_new);
	jry_bl_free(ptr);
	return ptr2;
#endif
#endif
}
void jry_bl_free(void * p)
{
	if(p==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
#if JRY_BL_MALLOC_FAST==1
	jry_bl_malloc_size_type size=jry_bl_malloc_size(p);
	if(size<=3072)//small
	{
		jry_bl_malloc_heap.size-=size;
		return __jry_bl_free_small(p);
	}
	else if(size<=2093056)//large 2*1024*1024-4*1024(2M-4K)
	{
		jry_bl_malloc_heap.size-=size;
		return __jry_bl_free_page(p);
	}
	else//huge
	{
		for(jry_bl_malloc_huge_struct *huge=jry_bl_malloc_heap.huge_list,*pre=NULL;huge!=NULL;pre=huge,huge=huge->next)
			if(p==huge->ptr)
			{
				if(pre==NULL)
					jry_bl_malloc_heap.huge_list=huge->next;
				else
					pre->next=huge->next;
				__jry_bl_malloc_munmap(huge->ptr,size);
				jry_bl_free(huge);
				jry_bl_malloc_heap.size-=size;
				return;
			}
		jry_bl_exception(JRY_BL_ERROR_MEMORY_ERROR);	
	}	
#else	
	jry_bl_malloc_heap.size-=jry_bl_malloc_size(p);
	free(p);
#endif
}
void jry_bl_memory_copy(void *to,const void * from,jry_bl_malloc_size_type len){for(register jry_bl_malloc_size_type i=0;i<len;++i)((char*)to)[i]=((char*)from)[i];}
void jry_bl_memory_copy_reverse(void *to,const void * from,jry_bl_malloc_size_type len,jry_bl_malloc_size_type size){for(register jry_bl_malloc_size_type i=0;i<len;i+=size)for(register jry_bl_malloc_size_type j=0;j<size;++j)((char*)to)[i+j]=((char*)from)[len-i-size+j];}
#endif
