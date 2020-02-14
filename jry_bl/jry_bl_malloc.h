/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_MALLOC_H
#define __JRY_BL_MALLOC_H
#include "jry_bl_malloc_config.h"
#if JRY_BL_MALLOC_ENABLE==1
#include "jry_bl_ying.h"
void					jry_bl_malloc_start			();
void					jry_bl_malloc_stop			();
void*					jry_bl_malloc				(jry_bl_malloc_size_type size);
void*					jry_bl_realloc				(void* ptr,jry_bl_malloc_size_type size);
void					jry_bl_free					(void* p);
jry_bl_malloc_size_type	jry_bl_malloc_size			(void* ptr);
void					jry_bl_memory_copy			(void *to,const void * from,jry_bl_malloc_size_type len);
void					jry_bl_memory_copy_reverse	(void *to,const void * from,jry_bl_malloc_size_type len,jry_bl_malloc_size_type size);
#if JRY_BL_MALLOC_FAST==1

	typedef struct __jry_bl_malloc_free_slot	jry_bl_malloc_free_slot;
	typedef struct __jry_bl_malloc_heap_struct	jry_bl_malloc_heap_struct;
	typedef struct __jry_bl_malloc_huge_struct	jry_bl_malloc_huge_struct;
	typedef struct __jry_bl_malloc_chunk_struct	jry_bl_malloc_chunk_struct;
	
	typedef struct __jry_bl_malloc_free_slot
	{
		struct __jry_bl_malloc_free_slot	*next;
	}jry_bl_malloc_free_slot;
	typedef struct __jry_bl_malloc_heap_struct
	{
		jry_bl_malloc_size_type size;//实际使用
		jry_bl_malloc_size_type peak;//峰值
		
		jry_bl_malloc_size_type applied_size;//申请
		jry_bl_malloc_size_type applied_peak;//申请峰值
		
		struct __jry_bl_malloc_huge_struct *huge_list;
		
		jry_bl_malloc_chunk_struct	*main_chunk;
		jry_bl_malloc_chunk_struct	*cached_chunk;
		
		jry_bl_malloc_free_slot		slot[30];
		
		jry_bl_uint32	cached_chunk_count;
	}jry_bl_malloc_heap_struct;
	typedef struct __jry_bl_malloc_huge_struct
	{
		void *ptr;
		jry_bl_malloc_size_type size;
		struct __jry_bl_malloc_huge_struct *next;
	}jry_bl_malloc_huge_struct;
	typedef struct __jry_bl_malloc_chunk_struct
	{
		struct __jry_bl_malloc_chunk_struct	*next;
		struct __jry_bl_malloc_chunk_struct	*pre;
		jry_bl_uint16						free_pages;		
		jry_bl_uint32						map[512];		//2KB=512*4
		jry_bl_malloc_fmap_type				fmap[jry_bl_malloc_fmap_len];		//16*32bit
	}jry_bl_malloc_chunk_struct;
	

#else	//不开fast
	typedef struct __jry_bl_malloc_heap_struct
	{
		jry_bl_malloc_size_type size;
		jry_bl_malloc_size_type peak;
	}jry_bl_malloc_heap_struct;	
	extern jry_bl_malloc_heap_struct jry_bl_malloc_heap;
#endif

#else
#define jry_bl_malloc_start()	1
#define jry_bl_malloc_stop()	1
#endif
#endif
