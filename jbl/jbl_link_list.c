/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_link_list.h"
#if JBL_LINK_LIST_ENABLE==1
#if JBL_USE_STDARG==1
#include <stdarg.h>
#endif
#include "jbl_exception.h"
#include "jbl_malloc.h"
#include "jbl_var.h"
#include "jbl_ying.h"

inline void jbl_link_list_init(jbl_link_list *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	this->head=NULL,this->tail=NULL;
	this->length=0;this->light_copy=false;
}
inline void jbl_link_list_node_init(jbl_link_list_node *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_var_init(&this->v);
}
void jbl_link_list_free(jbl_link_list *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(!this->light_copy)
		jbl_link_list_foreach_del(this,i,j)
			jbl_link_list_delete_node(this,i);
	this->head=NULL,this->tail=NULL;
}
void jbl_link_list_node_free(jbl_link_list_node *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_var_free(&this->v);
	this->nxt=NULL,this->pre=NULL;
}
void jbl_link_list_node_delink(jbl_link_list *this,jbl_link_list_node *node)
{
	if(this==NULL||node==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(node->nxt==NULL)
		this->tail=node->pre;
	else
		node->nxt->pre=node->pre;
	if(node->pre==NULL)
		this->head=node->nxt;
	else
		node->pre->nxt=node->nxt;
	--this->length;
	node->nxt=NULL,node->pre=NULL;
}
void jbl_link_list_insert_node(jbl_link_list *this,jbl_link_list_node *node,jbl_link_list_node *after)
{
	if(this==NULL||node==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(after==NULL)
	{
		node->nxt=this->head;
		node->pre=NULL;
		if(node->nxt==NULL)
			this->tail=node;
		else
			node->nxt->pre=node;
		this->head=node;
	}
	else
	{
		node->nxt=after->nxt;
		node->pre=after;
		after->nxt=node;
		if(node->nxt==NULL)
			this->tail=node;
		else
			node->nxt->pre=node;
	}	
	++this->length;
}
void jbl_link_list_insert_var(jbl_link_list *this,jbl_var *var,jbl_link_list_node *after)
{
	if(this==NULL||var==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_link_list_node *node=jbl_malloc(sizeof(jbl_link_list_node));
	if(node==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);
	jbl_link_list_node_init(node);
	jbl_var_equal(&(node->v),var);
	jbl_link_list_insert_node(this,node,after);
}
void jbl_link_list_insert_var_light(jbl_link_list *this,jbl_var *var,jbl_link_list_node *after)
{
	if(this==NULL||var==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_link_list_node *node=jbl_malloc(sizeof(jbl_link_list_node));
	if(node==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);
	jbl_link_list_node_init(node);
	jbl_var_equal_light(&(node->v),var);
	jbl_link_list_insert_node(this,node,after);
}
void jbl_link_list_insert_var_move(jbl_link_list *this,jbl_var *var,jbl_link_list_node *after)
{
	if(this==NULL||var==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_link_list_node *node=jbl_malloc(sizeof(jbl_link_list_node));
	if(node==NULL)jbl_exception(JBL_ERROR_MEMORY_ERROR);
	jbl_link_list_node_init(node);
	jbl_var_equal_light_copy(&(node->v),var);
	jbl_link_list_insert_node(this,node,after);
}
inline void jbl_link_list_delete_node(jbl_link_list *this,jbl_link_list_node *node)
{
	if(this==NULL||node==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_link_list_node_delink(this,node);
	jbl_link_list_node_free(node);
	jbl_free(node);
	node=NULL;
}
inline void jbl_link_list_swap_node(jbl_link_list *this,jbl_link_list_node *a,jbl_link_list_node *b)
{
	if(a==b)return;
	if(this==NULL||a==NULL||b==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_link_list_node *c;
	(a->pre==NULL)?(this->head=b,b->pre->nxt=a):((b->pre==NULL)?(this->head=a,a->pre->nxt=b):(a->pre->nxt=b,b->pre->nxt=a));
	(a->nxt==NULL)?(this->tail=b,b->nxt->pre=a):((b->nxt==NULL)?(this->tail=a,a->nxt->pre=b):(a->nxt->pre=b,b->nxt->pre=a));
	c=a->pre,a->pre=b->pre,b->pre=c;
	c=a->nxt,a->nxt=b->nxt,b->nxt=c;
}
char jbl_link_list_space_ship(const jbl_link_list *this,const jbl_link_list *that)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this==that)
		return 0;	
	if(this->length!=that->length)
		return (this->length>that->length)?(1):(-1);
	char a=0;
	for(jbl_link_list_node *i=this->head,*j=that->head;i!=NULL&&a==0;a=jbl_var_space_ship(&i->v,&j->v),i=i->nxt,j=j->nxt);
	return a;
}
void jbl_link_list_copy(jbl_link_list *this,jbl_link_list *that,jbl_copy_type copytype)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_link_list_free(this);
	if(copytype==copy)
		jbl_link_list_foreach(that,i)
			jbl_link_list_add_var(this,jbl_link_list_data(i));
	else
	{
		this->head=that->head;this->tail=that->tail;this->length=that->length;
		if(copytype==light)
			this->light_copy=true;
		else	
			this->light_copy,that->light_copy,that->light_copy=true;
	}
}
jbl_string_size_type jbl_link_list_from_json_start(jbl_link_list *this,const jbl_string *in,jbl_string_size_type start)
{
	if(this==NULL||in==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	register jbl_string_size_type i=start,n=jbl_string_get_length(in),ii;
	jbl_link_list that;
	jbl_link_list_init(&that);
	for(;(i<n)&&(!(in->s[i]=='['));++i);++i;
	jbl_link_list_node *node;
	while(i<n)
	{
begin:
		node=jbl_malloc(sizeof(jbl_link_list_node));
		jbl_link_list_node_init(node);
		ii=jbl_var_from_json_start(&(node->v),in,i);
		if(ii==i){jbl_free(node);node=NULL;for(;i<n;++i)if(in->s[i]==']')goto success;else if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')goto fail;goto fail;}i=ii;	
		jbl_link_list_add_node(&that,node);
		for(;i<n;++i)
			if(in->s[i]==',')
				{++i;goto begin;}
			else if(in->s[i]==']')
				goto success;
			else if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')
				goto fail;
		goto fail;
	}
fail:
	jbl_link_list_free(&that);
	return start;
success:
	jbl_link_list_merge_light(this,&that);
	jbl_link_list_free(&that);
	return i+1;	
}
void jbl_link_list_merge(jbl_link_list *this,jbl_link_list *that)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_link_list_foreach(that,i)
		jbl_link_list_add_var(this,jbl_link_list_data(i));		
}
void jbl_link_list_merge_light(jbl_link_list *this,jbl_link_list *that)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this->tail!=NULL)
		this->tail->nxt=that->head;
	else
		this->head=that->head;
	if(that->head!=NULL)
		that->head->pre=this->tail;
	this->tail=that->tail;
	this->length+=that->length;
	that->light_copy=true;
}
inline void	jbl_var_equal_link_list(jbl_var *this,jbl_link_list *that,jbl_copy_type copytype){jbl_var_init_as(this,JBL_VAR_TYPE_LINK_LIST);jbl_link_list_copy(this->data.p,that,copytype);}
#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void jbl_link_list_put(const jbl_link_list* this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str)
{
	if(this==NULL||output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_int16 tabs=(format>>16);
	
	if(format&1)if(tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);else tabs=-tabs;
	if(type==json)
		jbl_stream_push_char(output_stream,'[');
	else if(type==view)
	{
		jbl_stream_push_chars(output_stream,"jbl_link_list ");
		if(((jbl_uint16)format>>1)!=0)
			jbl_stream_push_chars(output_stream,str),jbl_stream_push_char(output_stream,' '),jbl_stream_push_uint64(output_stream,((jbl_uint16)format>>1));
		jbl_stream_push_chars(output_stream,"\tlen:");
		jbl_stream_push_uint64(output_stream,this->length);
	}
	jbl_uint32 format_nxt=(format&1)|((-(tabs+1))<<16);
	jbl_link_list_size_type j=0;
	jbl_uint8 flag=0;
	jbl_link_list_foreach(this,i)
	{
		if(type==json&&flag)jbl_stream_push_char(output_stream,',');flag=1;//JSON的逗号
		if(format&1){jbl_stream_push_char(output_stream,'\n');for(jbl_int16 i=0;i<tabs+1;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
		if(type==view){jbl_stream_push_uint64(output_stream,j);jbl_stream_push_char(output_stream,':');++j;}//view的序号
		jbl_var_put(jbl_link_list_data(i),output_stream,type,format_nxt,NULL);
	}		
	if(type==json)
	{
		if(format&1){jbl_stream_push_char(output_stream,'\n');for(jbl_int16 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);}
		jbl_stream_push_char(output_stream,']');
	}
}
#if JBL_STRING_ENABLE==1
void jbl_link_list_to_json(const jbl_link_list *this,jbl_string *result)
{
	if(this==NULL||result==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_stream output_stream;
	jbl_string_stream_init(&output_stream,result);
	jbl_link_list_put(this,&output_stream,json,0,NULL);
	jbl_stream_do(&output_stream,jbl_stream_force);
	jbl_string_stream_free(&output_stream);
}
#endif
#endif
#if JBL_USE_STDARG==1
inline void jbl_link_list_inits		(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_link_list_init(va_arg(valist,jbl_link_list*));va_end(valist);}
inline void jbl_link_list_node_inits	(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_link_list_node_init(va_arg(valist,jbl_link_list_node*));va_end(valist);}
inline void jbl_link_list_frees		(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_link_list_free(va_arg(valist,jbl_link_list*));va_end(valist);}
inline void jbl_link_list_node_frees	(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_link_list_node_free(va_arg(valist,jbl_link_list_node*));va_end(valist);}
#endif

#endif
