/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_GC_H
#define __JRY_BL_GC_H
#include "jry_bl_gc_config.h"
#if JRY_BL_GC_ENABLE==1
#include "jry_bl_ying.h"
typedef jry_bl_uint32 jry_bl_gc;
typedef struct
{
	jry_bl_gc gc;
	void * ptr;
}jry_bl_reference;
void 	*jry_bl_refer(void *ptr);						//引用一个变量，********************特别的该函数必须传入一个二级指针********************
void 	*jry_bl_derefer(void *ptr);						//取消引用一个变量
#define jry_bl_refer_pull(x)			((jry_bl_gc_is_ref(x))?(((const jry_bl_reference*)x)->ptr):x)//脱离引用

#define	jry_bl_gc_init(x)				((x)->gc=0)		//初始化gc字段
#define	jry_bl_gc_plus(x)				((x)->gc+=2)	//引用计数加一
#define	jry_bl_gc_minus(x)				((x)->gc-=2)	//引用计数减一
#define	jry_bl_gc_reference_cnt(x)		(((x)->gc)>>1)	//获取引用计数

#define	jry_bl_gc_set_ref(x)			((x)->gc|=0X01)	//设置引用标记
#define	jry_bl_gc_reset_ref(x)			((x)->gc&=(-2))	//删除引用标记
#define	jry_bl_gc_is_ref(x)				(((x)->gc)&0X01)//获取引用标记


#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_stream.h"
#define jry_bl_gc_view(x)	jry_bl_stream_push_chars(jry_bl_stream_stdout,#x " @ "__FILE__" "),\
							jry_bl_stream_push_uint64(jry_bl_stream_stdout,__LINE__),\
							jry_bl_stream_push_chars(jry_bl_stream_stdout,"\tref_cnt:"),\
							jry_bl_stream_push_uint64(jry_bl_stream_stdout,jry_bl_gc_reference_cnt(x)),\
							jry_bl_stream_push_char(jry_bl_stream_stdout,'\n'),jry_bl_stream_do(jry_bl_stream_stdout,1)
#endif




#endif
#endif
