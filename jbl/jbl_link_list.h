/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_LINK_LIST_H
#define __JBL_LINK_LIST_H
#include "jbl_link_list_config.h"
#if JBL_LINK_LIST_ENABLE==1
#include "jbl_var.h"
#include "jbl_ying.h"

typedef struct __jbl_link_list_node
{
	struct __jbl_link_list_node *pre,*nxt;
	jbl_var v;
}jbl_link_list_node;
typedef struct __jbl_link_list
{
	struct __jbl_link_list_node *head,*tail;
	jbl_link_list_size_type length;
	jbl_uint8 light_copy:1;
}jbl_link_list;
#define					jbl_link_list_flag_light_copy(this)			((this)->light_copy)
#define					jbl_link_list_get_length(this)				((this)->length)

void					jbl_link_list_init							(jbl_link_list *this);
void					jbl_link_list_node_init						(jbl_link_list_node *this);
void					jbl_link_list_free							(jbl_link_list *this);
void					jbl_link_list_node_free						(jbl_link_list_node *this);
void					jbl_link_list_node_delink					(jbl_link_list *this,jbl_link_list_node *node);
void					jbl_link_list_insert_node					(jbl_link_list *this,jbl_link_list_node *node,jbl_link_list_node *after);
void					jbl_link_list_insert_var						(jbl_link_list *this,jbl_var *var,jbl_link_list_node *after);
void					jbl_link_list_insert_var_light				(jbl_link_list *this,jbl_var *var,jbl_link_list_node *after);
void					jbl_link_list_insert_var_move				(jbl_link_list *this,jbl_var *var,jbl_link_list_node *after);
void					jbl_link_list_delete_node					(jbl_link_list *this,jbl_link_list_node *node);
void					jbl_link_list_swap_node						(jbl_link_list *this,jbl_link_list_node *a,jbl_link_list_node *b);
#define 				jbl_link_list_delete_head(x)					jbl_link_list_delete_node((x),(x)->head)
#define 				jbl_link_list_delete_tail(x)					jbl_link_list_delete_node((x),(x)->tail)
#define 				jbl_link_list_add_node(x,y)					jbl_link_list_insert_node((x),(y),(x)->tail)
#define 				jbl_link_list_add_var(x,y)					jbl_link_list_insert_var((x),(y),(x)->tail)
#define 				jbl_link_list_add_var_light(x,y)				jbl_link_list_insert_var_light((x),(y),(x)->tail)
#define 				jbl_link_list_add_var_move(x,y)				jbl_link_list_insert_var_move((x),(y),(x)->tail)
#define 				jbl_link_list_data(x)						(&((x)->v))
#define 				jbl_link_list_foreach(x,y)					for(jbl_link_list_node *(y)=(x)->head;(y)!=NULL;(y)=(y)->nxt)
#define 				jbl_link_list_foreach_del(x,y,z)				for(jbl_link_list_node *(y)=(x)->head,*(z)=((y)==NULL?NULL:(y)->nxt);(y)!=NULL;(y)=(z),(z)=((y)==NULL?NULL:(y)->nxt))
char					jbl_link_list_space_ship						(const jbl_link_list *this,const jbl_link_list *that);
#define					jbl_link_list_if_big(x,y)					(jbl_link_list_space_ship(x,y)>0)
#define					jbl_link_list_if_equal(x,y)					(jbl_link_list_space_ship(x,y)==0)
#define					jbl_link_list_if_small(x,y) 					(jbl_link_list_space_ship(x,y)<0)
#define					jbl_link_list_if_equal_small(x,y)			(jbl_link_list_space_ship(x,y)<=0)
#define					jbl_link_list_if_equal_big(x,y) 				(jbl_link_list_space_ship(x,y)>=0)

void					jbl_link_list_copy							(jbl_link_list *this,jbl_link_list *that,jbl_copy_type copytype);	
#define					jbl_link_list_equal(a,b)						jbl_link_list_copy(a,b,copy)
#define					jbl_link_list_equal_light(a,b)				jbl_link_list_copy(a,b,light)
#define					jbl_link_list_equal_move(a,b)				jbl_link_list_copy(a,b,move)
	
#define					jbl_link_list_from_json(x,y)					jbl_link_list_from_json_start(x,y,0)
jbl_string_size_type	jbl_link_list_from_json_start				(jbl_link_list *this,const jbl_string *in,jbl_string_size_type start);
void					jbl_link_list_merge							(jbl_link_list *this,jbl_link_list *that);
void					jbl_link_list_merge_light					(jbl_link_list *this,jbl_link_list *that);
void					jbl_var_equal_link_list						(jbl_var *this,jbl_link_list *that,jbl_copy_type copytype);
#define 				jbl_var_get_link_list(this)					((jbl_link_list*)(this)->data.p)

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void					jbl_link_list_put							(const jbl_link_list* this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str);
#define					jbl_link_list_view(x) 						jbl_link_list_put(x,&jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jbl_stream_push_char(&jbl_stream_stdout,'\n'),jbl_stream_do(&jbl_stream_stdout,1);
#if JBL_STRING_ENABLE==1
void					jbl_link_list_to_json						(const jbl_link_list *this,jbl_string *result);
#endif
#endif
#if JBL_USE_STDARG==1
void					jbl_link_list_inits							(int n,...);
void					jbl_link_list_node_inits						(int n,...);
void					jbl_link_list_frees							(int n,...);
void					jbl_link_list_node_frees						(int n,...);
#endif


#endif
#endif
