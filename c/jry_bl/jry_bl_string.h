/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_STRING_H
#define __JRY_BL_STRING_H
#include "jry_bl_string_config.h"
#if JRY_BL_STRING_ENABLE==1

#include "jry_bl_ying.h"
#include "jry_bl_exception.h"
#include "jry_bl_malloc.h"
#include <math.h>
#if JRY_BL_STRING_USE_STDIO==1
#include <stdio.h>
#endif
#if JRY_BL_STRING_USE_STDARG==1
#include <stdarg.h>
#endif

typedef struct
{
	jry_bl_string_size_type	len;
	jry_bl_string_size_type	size;
	unsigned char *					s;
	char 					light_copy;
}jry_bl_string;
void					jry_bl_string_init							(jry_bl_string *this);
void					jry_bl_string_free							(jry_bl_string *this);
unsigned char			jry_bl_string_get							(jry_bl_string *this,jry_bl_string_size_type i);
unsigned char			jry_bl_string_set							(jry_bl_string *this,jry_bl_string_size_type i,unsigned char a);
void					jry_bl_string_clear							(jry_bl_string *this);
void					jry_bl_string_parse							(jry_bl_string *this);
void					jry_bl_string_extend						(jry_bl_string *this,jry_bl_string_size_type size);
void					jry_bl_string_add_string					(jry_bl_string *this,jry_bl_string *in);
void					jry_bl_string_add_char_pointer				(jry_bl_string *this,unsigned char *in);
void					jry_bl_string_add_char_pointer_length		(jry_bl_string *this,unsigned char *in,jry_bl_string_size_type len);
void					jry_bl_string_add_char						(jry_bl_string *this,unsigned char in);
void					jry_bl_string_add_long_long					(jry_bl_string *this,long long in);
void					jry_bl_string_add_unsigned_long_long		(jry_bl_string *this,unsigned long long in);
void					jry_bl_string_add_long_double				(jry_bl_string *this,long double in);
void					jry_bl_string_add_long_double_len			(jry_bl_string *this,long double in,unsigned char len);
void					jry_bl_string_equal_string					(jry_bl_string *this,jry_bl_string *in);
void					jry_bl_string_equal_string_light			(jry_bl_string *this,jry_bl_string *in);
void					jry_bl_string_equal_string_light_move		(jry_bl_string *this,jry_bl_string *in);
void					jry_bl_string_equal_char_pointer			(jry_bl_string *this,unsigned char *in);
void					jry_bl_string_equal_char_pointer_length		(jry_bl_string *this,unsigned char *in,jry_bl_string_size_type len);
void					jry_bl_string_equal_char					(jry_bl_string *this,unsigned char in);
void					jry_bl_string_equal_long_long				(jry_bl_string *this,long long in);
void					jry_bl_string_equal_unsigned_long_long		(jry_bl_string *this,unsigned long long in);
void					jry_bl_string_equal_long_double				(jry_bl_string *this,long double in);
void					jry_bl_string_equal_long_double_length		(jry_bl_string *this,long double in,unsigned char l);
char					jry_bl_string_space_ship					(jry_bl_string *this,jry_bl_string *that);
long long				jry_bl_string_get_long_long					(jry_bl_string *this);
unsigned long long		jry_bl_string_get_unsigned_long_long		(jry_bl_string *this);
long double				jry_bl_string_get_long_double				(jry_bl_string *this);
long long				jry_bl_string_get_long_long_start			(jry_bl_string *this,jry_bl_string_size_type start);
unsigned long long		jry_bl_string_get_unsigned_long_long_start	(jry_bl_string *this,jry_bl_string_size_type start);
long double				jry_bl_string_get_long_double_start			(jry_bl_string *this,jry_bl_string_size_type start);

void					jry_bl_string_to_json						(jry_bl_string *this,jry_bl_string *result);
void					jry_bl_string_from_json						(jry_bl_string *this,jry_bl_string *in);
void					jry_bl_string_from_json_start				(jry_bl_string *this,jry_bl_string *in,jry_bl_string_size_type start);





#define jry_bl_string_if_light_copy(this)					((this)->light_copy)
#define jry_bl_string_get_char_pointer(this)				((this)->s)
#define jry_bl_string_get_length(this) 						((this)->len)
#define jry_bl_string_get_size(this) 						((this)->size)
#define	jry_bl_string_add_char1(this,in)					(this)->s[(this)->len]=(in),++(this)->len
#define	jry_bl_string_get1(this,i)							(((i)<0||(i)>=(this)->len)?0:(this)->s[(i)])

#if JRY_BL_STRING_USE_STDIO==1
void 					jry_bl_string_print							(jry_bl_string *this,FILE * file);
void 					jry_bl_string_view_ex						(jry_bl_string *this,FILE * file,char*str,int a);
void					jry_bl_string_add_file						(jry_bl_string *this,FILE * file);
void					jry_bl_string_add_file_end_by				(jry_bl_string *this,FILE * file,unsigned char end);
void					jry_bl_string_equal_file					(jry_bl_string *this,FILE * file);
void					jry_bl_string_equal_file_end_by				(jry_bl_string *this,FILE * file,unsigned char end);
#endif
#if JRY_BL_STRING_USE_STDARG==1
void					jry_bl_string_inits							(int n,...);
void					jry_bl_string_frees							(int n,...);
void					jry_bl_string_clears						(int n,...);
#if JRY_BL_STRING_USE_STDIO==1
void					jry_bl_string_views							(FILE * file,int n,...);
#endif
#endif
#define					jry_bl_string_view(x,y) 					jry_bl_string_view_ex(x,y,#x,__LINE__)
#define					jry_bl_string_if_big(x,y)					(jry_bl_string_space_ship(x,y)>0)
#define					jry_bl_string_if_equal(x,y)					(jry_bl_string_space_ship(x,y)==0)
#define					jry_bl_string_if_small(x,y) 				(jry_bl_string_space_ship(x,y)<0)
#define					jry_bl_string_if_equal_small(x,y)			(jry_bl_string_space_ship(x,y)<=0)
#define					jry_bl_string_if_equal_big(x,y) 			(jry_bl_string_space_ship(x,y)>=0)
#endif
#endif
