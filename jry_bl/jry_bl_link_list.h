/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_LINK_LIST_H
#define __JRY_BL_LINK_LIST_H
#include "jry_bl_link_list_config.h"
#if JRY_BL_LINK_LIST_ENABLE==1
#include "jry_bl_var.h"
#include "jry_bl_ying.h"

typedef struct __jry_bl_link_list_node
{
	struct __jry_bl_link_list_node *pre,*nxt;
	jry_bl_var v;
}jry_bl_link_list_node;
typedef struct __jry_bl_link_list
{
	struct __jry_bl_link_list_node *head,*tail;
	jry_bl_link_list_size_type length;
	jry_bl_uint8 light_copy:1;
}jry_bl_link_list;
#define					jry_bl_link_list_flag_light_copy(this)			((this)->light_copy)
#define					jry_bl_link_list_get_length(this)				((this)->length)

void					jry_bl_link_list_init							(jry_bl_link_list *this);
void					jry_bl_link_list_node_init						(jry_bl_link_list_node *this);
void					jry_bl_link_list_free							(jry_bl_link_list *this);
void					jry_bl_link_list_node_free						(jry_bl_link_list_node *this);
void					jry_bl_link_list_node_delink					(jry_bl_link_list *this,jry_bl_link_list_node *node);
void					jry_bl_link_list_insert_node					(jry_bl_link_list *this,jry_bl_link_list_node *node,jry_bl_link_list_node *after);
void					jry_bl_link_list_insert_var						(jry_bl_link_list *this,jry_bl_var *var,jry_bl_link_list_node *after);
void					jry_bl_link_list_insert_var_light				(jry_bl_link_list *this,jry_bl_var *var,jry_bl_link_list_node *after);
void					jry_bl_link_list_insert_var_move				(jry_bl_link_list *this,jry_bl_var *var,jry_bl_link_list_node *after);
void					jry_bl_link_list_delete_node					(jry_bl_link_list *this,jry_bl_link_list_node *node);
void					jry_bl_link_list_swap_node						(jry_bl_link_list *this,jry_bl_link_list_node *a,jry_bl_link_list_node *b);
#define 				jry_bl_link_list_delete_head(x)					jry_bl_link_list_delete_node((x),(x)->head)
#define 				jry_bl_link_list_delete_tail(x)					jry_bl_link_list_delete_node((x),(x)->tail)
#define 				jry_bl_link_list_add_node(x,y)					jry_bl_link_list_insert_node((x),(y),(x)->tail)
#define 				jry_bl_link_list_add_var(x,y)					jry_bl_link_list_insert_var((x),(y),(x)->tail)
#define 				jry_bl_link_list_add_var_light(x,y)				jry_bl_link_list_insert_var_light((x),(y),(x)->tail)
#define 				jry_bl_link_list_add_var_move(x,y)				jry_bl_link_list_insert_var_move((x),(y),(x)->tail)
#define 				jry_bl_link_list_data(x)						(&((x)->v))
#define 				jry_bl_link_list_foreach(x,y)					for(jry_bl_link_list_node *(y)=(x)->head;(y)!=NULL;(y)=(y)->nxt)
#define 				jry_bl_link_list_foreach_del(x,y,z)				for(jry_bl_link_list_node *(y)=(x)->head,*(z)=((y)==NULL?NULL:(y)->nxt);(y)!=NULL;(y)=(z),(z)=((y)==NULL?NULL:(y)->nxt))
char					jry_bl_link_list_space_ship						(const jry_bl_link_list *this,const jry_bl_link_list *that);
#define					jry_bl_link_list_if_big(x,y)					(jry_bl_link_list_space_ship(x,y)>0)
#define					jry_bl_link_list_if_equal(x,y)					(jry_bl_link_list_space_ship(x,y)==0)
#define					jry_bl_link_list_if_small(x,y) 					(jry_bl_link_list_space_ship(x,y)<0)
#define					jry_bl_link_list_if_equal_small(x,y)			(jry_bl_link_list_space_ship(x,y)<=0)
#define					jry_bl_link_list_if_equal_big(x,y) 				(jry_bl_link_list_space_ship(x,y)>=0)

void					jry_bl_link_list_copy							(jry_bl_link_list *this,jry_bl_link_list *that,jry_bl_copy_type copytype);	
#define					jry_bl_link_list_equal(a,b)						jry_bl_link_list_copy(a,b,copy)
#define					jry_bl_link_list_equal_light(a,b)				jry_bl_link_list_copy(a,b,light)
#define					jry_bl_link_list_equal_move(a,b)				jry_bl_link_list_copy(a,b,move)
	
#define					jry_bl_link_list_from_json(x,y)					jry_bl_link_list_from_json_start(x,y,0)
jry_bl_string_size_type	jry_bl_link_list_from_json_start				(jry_bl_link_list *this,const jry_bl_string *in,jry_bl_string_size_type start);
void					jry_bl_link_list_merge							(jry_bl_link_list *this,jry_bl_link_list *that);
void					jry_bl_link_list_merge_light					(jry_bl_link_list *this,jry_bl_link_list *that);
void					jry_bl_var_equal_link_list						(jry_bl_var *this,jry_bl_link_list *that,jry_bl_copy_type copytype);
#define 				jry_bl_var_get_link_list(this)					((jry_bl_link_list*)(this)->data.p)

#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_stream.h"
void					jry_bl_link_list_put							(const jry_bl_link_list* this,jry_bl_stream *output_stream,jry_bl_put_type type,jry_bl_uint32 format,char*str);
#define					jry_bl_link_list_view(x) 						jry_bl_link_list_put(x,&jry_bl_stream_stdout,view,(jry_bl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jry_bl_stream_push_char(&jry_bl_stream_stdout,'\n'),jry_bl_stream_do(&jry_bl_stream_stdout,1);
#if JRY_BL_STRING_ENABLE==1
void					jry_bl_link_list_to_json						(const jry_bl_link_list *this,jry_bl_string *result);
#endif
#endif
#if JRY_BL_USE_STDARG==1
void					jry_bl_link_list_inits							(int n,...);
void					jry_bl_link_list_node_inits						(int n,...);
void					jry_bl_link_list_frees							(int n,...);
void					jry_bl_link_list_node_frees						(int n,...);
#endif


#endif
#endif
