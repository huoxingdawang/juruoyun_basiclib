/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/   
#include "jry_bl_var.h"
#if JRY_BL_VAR_ENABLE==1
#include "jry_bl_link_list.h"
#include "jry_bl_hash_table.h"
#include "jry_bl_file.h"
#include "jry_bl_string.h"
#define ghl(x)		((x->type)&(1<<jry_bl_var_type_bit))
#define gth(x)		((x->type)>>jry_bl_var_type_bit)
#define gop(x,y)	jry_bl_var_functions_struct *x=((gth((y))!=0)?&jry_bl_var_fs[gth((y))][ghl((y))]:((((y)->type>=9)?(&jry_bl_var_functions[(y)->type-9]):NULL)))
const jry_bl_var_functions_struct jry_bl_var_functions[5]=
{
	[JRY_BL_VAR_TYPE_VAR-9]			={(sizeof (jry_bl_var))			,jry_bl_var_init		,jry_bl_var_free		,jry_bl_var_copy		,jry_bl_var_space_ship			,jry_bl_var_put},
#if JRY_BL_STRING_ENABLE==1
	[JRY_BL_VAR_TYPE_STRING-9]		={(sizeof (jry_bl_string))		,jry_bl_string_init		,jry_bl_string_free		,jry_bl_string_copy		,jry_bl_string_space_ship		,jry_bl_string_put},
#endif
#if JRY_BL_LINK_LIST_ENABLE==1	
	[JRY_BL_VAR_TYPE_LINK_LIST-9]	={(sizeof (jry_bl_link_list))	,jry_bl_link_list_init	,jry_bl_link_list_free	,jry_bl_link_list_copy	,jry_bl_link_list_space_ship	,jry_bl_link_list_put},
#endif
#if JRY_BL_HASH_TABLE_ENABLE==1
	[JRY_BL_VAR_TYPE_HASH_TABLE-9]	={(sizeof (jry_bl_hash_table))	,jry_bl_hash_table_init	,jry_bl_hash_table_free	,jry_bl_hash_table_copy	,jry_bl_hash_table_space_ship	,jry_bl_hash_table_put},
#endif
#if JRY_BL_FILE_ENABLE==1
	[JRY_BL_VAR_TYPE_FILE-9]		={(sizeof (jry_bl_file))		,jry_bl_file_init		,jry_bl_file_free		,jry_bl_file_copy		,jry_bl_file_space_ship			,NULL},
#endif
};
jry_bl_var_functions_struct jry_bl_var_tmp_functions[jry_bl_var_tmp_size];
jry_bl_var_functions_struct* jry_bl_var_fs[jry_bl_var_fs_size]={jry_bl_var_functions,jry_bl_var_tmp_functions};
inline void jry_bl_var_init(jry_bl_var *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	this->flags=(int)0;
	this->type=JRY_BL_VAR_TYPE_NULL;
}
inline void jry_bl_var_init_as(jry_bl_var *this,jry_bl_var_type_type type)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	jry_bl_var_free(this);
	this->type=type;
	gop(op,this);
	if(op==NULL||op->init==NULL)return;
	this->data.p=jry_bl_malloc(op->size);
	this->pointer=0;
	op->init(this->data.p);
}
void jry_bl_var_free(jry_bl_var *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	gop(op,this);
	if(op==NULL||op->free==NULL)return;
	op->free(this->data.p);
	if((!this->pointer)&&this->type>=9)
		jry_bl_free(this->data.p);
	this->type=JRY_BL_VAR_TYPE_NULL;
	this->pointer=0;
}
void jry_bl_var_copy(jry_bl_var *this,jry_bl_var *that,jry_bl_copy_type copytype)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	jry_bl_var_init_as(this,that->type);
	this->flags=that->flags;
	gop(op,this);
	if(op==NULL||op->copy==NULL||this->pointer)
		return jry_bl_memory_copy(&this->data,&that->data,sizeof that->data);
	op->copy(this->data.p,that->data.p,copytype);
}
char jry_bl_var_space_ship(const jry_bl_var *this,const jry_bl_var *that)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this==that)
		return 0;
	if(this->type==that->type)
	{
		gop(op,this);
		if(op==NULL||op->space_ship==NULL)
			switch(this->type)
			{
				case JRY_BL_VAR_TYPE_INT64	:return ((this->data.ll<that->data.ll)?(-1):((this->data.ll>that->data.ll)));break;
				case JRY_BL_VAR_TYPE_UINT64	:return ((this->data.ll<that->data.ull)?(-1):((this->data.ll>that->data.ull)));break;
				case JRY_BL_VAR_TYPE_DOUBLE	:return ((this->data.d<that->data.d)?(-1):((this->data.d>that->data.d)));break;
				case JRY_BL_VAR_TYPE_CHAR	:return ((this->data.c<that->data.c)?(-1):((this->data.c>that->data.c)));break;
				default						:return 1;break;
			}
		op->space_ship(this->data.p,that->data.p);	
	}
	else
		return (this->type>that->type)?1:-1;
}
#if JRY_BL_STREAM_ENABLE==1
void jry_bl_var_put(jry_bl_var* this,jry_bl_stream *output_stream,jry_bl_put_type type,jry_bl_uint32 format,char*str)
{
	if(this==NULL||output_stream==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	jry_bl_int16 tabs=(format>>16);
	gop(op,this);
	if(type==json)
	{
		if(op!=NULL&&op->put!=NULL)
			op->put(this->data.p,output_stream,type,format,str);
		else
		{
			if(format&1)if(tabs>=0)for(jry_bl_int16 i=0;i<tabs;jry_bl_stream_push_char(output_stream,'\t'),++i);else tabs=-tabs;
			switch(this->type)
			{
				case JRY_BL_VAR_TYPE_NULL	:jry_bl_stream_push_char_pointer(output_stream,"null")		;break;
				case JRY_BL_VAR_TYPE_TRUE	:jry_bl_stream_push_uint64	(output_stream,1)				;break;
				case JRY_BL_VAR_TYPE_FALSE	:jry_bl_stream_push_uint64	(output_stream,0)				;break;
				case JRY_BL_VAR_TYPE_INT64	:jry_bl_stream_push_int64	(output_stream,this->data.ll)	;break;
				case JRY_BL_VAR_TYPE_UINT64	:jry_bl_stream_push_uint64	(output_stream,this->data.ull)	;break;
				case JRY_BL_VAR_TYPE_DOUBLE	:jry_bl_stream_push_double	(output_stream,this->data.d)	;break;
				case JRY_BL_VAR_TYPE_CHAR	:jry_bl_stream_push_char	(output_stream,this->data.c)	;break;
			}	
		}			
	}
	else if(type==view)
	{
		if(op==NULL||op->put==NULL)
		{
			if(format&1)if(tabs>=0)for(jry_bl_int16 i=0;i<tabs;jry_bl_stream_push_char(output_stream,'\t'),++i);else tabs=-tabs;
			switch(this->type)
			{		
				case JRY_BL_VAR_TYPE_UNUSE	:jry_bl_stream_push_char_pointer(output_stream,"unuse             ");break;
				case JRY_BL_VAR_TYPE_NULL	:jry_bl_stream_push_char_pointer(output_stream,"null              ");break;
				case JRY_BL_VAR_TYPE_TRUE	:jry_bl_stream_push_char_pointer(output_stream,"true              ");break;
				case JRY_BL_VAR_TYPE_FALSE	:jry_bl_stream_push_char_pointer(output_stream,"false             ");break;
				case JRY_BL_VAR_TYPE_INT64	:jry_bl_stream_push_char_pointer(output_stream,"int64             ");break;
				case JRY_BL_VAR_TYPE_UINT64	:jry_bl_stream_push_char_pointer(output_stream,"uint64            ");break;
				case JRY_BL_VAR_TYPE_DOUBLE	:jry_bl_stream_push_char_pointer(output_stream,"double            ");break;
				case JRY_BL_VAR_TYPE_CHAR	:jry_bl_stream_push_char_pointer(output_stream,"char              ");break;
				case JRY_BL_VAR_TYPE_POINTER:jry_bl_stream_push_char_pointer(output_stream,"pointer           ");break;
			}
			if(((jry_bl_uint16)format>>1)!=0)
				jry_bl_stream_push_char_pointer(output_stream,str),jry_bl_stream_push_char(output_stream,' '),jry_bl_stream_push_uint64(output_stream,((jry_bl_uint16)format>>1));
			switch(this->type)
			{		
				case JRY_BL_VAR_TYPE_INT64	:jry_bl_stream_push_int64	(output_stream,this->data.ll)	;break;
				case JRY_BL_VAR_TYPE_UINT64	:jry_bl_stream_push_uint64	(output_stream,this->data.ull)	;break;
				case JRY_BL_VAR_TYPE_DOUBLE	:jry_bl_stream_push_double	(output_stream,this->data.d)	;break;
				case JRY_BL_VAR_TYPE_CHAR	:jry_bl_stream_push_char	(output_stream,this->data.c)	;break;
			}			
		}
		else
			op->put(this->data.p,output_stream,type,format,str);
	}
}
#if JRY_BL_STRING_ENABLE==1
void jry_bl_var_to_json(const jry_bl_var *this,jry_bl_string *result)
{
	if(this==NULL||result==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	jry_bl_stream output_stream;
	jry_bl_string_stream_init(&output_stream,result);
	jry_bl_var_put(this,&output_stream,json,0,NULL);
	jry_bl_stream_do(&output_stream,jry_bl_stream_force);
	jry_bl_string_stream_free(&output_stream);
}
#endif
#endif
#if JRY_BL_STRING_ENABLE==1
jry_bl_string_size_type jry_bl_var_from_json_start(jry_bl_var *this,const jry_bl_string *in,jry_bl_string_size_type start)
{
	if(this==NULL||in==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	for(jry_bl_string_size_type n=jry_bl_string_get_length(in),i=start,ii;i<n;++i)
	{
		register unsigned char c=jry_bl_string_get1(in,i);
		if(c=='"'&&(i==0||jry_bl_string_get1(in,i-1)!='\\'))
		{
			jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);
			return ((ii=jry_bl_string_from_json_start(this->data.p,in,i))==i)?(jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_NULL),start):ii;
		}
		else if(c=='{')
		{
			jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_HASH_TABLE);
			return ((ii=jry_bl_hash_table_from_json_start(this->data.p,in,i))==i)?(jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_NULL),start):ii;
		}
		else if(c=='[')
		{
			jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_LINK_LIST);
			return ((ii=jry_bl_link_list_from_json_start(this->data.p,in,i))==i)?(jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_NULL),start):ii;
		}
		else if(c=='n'&&(i+3)<n&&jry_bl_string_get1(in,i+1)=='u'&&jry_bl_string_get1(in,i+2)=='l'&&jry_bl_string_get1(in,i+3)=='l')
			return jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_NULL),i+4;
		else if(c=='-')
		{
			jry_bl_string_size_type i1=i,i2=i;
			jry_bl_int64	t1=jry_bl_string_get_int64_start(in,&i1);
			double			t2=jry_bl_string_get_double_start(in,&i2);
			if(i1==i2)
				return jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_INT64),this->data.ll=t1,i1;
			else if(i1<i2)
				return jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_DOUBLE),this->data.d=t2,i2;
			return start;
		}
		else if(c>='0'&&c<='9')
		{
			jry_bl_string_size_type i1=i,i2=i;
			jry_bl_uint64	t1=jry_bl_string_get_uint64_start(in,&i1);
			double			t2=jry_bl_string_get_double_start(in,&i2);
			if(i1==i2)
				return jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_UINT64),this->data.ull=t1,i1;
			else if(i1<i2)
				return jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_DOUBLE),this->data.d=t2,i2;
			return start;
		}
		else if(c!=' '&&c!='\r'&&c!='\t'&&c!='\n')
			return start;
	}
	return start;
}
#endif
#if JRY_BL_USE_STDARG==1
inline void jry_bl_var_inits(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_var_init(va_arg(valist,jry_bl_var*));va_end(valist);}
inline void jry_bl_var_frees(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_var_free(va_arg(valist,jry_bl_var*));va_end(valist);}
#if JRY_BL_STREAM_ENABLE==1
inline void jry_bl_var_views(int n,...){va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_var_put(va_arg(valist,jry_bl_var*),&jry_bl_stream_stdout,view,(jry_bl_view_default_tabs_num<<16)|1,""),jry_bl_stream_push_char(&jry_bl_stream_stdout,'\n');jry_bl_stream_do(&jry_bl_stream_stdout,1);va_end(valist);}
#endif
#endif
#endif