/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/   
#include "jbl_var.h"
#if JBL_VAR_ENABLE==1
#if JBL_USE_STDARG==1
#include <stdarg.h>
#endif
#include "jbl_exception.h"
#include "jbl_link_list.h"
#include "jbl_hash_table.h"
#include "jbl_file.h"
#include "jbl_malloc.h"
#include "jbl_string.h"


inline jbl_var * jbl_var_free(jbl_var * this){void*(*free)(void*)=jbl_var_get_operators(this)->free;if(free)free(this);}
inline jbl_var * jbl_var_copy(jbl_var * this){void*(*copy)(void*)=jbl_var_get_operators(this)->copy;if(copy)copy(this);}


#if JBL_STREAM_ENABLE==1
inline jbl_var * jbl_var_put(jbl_var * this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str){void(*put)(const void*,jbl_stream *,jbl_put_type,jbl_uint32,char*)=jbl_var_get_operators(this)->put;if(put)put(this,output_stream,type,format,str);}
#endif




/*
#define ghl(x)		((x->type)&(1<<jbl_var_type_bit))
#define gth(x)		((x->type)>>jbl_var_type_bit)
#define gop(x,y)	jbl_var_functions_struct *x=((gth((y))!=0)?&jbl_var_fs[gth((y))][ghl((y))]:((((y)->type>=9)?(&jbl_var_functions[(y)->type-9]):NULL)))


#if JBL_STREAM_ENABLE==1	
	#define __r(a,b,c,d,e,f)	a,b,c,d,e,f
#else
	#define __r(a,b,c,d,e,f)	a,b,c,d,e
#endif

const jbl_var_functions_struct jbl_var_functions[5]=
{
	[JBL_VAR_TYPE_VAR-9]			={__r((sizeof (jbl_var))			,jbl_var_init		,jbl_var_free		,jbl_var_copy		,jbl_var_space_ship			,jbl_var_put)},
#if JBL_STRING_ENABLE==1
	[JBL_VAR_TYPE_STRING-9]		={__r((sizeof (jbl_string))		,jbl_string_init		,jbl_string_free		,jbl_string_copy		,jbl_string_space_ship		,jbl_string_put)},
#endif
#if JBL_LINK_LIST_ENABLE==1	
	[JBL_VAR_TYPE_LINK_LIST-9]	={__r((sizeof (jbl_link_list))	,jbl_link_list_init	,jbl_link_list_free	,jbl_link_list_copy	,jbl_link_list_space_ship	,jbl_link_list_put)},
#endif
#if JBL_HASH_TABLE_ENABLE==1
	[JBL_VAR_TYPE_HASH_TABLE-9]	={__r((sizeof (jbl_hash_table))	,jbl_hash_table_init	,jbl_hash_table_free	,jbl_hash_table_copy	,jbl_hash_table_space_ship	,jbl_hash_table_put)},
#endif
#if JBL_FILE_ENABLE==1
	[JBL_VAR_TYPE_FILE-9]		={__r((sizeof (jbl_file))		,jbl_file_init		,jbl_file_free		,jbl_file_copy		,jbl_file_space_ship			,NULL)},
#endif
};
jbl_var_functions_struct jbl_var_tmp_functions[jbl_var_tmp_size];
jbl_var_functions_struct* jbl_var_fs[jbl_var_fs_size]={jbl_var_functions,jbl_var_tmp_functions};
inline void jbl_var_init(jbl_var *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	this->flags=(int)0;
	this->type=JBL_VAR_TYPE_NULL;
}
inline void jbl_var_init_as(jbl_var *this,jbl_var_type_type type)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_var_free(this);
	this->type=type;
	gop(op,this);
	if(op==NULL||op->init==NULL)return;
	this->data.p=jbl_malloc(op->size);
	this->pointer=0;
	op->init(this->data.p);
}
void jbl_var_free(jbl_var *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	gop(op,this);
	if(op==NULL||op->free==NULL)return;
	op->free(this->data.p);
	if((!this->pointer)&&this->type>=9)
		jbl_free(this->data.p);
	this->type=JBL_VAR_TYPE_NULL;
	this->pointer=0;
}
void jbl_var_copy(jbl_var *this,jbl_var *that,jbl_copy_type copytype)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_var_init_as(this,that->type);
	this->flags=that->flags;
	gop(op,this);
	if(op==NULL||op->copy==NULL||this->pointer)
		return jbl_memory_copy(&this->data,&that->data,sizeof that->data);
	op->copy(this->data.p,that->data.p,copytype);
}
char jbl_var_space_ship(const jbl_var *this,const jbl_var *that)
{
	if(this==NULL||that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(this==that)
		return 0;
	if(this->type==that->type)
	{
		gop(op,this);
		if(op==NULL||op->space_ship==NULL)
			switch(this->type)
			{
				case JBL_VAR_TYPE_INT64	:return ((this->data.ll<that->data.ll)?(-1):((this->data.ll>that->data.ll)));break;
				case JBL_VAR_TYPE_UINT64	:return ((this->data.ll<that->data.ull)?(-1):((this->data.ll>that->data.ull)));break;
				case JBL_VAR_TYPE_DOUBLE	:return ((this->data.d<that->data.d)?(-1):((this->data.d>that->data.d)));break;
				case JBL_VAR_TYPE_CHAR	:return ((this->data.c<that->data.c)?(-1):((this->data.c>that->data.c)));break;
				default						:return 1;break;
			}
		op->space_ship(this->data.p,that->data.p);	
	}
	else
		return (this->type>that->type)?1:-1;
}
#if JBL_STREAM_ENABLE==1
void jbl_var_put(jbl_var* this,jbl_stream *output_stream,jbl_put_type type,jbl_uint32 format,char*str)
{
	if(this==NULL||output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	jbl_int16 tabs=(format>>16);
	gop(op,this);
	if(type==json)
	{
		if(op!=NULL&&op->put!=NULL)
			op->put(this->data.p,output_stream,type,format,str);
		else
		{
			if(format&1)if(tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);else tabs=-tabs;
			switch(this->type)
			{
				case JBL_VAR_TYPE_NULL	:jbl_stream_push_chars(output_stream,"null")		;break;
				case JBL_VAR_TYPE_TRUE	:jbl_stream_push_uint64	(output_stream,1)				;break;
				case JBL_VAR_TYPE_FALSE	:jbl_stream_push_uint64	(output_stream,0)				;break;
				case JBL_VAR_TYPE_INT64	:jbl_stream_push_int64	(output_stream,this->data.ll)	;break;
				case JBL_VAR_TYPE_UINT64	:jbl_stream_push_uint64	(output_stream,this->data.ull)	;break;
				case JBL_VAR_TYPE_DOUBLE	:jbl_stream_push_double	(output_stream,this->data.d)	;break;
				case JBL_VAR_TYPE_CHAR	:jbl_stream_push_char	(output_stream,this->data.c)	;break;
			}	
		}			
	}
	else if(type==view)
	{
		if(op==NULL||op->put==NULL)
		{
			if(format&1)if(tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char(output_stream,'\t'),++i);else tabs=-tabs;
			switch(this->type)
			{		
				case JBL_VAR_TYPE_UNUSE	:jbl_stream_push_chars(output_stream,"unuse             ");break;
				case JBL_VAR_TYPE_NULL	:jbl_stream_push_chars(output_stream,"null              ");break;
				case JBL_VAR_TYPE_TRUE	:jbl_stream_push_chars(output_stream,"true              ");break;
				case JBL_VAR_TYPE_FALSE	:jbl_stream_push_chars(output_stream,"false             ");break;
				case JBL_VAR_TYPE_INT64	:jbl_stream_push_chars(output_stream,"int64             ");break;
				case JBL_VAR_TYPE_UINT64	:jbl_stream_push_chars(output_stream,"uint64            ");break;
				case JBL_VAR_TYPE_DOUBLE	:jbl_stream_push_chars(output_stream,"double            ");break;
				case JBL_VAR_TYPE_CHAR	:jbl_stream_push_chars(output_stream,"char              ");break;
				case JBL_VAR_TYPE_POINTER:jbl_stream_push_chars(output_stream,"pointer           ");break;
			}
			if(((jbl_uint16)format>>1)!=0)
				jbl_stream_push_chars(output_stream,str),jbl_stream_push_char(output_stream,' '),jbl_stream_push_uint64(output_stream,((jbl_uint16)format>>1));
			switch(this->type)
			{		
				case JBL_VAR_TYPE_INT64	:jbl_stream_push_int64	(output_stream,this->data.ll)	;break;
				case JBL_VAR_TYPE_UINT64	:jbl_stream_push_uint64	(output_stream,this->data.ull)	;break;
				case JBL_VAR_TYPE_DOUBLE	:jbl_stream_push_double	(output_stream,this->data.d)	;break;
				case JBL_VAR_TYPE_CHAR	:jbl_stream_push_char	(output_stream,this->data.c)	;break;
			}			
		}
		else
			op->put(this->data.p,output_stream,type,format,str);
	}
}
#if JBL_STRING_ENABLE==1
void jbl_var_to_json(const jbl_var *this,jbl_string *result)
{
	if(this==NULL||result==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	jbl_stream output_stream;
	jbl_string_stream_init(&output_stream,result);
	jbl_var_put(this,&output_stream,json,0,NULL);
	jbl_stream_do(&output_stream,jbl_stream_force);
	jbl_string_stream_free(&output_stream);
}
#endif
#endif
#if JBL_STRING_ENABLE==1
jbl_string_size_type jbl_var_from_json_start(jbl_var *this,const jbl_string *in,jbl_string_size_type start)
{
	if(this==NULL||in==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	for(jbl_string_size_type n=jbl_string_get_length(in),i=start,ii;i<n;++i)
	{
		register unsigned char c=jbl_string_get1(in,i);
		if(c=='n'&&(i+3)<n&&jbl_string_get1(in,i+1)=='u'&&jbl_string_get1(in,i+2)=='l'&&jbl_string_get1(in,i+3)=='l')
			return jbl_var_init_as(this,JBL_VAR_TYPE_NULL),i+4;
#if JBL_STRING_ENABLE==1		
		else if(c=='"'&&(i==0||jbl_string_get1(in,i-1)!='\\'))
		{
			jbl_var_init_as(this,JBL_VAR_TYPE_STRING);
			return ((ii=jbl_string_from_json_start(this->data.p,in,i))==i)?(jbl_var_init_as(this,JBL_VAR_TYPE_NULL),start):ii;
		}
#endif
#if JBL_HASH_TABLE_ENABLE==1		
		else if(c=='{')
		{
			jbl_var_init_as(this,JBL_VAR_TYPE_HASH_TABLE);
			return ((ii=jbl_hash_table_from_json_start(this->data.p,in,i))==i)?(jbl_var_init_as(this,JBL_VAR_TYPE_NULL),start):ii;
		}
#endif
#if JBL_LINK_LIST_ENABLE==1
		
		else if(c=='[')
		{
			jbl_var_init_as(this,JBL_VAR_TYPE_LINK_LIST);
			return ((ii=jbl_link_list_from_json_start(this->data.p,in,i))==i)?(jbl_var_init_as(this,JBL_VAR_TYPE_NULL),start):ii;
		}
#endif
		else if(c=='-')
		{
			jbl_string_size_type i1=i,i2=i;
			jbl_int64	t1=jbl_string_get_int64_start(in,&i1);
			double			t2=jbl_string_get_double_start(in,&i2);
			if(i1==i2)
				return jbl_var_init_as(this,JBL_VAR_TYPE_INT64),this->data.ll=t1,i1;
			else if(i1<i2)
				return jbl_var_init_as(this,JBL_VAR_TYPE_DOUBLE),this->data.d=t2,i2;
			return start;
		}
		else if(c>='0'&&c<='9')
		{
			jbl_string_size_type i1=i,i2=i;
			jbl_uint64	t1=jbl_string_get_uint64_start(in,&i1);
			double			t2=jbl_string_get_double_start(in,&i2);
			if(i1==i2)
				return jbl_var_init_as(this,JBL_VAR_TYPE_UINT64),this->data.ull=t1,i1;
			else if(i1<i2)
				return jbl_var_init_as(this,JBL_VAR_TYPE_DOUBLE),this->data.d=t2,i2;
			return start;
		}
		else if(c!=' '&&c!='\r'&&c!='\t'&&c!='\n')
			return start;
	}
	return start;
}
#endif
#if JBL_USE_STDARG==1
inline void jbl_var_inits(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_var_init(va_arg(valist,jbl_var*));va_end(valist);}
inline void jbl_var_frees(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_var_free(va_arg(valist,jbl_var*));va_end(valist);}
#if JBL_STREAM_ENABLE==1
inline void jbl_var_views(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_var_put(va_arg(valist,jbl_var*),&jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|1,""),jbl_stream_push_char(&jbl_stream_stdout,'\n');jbl_stream_do(&jbl_stream_stdout,1);va_end(valist);}
#endif

#endif
*/
#endif