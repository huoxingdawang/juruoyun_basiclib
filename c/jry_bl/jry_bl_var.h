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
#include "jry_bl_exception.h"
#include "jry_bl_malloc.h"
#include "jry_bl_ying.h"
#if JRY_BL_USE_STDARG==1
#include <stdarg.h>
#endif
#define	jry_bl_var_get_flag_pointer(this) 	((this)->f.f.flags&(1<<0))
#define	jry_bl_var_set_flag_pointer(this,a)	((this)->f.f.flags&=~(1<<0)),((this)->f.f.flags|=((a)<<0))

#define JRY_BL_VAR_TYPE_NULL				0
#define JRY_BL_VAR_TYPE_LONG_LONG			1
#define JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	2
#define JRY_BL_VAR_TYPE_DOUBLE				3
#define JRY_BL_VAR_TYPE_TRUE				4
#define JRY_BL_VAR_TYPE_FALSE				5
#define JRY_BL_VAR_TYPE_CHAR				6
#define JRY_BL_VAR_TYPE_POINTER				7
#define JRY_BL_VAR_TYPE_VAR					8
#if JRY_BL_STRING_ENABLE==1
#define JRY_BL_VAR_TYPE_STRING				9
#include "jry_bl_string.h"
#endif
#if JRY_BL_LINK_LIST_ENABLE==1
#define JRY_BL_VAR_TYPE_LINK_LIST			10
typedef struct __jry_bl_link_list jry_bl_link_list;
#endif


typedef struct __jry_bl_var
{
	union
	{
		jry_bl_int64 ll;
		jry_bl_uint64 ull;
		double d;
		char c;
		void * p;
		struct __jry_bl_var* var;
#if JRY_BL_STRING_ENABLE==1
		jry_bl_string *str;
#endif
#if JRY_BL_STRING_ENABLE==1
		jry_bl_link_list *lst;
#endif
	}data;
	union
	{
		int ff;
		struct
		{
			jry_bl_var_type_type type;
			unsigned char flags;			
		}f;
	}f;
}jry_bl_var;
void					jry_bl_var_init								(jry_bl_var *this);
void					jry_bl_var_free								(jry_bl_var *this);
void					jry_bl_var_init_as							(jry_bl_var *this,jry_bl_var_type_type type);
void					jry_bl_var_equal							(jry_bl_var *this,jry_bl_var *that);
void					jry_bl_var_equal_light						(jry_bl_var *this,jry_bl_var *that);
void					jry_bl_var_equal_light_move					(jry_bl_var *this,jry_bl_var *that);
char					jry_bl_var_space_ship						(jry_bl_var *this,jry_bl_var *that);
#define					jry_bl_var_if_big(x,y)						(jry_bl_var_space_ship(x,y)>0)
#define					jry_bl_var_if_equal(x,y)					(jry_bl_var_space_ship(x,y)==0)
#define					jry_bl_var_if_small(x,y) 					(jry_bl_var_space_ship(x,y)<0)
#define					jry_bl_var_if_equal_small(x,y)				(jry_bl_var_space_ship(x,y)<=0)
#define					jry_bl_var_if_equal_big(x,y) 				(jry_bl_var_space_ship(x,y)>=0)



#define 				jry_bl_var_get_long_long(this)				((this)->data.ll)
#define 				jry_bl_var_get_unsigned_long_long(this)		((this)->data.ull)
#define 				jry_bl_var_get_double(this)					((this)->data.d)
#define 				jry_bl_var_get_char(this)					((this)->data.x)
#define 				jry_bl_var_get_pointer(this)				((this)->data.p)

#define 				jry_bl_var_equal_long_long(this,a)			jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_LONG_LONG)			,((this)->data.ll=(a))
#define 				jry_bl_var_equal_unsigned_long_long(this,a)	jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG)	,((this)->data.ull=(a))
#define 				jry_bl_var_equal_double(this,a)				jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_DOUBLE)				,((this)->data.d=(a))
#define 				jry_bl_var_equal_char(this,a)				jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_CHAR)					,((this)->data.x=(a))
#define 				jry_bl_var_equal_pointer(this,a)			jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_POINTER)				,((this)->data.p=(a))
#define 				jry_bl_var_equal_true(this)					jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_TRUE)
#define 				jry_bl_var_equal_false(this)				jry_bl_var_init_as((this),JRY_BL_VAR_TYPE_FALSE)

#if JRY_BL_STRING_ENABLE==1
void					jry_bl_var_equal_string						(jry_bl_var *this,jry_bl_string *that);
void					jry_bl_var_equal_string_light				(jry_bl_var *this,jry_bl_string *that);
void					jry_bl_var_equal_string_light_move			(jry_bl_var *this,jry_bl_string *that);
void					jry_bl_var_equal_string_pointer				(jry_bl_var *this,jry_bl_string *that);
#define 				jry_bl_var_get_string(this)					((this)->data.str)
void					jry_bl_string_equal_var						(jry_bl_string *this,jry_bl_var *that);
void					jry_bl_string_equal_var_light				(jry_bl_string *this,jry_bl_var *that);
void					jry_bl_string_equal_var_light_move			(jry_bl_string *this,jry_bl_var *that);
#endif

void					jry_bl_var_turn								(jry_bl_var *this,jry_bl_var_type_type type);
#if JRY_BL_STRING_ENABLE==1
void					jry_bl_var_to_json							(jry_bl_var *this,jry_bl_string *result);
jry_bl_string_size_type	jry_bl_var_from_json_start					(jry_bl_var *this,jry_bl_string *in,jry_bl_string_size_type i);
#define					jry_bl_var_from_json(this,in)				jry_bl_var_from_json_start(this,in,0)
#endif


#if JRY_BL_USE_STDIO==1
#define					jry_bl_var_view(x,y) 						jry_bl_var_view_ex(x,y,#x,__LINE__)
void 					jry_bl_var_view_ex							(jry_bl_var *this,FILE * file,char*str,int a);
#endif
#if JRY_BL_USE_STDARG==1
void					jry_bl_var_inits							(int n,...);
void					jry_bl_var_frees							(int n,...);
#if JRY_BL_USE_STDIO==1
void					jry_bl_var_views							(FILE * file,int n,...);
#endif
#endif
#endif
#endif