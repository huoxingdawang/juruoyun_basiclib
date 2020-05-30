/* Copyright (c) [2019] juruoyun developer team
	 Juruoyun basic lib is licensed under the Mulan PSL v1.
	 You can use this software according to the terms and conditions of the Mulan PSL v1.
	 You may obtain a copy of Mulan PSL v1 at:
			http://license.coscl.org.cn/MulanPSL
	 THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
	 IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
	 PURPOSE.
	 See the Mulan PSL v1 for more details.*/
#include "jbl_ht.h"
#if JBL_HT_ENABLE==1
#include "jbl_exception.h"
#include "jbl_malloc.h"
#include "jbl_string.h"
#include "jbl_ying.h"
#include "jbl_var.h"
#if JBL_LL_ENABLE==1
#include "jbl_ll.h"
#endif
#define st jbl_ht_size_type
#define _st __jbl_ht_size_type
#define ht jbl_string_hash_type
#define dt jbl_ht_data
#define gh2(x,y) ((_st)(((st)(y))|(-(st)(x)->size)))
#define htvh(x) for(st i=0;i<(x)->size;jbl_stream_push_char(jbl_stream_stdout,' '),jbl_stream_push_int64(jbl_stream_stdout,(_st)((st*)(x)->data)[-i-1]),++i);jbl_stream_push_char(jbl_stream_stdout,'\n')		//查看hash值

const jbl_var_operators jbl_ht_operators={
	(void* (*)(void *))jbl_ht_free,
	(void* (*)(void *))jbl_ht_copy,
	(char  (*)(const void*,const void*))jbl_ht_space_ship,
#if JBL_JSON_ENABLE==1
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_ht_json_encode,
#endif	
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_ht_view_put,
#if JBL_JSON_ENABLE==1
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_ht_json_put,
#endif	
#endif	
};
inline jbl_ht* jbl_Vht(jbl_var * this){if(!Vis_jbl_ht(this))jbl_exception(JBL_ERROR_VAR_TYPE_ERROR);return((jbl_ht*)this);}
inline jbl_var * jbl_htv(jbl_ht_data *node){return node->v;}
inline jbl_string * jbl_htk(jbl_ht_data *node){return node->k;}
inline jbl_string_hash_type jbl_hth(jbl_ht_data *node){return node->h;}
void __jbl_ht_data_init(jbl_ht_data *this);
void __jbl_ht_data_free(jbl_ht_data *this);
inline void __jbl_ht_data_init(jbl_ht_data *this)
{
	this->k=NULL;
	this->v=NULL;
	this->h=0;
	this->nxt=((st)-1);
}
inline void __jbl_ht_data_free(jbl_ht_data *this)
{
	this->k=jbl_string_free(this->k);
	this->v=jbl_var_free(this->v);
	this->h=0;
	this->nxt=((st)-1);
}

inline jbl_ht * jbl_ht_new()
{
	return jbl_ht_init(jbl_malloc((sizeof(jbl_ht))));	
}
jbl_var * jbl_Vht_new()
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_ht))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_var_set_operators(this,&jbl_ht_operators);
	jbl_ht_init(jbl_Vht(this));
	jbl_gc_set_var(jbl_Vht(this));
	return this;		
}
inline jbl_ht * jbl_ht_init(jbl_ht *this)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);
	this->size=this->len=this->nxt=0;
	this->data=NULL;
	return this;
}
jbl_ht* jbl_ht_free(jbl_ht *this)
{
	if(this==NULL)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_reference_cnt(this))
	{
		if(jbl_gc_is_ref(this))
			jbl_ht_free((jbl_ht *)jbl_refer_pull(this));
		else
			if(this->size!=0)
			{
				for(register st i=0;i<this->size;__jbl_ht_data_free(&this->data[i]),++i);	
				jbl_free((char*)this->data-sizeof(st)*this->size);
			}
		jbl_free(((jbl_gc_is_var(this))?(jbl_ht*)((char*)this-sizeof(jbl_var)):this));
	}
	return NULL;
}
inline jbl_ht * jbl_ht_extend(jbl_ht *this,st size)
{
	if(this==NULL)this=jbl_ht_new();
	return jbl_ht_extend_to(this,size+((jbl_ht *)jbl_refer_pull(this))->nxt);
}
jbl_ht * jbl_ht_extend_to(jbl_ht *this,st size)
{
	if(this==NULL)this=jbl_ht_new();
	jbl_reference *ref=NULL;
	if(jbl_gc_is_ref(this))
		ref=(jbl_reference*)this,this=((jbl_reference*)this)->ptr;
	
	jbl_ht *tmp=NULL;
	if((jbl_gc_reference_cnt(this)==1))	tmp=this;
	else								tmp=(jbl_gc_is_var(this))?jbl_Vht(jbl_Vht_new()):jbl_ht_new();
	st old_size=this->size;
	jbl_max_update(tmp->size,JBL_HT_MIN_SIZE);
	jbl_max_update(tmp->size,this->len);
	while(tmp->size<size)tmp->size<<=1;
	
	if(tmp->size<=old_size)
		if((jbl_gc_reference_cnt(this)==1))
			return ref?((jbl_ht *)ref):this;

	if((jbl_gc_reference_cnt(this)==1)&&size-old_size+this->len<=old_size&&(this->len<=(this->nxt>>1))&&this->data!=NULL)
		return ref?(ref->ptr=jbl_ht_rehash(this),((jbl_ht *)ref)):tmp;
	dt *tmpd=(dt*)(((char*)jbl_malloc(tmp->size*(sizeof(dt)+sizeof(st))))+sizeof(st)*tmp->size);
	for(register st i=0;i<tmp->size;__jbl_ht_data_init(&tmpd[i]),((st*)tmpd)[-i-1]=((_st)-1),++i);
	if(this->data==NULL)
		tmp->data=tmpd;
	else
	{
		register st old_nxt=this->nxt;
		tmp->nxt=0;
		for(register st j=0;j<old_nxt;++j)
			if(this->data[j].v!=NULL)
			{
				jbl_int64 h2=gh2(tmp,tmpd[tmp->nxt].h=this->data[j].h);
				tmpd[tmp->nxt].k=jbl_string_copy(this->data[j].k);
				tmpd[tmp->nxt].v=jbl_var_copy(this->data[j].v);
				tmpd[tmp->nxt].nxt=((st*)tmpd)[h2];
				((st*)tmpd)[h2]=tmp->nxt;
				++tmp->nxt;
			}		
		if(old_size!=0&&(jbl_gc_reference_cnt(this)==1))
		{
			for(register st i=0;i<old_size;__jbl_ht_data_free(&this->data[i]),++i);	
			jbl_free((char*)this->data-sizeof(st)*old_size);
		}
		tmp->data=tmpd;
	}
	if(jbl_gc_reference_cnt(this)>1)jbl_gc_minus(this);
	return ref?(ref->ptr=tmp,((jbl_ht *)ref)):tmp;
}
jbl_ht * jbl_ht_rehash(jbl_ht *this)
{
	jbl_ht * thi=jbl_refer_pull(this);
	if(thi->data==NULL)return this;
	thi=jbl_ht_extend_to(thi,0);
	register st i=0,j=0;
	for(;j<thi->nxt&&thi->data[j].v!=NULL;++j);	
	for(i=j+1;i<thi->nxt;++i)
		if(thi->data[i].v!=NULL&&j<i)
		{
			jbl_int64 h2=gh2(thi,thi->data[j].h=thi->data[i].h);		
			thi->data[j].k=jbl_string_copy(thi->data[i].k);
			thi->data[j].v=jbl_var_copy(thi->data[i].v);
			thi->data[j].nxt=(((st*)thi->data)[h2]>=i)?(thi->data[i].nxt):(((st*)thi->data)[h2]);
			((st*)thi->data)[h2]=j;		
			++j;
			__jbl_ht_data_free(&thi->data[i]);
		}
	thi->nxt=j;
	return this;
}
jbl_ht * __jbl_ht_insert(jbl_ht *this,ht h,jbl_string *k,jbl_var *v)
{
	this=jbl_ht_extend(this,1);
	jbl_ht * thi=jbl_refer_pull(this);
	_st h2;
	if(thi->data!=NULL)
	{
		h2=gh2(thi,h);
		for(register st i=((st*)thi->data)[h2];i<thi->nxt;i=thi->data[i].nxt)
			if(h==thi->data[i].h&&jbl_string_if_equal(thi->data[i].k,k))
			{
				jbl_var_free(thi->data[i].v);
				thi->data[i].v=v?jbl_var_copy(v):jbl_Vnull_new();
				return thi;
			}
	}
	h2=gh2(thi,h);
	thi->data[thi->nxt].h=h;
	thi->data[thi->nxt].k=jbl_string_copy(jbl_refer_pull(k));
	thi->data[thi->nxt].v=v?jbl_var_copy(v):jbl_Vnull_new();
	thi->data[thi->nxt].nxt=((st*)thi->data)[h2];
	((st*)thi->data)[h2]=thi->nxt;
	++thi->len;
	++thi->nxt;
	return this;
}
jbl_var * __jbl_ht_get(const jbl_ht *this,ht h,jbl_string *k)
{
	this=jbl_refer_pull(this);
	if(this->size!=0)
	{
		_st	h2=gh2(this,h);
		for(register st i=((st*)this->data)[h2];i<this->nxt;i=this->data[i].nxt)
			if(h==this->data[i].h&&jbl_string_if_equal(this->data[i].k,k))
				return jbl_var_copy(this->data[i].v);
	}
	return NULL;
}
jbl_ht * __jbl_ht_unset(jbl_ht *this,ht h,jbl_string *k)
{
	this=jbl_ht_extend(this,0);
	jbl_ht * thi=jbl_refer_pull(this);	
	if(thi->size!=0)
	{
		_st h2=gh2(thi,h);
		for(register st i=((st*)thi->data)[h2],j=((_st)-1);i<thi->nxt;j=i,i=thi->data[i].nxt)
			if(h==thi->data[i].h&&jbl_string_if_equal(thi->data[i].k,k))
			{
				if(j==((_st)-1))
					(((st*)thi->data)[h2])=thi->data[i].nxt;
				else
					thi->data[j].nxt=thi->data[i].nxt;
				__jbl_ht_data_free(&thi->data[i]);
				--thi->len;
			}
	}
	return this;
}
inline jbl_ht  * jbl_ht_insert		(jbl_ht *this,jbl_string *k,jbl_var *v)		{return __jbl_ht_insert(this,jbl_string_hash(k),k,v);}
inline jbl_ht  * jbl_ht_insert_chars(jbl_ht *this,unsigned char *kk,jbl_var *v)	{jbl_string * k=jbl_string_add_chars(NULL,kk);this=jbl_ht_insert(this,k,v);jbl_string_free(k);return this;}
inline jbl_ht  * jbl_ht_insert_int	(jbl_ht *this,ht h,jbl_var *v)				{return __jbl_ht_insert(this,h,NULL,v);}
inline jbl_var * jbl_ht_get			(const jbl_ht *this,jbl_string *k)			{return __jbl_ht_get(this,jbl_string_hash(k),k);}
inline jbl_var * jbl_ht_get_chars	(const jbl_ht *this,unsigned char *kk)		{jbl_string * k=jbl_string_add_chars(NULL,kk);jbl_var *v=jbl_ht_get(this,k);jbl_string_free(k);return v;}
inline jbl_var * jbl_ht_get_int		(const jbl_ht *this,ht h)					{return __jbl_ht_get(this,h,NULL);}
inline jbl_ht  * jbl_ht_unset		(jbl_ht *this,jbl_string *k)				{return __jbl_ht_unset(this,jbl_string_hash(k),k);}
inline jbl_ht  * jbl_ht_unset_chars	(jbl_ht *this,unsigned char *kk)			{jbl_string * k=jbl_string_add_chars(NULL,kk);this=jbl_ht_unset(this,k);jbl_string_free(k);return this;}
inline jbl_ht  * jbl_ht_unset_int	(jbl_ht *this,ht h)							{return __jbl_ht_unset(this,h,NULL);}


inline jbl_ht *jbl_ht_copy(jbl_ht *that)
{
	if(that==NULL)return NULL;
	jbl_gc_plus(that);
	return that;
}
char jbl_ht_space_ship(const jbl_ht *this_,const jbl_ht *that_)
{
	if(this_==that_){return 0;}if(this_==NULL){return -1;}if(that_==NULL){return 1;}
	const jbl_ht *this=jbl_refer_pull(this_);
	const jbl_ht *that=jbl_refer_pull(that_);	
	if(this==that){return 0;}if(this==NULL){return -1;}if(that==NULL){return 1;}
	if(this->len!=that->len)
		return (this->len>that->len)?(1):(-1);
	jbl_var *v2;
	jbl_ht_foreach(this,i)
	{
		v2=jbl_ht_get(that,i->k);
		char tmp=jbl_var_space_ship(i->v,v2);
		v2=jbl_var_free(v2);
		if(!tmp)return tmp;
	}
	return 0;
}
jbl_ht * jbl_ht_merge(jbl_ht *this,jbl_ht *that)
{
	if(this==NULL)this=jbl_ht_new();
	if(that==NULL)return this;
	this=jbl_ht_extend(this,that->len);
	jbl_ht_foreach(that,i)
		__jbl_ht_insert(this,i->h,i->k,i->v);
	return this;
}
jbl_ht * jbl_ht_merge_int(jbl_ht *this)
{
	this=jbl_ht_extend(this,1);	
	jbl_ht * thi=jbl_refer_pull(this);
	if(thi->data==NULL)return this;
	for(register st i=0,j;i<thi->nxt;++i)
		if((!thi->data[i].k)&&thi->data[i].v)
		{
			jbl_string *s=jbl_string_add_uint64(NULL,thi->data[i].h);
			char flag=0;
			ht h=jbl_string_hash(s);
			_st	h2=gh2(thi,h);
			for(j=((st*)thi->data)[h2];j<thi->nxt;j=thi->data[j].nxt)
				if(h==thi->data[j].h&&jbl_string_if_equal(thi->data[j].k,s))
				{flag=1;break;}
			if(flag)
				{if(i>j)jbl_var_free(thi->data[j].v),thi->data[j].v=jbl_var_copy(thi->data[i].v);}
			else
			{
				this=jbl_ht_extend(this,1);	
				thi=jbl_refer_pull(this);
				h2=gh2(thi,h);
				thi->data[thi->nxt].h=h;
				thi->data[thi->nxt].k=jbl_string_copy(s);
				thi->data[thi->nxt].v=jbl_var_copy(thi->data[i].v);
				thi->data[thi->nxt].nxt=((st*)thi->data)[h2];
				((st*)thi->data)[h2]=thi->nxt;
				++thi->len;
				++thi->nxt;
			}
			__jbl_ht_data_free(&thi->data[i]);
			jbl_string_free(s);
			
		}
	return this;
}
#if JBL_JSON_ENABLE==1
jbl_string* jbl_ht_json_encode(const jbl_ht* this,jbl_string *out,char format,jbl_int32 tabs)
{
	out=jbl_string_json_put_format(this=jbl_refer_pull(this),out,format,&tabs);if(!this)return out;

	out=jbl_string_add_char(out,'{');

	char flag=0;
	jbl_ht_foreach(this,i)
	{
		if(i->k==NULL)continue;
		if(flag)out=jbl_string_add_char(out,',');else flag=1;
		if(format){out=jbl_string_add_char(out,'\n');for(jbl_int32 i=0;i<tabs;out=jbl_string_add_char(out,'\t'),++i);}//格式化的\t和\n
		if(i->k==NULL)
			out=jbl_string_add_uint64(out,i->h);
		else
			out=jbl_string_json_encode(i->k,out,0,0);
		out=jbl_string_add_char(out,':');
		out=jbl_var_json_encode(i->v,out,format,-tabs);
	}	

	if(format){out=jbl_string_add_char(out,'\n');for(jbl_int32 i=0;i<tabs-1;out=jbl_string_add_char(out,'\t'),++i);}
	out=jbl_string_add_char(out,'}');
	return out;
}
jbl_ht* jbl_ht_json_decode(jbl_ht *this,const jbl_string* in,jbl_string_size_type *start)
{
	char flag=0;
	if(!this)this=jbl_ht_new(),flag=1;
	in=jbl_refer_pull(in);
	if(!in)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_string_size_type i=start?(*start):0,n=in->len;
	for(;i<n&&in->s[i]<=32;++i);
//	pchar(in->s[i]);pn();
	if(in->s[i]!='{')goto fail;
	++i;
	for(;i<n;)
	{
		for(;i<n&&in->s[i]<=32;++i);
		if(in->s[i]=='}'){++i;goto success;}
		jbl_string * k=jbl_string_json_decode(NULL,in,&i);
		if(k==NULL)goto fail;
		for(;i<n&&in->s[i]<=32;++i);
		if(in->s[i]!=':'){k=jbl_string_free(k);goto fail;}
		++i;
		jbl_var *v=jbl_var_json_decode(NULL,in,&i);
		if(v==NULL)goto fail;
		this=jbl_ht_insert(this,k,v);
		v=jbl_var_free(v);
		k=jbl_string_free(k);
		for(;i<n&&in->s[i]<=32;++i);
		if(in->s[i]=='}'){++i;goto success;}
		if(in->s[i]!=',')goto fail;
		++i;
	}
	goto fail;
success:;
	start?(*start=i):0;
	return this;
fail:;
	if(flag)this=jbl_ht_free(this);
	return NULL;
}
#endif
#if JBL_STREAM_ENABLE==1
void jbl_ht_view_put(const jbl_ht* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	if(jbl_stream_view_put_format(this=jbl_refer_pull(this),output_stream,"jbl_ht        ",format,str,&tabs))return;
	jbl_stream_push_chars(output_stream,"\tlen:");
	jbl_stream_push_uint64(output_stream,this->len);
	jbl_stream_push_chars(output_stream,"\tnxt:");
	jbl_stream_push_uint64(output_stream,this->nxt);
	jbl_stream_push_chars(output_stream,"\tsize:");
	jbl_stream_push_uint64(output_stream,this->size);
	jbl_ht_foreach(this,i)
	{
		if(format){jbl_stream_push_char(output_stream,'\n');for(jbl_int32 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
		if(i->k==NULL)
			jbl_stream_push_uint64(output_stream,i->h);
		else
			jbl_stream_push_char(output_stream,'"'),jbl_stream_push_string(output_stream,i->k),jbl_stream_push_char(output_stream,'"');
		jbl_stream_push_char(output_stream,':');
		jbl_var_view_put(i->v,output_stream,(format?(-1):0),NULL,-tabs);
	}	
}
#if JBL_JSON_ENABLE==1
void jbl_ht_json_put(const jbl_ht* this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{	
	if(jbl_stream_json_put_format(this=jbl_refer_pull(this),output_stream,format,&tabs))return;
	jbl_stream_push_char(output_stream,'{');
	char flag=0;
	jbl_ht_foreach(this,i)
	{
		if(i->k==NULL)continue;
		if(flag)jbl_stream_push_char(output_stream,',');else flag=1;
		if(format){jbl_stream_push_char(output_stream,'\n');for(jbl_int32 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
		if(i->k==NULL)
			jbl_stream_push_uint64(output_stream,i->h);
		else
			jbl_string_json_put(i->k,output_stream,0,0);
		jbl_stream_push_char(output_stream,':');
		jbl_var_json_put(i->v,output_stream,format,-tabs);
	}	
	if(format){jbl_stream_push_char(output_stream,'\n');for(jbl_int32 i=0;i<tabs-1;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
	jbl_stream_push_char(output_stream,'}');
}
#endif
#endif
#if JBL_LL_ENABLE==1
jbl_ht *jbl_ht_merge_ll(jbl_ht *this,jbl_ll *that)
{
	this=jbl_ht_extend(this,jbl_ll_get_length(that));
	jbl_ll_size_type j=0;
	jbl_ll_foreach(that,i)
		jbl_ht_insert_int(this,j++,i->v);	
	return this;
}
#endif
#undef st
#undef _st
#undef ht
#undef dt
#undef gh2
#undef htvh

#endif