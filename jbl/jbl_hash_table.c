/* Copyright (c) [2019] juruoyun developer team
	 Juruoyun basic lib is licensed under the Mulan PSL v1.
	 You can use this software according to the terms and conditions of the Mulan PSL v1.
	 You may obtain a copy of Mulan PSL v1 at:
			http://license.coscl.org.cn/MulanPSL
	 THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
	 IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
	 PURPOSE.
	 See the Mulan PSL v1 for more details.*/
#include "jbl_hash_table.h"
#if JBL_HASH_TABLE_ENABLE==1
#if JBL_USE_STDARG==1
#include <stdarg.h>
#endif
#include "jbl_exception.h"
#include "jbl_malloc.h"
#include "jbl_string.h"
#include "jbl_ying.h"
#include "jbl_var.h"

#define st jbl_hash_table_size_type
#define dt jbl_hash_table_data
#define gh2(x,y) ((jbl_int64)(((jbl_uint64)(y))|(-(jbl_uint64)(x)->size)))
#define htvh(x,y) for(register st i=0;i<(x)->size;fprintf(y,"%lld ",(jbl_int64)((st*)(x)->data)[-i-1]),++i);putc('\n',y)
void jbl_hash_table_data_init(jbl_hash_table_data *this);
void jbl_hash_table_data_free(jbl_hash_table_data *this);
inline void jbl_hash_table_data_init(jbl_hash_table_data *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_string_init(&this->k);
	jbl_var_init(&this->v);
	jbl_var_get_type(&this->v)=JBL_VAR_TYPE_UNUSE;
	this->nxt=((jbl_int64)-1);
}
inline void jbl_hash_table_data_free(jbl_hash_table_data *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_string_free(&this->k);
	jbl_var_free(&this->v);	
	jbl_var_get_type(&this->v)=JBL_VAR_TYPE_UNUSE;
	this->nxt=((jbl_int64)-1);
}
inline void jbl_hash_table_init(jbl_hash_table *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	this->size=0;this->len=0;this->nxt=0;this->data=NULL;
}
void jbl_hash_table_free(jbl_hash_table *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	if(this->size==0)
	{
		this->len=0,this->nxt=0,this->data=NULL;
		return;
	}
	for(register st i=0;i<this->size;jbl_hash_table_data_free(&this->data[i]),++i);	
	jbl_free((char*)this->data-sizeof(st)*this->size),this->data=NULL;
	this->size=0,this->len=0,this->nxt=0;
}
void jbl_hash_table_extend_to(jbl_hash_table *this,st size)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	st old_size=this->size;
	if(size-old_size+this->len<=old_size&&(this->len<=(this->nxt>>1))&&this->data!=NULL)
		return jbl_hash_table_rehash(this);
	if(this->size==0)
		this->size=JBL_HASH_TABLE_MIN_SIZE;
	while(this->size<size)
		this->size<<=1;
	if(this->size<=old_size)
		return;
	if(this->data==NULL)
	{
		this->data=(dt*)(((char*)jbl_malloc(this->size*(sizeof(dt)+sizeof(st))))+sizeof(st)*this->size);
		for(register st i=0;i<this->size;jbl_hash_table_data_init(&this->data[i]),((st*)this->data)[-i-1]=((jbl_int64)-1),++i);
	}
	else
	{
		dt *tmp=(dt*)(((char*)jbl_malloc(this->size*(sizeof(dt)+sizeof(st))))+sizeof(st)*this->size);
		register st old_nxt=this->nxt;
		this->nxt=0;
		for(register st i=0;i<this->size;jbl_hash_table_data_init(&tmp[i]),((st*)tmp)[-i-1]=((jbl_int64)-1),++i);
		for(register st j=0;j<old_nxt;++j)
			if(jbl_var_get_type(&this->data[j].v)!=JBL_VAR_TYPE_UNUSE)
			{
				jbl_int64 h2=gh2(this,tmp[this->nxt].h=this->data[j].h);
				jbl_string_copy(&tmp[this->nxt].k,&this->data[j].k,move);
				jbl_var_copy(&tmp[this->nxt].v,&this->data[j].v,move);
				tmp[this->nxt].nxt=((st*)tmp)[h2];
				((st*)tmp)[h2]=this->nxt;
				++this->nxt;
			}
		if(old_size!=0)
		{
			for(register st i=0;i<old_size;jbl_hash_table_data_free(&this->data[i]),++i);	
			jbl_free((char*)this->data-sizeof(st)*old_size);
		}
		this->data=tmp;
	}	
}
void jbl_hash_table_insert(jbl_hash_table *this,jbl_string *k,jbl_var *v,jbl_uint8 kcpt,jbl_uint8 vcpt)
{
	if(this==NULL||k==NULL||v==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_uint64 h=jbl_string_hash(k);
	jbl_int64 h2=gh2(this,h);
	if(this->data!=NULL)
	{
		if(this->size==0)
			jbl_hash_table_extend(this,0),h2=gh2(this,h);
		for(register st i=((st*)this->data)[h2];i<this->nxt;i=this->data[i].nxt)
			if(h==this->data[i].h&&jbl_string_if_equal(&this->data[i].k,k))
				return jbl_var_copy(&this->data[i].v,v,vcpt);
	}
	jbl_hash_table_extend(this,1);
	h2=gh2(this,h);
	this->data[this->nxt].h=h;
	jbl_string_copy(&this->data[this->nxt].k,k,kcpt);
	jbl_var_copy(&this->data[this->nxt].v,v,vcpt);
	this->data[this->nxt].nxt=((st*)this->data)[h2];
	((st*)this->data)[h2]=this->nxt;
	++this->len;
	++this->nxt;
}
void jbl_hash_table_get(const jbl_hash_table *this,const jbl_string *k,jbl_var *v,jbl_uint8 vcpt)
{
	if(this==NULL||k==NULL||v==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this->size!=0)
	{
		jbl_uint64	h=jbl_string_hash(k);
		jbl_int64	h2=gh2(this,h);
		for(register st i=((st*)this->data)[h2];i<this->nxt;i=this->data[i].nxt)
			if(h==this->data[i].h&&jbl_string_if_equal(&this->data[i].k,k))
				return jbl_var_copy(v,&this->data[i].v,vcpt);
	}
	return jbl_var_init_as(v,JBL_VAR_TYPE_UNUSE);
}
void jbl_hash_table_unset(jbl_hash_table *this,const jbl_string *k)
{
	if(this==NULL||k==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this->size!=0)
	{
		jbl_uint64	h=jbl_string_hash(k);
		jbl_int64	h2=gh2(this,h);
		for(register st i=((st*)this->data)[h2],j=((jbl_int64)-1);i<this->nxt;j=i,i=this->data[i].nxt)
			if(h==this->data[i].h&&jbl_string_if_equal(&this->data[i].k,k))
			{
				if(j==((jbl_int64)-1))
					((st*)this->data)[h2]=this->data[i].nxt;
				else
					this->data[j].nxt=this->data[i].nxt;
				jbl_hash_table_data_free(&this->data[i]);
				--this->len;
				for(;this->nxt!=0&&jbl_var_get_type(&this->data[this->nxt-1].v)==JBL_VAR_TYPE_UNUSE;--this->nxt);;
				return;
			}
	}
}
char jbl_hash_table_space_ship(const jbl_hash_table *this,const jbl_hash_table *that)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this==that)
		return 0;
	if(this->len!=that->len)
		return (this->len>that->len)?(1):(-1);
	jbl_var tv;jbl_var_init(&tv);
	jbl_hash_table_foreach(this,i)
	{
		jbl_hash_table_get(that,&i->k,&tv,light);
		char tmp=jbl_var_space_ship(&i->v,&tv);
		if(!tmp)
			return jbl_var_free(&tv),tmp;
	}
	return jbl_var_free(&tv),0;
}
void jbl_hash_table_clear(jbl_hash_table *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this->len==0||this->data==NULL)
		return;
	if(this->size==0)
	{
		this->len=0,this->nxt=0,this->data=NULL;
		return;
	}	
	for(register st i=0;i<this->size;jbl_hash_table_data_free(&this->data[i]),((st*)this->data)[-i-1]=((jbl_int64)-1),++i);
	this->len=0;
	this->nxt=0;
}
void jbl_hash_table_copy(jbl_hash_table *this,jbl_hash_table *that,jbl_copy_type copytype)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(copytype==copy)
	{
		jbl_hash_table_clear(this);
		jbl_hash_table_extend(this,that->len);
		jbl_hash_table_foreach(that,i)
			jbl_hash_table_insert(this,&i->k,&i->v,copy,copy);
	}
	else
	{		
		jbl_hash_table_free(this);
		this->len=that->len;
		this->nxt=that->nxt;
		this->data=that->data;
		this->size=that->size;
		if(copytype==light)
			this->size=0;
		else
			that->size=0;
	}
}
void jbl_hash_table_merge(jbl_hash_table *this,jbl_hash_table *that,jbl_uint8 copytype)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this->len==0)
		return jbl_hash_table_copy(this,that,copytype);	
	jbl_hash_table_extend(this,that->len);
	jbl_hash_table_foreach(that,i)
		jbl_hash_table_insert(this,&i->k,&i->v,copytype,copytype);
}
jbl_string_size_type jbl_hash_table_from_json_start(jbl_hash_table *this,const jbl_string *in,jbl_string_size_type start)
{
	if(this==NULL||in==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	register jbl_string_size_type i=start,n=jbl_string_get_length(in),ii;
	jbl_string		k;jbl_string_init(&k);
	jbl_var 			v;jbl_var_init(&v);
	jbl_hash_table	t;jbl_hash_table_init(&t);	
	for(;(i<n)&&(!(in->s[i]=='{'));++i);++i;
	jbl_uint64 cnt=0,deep=0;jbl_uint8 str=1;
	for(register jbl_string_size_type j=i;(j<n)&&(!(in->s[j]=='}'&&deep==0));++j)
	{
		if((in->s[j]=='"'&&in->s[j-1]!='\\'))
			str=!str;
		else if(in->s[j]=='{'||in->s[j]=='[')
			deep+=str;
		else if(in->s[j]=='}'||in->s[j]==']')
			deep-=str;
		else if(in->s[j]==','&&deep==0)
			++cnt;
	}
	if(cnt!=0)++cnt;
	jbl_hash_table_extend(&t,cnt);
	while(i<n)
	{
begin:
		jbl_string_clear(&k);
		ii=jbl_string_from_json_start(&k,in,i);
		if(ii==i){for(;i<n;++i)if(in->s[i]=='}')goto success;else if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')goto fail;goto fail;}i=ii;
		for(;(i<n)&&(!(in->s[i]==':'));++i)if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')goto fail;if(i>=n)goto fail;++i;
		ii=jbl_var_from_json_start(&v,in,i);if(ii==i)goto fail;i=ii;
		jbl_hash_table_insert(&t,&k,&v,move,move);
		for(;i<n;++i)
			if(in->s[i]==',')
				{++i;goto begin;}
			else if(in->s[i]=='}')
				goto success;
			else if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')
				goto fail;
		goto fail;
	}
fail:	
	jbl_hash_table_free(&t);jbl_string_free(&k);jbl_var_free(&v);
	return start;
success:
	jbl_hash_table_merge(this,&t,move);
	jbl_hash_table_free(&t);jbl_string_free(&k);jbl_var_free(&v);
	return i+1;
}
void jbl_hash_table_rehash(jbl_hash_table *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this->data==NULL)
		return;
	register st i=0,j=0;
	for(;j<this->nxt&&jbl_var_get_type(&this->data[j].v)!=JBL_VAR_TYPE_UNUSE;++j);	
	for(i=j+1;i<this->nxt;++i)
		if(jbl_var_get_type(&this->data[i].v)!=JBL_VAR_TYPE_UNUSE&&j<i)
		{
			jbl_int64 h2=gh2(this,this->data[j].h=this->data[i].h);
			jbl_string_copy(&this->data[j].k,&this->data[i].k,move);
			jbl_var_copy(&this->data[j].v,&this->data[i].v,move);
			this->data[j].nxt=(((st*)this->data)[h2]>=i)?(this->data[i].nxt):(((st*)this->data)[h2]);
			((st*)this->data)[h2]=j;		
			++j;
			jbl_hash_table_data_free(&this->data[i]);
		}
	this->nxt=j;
}
inline void	jbl_var_equal_hash_table(jbl_var *this,jbl_hash_table *that,jbl_uint8 copytype){jbl_var_init_as(this,JBL_VAR_TYPE_HASH_TABLE);jbl_hash_table_copy(this->data.p,that,copytype);}
#if JBL_STREAM_ENABLE==1
void jbl_hash_table_put(const jbl_hash_table* this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str)
{
	if(this==NULL||output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_int16 tabs=(format>>16);
	
	if(format&1)if(tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);else tabs=-tabs;
	if(type==json)
		jbl_stream_push_char(output_stream,'{');
	else if(type==view)
	{
		jbl_stream_push_chars(output_stream,"jbl_hash_table ");
		if(((jbl_uint16)format>>1)!=0)
			jbl_stream_push_chars(output_stream,str),jbl_stream_push_char(output_stream,' '),jbl_stream_push_uint64(output_stream,((jbl_uint16)format>>1));
		jbl_stream_push_chars(output_stream,"\tlen:");
		jbl_stream_push_uint64(output_stream,this->len);
		jbl_stream_push_chars(output_stream,"\tnxt:");
		jbl_stream_push_uint64(output_stream,this->nxt);
		jbl_stream_push_chars(output_stream,"\tsize:");
		jbl_stream_push_uint64(output_stream,this->size);
	}
	jbl_uint32 format_nxt=(format&1)|((-(tabs+1))<<16);
	jbl_uint8 flag=0;
	jbl_hash_table_foreach(this,i)
	{
		if(type==json&&flag)jbl_stream_push_char(output_stream,',');flag=1;//JSON的逗号
		if(format&1){jbl_stream_push_char(output_stream,'\n');for(jbl_int16 i=0;i<tabs+1;jbl_stream_push_char(output_stream,'\t'),++i);}//格式化的\t和\n
		jbl_string_put(&i->k,output_stream,json,0,NULL);
		jbl_stream_push_char(output_stream,':');
		jbl_var_put(&i->v,output_stream,type,format_nxt,NULL);
	}		
	if(type==json)
	{
		if(format&1){jbl_stream_push_char(output_stream,'\n');for(jbl_int16 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);}
		jbl_stream_push_char(output_stream,'}');
	}	
	
}
#if JBL_STRING_ENABLE==1
void jbl_hash_table_to_json(const jbl_hash_table *this,jbl_string *result)
{
	if(this==NULL||result==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_stream output_stream;
	jbl_string_stream_init(&output_stream,result);
	jbl_hash_table_put(this,&output_stream,json,0,NULL);
	jbl_stream_do(&output_stream,jbl_stream_force);
	jbl_string_stream_free(&output_stream);
}
#endif
#endif
#if JBL_USE_STDARG==1
inline void jbl_hash_table_inits	(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_hash_table_init(va_arg(valist,jbl_hash_table*));va_end(valist);}
inline void jbl_hash_table_frees	(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_hash_table_free(va_arg(valist,jbl_hash_table*));va_end(valist);}
inline void jbl_hash_table_clears(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_hash_table_clear(va_arg(valist,jbl_hash_table*));va_end(valist);}
#endif
#endif