/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_LL_H
#define __JBL_LL_H
#include "jbl_ll_config.h"
#if JBL_LL_ENABLE==1
#include "jbl_var.h"
#include "jbl_ying.h"
typedef struct __jbl_ll_node
{
	struct __jbl_ll_node *pre,*nxt;
	jbl_var *v;
}jbl_ll_node;
typedef struct __jbl_ll
{
	jbl_gc gc;
	struct __jbl_ll_node *head,*tail;
	jbl_ll_size_type len;
}jbl_ll;
extern	const	jbl_var_operators			jbl_ll_operators;									//link list 操作器
#define			$jbl_ll(x)					((jbl_ll*)x)										//以link list德格式使用var
jbl_ll  *		jbl_ll_new					();													//新建一个link list
jbl_var *		jbl_Vll_new					();													//以var形式新建一个link list
jbl_ll  *		jbl_ll_init					(jbl_ll *this);										//初始化一个link list
jbl_ll  *		jbl_ll_free					(jbl_ll *this);										//释放一个link list
jbl_ll *jbl_ll_extend(jbl_ll *this,jbl_ll_node **a,jbl_ll_node **b);
#define 		jbl_ll_foreach(x,y)			for(jbl_ll_node *(y)=((jbl_ll *)jbl_refer_pull(x))->head;(y);(y)=(y)->nxt)
#define 		jbl_ll_foreach_del(x,y,z)	for(jbl_ll_node *(y)=((jbl_ll *)jbl_refer_pull(x))->head,*(z)=((y)==NULL?NULL:(y)->nxt);(y)!=NULL;(y)=(z),(z)=((y)==NULL?NULL:(y)->nxt))
#define 		jbl_llv(x)					((x)->v)
jbl_ll  *		jbl_ll_insert				(jbl_ll *this,jbl_var *var,jbl_ll_node *after);
#define			jbl_ll_add(x,y)				jbl_ll_insert(x,y,x?((jbl_ll *)jbl_refer_pull(x))->tail:NULL)

jbl_ll  *		jbl_ll_delete				(jbl_ll *this,jbl_ll_node *node);
#define			jbl_ll_delete_head(x)		jbl_ll_delete(x,((jbl_ll *)jbl_refer_pull(x))->head)
#define			jbl_ll_delete_tail(x)		jbl_ll_delete(x,((jbl_ll *)jbl_refer_pull(x))->tail)

#define			jbl_ll_get_length(x)		(((jbl_ll *)jbl_refer_pull(x))->len)
jbl_ll  * 		jbl_ll_swap_node			(jbl_ll *this,jbl_ll_node *a,jbl_ll_node *b);
char			jbl_ll_space_ship			(const jbl_ll *this,const jbl_ll *that);
#define			jbl_ll_if_big(x,y)			(jbl_ll_space_ship(x,y)>0)
#define			jbl_ll_if_equal(x,y)		(jbl_ll_space_ship(x,y)==0)
#define			jbl_ll_if_small(x,y) 		(jbl_ll_space_ship(x,y)<0)
#define			jbl_ll_if_equal_small(x,y)	(jbl_ll_space_ship(x,y)<=0)
#define			jbl_ll_if_equal_big(x,y) 	(jbl_ll_space_ship(x,y)>=0)
jbl_ll  *		jbl_ll_copy					(jbl_ll *that);
jbl_ll  *		jbl_ll_merge				(jbl_ll *this,jbl_ll *that);

#define			jbl_Vll_add(x,y)			((jbl_var*)jbl_ll_add($jbl_ll(x),y))
#define			jbl_Vll_merge(x,y)			((jbl_var*)jbl_ll_merge($jbl_ll(x),$jbl_ll(y)))


#if JBL_STRING_ENABLE==1
#include "jbl_string.h"
jbl_string* jbl_ll_json_encode(const jbl_ll* this,jbl_string *out,char format,jbl_int32 tabs);
#endif

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void			jbl_ll_view_put				(const jbl_ll* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs);//从output_stream浏览一个hash table
#define			jbl_ll_view(x) 				jbl_ll_view_put(x,jbl_stream_stdout,__LINE__,#x " @ "__FILE__,jbl_view_default_tabs_num),jbl_stream_push_char(jbl_stream_stdout,'\n')//浏览一个hash table
void			jbl_ll_json_put				(const jbl_ll* this,jbl_stream *output_stream,char format,jbl_int32 tabs);//从output_stream JSON输出一个hash table
#endif
#if JBL_HT_ENABLE==1
typedef struct __jbl_ht jbl_ht;
jbl_ll *		jbl_ll_merge_ht				(jbl_ll *this,jbl_ht *that);
#endif



/*
#define					jbl_ll_from_json(x,y)					jbl_ll_from_json_start(x,y,0)
jbl_string_size_type	jbl_ll_from_json_start				(jbl_ll *this,const jbl_string *in,jbl_string_size_type start);

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void					jbl_ll_put							(const jbl_ll* this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str);
#define					jbl_ll_view(x) 						jbl_ll_put(x,&jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jbl_stream_push_char(&jbl_stream_stdout,'\n'),jbl_stream_do(&jbl_stream_stdout,1);
#if JBL_STRING_ENABLE==1
void					jbl_ll_to_json						(const jbl_ll *this,jbl_string *result);
#endif
#endif
*/

#endif
#endif
