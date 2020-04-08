/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_gc.h"
#if JRY_BL_GC_ENABLE==1
void * jry_bl_refer(void *ptr)
{
	if(ptr==NULL||*((jry_bl_reference**)(ptr))==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(jry_bl_gc_is_ref(*((jry_bl_reference**)(ptr))))
	{
		jry_bl_gc_plus(*((jry_bl_reference**)(ptr)));		
		return *((jry_bl_reference**)(ptr));
	}
	jry_bl_reference *this=jry_bl_malloc((sizeof(jry_bl_reference)));
	jry_bl_gc_init(this);
	jry_bl_gc_plus(this);//增加引用计数
	jry_bl_gc_plus(this);//增加引用计数
	jry_bl_gc_set_ref(this);
	this->ptr=*((jry_bl_reference**)(ptr));
	(*((jry_bl_reference**)(ptr)))=this;
	return this;
}
void * jry_bl_derefer(void *ptr)
{
	if(ptr==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(!jry_bl_gc_is_ref((jry_bl_reference*)ptr))
		return ptr;
	void *data=((jry_bl_reference*)ptr)->ptr;
	jry_bl_gc_minus((jry_bl_reference*)ptr);//减掉ref_cnt
	jry_bl_gc_plus((jry_bl_reference*)data);//原始数据加一个ref_cnt，相当于从ref上转移一个ref_cnt到原始数据上
	if(!jry_bl_gc_reference_cnt((jry_bl_reference*)ptr))
		jry_bl_free(ptr);
	return data;
}
#endif
