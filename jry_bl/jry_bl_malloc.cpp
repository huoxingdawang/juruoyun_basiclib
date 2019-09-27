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
void* jry_bl_malloc(size_t size)
{
	return malloc(size);
}
size_t jry_bl_realloc(void* ptr)
{
#ifdef linux	
	return malloc_usable_size(ptr);
#else
	return _msize(ptr);
#endif
}
void* jry_bl_realloc(void* ptr,size_t size)
{
#ifdef linux	
	return realloc(ptr,size);
#else
	void * p=jry_bl_malloc(size);
	if(p==NULL)
		return NULL;
	size_t s=_msize(ptr);
	if(s>size)
		s=size;
	memcpy(p,ptr,s);
	jry_bl_free(ptr);
	return p;
#endif
}
void* jry_bl_free(void * p)
{
	free(p);
}