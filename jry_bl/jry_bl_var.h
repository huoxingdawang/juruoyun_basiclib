/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_VAR_H
#define __JRY_BL_VAR_H
#include "jry_bl_var_config.h"
#if JRY_BL_VAR_ENABLE==1
#include "jry_bl_ying.h"
#include "jry_bl_string.h"
#define					jry_bl_var_flag_pointer(this)					((this)->pointer)

#define JRY_BL_VAR_TYPE_UNUSE		0
#define JRY_BL_VAR_TYPE_NULL		1
#define JRY_BL_VAR_TYPE_INT64		2
#define JRY_BL_VAR_TYPE_UINT64		3
#define JRY_BL_VAR_TYPE_DOUBLE		4
#define JRY_BL_VAR_TYPE_TRUE		5
#define JRY_BL_VAR_TYPE_FALSE		6
#define JRY_BL_VAR_TYPE_CHAR		7
#define JRY_BL_VAR_TYPE_POINTER		8
#define JRY_BL_VAR_TYPE_VAR			9	
#if JRY_BL_STRING_ENABLE==1
#define JRY_BL_VAR_TYPE_STRING		10
#endif
#if JRY_BL_LINK_LIST_ENABLE==1
#define JRY_BL_VAR_TYPE_LINK_LIST	11
#endif
#if JRY_BL_HASH_TABLE_ENABLE==1
#define JRY_BL_VAR_TYPE_HASH_TABLE	12
#endif
#if JRY_BL_FILE_ENABLE==1
#define JRY_BL_VAR_TYPE_FILE		13
#endif
typedef struct __jry_bl_var
{
	union
	{
		jry_bl_int64 ll;
		jry_bl_uint64 ull;
		double d;
		char c;
		void* p;
	}data;
	union
	{
		int flags;
		struct
		{
			jry_bl_var_type_type type;
			jry_bl_uint8 pointer:1;
		};
	};
}jry_bl_var;

typedef struct __jry_bl_var_functions_struct
{
	jry_bl_uint32 size;
	void (*init)(void*);
	void (*free)(void*);
	void (*copy)(void*,void*,jry_bl_copy_type);
	char (*space_ship)(const void*,const void*);
#if JRY_BL_STREAM_ENABLE==1	
	void (*put)(const void*,jry_bl_stream*,jry_bl_put_type,jry_bl_uint32,char*);
#endif
}jry_bl_var_functions_struct;

extern const jry_bl_var_functions_struct jry_bl_var_functions[5];
extern jry_bl_var_functions_struct* jry_bl_var_fs[jry_bl_var_fs_size];
extern jry_bl_var_functions_struct jry_bl_var_tmp_functions[jry_bl_var_tmp_size];

#if jry_bl_var_tmp_size!=0
#define jry_bl_var_tmp_register(type,size,init,free,copy,space_ship,f,g,h,i)											\
									jry_bl_var_tmp_functions[((type)&(1<<jry_bl_var_type_bit))].size=size,				\
									jry_bl_var_tmp_functions[((type)&(1<<jry_bl_var_type_bit))].init=init,				\
									jry_bl_var_tmp_functions[((type)&(1<<jry_bl_var_type_bit))].free=free,				\
									jry_bl_var_tmp_functions[((type)&(1<<jry_bl_var_type_bit))].copy=copy,				\
									jry_bl_var_tmp_functions[((type)&(1<<jry_bl_var_type_bit))].space_ship=space_ship,	\
									jry_bl_var_tmp_functions[((type)&(1<<jry_bl_var_type_bit))].put=put	
#endif
void					jry_bl_var_init						(jry_bl_var *this);
void					jry_bl_var_free						(jry_bl_var *this);
void					jry_bl_var_init_as					(jry_bl_var *this,jry_bl_var_type_type type);
void					jry_bl_var_copy						(jry_bl_var *this,jry_bl_var *that,jry_bl_copy_type copytype);
#define					jry_bl_var_get_type(a)				((a)->type)
#define					jry_bl_var_equal(a,b)				jry_bl_var_copy(a,b,copy)
#define					jry_bl_var_equal_light(a,b)			jry_bl_var_copy(a,b,light)
#define					jry_bl_var_equal_light_copy(a,b)	jry_bl_var_copy(a,b,move)
char					jry_bl_var_space_ship				(const jry_bl_var *this,const jry_bl_var *that);
#define					jry_bl_var_if_big(x,y)				(jry_bl_var_space_ship(x,y)>0)
#define					jry_bl_var_if_equal(x,y)			(jry_bl_var_space_ship(x,y)==0)
#define					jry_bl_var_if_small(x,y) 			(jry_bl_var_space_ship(x,y)<0)
#define					jry_bl_var_if_equal_small(x,y)		(jry_bl_var_space_ship(x,y)<=0)
#define					jry_bl_var_if_equal_big(x,y) 		(jry_bl_var_space_ship(x,y)>=0)
#define 				jry_bl_var_get_int64(this)			((this)->data.ll)
#define 				jry_bl_var_get_uint64(this)			((this)->data.ull)
#define 				jry_bl_var_get_double(this)			((this)->data.d)
#define 				jry_bl_var_get_char(this)			((this)->data.x)
#define 				jry_bl_var_get_pointer(this)		((this)->data.p)
#define 				jry_bl_var_equal_int64(this,a)		jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_INT64)	,((this)->data.ll=(a))
#define 				jry_bl_var_equal_uint64(this,a)		jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_UINT64)	,((this)->data.ull=(a))
#define 				jry_bl_var_equal_double(this,a)		jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_DOUBLE)	,((this)->data.d=(a))
#define 				jry_bl_var_equal_char(this,a)		jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_CHAR)		,((this)->data.x=(a))
#define 				jry_bl_var_equal_pointer(this,a)	jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_POINTER)	,((this)->data.p=(a))
#define 				jry_bl_var_equal_true(this)			jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_TRUE)
#define 				jry_bl_var_equal_false(this)		jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_FALSE)
#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_stream.h"
void					jry_bl_var_put(jry_bl_var* this,jry_bl_stream *output_stream,jry_bl_put_type type,jry_bl_uint32 format,char*str);
#define					jry_bl_var_view(x) 					jry_bl_var_put(x,&jry_bl_stream_stdout,view,(jry_bl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jry_bl_stream_push_char(&jry_bl_stream_stdout,'\n'),jry_bl_stream_do(&jry_bl_stream_stdout,1);
#if JRY_BL_STRING_ENABLE==1
void					jry_bl_var_to_json					(const jry_bl_var *this,jry_bl_string *result);
#endif
#endif
#if JRY_BL_STRING_ENABLE==1
jry_bl_string_size_type	jry_bl_var_from_json_start			(jry_bl_var *this,const jry_bl_string *in,jry_bl_string_size_type start);
#define					jry_bl_var_from_json(this,in)		jry_bl_var_from_json_start(this,in,0)
#endif
#if JRY_BL_USE_STDARG==1
void					jry_bl_var_inits					(int n,...);
void					jry_bl_var_frees					(int n,...);
#if JRY_BL_STREAM_ENABLE==1
void					jry_bl_var_views					(int n,...);
#endif

#endif
#endif
#endif