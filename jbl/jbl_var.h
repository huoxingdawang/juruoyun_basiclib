/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_VAR_H
#define __JBL_VAR_H
#include "jbl_var_config.h"
#if JBL_VAR_ENABLE==1
#include "jbl_ying.h"
#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"	
#endif

typedef struct __jbl_var_operators
{
	void*	(*free)(void*);
	void*	(*copy)(void*);
	
#if JBL_STREAM_ENABLE==1
	void	(*put)(const void*,jbl_stream *,jbl_put_type,jbl_uint32,char*);
#endif
}jbl_var_operators;

typedef struct __jbl_var
{
	const jbl_var_operators *ops;
}jbl_var;
#define jbl_var_set_operators(this,op)	((jbl_var*)(((char*)this)-(sizeof(jbl_var))))->ops=(op)
#define jbl_var_get_operators(this)		(((jbl_var*)(((char*)this)-(sizeof(jbl_var))))->ops)

jbl_var * jbl_var_free(jbl_var * this);
jbl_var * jbl_var_copy(jbl_var * this);
#if JBL_STREAM_ENABLE==1
jbl_var * jbl_var_put(jbl_var * this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str);
#define		jbl_var_view(x) 	jbl_var_put(x,jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jbl_stream_push_char(jbl_stream_stdout,'\n'),jbl_stream_do(jbl_stream_stdout,1)
#endif

/*
#define					jbl_var_flag_pointer(this)					((this)->pointer)

#define JBL_VAR_TYPE_UNUSE		0
#define JBL_VAR_TYPE_NULL		1
#define JBL_VAR_TYPE_INT64		2
#define JBL_VAR_TYPE_UINT64		3
#define JBL_VAR_TYPE_DOUBLE		4
#define JBL_VAR_TYPE_TRUE		5
#define JBL_VAR_TYPE_FALSE		6
#define JBL_VAR_TYPE_CHAR		7
#define JBL_VAR_TYPE_POINTER		8
#define JBL_VAR_TYPE_VAR			9	
#if JBL_STRING_ENABLE==1
#define JBL_VAR_TYPE_STRING		10
#endif
#if JBL_LINK_LIST_ENABLE==1
#define JBL_VAR_TYPE_LINK_LIST	11
#endif
#if JBL_HASH_TABLE_ENABLE==1
#define JBL_VAR_TYPE_HASH_TABLE	12
#endif
#if JBL_FILE_ENABLE==1
#define JBL_VAR_TYPE_FILE		13
#endif
typedef struct __jbl_var
{
	union
	{
		jbl_int64 ll;
		jbl_uint64 ull;
		double d;
		char c;
		void* p;
	}data;
	union
	{
		int flags;
		struct
		{
			jbl_var_type_type type;
			jbl_uint8 pointer:1;
		};
	};
}jbl_var;

typedef struct __jbl_var_functions_struct
{
	jbl_uint32 size;
	void (*init)(void*);
	void (*free)(void*);
	void (*copy)(void*,void*,jbl_copy_type);
	char (*space_ship)(const void*,const void*);
#if JBL_STREAM_ENABLE==1	
	void (*put)(const void*,jbl_stream*,jbl_put_type,jbl_uint32,char*);
#endif
}jbl_var_functions_struct;

extern const jbl_var_functions_struct jbl_var_functions[5];
extern jbl_var_functions_struct* jbl_var_fs[jbl_var_fs_size];
extern jbl_var_functions_struct jbl_var_tmp_functions[jbl_var_tmp_size];

#if jbl_var_tmp_size!=0
#define jbl_var_tmp_register(type,size,init,free,copy,space_ship,f,g,h,i)											\
									jbl_var_tmp_functions[((type)&(1<<jbl_var_type_bit))].size=size,				\
									jbl_var_tmp_functions[((type)&(1<<jbl_var_type_bit))].init=init,				\
									jbl_var_tmp_functions[((type)&(1<<jbl_var_type_bit))].free=free,				\
									jbl_var_tmp_functions[((type)&(1<<jbl_var_type_bit))].copy=copy,				\
									jbl_var_tmp_functions[((type)&(1<<jbl_var_type_bit))].space_ship=space_ship,	\
									jbl_var_tmp_functions[((type)&(1<<jbl_var_type_bit))].put=put	
#endif
void					jbl_var_init						(jbl_var *this);
void					jbl_var_free						(jbl_var *this);
void					jbl_var_init_as					(jbl_var *this,jbl_var_type_type type);
void					jbl_var_copy						(jbl_var *this,jbl_var *that,jbl_copy_type copytype);
#define					jbl_var_get_type(a)				((a)->type)
#define					jbl_var_equal(a,b)				jbl_var_copy(a,b,copy)
#define					jbl_var_equal_light(a,b)			jbl_var_copy(a,b,light)
#define					jbl_var_equal_light_copy(a,b)	jbl_var_copy(a,b,move)
char					jbl_var_space_ship				(const jbl_var *this,const jbl_var *that);
#define					jbl_var_if_big(x,y)				(jbl_var_space_ship(x,y)>0)
#define					jbl_var_if_equal(x,y)			(jbl_var_space_ship(x,y)==0)
#define					jbl_var_if_small(x,y) 			(jbl_var_space_ship(x,y)<0)
#define					jbl_var_if_equal_small(x,y)		(jbl_var_space_ship(x,y)<=0)
#define					jbl_var_if_equal_big(x,y) 		(jbl_var_space_ship(x,y)>=0)
#define 				jbl_var_get_int64(this)			((this)->data.ll)
#define 				jbl_var_get_uint64(this)			((this)->data.ull)
#define 				jbl_var_get_double(this)			((this)->data.d)
#define 				jbl_var_get_char(this)			((this)->data.x)
#define 				jbl_var_get_pointer(this)		((this)->data.p)
#define 				jbl_var_equal_int64(this,a)		jbl_var_init_as((this),JBL_VAR_TYPE_INT64)	,((this)->data.ll=(a))
#define 				jbl_var_equal_uint64(this,a)		jbl_var_init_as((this),JBL_VAR_TYPE_UINT64)	,((this)->data.ull=(a))
#define 				jbl_var_equal_double(this,a)		jbl_var_init_as((this),JBL_VAR_TYPE_DOUBLE)	,((this)->data.d=(a))
#define 				jbl_var_equal_char(this,a)		jbl_var_init_as((this),JBL_VAR_TYPE_CHAR)		,((this)->data.x=(a))
#define 				jbl_var_equal_pointer(this,a)	jbl_var_init_as((this),JBL_VAR_TYPE_POINTER)	,((this)->data.p=(a))
#define 				jbl_var_equal_true(this)			jbl_var_init_as((this),JBL_VAR_TYPE_TRUE)
#define 				jbl_var_equal_false(this)		jbl_var_init_as((this),JBL_VAR_TYPE_FALSE)
#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void					jbl_var_put(jbl_var* this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str);
#define					jbl_var_view(x) 					jbl_var_put(x,&jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jbl_stream_push_char(&jbl_stream_stdout,'\n'),jbl_stream_do(&jbl_stream_stdout,1);
#if JBL_STRING_ENABLE==1
void					jbl_var_to_json					(const jbl_var *this,jbl_string *result);
#endif
#endif
#if JBL_STRING_ENABLE==1
jbl_string_size_type	jbl_var_from_json_start			(jbl_var *this,const jbl_string *in,jbl_string_size_type start);
#define					jbl_var_from_json(this,in)		jbl_var_from_json_start(this,in,0)
#endif
#if JBL_USE_STDARG==1
void					jbl_var_inits					(int n,...);
void					jbl_var_frees					(int n,...);
#if JBL_STREAM_ENABLE==1
void					jbl_var_views					(int n,...);
#endif

#endif


*/
#endif
#endif