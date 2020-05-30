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
#include "jbl_exception.h"
#include "jbl_ht.h"
#include "jbl_file.h"
#include "jbl_malloc.h"
#if JBL_STRING_ENABLE==1
#include "jbl_string.h"
#endif
#if JBL_LL_ENABLE==1
#include "jbl_ll.h"
#endif
#if JBL_HT_ENABLE==1
#include "jbl_ht.h"
#endif

inline jbl_var * jbl_var_free(jbl_var * this){if(!this)return;void*(*free)(void*)=jbl_var_get_operators(this)->free;if(free)free(this);}
inline jbl_var * jbl_var_copy(jbl_var * this){if(!this)return;void*(*copy)(void*)=jbl_var_get_operators(this)->copy;if(copy)copy(this);}
inline char      jbl_var_space_ship(const jbl_var * this,const jbl_var * that){if(this==that){return 0;}if(this==NULL){return -1;}if(that==NULL){return 1;}void*(*space_ship)(const void*,const void*)=jbl_var_get_operators(this)->space_ship;if(space_ship)return space_ship(this,that);}


#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
jbl_string * jbl_var_json_encode(const jbl_var * this,jbl_string *out,char format,jbl_int32 tabs)
{
	if(!this)
	{
		if(out==NULL)out=jbl_string_new();
		out=jbl_refer_pull(out);
		if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;out=jbl_string_add_char(out,'\t'),++i);	
		return jbl_string_add_chars_length(out,(unsigned char *)"null",4);
	}
	jbl_string*(*json_encode)(const void*,jbl_string *,char,jbl_int32)=jbl_var_get_operators(this)->json_encode;
	if(json_encode)return json_encode(this,out,format,tabs);
	return out;
}
jbl_var* jbl_var_json_decode(jbl_var *this,const jbl_string* in,jbl_string_size_type *start)
{
	in=jbl_refer_pull(in);
	jbl_string_size_type i=start?(*start):0,n=in->len,j;
	for(;i<n&&in->s[i]<=32;++i);
	jbl_var *v1=NULL,*v2=NULL;
	switch(in->s[i])
	{
#if JBL_STRING_ENABLE==1
		case '"':
			start?(*start=i):0;start=start?start:&i;
			v2=(jbl_var *)jbl_string_json_decode(v1=jbl_Vstring_new(),in,start);
			if(!v2)v1=v2=jbl_var_free(v1);
			return v2;
			break;
#endif
#if JBL_LL_ENABLE==1
		case '[':
			start?(*start=i):0;start=start?start:&i;
			v2=(jbl_var *)jbl_ll_json_decode(v1=jbl_Vll_new(),in,start);
			if(!v2)v1=v2=jbl_var_free(v1);
			return v2;
			break;
#endif
#if JBL_HT_ENABLE==1
		case '{':
			start?(*start=i):0;start=start?start:&i;
			v2=(jbl_var *)jbl_ht_json_decode(v1=jbl_Vht_new(),in,start);
			if(!v2)v1=v2=jbl_var_free(v1);
			return v2;
			break;
#endif
		case 'n':
			if((i+3)<n&&in->s[i+1]=='u'&&in->s[i+2]=='l'&&in->s[i+3]=='l')
			{
				i+=4;
				start?(*start=i):0;
				return jbl_Vnull_new();
			}
			else
				return NULL;
			break;
		case 't':
			if((i+3)<n&&in->s[i+1]=='r'&&in->s[i+2]=='u'&&in->s[i+3]=='e')
			{
				i+=4;
				start?(*start=i):0;
				return jbl_Vtrue_new();
			}
			else
				return NULL;
			break;
		case 'f':
			if((i+4)<n&&in->s[i+1]=='a'&&in->s[i+2]=='l'&&in->s[i+3]=='s'&&in->s[i+4]=='e')
			{
				i+=5;
				start?(*start=i):0;
				return jbl_Vfalse_new();
			}
			else
				return NULL;
			break;			
		case '0':
			if((i+1)<n&&(in->s[i+1]=='x'||in->s[i+1]=='X'))
			{
				i+=2;
				start?(*start=i):0;start=start?start:&i;
				return jbl_Vuint_set(NULL,jbl_string_get_hex_start(in,start));
			}
		case '1':case '2':case '3':case '4':case '5':
		case '6':case '7':case '8':case '9':case '-':
			{
				start?(*start=i):0;start=start?start:&i;
				return jbl_string_get_number_start(in,start);				
			}
			break;
	}
	return NULL;
	
}
#endif
#endif
#if JBL_STREAM_ENABLE==1
void jbl_var_view_put(const jbl_var * this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	jbl_uint8 pt=0;
	if(this==NULL)
	{
		pt=1;
		goto print;
	}
	void(*view_put)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32)=jbl_var_get_operators(this)->view_put;
	if(view_put)view_put(this,output_stream,format,str,tabs);
	else goto print;
	return;
print:;
	output_stream=jbl_refer_pull(output_stream);
	this=jbl_refer_pull(this);
	if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char_force(output_stream,'\t'),++i);	
	switch(pt)
	{
		case 1	:jbl_stream_push_chars(output_stream,"null          ")		;break;
		default	:jbl_stream_push_chars(output_stream,"unprintable   ")	;break;
	}		
	if(format&&str)jbl_stream_push_chars(output_stream,str),jbl_stream_push_char_force(output_stream,' '),(format!=-1?jbl_stream_push_uint64(output_stream,format):0);
}
#if JBL_JSON_ENABLE==1
void jbl_var_json_put(const jbl_var * this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{
	if(output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(!this){output_stream=jbl_refer_pull(output_stream);if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char_force(output_stream,'\t'),++i);return jbl_stream_push_chars(output_stream,"null");}
	void(*json_put)(const void*,jbl_stream *,char,jbl_int32)=jbl_var_get_operators(this)->json_put;
	if(json_put)json_put(this,output_stream,format,tabs);
}
#endif
#endif
jbl_var * __jbl_var_data_free(jbl_var *this)
{
	if(this==NULL)return NULL;
	jbl_gc_minus(((jbl_var_data*)this));
	if(!jbl_gc_reference_cnt(((jbl_var_data*)this)))
	{
		((jbl_gc_is_ref(((jbl_var_data*)this)))?__jbl_var_data_free((jbl_var *)jbl_refer_pull(this)):0);
		jbl_free((char*)this-sizeof(jbl_var));
	}
	return NULL;
}
jbl_var * __jbl_var_data_new(const jbl_var_operators *ops)
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_var_data))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_gc_init(((jbl_var_data*)this));
	jbl_gc_plus(((jbl_var_data*)this));//增加引用计数
	jbl_gc_set_var(((jbl_var_data*)this));
	jbl_var_set_operators(this,ops);
	return this;
}
inline jbl_var * jbl_Vuint_new(){return __jbl_var_data_new(&jbl_uint_operators);}
inline jbl_var * jbl_Vuint_set(jbl_var * this,jbl_uint64 data)
{
	if(!this)this=jbl_Vuint_new();
	((jbl_var_data*)jbl_refer_pull(this))->u=data;
	return this;
}
inline jbl_var * jbl_Vuint_copy(jbl_var * that)
{
	return jbl_Vuint_set(NULL,((jbl_var_data*)jbl_refer_pull(that))->u);
}
inline char jbl_Vuint_space_ship(jbl_var * this,jbl_var * that)
{
	jbl_uint64 a=((jbl_var_data*)jbl_refer_pull(this))->u,b=((jbl_var_data*)jbl_refer_pull(that))->u;
	return (a>b?1:(a<b?-1:0));
}
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
jbl_string* jbl_Vuint_json_encode(const jbl_var* this,jbl_string *out,char format,jbl_int32 tabs)
{
	out=jbl_string_json_put_format(this=jbl_refer_pull(this),out,format,&tabs);if(!this)return out;
	return jbl_string_add_uint64(out,((jbl_var_data*)this)->u);
}
#endif 
#endif 
#if JBL_STREAM_ENABLE==1
void jbl_Vuint_view_put(const jbl_var* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	if(jbl_stream_view_put_format(this=jbl_refer_pull(this),output_stream,"uint64        ",format,str,&tabs))return;
	jbl_stream_push_char(output_stream,':');
	jbl_stream_push_uint64(output_stream,((jbl_var_data*)this)->u);
}
#if JBL_JSON_ENABLE==1
void jbl_Vuint_json_put(const jbl_var* this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{
	if(jbl_stream_json_put_format(this=jbl_refer_pull(this),output_stream,format,&tabs))return;
	jbl_stream_push_uint64(output_stream,((jbl_var_data*)this)->u);
}
#endif
#endif
const jbl_var_operators jbl_uint_operators={
	(void* (*)(void *))__jbl_var_data_free,
	(void* (*)(void *))jbl_Vuint_copy,
	(char  (*)(const void*,const void*))jbl_Vuint_space_ship,
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_Vuint_json_encode,
#endif
#endif
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_Vuint_view_put,
#if JBL_JSON_ENABLE==1
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_Vuint_json_put,
#endif
#endif
};
inline jbl_var * jbl_Vint_new(){return __jbl_var_data_new(&jbl_int_operators);}
inline jbl_var * jbl_Vint_set(jbl_var * this,jbl_int64 data)
{
	if(!this)this=jbl_Vint_new();
	((jbl_var_data*)jbl_refer_pull(this))->i=data;
	return this;
}
inline jbl_var * jbl_Vint_copy(jbl_var * that)
{
	return jbl_Vint_set(NULL,((jbl_var_data*)jbl_refer_pull(that))->i);
}
inline char jbl_Vint_space_ship(jbl_var * this,jbl_var * that)
{
	jbl_int64 a=((jbl_var_data*)jbl_refer_pull(this))->i,b=((jbl_var_data*)jbl_refer_pull(that))->i;
	return (a>b?1:(a<b?-1:0));
}
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
jbl_string* jbl_Vint_json_encode(const jbl_var* this,jbl_string *out,char format,jbl_int32 tabs)
{
	out=jbl_string_json_put_format(this=jbl_refer_pull(this),out,format,&tabs);if(!this)return out;
	return jbl_string_add_int64(out,((jbl_var_data*)this)->i);
}
#endif 
#endif 
#if JBL_STREAM_ENABLE==1
void jbl_Vint_view_put(const jbl_var* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	if(jbl_stream_view_put_format(this=jbl_refer_pull(this),output_stream,"int64         ",format,str,&tabs))return;
	jbl_stream_push_char(output_stream,':');
	jbl_stream_push_int64(output_stream,((jbl_var_data*)this)->i);
}
#if JBL_JSON_ENABLE==1
void jbl_Vint_json_put(const jbl_var* this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{
	if(jbl_stream_json_put_format(this=jbl_refer_pull(this),output_stream,format,&tabs))return;
	jbl_stream_push_int64(output_stream,((jbl_var_data*)this)->i);
}
#endif
#endif
const jbl_var_operators jbl_int_operators={
	(void* (*)(void *))__jbl_var_data_free,
	(void* (*)(void *))jbl_Vint_copy,
	(char  (*)(const void*,const void*))jbl_Vint_space_ship,
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_Vint_json_encode,
#endif
#endif
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_Vint_view_put,
#if JBL_JSON_ENABLE==1
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_Vint_json_put,
#endif
#endif
};
inline jbl_var * jbl_Vdouble_new(){return __jbl_var_data_new(&jbl_double_operators);}
inline jbl_var * jbl_Vdouble_set(jbl_var * this,double data)
{
	if(!this)this=jbl_Vdouble_new();
	((jbl_var_data*)jbl_refer_pull(this))->d=data;
	return this;
}
inline jbl_var * jbl_Vdouble_copy(jbl_var * that)
{
	return jbl_Vdouble_set(NULL,((jbl_var_data*)jbl_refer_pull(that))->d);
}
inline char jbl_Vdouble_space_ship(jbl_var * this,jbl_var * that)
{
	double a=((jbl_var_data*)jbl_refer_pull(this))->d,b=((jbl_var_data*)jbl_refer_pull(that))->d;
	return (a>b?1:(a<b?-1:0));
}
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
jbl_string* jbl_Vdouble_json_encode(const jbl_var* this,jbl_string *out,char format,jbl_int32 tabs)
{
	out=jbl_string_json_put_format(this=jbl_refer_pull(this),out,format,&tabs);if(!this)return out;
	return jbl_string_add_double(out,((jbl_var_data*)this)->d);
}
#endif 
#endif 
#if JBL_STREAM_ENABLE==1
void jbl_Vdouble_view_put(const jbl_var* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	if(jbl_stream_view_put_format(this=jbl_refer_pull(this),output_stream,"double        ",format,str,&tabs))return;
	jbl_stream_push_char(output_stream,':');
	jbl_stream_push_double(output_stream,((jbl_var_data*)this)->d);	
}
#if JBL_JSON_ENABLE==1
void jbl_Vdouble_json_put(const jbl_var* this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{
	if(jbl_stream_json_put_format(this=jbl_refer_pull(this),output_stream,format,&tabs))return;
	jbl_stream_push_double(output_stream,((jbl_var_data*)this)->d);
}
#endif
#endif
const jbl_var_operators jbl_double_operators={
	(void* (*)(void *))__jbl_var_data_free,
	(void* (*)(void *))jbl_Vdouble_copy,
	(char  (*)(const void*,const void*))jbl_Vdouble_space_ship,
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_Vdouble_json_encode,
#endif
#endif
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_Vdouble_view_put,
#if JBL_JSON_ENABLE==1
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_Vdouble_json_put,
#endif
#endif
};
inline jbl_var * jbl_Vnull_new(){jbl_var *this=__jbl_var_data_new(&jbl_ntf_operators);((jbl_var_data*)this)->u=0;return this;}
inline jbl_var * jbl_Vtrue_new(){jbl_var *this=__jbl_var_data_new(&jbl_ntf_operators);((jbl_var_data*)this)->u=2;return this;}
inline jbl_var * jbl_Vfalse_new(){jbl_var *this=__jbl_var_data_new(&jbl_ntf_operators);((jbl_var_data*)this)->u=1;return this;}

// NULL true 和 false类型共享同一组操作符,合称ntf,具体类型由u中值确定,0为NULL,1为false,2为true
inline jbl_var * jbl_Vntf_copy(jbl_var * that)
{
	jbl_var *this=jbl_Vnull_new();
	((jbl_var_data*)jbl_refer_pull(this))->u=((jbl_var_data*)jbl_refer_pull(that))->u;
	return this;
}
inline char jbl_Vntf_space_ship(jbl_var * this,jbl_var * that)
{
	jbl_uint64 a=((jbl_var_data*)jbl_refer_pull(this))->u,b=((jbl_var_data*)jbl_refer_pull(that))->u;
	return (a>b?1:(a<b?-1:0));
}
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
jbl_string* jbl_Vntf_json_encode(const jbl_var* this,jbl_string *out,char format,jbl_int32 tabs)
{
	out=jbl_string_json_put_format(this=jbl_refer_pull(this),out,format,&tabs);if(!this)return out;
	switch(((jbl_var_data*)jbl_refer_pull(this))->u)
	{
		case 0:	return jbl_string_add_chars(out,"null")	;break;
		case 2:	return jbl_string_add_chars(out,"true")	;break;
		case 1:	return jbl_string_add_chars(out,"false");break;
	}
}
#endif 
#endif 
#if JBL_STREAM_ENABLE==1
void jbl_Vntf_view_put(const jbl_var* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	switch(((jbl_var_data*)jbl_refer_pull(this))->u)
	{
		case 0:	jbl_stream_view_put_format(this,output_stream,"null          ",format,str,&tabs);break;
		case 2:	jbl_stream_view_put_format(this,output_stream,"true          ",format,str,&tabs);break;
		case 1:	jbl_stream_view_put_format(this,output_stream,"false         ",format,str,&tabs);break;
	}
}
#if JBL_JSON_ENABLE==1
void jbl_Vntf_json_put(const jbl_var* this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{
	if(jbl_stream_json_put_format(this=jbl_refer_pull(this),output_stream,format,&tabs))return;
	switch(((jbl_var_data*)jbl_refer_pull(this))->u)
	{
		case 0:	jbl_stream_push_chars(output_stream,"null")	;break;
		case 2:	jbl_stream_push_chars(output_stream,"true")	;break;
		case 1:	jbl_stream_push_chars(output_stream,"false");break;
	}
}
#endif
#endif
const jbl_var_operators jbl_ntf_operators={
	(void* (*)(void *))__jbl_var_data_free,
	(void* (*)(void *))jbl_Vntf_copy,
	(char  (*)(const void*,const void*))jbl_Vntf_space_ship,
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_Vntf_json_encode,
#endif
#endif
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_Vntf_view_put,
#if JBL_JSON_ENABLE==1
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_Vntf_json_put,
#endif
#endif
};

#endif