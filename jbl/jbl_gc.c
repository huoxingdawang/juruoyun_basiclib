/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_gc.h"
#if JBL_GC_ENABLE==1
#if JBL_VAR_ENABLE==1
#include "jbl_var.h"
#endif
#if JBL_VAR_ENABLE==1
void * jbl_refer_as_var(void *ptr,const jbl_var_operators *ops)
#else
void * jbl_refer(void *ptr)
#endif
{
	if(ptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_reference *pptr=*((jbl_reference**)(ptr));
	if(pptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(jbl_gc_is_ref(pptr))
	{
		jbl_gc_plus(pptr);		
		return pptr;
	}
	jbl_reference *this;
#if JBL_VAR_ENABLE==1
	if(jbl_gc_is_var(pptr)||ops)
		this=(jbl_reference*)((char*)(jbl_malloc((sizeof(jbl_reference))+(sizeof(jbl_var)))+(sizeof(jbl_var))));	
	else
#endif	
		this=jbl_malloc((sizeof(jbl_reference)));
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数
	jbl_gc_plus(this);//增加引用计数
	jbl_gc_set_ref(this);
#if JBL_VAR_ENABLE==1
	if(jbl_gc_is_var(pptr))
	{
		jbl_var_set_operators(this,jbl_var_get_operators(pptr));
		jbl_gc_set_var(this);		
	}
	else if(ops)
	{
		jbl_var_set_operators(this,ops);
		jbl_gc_set_var(this);		
	}
#endif	
	this->ptr=pptr;
	(*((jbl_reference**)(ptr)))=this;
	return this;
}
void * jbl_derefer(void *ptr)
{
	if(ptr==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(!jbl_gc_is_ref((jbl_reference*)ptr))
		return ptr;
	void *data=((jbl_reference*)ptr)->ptr;
	jbl_gc_minus((jbl_reference*)ptr);//减掉ref_cnt
	jbl_gc_plus((jbl_reference*)data);//原始数据加一个ref_cnt，相当于从ref上转移一个ref_cnt到原始数据上
	if(!jbl_gc_reference_cnt((jbl_reference*)ptr))
	{
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var((jbl_reference*)ptr))		
			jbl_free(((char*)ptr)-(sizeof(jbl_var)));
		else
#endif
			jbl_free(ptr);
	}
	return data;
}
#endif
