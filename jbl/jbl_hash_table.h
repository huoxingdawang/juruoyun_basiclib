
/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_HASH_TABLE_H
#define __JBL_HASH_TABLE_H
#include "jbl_hash_table_config.h"
#if JBL_HASH_TABLE_ENABLE==1
#if JBL_USE_STDARG==1
#include <stdarg.h>
#endif
#include "jbl_string.h"
#include "jbl_ying.h"
#include "jbl_var.h"
typedef struct __jbl_hash_table_data
{
	jbl_uint64				h;
	jbl_hash_table_size_type	nxt;	
	jbl_string				k;
	jbl_var					v;
}jbl_hash_table_data;
typedef struct __jbl_hash_table
{
	jbl_hash_table_size_type size;
	jbl_hash_table_size_type len;
	jbl_hash_table_size_type nxt;
	jbl_hash_table_data		*data;
}jbl_hash_table;
void					jbl_hash_table_init								(jbl_hash_table *this);
void					jbl_hash_table_free								(jbl_hash_table *this);
void					jbl_hash_table_extend_to							(jbl_hash_table *this,jbl_hash_table_size_type size);
#define					jbl_hash_table_extend(x,y)						jbl_hash_table_extend_to((x),(y)+(x)->nxt)
#define					jbl_hash_table_get_data(x)						(&(x)->v)
void					jbl_hash_table_insert							(jbl_hash_table *this,jbl_string *k,jbl_var *v,jbl_uint8 kcpt,jbl_uint8 vcpt);
void					jbl_hash_table_get								(const jbl_hash_table *this,const jbl_string *k,jbl_var *v,jbl_uint8 vcpt);
void					jbl_hash_table_unset								(jbl_hash_table *this,const jbl_string *k);
char					jbl_hash_table_space_ship						(const jbl_hash_table *this,const jbl_hash_table *that);
#define					jbl_hash_table_if_big(x,y)						(jbl_hash_table_space_ship(x,y)>0)
#define					jbl_hash_table_if_equal(x,y)						(jbl_hash_table_space_ship(x,y)==0)
#define					jbl_hash_table_if_small(x,y) 					(jbl_hash_table_space_ship(x,y)<0)
#define					jbl_hash_table_if_equal_small(x,y)				(jbl_hash_table_space_ship(x,y)<=0)
#define					jbl_hash_table_if_equal_big(x,y) 				(jbl_hash_table_space_ship(x,y)>=0)
void					jbl_hash_table_clear								(jbl_hash_table *this);
void					jbl_hash_table_copy								(jbl_hash_table *this,jbl_hash_table *that,jbl_copy_type copytype);
void					jbl_hash_table_merge								(jbl_hash_table *this,jbl_hash_table *that,jbl_uint8 copytype);
jbl_string_size_type jbl_hash_table_from_json_start					(jbl_hash_table *this,const jbl_string *in,jbl_string_size_type start);
#define					jbl_hash_table_from_json(this,in)				jbl_hash_table_from_json_start(this,in,0)


void					jbl_hash_table_rehash							(jbl_hash_table *this);

#define					jbl_hash_table_get_key(x)						(&((x)->k))
#define					jbl_hash_table_get_var(x)						(&((x)->v))

#define					jbl_hash_table_foreach(this,i)					for(jbl_hash_table_data *i=&(this)->data[0];i!=&(this)->data[(this)->nxt];i++)if(jbl_var_get_type(&i->v)!=JBL_VAR_TYPE_UNUSE)
#define 				jbl_hash_table_insert_str(x,k,v,s1,s2,v2)		jbl_string_equal_chars_light((s1),(k));jbl_string_equal_chars_light((s2),(v));jbl_var_equal_string((v2),(s2),move);jbl_hash_table_insert((x),(s1),(v2),(move),(move));	
#define 				jbl_hash_table_insert_str_int64(x,k,v,s1,v2)		jbl_string_equal_chars_light((s1),(k));jbl_var_equal_int64((v2),(v));jbl_hash_table_insert((x),(s1),(v2),(move),(move));	
#define 				jbl_hash_table_insert_str_uint64(x,k,v,s1,v2)	jbl_string_equal_chars_light((s1),(k));jbl_var_equal_uint64((v2),(v));jbl_hash_table_insert((x),(s1),(v2),(move),(move));	
#define 				jbl_hash_table_insert_str_double(x,k,v,s1,v2)	jbl_string_equal_chars_light((s1),(k));jbl_var_equal_double((v2),(v));jbl_hash_table_insert((x),(s1),(v2),(move),(move));	
#define 				jbl_hash_table_insert_str_true(x,k,s1,v2)		jbl_string_equal_chars_light((s1),(k));jbl_var_equal_true((v2));jbl_hash_table_insert((x),(s1),(v2),(move),(move));	
#define 				jbl_hash_table_insert_str_false(x,k,s1,v2)		jbl_string_equal_chars_light((s1),(k));jbl_var_equal_false((v2));jbl_hash_table_insert((x),(s1),(v2),(move),(move));	
void					jbl_var_equal_hash_table							(jbl_var *this,jbl_hash_table *that,jbl_uint8 copytype);
#define 				jbl_var_get_hash_table(this)						((jbl_hash_table*)(this)->data.p)
#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void					jbl_hash_table_put								(const jbl_hash_table* this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str);
#define					jbl_hash_table_view(x) 							jbl_hash_table_put(x,&jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jbl_stream_push_char(&jbl_stream_stdout,'\n'),jbl_stream_do(&jbl_stream_stdout,1);
#if JBL_STRING_ENABLE==1
void					jbl_hash_table_to_json							(const jbl_hash_table *this,jbl_string *result);
#endif
#endif
#if JBL_USE_STDARG==1
void					jbl_hash_table_inits								(int n,...);
void					jbl_hash_table_frees								(int n,...);
void					jbl_hash_table_clears							(int n,...);
#endif

#endif
#endif