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
#if JRY_BL_USE_STDARG==1
#include <stdarg.h>
#include <stdio.h> ///////////////////////////////////////
#endif
#include "jry_bl_gc.h"
#include "jry_bl_ying.h"

typedef struct __jry_bl_string
{
	jry_bl_gc gc;
	jry_bl_string_size_type	len;
	jry_bl_string_size_type	size;
	unsigned char *s;
	jry_bl_uint32 h;
}jry_bl_string;
jry_bl_string_size_type	jry_bl_strlen										(char *a);
jry_bl_string *			jry_bl_string_new									();
jry_bl_string *			jry_bl_string_free									(jry_bl_string *this);
#define					jry_bl_string_extend(a,b)							jry_bl_string_extend_to((a),(jry_bl_string_get_length((a))+(b)))
jry_bl_string *			jry_bl_string_extend_to								(jry_bl_string *this,jry_bl_string_size_type size);
jry_bl_string *			jry_bl_string_clear									(jry_bl_string *this);
jry_bl_string *			jry_bl_string_copy									(jry_bl_string *that);
jry_bl_string *			jry_bl_string_equal									(jry_bl_string *this,jry_bl_string *that);

jry_bl_uint32			jry_bl_string_hash									(jry_bl_string *this);
#define					jry_bl_string_get_length(a)							(a==NULL?0:(a)->len)
#define					jry_bl_string_set_length(a,l)						((a)->len=l)
#define					jry_bl_string_get_chars(this)						((this)->s)
#define					jry_bl_string_get_size(this) 						((this)->size)
#define					jry_bl_string_get_force(this,i)						((this)->s[(i)])
#define					jry_bl_string_get(this,i)							(((i)<0||(i)>=(this)->len)?0:jry_bl_string_get_force(this,i))

#define					jry_bl_string_get_int64(this)						jry_bl_string_get_int64_start_v(this,0)
jry_bl_int64			jry_bl_string_get_int64_start						(const jry_bl_string *this,jry_bl_string_size_type *start);
jry_bl_int64			jry_bl_string_get_int64_start_v						(const jry_bl_string *this,jry_bl_string_size_type start);
#define					jry_bl_string_get_uint64(this)						jry_bl_string_get_uint64_start_v(this,0)
jry_bl_uint64			jry_bl_string_get_uint64_start						(const jry_bl_string *this,jry_bl_string_size_type *start);
jry_bl_uint64			jry_bl_string_get_uint64_start_v					(const jry_bl_string *this,jry_bl_string_size_type start);
#define					jry_bl_string_get_double(this)						jry_bl_string_get_double_start_v(this,0)
double					jry_bl_string_get_double_start						(const jry_bl_string *this,jry_bl_string_size_type *start);
double					jry_bl_string_get_double_start_v					(const jry_bl_string *this,jry_bl_string_size_type start);
#define					jry_bl_string_get_hex(this)							jry_bl_string_get_hex_start_v(this,0)
jry_bl_uint64			jry_bl_string_get_hex_start							(const jry_bl_string *this,jry_bl_string_size_type *start);
jry_bl_uint64			jry_bl_string_get_hex_start_v						(const jry_bl_string *this,jry_bl_string_size_type start);


#define					jry_bl_string_set_force(this,i,c)					(((this)->s[(i)]=c))
#define					jry_bl_string_set(this,i,c)							((i<0?0:(this=jry_bl_string_extend_to(this,i),jry_bl_string_set_force(this,i,c))),this)
#define					jry_bl_string_set_tail0(this)						(this=jry_bl_string_extend_to(this,jry_bl_string_get_length(this)+1),jry_bl_string_set_force(this,jry_bl_string_get_length(this),0),this)
#define					jry_bl_string_add_chars(x,y)						jry_bl_string_add_chars_length(x,y,jry_bl_strlen(y))
jry_bl_string *			jry_bl_string_add_chars_length						(jry_bl_string *this,unsigned char *in,jry_bl_string_size_type len);
jry_bl_string *			jry_bl_string_add_string							(jry_bl_string *this,jry_bl_string *in);
#define					jry_bl_string_add_char(this,in)						(this=jry_bl_string_extend(this,1),this->s[this->len++]=in,this)
#define					jry_bl_string_add_char_force(this,in)				(this->s[this->len++]=(in))
#define					jry_bl_string_add_int64(this,in)					jry_bl_string_add_int64_length(this,in,0,0)
jry_bl_string *			jry_bl_string_add_int64_length						(jry_bl_string *this,jry_bl_int64 in,jry_bl_uint8 len,char c);
#define					jry_bl_string_add_uint64(this,in)					jry_bl_string_add_uint64_length(this,in,0,0)
jry_bl_string *			jry_bl_string_add_uint64_length						(jry_bl_string *this,jry_bl_uint64 in,jry_bl_uint8 len,char c);
#define					jry_bl_string_add_double(this,in)					jry_bl_string_add_double_length(this,in,10)
jry_bl_string *			jry_bl_string_add_double_length						(jry_bl_string *this,double in,unsigned char len);
jry_bl_string *			jry_bl_string_add_unicode_as_utf8					(jry_bl_string *this,unsigned long unicode);
jry_bl_string *			jry_bl_string_add_hex								(jry_bl_string *this,jry_bl_uint64 in);
jry_bl_string *			jry_bl_string_add_hex_8bits							(jry_bl_string *this,jry_bl_uint8 in);
#define					jry_bl_string_delete_1_force(this)					(((this->len)>0?(--(this)->len):(0)))
#define					jry_bl_string_delete_1(this)						(this=jry_bl_string_extend_to(this,0),jry_bl_string_delete_1_force(this),this)

char					jry_bl_string_space_ship							(const jry_bl_string *this,const jry_bl_string *that);
#define					jry_bl_string_if_big(x,y)							(jry_bl_string_space_ship(x,y)>0)
#define					jry_bl_string_if_equal(x,y)							(jry_bl_string_space_ship(x,y)==0)
#define					jry_bl_string_if_small(x,y) 						(jry_bl_string_space_ship(x,y)<0)
#define					jry_bl_string_if_equal_small(x,y)					(jry_bl_string_space_ship(x,y)<=0)
#define					jry_bl_string_if_equal_big(x,y) 					(jry_bl_string_space_ship(x,y)>=0)

#define					jry_bl_string_find_char(this,in)					jry_bl_string_find_char_start(this,in,0)
jry_bl_string_size_type	jry_bl_string_find_char_start						(const jry_bl_string *this,unsigned char in,jry_bl_string_size_type start);




// #define					jry_bl_string_from_json(this,in)					jry_bl_string_from_json_start(this,in,0)
// jry_bl_string_size_type	jry_bl_string_from_json_start						(jry_bl_string *this,const jry_bl_string *in,jry_bl_string_size_type start);
// void 					jry_bl_string_print									(const jry_bl_string *this,FILE * file);

// void					jry_bl_string_add_file								(jry_bl_string *this,FILE * file);
// void					jry_bl_string_add_file_end_by						(jry_bl_string *this,FILE * file,unsigned char end);
// #define					jry_bl_string_equal_file(this,file)					jry_bl_string_clear(this),jry_bl_string_add_file(this,file)
// #define					jry_bl_string_equal_file_end_by(this,file,end)		jry_bl_string_clear(this),jry_bl_string_add_file_end_by(this,file,end)

// #if JRY_BL_VAR_ENABLE==1
// typedef struct __jry_bl_var jry_bl_var;
// #define 				jry_bl_var_get_string(this)							((jry_bl_string*)(this)->data.p)
// void					jry_bl_var_equal_string								(jry_bl_var *this,jry_bl_string *that,jry_bl_uint8 copytype);
// void					jry_bl_var_equal_string_pointer						(jry_bl_var *this,jry_bl_string *that);
// void					jry_bl_string_add_var								(jry_bl_string *this,jry_bl_var *that);
// void					jry_bl_string_equal_var								(jry_bl_string *this,jry_bl_var *that,jry_bl_uint8 cpt);
// #endif
#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_stream.h"
void					jry_bl_string_put									(const jry_bl_string* this,jry_bl_stream *output_stream,jry_bl_put_type type,jry_bl_uint32 format,char*str);//format bit0 表示是否格式化 [1,16]位表示另一个整数 [17,31]位表示格式化tab个数
#define					jry_bl_string_view(x) 								jry_bl_string_put(x,jry_bl_stream_stdout,view,(jry_bl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jry_bl_stream_push_char(jry_bl_stream_stdout,'\n'),jry_bl_stream_do(jry_bl_stream_stdout,1)
void					jry_bl_string_to_json								(const jry_bl_string *this,jry_bl_string *result);

void					jry_bl_string_stream_operater						(jry_bl_stream* this,jry_bl_uint8 flags);
jry_bl_stream *			jry_bl_string_stream_new							(jry_bl_string *str);
#define					jry_bl_string_stream_reset(a)						jry_bl_stream_reset(a),(a)->buf=((jry_bl_string *)(a)->data)->s+((jry_bl_string *)(a)->data)->len,(a)->size=((jry_bl_string *)(a)->data)->size-((jry_bl_string *)(a)->data)->len
#define					jry_bl_string_stream_free(a)						jry_bl_stream_free(a)
#endif
// #if JRY_BL_LINK_LIST_ENABLE==1
// typedef struct __jry_bl_link_list jry_bl_link_list;
// jry_bl_string_size_type	jry_bl_string_cut_start								(jry_bl_string *this,jry_bl_link_list *list,char cut,jry_bl_string_size_type start);
// #define					jry_bl_string_cut(x,y,z)							jry_bl_string_cut_start(x,y,z,0)
// #endif

#endif	
#endif
