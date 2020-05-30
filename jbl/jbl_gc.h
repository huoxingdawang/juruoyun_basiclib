/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_GC_H
#define __JBL_GC_H
#include "jbl_gc_config.h"
#if JBL_GC_ENABLE==1
#include "jbl_ying.h"
typedef jbl_uint32 jbl_gc;
typedef struct
{
	jbl_gc gc;
	void * ptr;
}jbl_reference;
#if JBL_VAR_ENABLE==1
typedef struct __jbl_var_operators jbl_var_operators;
#define jbl_refer(x)		jbl_refer_as_var(x,NULL) 
void *	jbl_refer_as_var	(void *ptr,const jbl_var_operators *ops);			//引用一个变量，********************特别的该函数必须传入一个二级指针********************
#else
void *	jbl_refer			(void *ptr);										//引用一个变量，********************特别的该函数必须传入一个二级指针********************
#endif
void *	jbl_derefer			(void *ptr);										//取消引用一个变量
#define jbl_refer_pull(x)			(x?((jbl_gc_is_ref((const jbl_reference*)x))?(((const jbl_reference*)x)->ptr):x):NULL)	//脱离引用

#define	jbl_gc_init(x)				((x)->gc=0)			//初始化gc字段
#define	jbl_gc_plus(x)				((x)->gc+=4)		//引用计数加一
#define	jbl_gc_minus(x)				((x)->gc-=4)		//引用计数减一
#define	jbl_gc_reference_cnt(x)		(((x)->gc)>>2)		//获取引用计数

#define	jbl_gc_set_ref(x)			((x)->gc|=0X01)		//设置引用标记
#define	jbl_gc_reset_ref(x)			((x)->gc&=(-2))		//删除引用标记
#define	jbl_gc_is_ref(x)			(((x)->gc)&0X01)	//获取引用标记

#define	jbl_gc_set_var(x)			((x)->gc|=0X02)		//设置var标记
#define	jbl_gc_reset_var(x)			((x)->gc&=(-3))		//删除var标记
#define	jbl_gc_is_var(x)			(((x)->gc)&0X02)	//获取var标记


#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
#define jbl_gc_view(x)	jbl_stream_push_chars(jbl_stream_stdout,#x " @ "__FILE__" "),\
							jbl_stream_push_uint64(jbl_stream_stdout,__LINE__),\
							jbl_stream_push_chars(jbl_stream_stdout,"\tref_cnt:"),\
							jbl_stream_push_uint64(jbl_stream_stdout,jbl_gc_reference_cnt(x)),\
							jbl_stream_push_char(jbl_stream_stdout,'\n'),jbl_stream_do(jbl_stream_stdout,1)
#endif




#endif
#endif
