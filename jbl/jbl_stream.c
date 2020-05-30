/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_stream.h"
#if JBL_STREAM_ENABLE==1
#if JBL_VAR_ENABLE==1
#include "jbl_var.h"
#endif
#include <stdio.h>
inline jbl_stream * jbl_stream_new(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmpv,const void* tmpp)
{
	return jbl_stream_init(jbl_malloc((sizeof(jbl_stream))+((buf==NULL)?size:0)),op,data,size,buf,tmpv,tmpp);
}
jbl_stream * jbl_stream_init(jbl_stream *this,const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmpv,const void* tmpp)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数		
	this->op	=op;
	this->data	=data;
	this->size	=size;
	this->en	=0;
	if(tmpp)this->tmpp=tmpp;
	else	this->tmpv=tmpv;
	this->buf	=((buf==NULL)?(((jbl_uint8*)this)+(sizeof(jbl_stream))):buf);
	this->nxt	=NULL;
	return this;
}
jbl_stream * jbl_stream_free(jbl_stream* this)
{
	if(this==NULL)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_reference_cnt(this))
	{
		((jbl_gc_is_ref(this))?jbl_stream_free((jbl_stream *)jbl_refer_pull(this)):((((this->op->free!=NULL)?(this->op->free(this->data)):0)),jbl_stream_free(((jbl_stream *)jbl_refer_pull(this))->nxt)));
		
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var(this))
			jbl_free((char*)this-sizeof(jbl_var));
		else
#endif		
			jbl_free(this);
	}
	return NULL;
}
jbl_stream * jbl_stream_copy(jbl_stream* this)
{
	if(this==NULL)return NULL;
	if(jbl_gc_is_ref(this))
	{
		jbl_gc_plus(this);
		return this;
	}
	jbl_uint16 size=jbl_malloc_size(this);
	jbl_stream *that=jbl_malloc(size);
	jbl_gc_init(that);
	jbl_gc_plus(that);//增加引用计数	
	that->op	=this->op;
	that->tmpv	=this->tmpv;
	that->nxt	=jbl_stream_copy(this->nxt);
	if(that->op->scp!=NULL)
		that->data	=that->op->scp(this->data);
	if(that->op->usb!=NULL)
		that->op->usb(that);
	else if(this->buf==(((jbl_uint8*)this)+(sizeof(jbl_stream))))
	{
		that->en	=this->en;
		that->size	=this->size;
		that->buf	=(((jbl_uint8*)that)+(sizeof(jbl_stream)));
		jbl_memory_copy(that->buf,this->buf,this->en);
	}
	else
		that->en=0,that->size=0,that->buf=NULL;
	return that;
}
inline void jbl_stream_push_char(jbl_stream* this,char c)
{
	this=jbl_refer_pull(this);
	jbl_stream_push_char_force(this,c);
}
void jbl_stream_push_chars(jbl_stream* this,char *str)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	this=jbl_refer_pull(this);
	for(;*str;jbl_stream_push_char_force(this,*str),++str);
}
void jbl_stream_push_uint64(jbl_stream* this,jbl_uint64 in)
{
	this=jbl_refer_pull(this);
	if(in==0)
		return jbl_stream_push_char(this,'0');
	int cnt=20;
	char b[21];
	b[cnt--]=0;
	while(in)b[cnt--]=in%10+'0',in/=10;
	jbl_stream_push_chars(this,b+cnt+1);	
}
inline void jbl_stream_push_int64(jbl_stream* this,jbl_int64 in)
{
	this=jbl_refer_pull(this);
	if(in<0)
		jbl_stream_push_char_force(this,'-'),in=-in;
	jbl_stream_push_uint64(this,in);
}
inline void jbl_stream_push_double(jbl_stream* this,double in)
{
	this=jbl_refer_pull(this);
	jbl_stream_push_int64(this,in);
	if(in<0)in=-in;
	in-=(jbl_uint64)in;
	jbl_stream_push_char_force(this,'.');
	jbl_uint64 t=(in*1000000+0.5)/10;
	if(t==0)
		return jbl_stream_push_char(this,'0');
	char b[21];
	for(register unsigned char i=0;i<21;b[i]='0',++i);
	register unsigned char cnt=20;
	b[cnt--]=0;
	while(t)b[cnt--]=t%10+'0',t/=10;
	jbl_stream_push_chars(this,b+20-7+2);
}
void jbl_stream_push_hex_8bits(jbl_stream *this,jbl_uint8 in)
{
	const char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	jbl_stream_push_char(this,hex[in>>4]),jbl_stream_push_char(this,hex[in&15]);	
}
inline char jbl_stream_view_put_format(const void *this,jbl_stream *out,char*name,jbl_int32 format,char*str,jbl_int32 *tabs)
{
	if(out==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(format&&*tabs>=0)for(jbl_int16 i=0;i<*tabs;jbl_stream_push_char(out,'\t'),++i);else *tabs=-*tabs;
	if(this)jbl_stream_push_chars(out,name);
	else	jbl_stream_push_chars(out,"null          ");
	if(format&&str)jbl_stream_push_chars(out,str),jbl_stream_push_char(out,' '),(format!=-1?jbl_stream_push_uint64(out,format):0);
	++*tabs;
	return this?0:1;
}
#if JBL_JSON_ENABLE==1
inline char jbl_stream_json_put_format(const void *this,jbl_stream *out,char format,jbl_int32 *tabs)
{
	if(out==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	if(format&&*tabs>=0)for(jbl_int16 i=0;i<*tabs;jbl_stream_push_char(out,'\t'),++i);else *tabs=-*tabs;	
	++*tabs;
	if(!this)return jbl_stream_push_chars(out,"null"),1;
	return 0;
}
#endif
void jbl_stream_file_operator(jbl_stream* this,jbl_uint8 flags)
{
	this=jbl_refer_pull(this);
	jbl_stream* nxt=(this->nxt!=NULL?jbl_refer_pull(this->nxt):NULL);
	if(nxt==NULL)
	{
		for(jbl_uint16 i=0;i<this->en;fputc(this->buf[i],this->data),++i);
		this->en=0;
	}
	else
		for(;;)
		{
			if((nxt->en+1)>nxt->size)jbl_stream_do(nxt,0);
			jbl_int8 c=fgetc(this->data);
			if(c==EOF||(c=='\n'&&this->data==stdin))
				return jbl_stream_do(nxt,flags);
			nxt->buf[nxt->en++]=c;
		}		
}
FILE* jbl_stream_file_copy(FILE* this)
{
	return  this;
}
const jbl_stream_operater jbl_stream_file_operators={jbl_stream_file_operator,NULL,(void* (*)(void *))jbl_stream_file_copy,NULL};
jbl_stream *jbl_stream_stdout;
jbl_stream *jbl_stream_stdin;
#if JBL_VAR_ENABLE==1
const jbl_var_operators jbl_stream_operators={
	(void* (*)(void *))jbl_stream_free,
	(void* (*)(void *))jbl_stream_copy,
	NULL,
#if JBL_STRING_ENABLE==1
#if JBL_JSON_ENABLE==1
	NULL,
#endif		
#endif		
#if JBL_STREAM_ENABLE==1
	NULL,
#if JBL_JSON_ENABLE==1
	NULL,
#endif	
#endif	
};
inline jbl_stream * jbl_Vstream(jbl_var * this){if(!Vis_jbl_stream(this))jbl_exception(JBL_ERROR_VAR_TYPE_ERROR);return((jbl_stream*)this);}
inline jbl_var * jbl_Vstream_new(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmpv,const void* tmpp)
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_stream))+(sizeof(jbl_var))+((buf==NULL)?size:0))+(sizeof(jbl_var))));	
	jbl_stream_init(jbl_Vstream(this),op,data,size,buf,tmpv,tmpp);
	jbl_gc_set_var(jbl_Vstream(this));
	jbl_var_set_operators(this,&jbl_stream_operators);
	return this;	
}

#endif

#endif
