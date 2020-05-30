/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_MALLOC_H
#define __JBL_MALLOC_H
#include "jbl_malloc_config.h"
#if JBL_MALLOC_ENABLE==1
#include "jbl_ying.h"
#include "jbl_bitset.h"
void					jbl_malloc_start		();										//启动内存管理
void					jbl_malloc_stop			();										//关闭内存管理
void*					jbl_malloc				(jbl_malloc_size_type size);			//申请一段内存
void*					jbl_realloc				(void* ptr,jbl_malloc_size_type size);	//重新申请一段内存
void					jbl_free				(void* p);								//释放一段内存
jbl_malloc_size_type	jbl_malloc_size			(void* ptr);							//获取一段内存的大小
void					jbl_memory_copy			(void *to,const void * from,jbl_malloc_size_type len);								//复制
void					jbl_memory_copy_reverse	(void *to,const void * from,jbl_malloc_size_type len,jbl_malloc_size_type size);	//倒序复制
#if JBL_MALLOC_FAST==1
	#if  jbl_bitset_bits==32
		#define jbl_malloc_fmap_len		16	//(512/jbl_bitset_bits)
	#else
		#define jbl_malloc_fmap_len		8	//(512/jbl_bitset_bits)
	#endif
	typedef struct __jbl_malloc_free_slot		jbl_malloc_free_slot;
	typedef struct __jbl_malloc_heap_struct		jbl_malloc_heap_struct;
	typedef struct __jbl_malloc_huge_struct		jbl_malloc_huge_struct;
	typedef struct __jbl_malloc_chunk_struct	jbl_malloc_chunk_struct;
	
	typedef struct __jbl_malloc_free_slot
	{
		struct __jbl_malloc_free_slot	*next;
	}jbl_malloc_free_slot;
	typedef struct __jbl_malloc_heap_struct
	{
		jbl_malloc_size_type size;//实际使用
		jbl_malloc_size_type peak;//峰值
		
		jbl_malloc_size_type applied_size;//申请
		jbl_malloc_size_type applied_peak;//申请峰值
		
		struct __jbl_malloc_huge_struct *huge_list;
		
		jbl_malloc_chunk_struct	*main_chunk;
		jbl_malloc_chunk_struct	*cached_chunk;
		
		jbl_malloc_free_slot		slot[30];
		
		jbl_uint32	cached_chunk_count;
	}jbl_malloc_heap_struct;
	typedef struct __jbl_malloc_huge_struct
	{
		void *ptr;
		jbl_malloc_size_type size;
		struct __jbl_malloc_huge_struct *next;
	}jbl_malloc_huge_struct;
	typedef struct __jbl_malloc_chunk_struct
	{
		struct __jbl_malloc_chunk_struct	*next;
		struct __jbl_malloc_chunk_struct	*pre;
		jbl_uint16						free_pages;		
		jbl_uint32						map[512];		//2KB=512*4
		jbl_bitset_type					fmap[jbl_malloc_fmap_len];		//16*32bit
	}jbl_malloc_chunk_struct;
	

#else	//不开fast
	typedef struct __jbl_malloc_heap_struct
	{
		jbl_malloc_size_type size;
		jbl_malloc_size_type peak;
	}jbl_malloc_heap_struct;	
	extern jbl_malloc_heap_struct jbl_malloc_heap;

#endif
#else
#define jbl_malloc_start()	1
#define jbl_malloc_stop()	1
#endif
#endif
