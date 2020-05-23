/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_ll.h"
#if JBL_LL_ENABLE==1
#include "jbl_exception.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
#include "jbl_var.h"
#if JBL_STRING_ENABLE==1
#include "jbl_string.h"
#endif
#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
#endif
#if JBL_HT_ENABLE==1
#include "jbl_ht.h"
#endif

const jbl_var_operators jbl_ll_operators={
	(void* (*)(void *))jbl_ll_free,
	(void* (*)(void *))jbl_ll_copy,
	(char  (*)(const void*,const void*))jbl_ll_space_ship,
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_ll_json_encode,
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_ll_view_put,
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_ll_json_put,
#endif	
};
jbl_ll_node * jbl_ll_node_init(jbl_ll_node *node)
{
	node->pre=NULL;
	node->nxt=NULL;
	node->v=NULL;
	return node;
}
jbl_ll_node * jbl_ll_node_new()
{
	return jbl_ll_node_init(jbl_malloc(sizeof(jbl_ll_node)));
}
void jbl_ll_node_free(jbl_ll_node *node)
{
	node->v=jbl_var_free(node->v);
	jbl_free(node);
}
void jbl_ll_node_delink(jbl_ll *this,jbl_ll_node *node)
{
	if(node->nxt==NULL)	this->tail=node->pre;
	else				node->nxt->pre=node->pre;
	if(node->pre==NULL)	this->head=node->nxt;
	else				node->pre->nxt=node->nxt;
	--this->len;
	node->nxt=NULL,node->pre=NULL;
}
void jbl_ll_node_insert(jbl_ll *this,jbl_ll_node *node,jbl_ll_node *after)
{
	if(after==NULL)
	{
		node->nxt=this->head;
		node->pre=NULL;
		if(node->nxt==NULL)	this->tail=node;
		else				node->nxt->pre=node;
		this->head=node;
	}
	else
	{
		node->nxt=after->nxt;
		node->pre=after;
		after->nxt=node;
		if(node->nxt==NULL)	this->tail=node;
		else				node->nxt->pre=node;
	}	
	++this->len;
}
void jbl_ll_node_delete(jbl_ll *this,jbl_ll_node *node)
{
	jbl_ll_node_delink(this,node);
	jbl_ll_node_free(node);
}



inline jbl_ll * jbl_ll_new()
{
	return jbl_ll_init(jbl_malloc((sizeof(jbl_ll))));	
}
jbl_var * jbl_Vll_new()
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_ll))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_ll_init($jbl_ll(this));
	jbl_gc_set_var($jbl_ll(this));
	jbl_var_set_operators(this,&jbl_ll_operators);
	return this;		
}
inline jbl_ll* jbl_ll_init(jbl_ll *this)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);	
	this->head=NULL,this->tail=NULL;
	this->len=0;
	return this;
}
jbl_ll* jbl_ll_free(jbl_ll *this)
{
	if(this==NULL)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_reference_cnt(this))
	{
		if(jbl_gc_is_ref(this))
			jbl_ll_free((jbl_ll *)jbl_refer_pull(this));
		else
			jbl_ll_foreach_del(this,i,j)
				jbl_ll_node_delete(this,i);	
		jbl_free(((jbl_gc_is_var(this))?(jbl_ll*)((char*)this-sizeof(jbl_var)):this));
	}
	return NULL;	
}
jbl_ll *jbl_ll_extend(jbl_ll *this,jbl_ll_node **a,jbl_ll_node **b)
{
	if(this==NULL)return jbl_ll_new();
	jbl_reference *ref=NULL;
	if(jbl_gc_is_ref(this))
		ref=(jbl_reference*)this,this=((jbl_reference*)this)->ptr;
	if((jbl_gc_reference_cnt(this)<=1))return ref?((jbl_ll *)ref):this;
	jbl_ll *tmp=(jbl_gc_is_var(this))?$jbl_ll(jbl_Vll_new()):jbl_ll_new();
	jbl_ll_foreach(this,i)
	{
		jbl_ll_node *node=jbl_ll_node_new();
		node->v=jbl_var_copy(i->v);
		if(a&&(*a==i))*a=node;
		if(b&&(*b==i))*b=node;
		jbl_ll_node_insert(tmp,node,tmp->tail);		
	}
	jbl_gc_minus(this);
	return ref?(ref->ptr=tmp,((jbl_ll *)ref)):tmp;
}
jbl_ll * jbl_ll_insert(jbl_ll *this,jbl_var *var,jbl_ll_node *after)
{
	this=jbl_ll_extend(this,&after,NULL);
	jbl_ll_node *node=jbl_ll_node_new();
	node->v=jbl_var_copy(var);
	jbl_ll_node_insert(((jbl_ll *)jbl_refer_pull(this)),node,after);
	return this;
}
jbl_ll * jbl_ll_delete(jbl_ll *this,jbl_ll_node *node)
{
	if(!node)return this;
	this=jbl_ll_extend(this,&node,NULL);
	jbl_ll_node_delete(((jbl_ll *)jbl_refer_pull(this)),node);
	return this;
}
jbl_ll * jbl_ll_swap_node(jbl_ll *this,jbl_ll_node *a,jbl_ll_node *b)
{
	if(a==b)return this;
	this=jbl_ll_extend(this,&a,&b);
	jbl_var *v;
	v=a->v;
	a->v=b->v;
	b->v=v;
	return this;
}
char jbl_ll_space_ship(const jbl_ll *this,const jbl_ll *that)
{
	if(this==that){return 0;}if(this==NULL){return -1;}if(that==NULL){return 1;}
	const jbl_ll *thi=jbl_refer_pull(this);
	const jbl_ll *tha=jbl_refer_pull(that);	
	if(thi==tha){return 0;}if(thi==NULL){return -1;}if(tha==NULL){return 1;}
	if(thi->len!=tha->len)
		return (thi->len>tha->len)?(1):(-1);
	char a=0;
	for(jbl_ll_node *i=thi->head,*j=tha->head;i!=NULL&&a==0;a=jbl_var_space_ship(i->v,j->v),i=i->nxt,j=j->nxt);
	return a;
}
inline jbl_ll *jbl_ll_copy(jbl_ll *that)
{
	if(that==NULL)return NULL;
	jbl_gc_plus(that);
	return that;
}
jbl_ll *jbl_ll_merge(jbl_ll *this,jbl_ll *that)
{
	if(that==NULL)return this;
	jbl_ll * tha=jbl_refer_pull(that);
	if(tha==NULL)return this;
	this=jbl_ll_extend(this,NULL,NULL);
	jbl_ll * thi=jbl_refer_pull(this);
	jbl_ll_foreach(tha,i)
		jbl_ll_insert(thi,i->v,thi->tail);
	return this;
}
/*
jbl_string_size_type jbl_ll_from_json_start(jbl_ll *this,const jbl_string *in,jbl_string_size_type start)
{
	if(this==NULL||in==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	register jbl_string_size_type i=start,n=jbl_string_get_length(in),ii;
	jbl_ll that;
	jbl_ll_init(&that);
	for(;(i<n)&&(!(in->s[i]=='['));++i);++i;
	jbl_ll_node *node;
	while(i<n)
	{
begin:
		node=jbl_malloc(sizeof(jbl_ll_node));
		jbl_ll_node_init(node);
		ii=jbl_var_from_json_start(&(node->v),in,i);
		if(ii==i){jbl_free(node);node=NULL;for(;i<n;++i)if(in->s[i]==']')goto success;else if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')goto fail;goto fail;}i=ii;	
		jbl_ll_add_node(&that,node);
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
	jbl_ll_free(&that);
	return start;
success:
	jbl_ll_merge_light(this,&that);
	jbl_ll_free(&that);
	return i+1;	
}
*/
#if JBL_STRING_ENABLE==1
jbl_string* jbl_ll_json_encode(const jbl_ll* this,jbl_string *out,char format,jbl_int32 tabs)
{
	if(out==NULL)out=jbl_string_new();
	this=jbl_refer_pull(this);
	out=jbl_refer_pull(out);
	if(format&&tabs<0)out=jbl_string_add_char(out,'\n'),tabs=-tabs;
	if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;out=jbl_string_add_char(out,'\t'),++i);else tabs=-tabs;
	if(!this)return jbl_string_add_chars_length(out,(unsigned char *)"null",4);	
	
	out=jbl_string_add_char(out,'[');

	++tabs;
	char flag=0;
	jbl_ll_foreach(this,i)
	{
		if(flag)out=jbl_string_add_char(out,',');else flag=1;
		if(format){out=jbl_string_add_char(out,'\n');for(jbl_int32 i=0;i<tabs;out=jbl_string_add_char(out,'\t'),++i);}//格式化的\t和\n
		out=jbl_var_json_encode(i->v,out,format,-tabs);
	}	

	if(format){out=jbl_string_add_char(out,'\n');for(jbl_int32 i=0;i<tabs-1;out=jbl_string_add_char(out,'\t'),++i);}
	out=jbl_string_add_char(out,']');
	return out;
}
#endif
#if JBL_STREAM_ENABLE==1
void jbl_ll_view_put(const jbl_ll* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	if(output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	output_stream=jbl_refer_pull(output_stream);
	this=jbl_refer_pull(this);
	if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char_force(output_stream,'\t'),++i);else tabs=-tabs;	
	if(this)jbl_stream_push_chars(output_stream,"jbl_ll        ");
	else	jbl_stream_push_chars(output_stream,"null          ");
	if(format&&str)jbl_stream_push_chars(output_stream,str),jbl_stream_push_char_force(output_stream,' '),(format!=-1?jbl_stream_push_uint64(output_stream,format):0);
	if(!this)return;	
	jbl_stream_push_chars(output_stream,"\tlen:");
	jbl_stream_push_uint64(output_stream,this->len);
	++tabs;
	jbl_ll_size_type j=0;
	jbl_ll_foreach(this,i)
	{
		if(format){jbl_stream_push_char(output_stream,'\n');for(jbl_int32 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
		jbl_stream_push_uint64(output_stream,j++);
		jbl_stream_push_char(output_stream,':');
		jbl_var_view_put(i->v,output_stream,(format?(-1):0),NULL,-tabs);
	}	
}
void jbl_ll_json_put(const jbl_ll* this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{
	if(output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	output_stream=jbl_refer_pull(output_stream);
	this=jbl_refer_pull(this);
	if(format&&tabs<0)jbl_stream_push_char_force(output_stream,'\n'),tabs=-tabs;	
	if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char_force(output_stream,'\t'),++i);else tabs=-tabs;
	if(!this)return jbl_stream_push_chars(output_stream,"null");	
	jbl_stream_push_char(output_stream,'[');
	++tabs;
	char flag=0;
	jbl_ll_foreach(this,i)
	{
		if(flag)jbl_stream_push_char(output_stream,',');else flag=1;
		if(format){jbl_stream_push_char(output_stream,'\n');for(jbl_int32 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
		jbl_var_json_put(i->v,output_stream,format,-tabs);
	}	
	if(format){jbl_stream_push_char(output_stream,'\n');for(jbl_int32 i=0;i<tabs-1;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
	jbl_stream_push_char(output_stream,']');
}
#endif
#if JBL_HT_ENABLE==1
jbl_ll *jbl_ll_merge_ht(jbl_ll *this,jbl_ht *that)
{
	jbl_ht_foreach(that,i)
		this=jbl_ll_add(this,i->v);	
	return this;
}
#endif
#endif
