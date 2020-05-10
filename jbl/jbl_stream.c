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
inline jbl_stream * jbl_stream_new(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmp)
{
	return jbl_stream_init(jbl_malloc((sizeof(jbl_stream))+((buf==NULL)?size:0)),op,data,size,buf,tmp);
}
jbl_stream * jbl_stream_init(jbl_stream *this,const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmp)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数		
	this->op	=op;
	this->data	=data;
	this->size	=size;
	this->en	=0;
	this->tmpv	=tmp;
	this->buf	=((buf==NULL)?(((jbl_uint8*)this)+(sizeof(jbl_stream))):buf);
	return this;
}
jbl_stream * jbl_stream_free(jbl_stream* this)
{
	jbl_gc_minus(this);
	if(!jbl_gc_reference_cnt(this))
	{
		((jbl_gc_is_ref(this))?jbl_stream_free((jbl_stream *)jbl_refer_pull(this)):((((this->op->free!=NULL)?(this->op->free(this->data)):0))));
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
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
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
	that->size	=this->size;
	that->en	=this->en;
	that->tmpv	=this->tmpv;
	if(that->op->scp!=NULL)
		that->data	=that->op->scp(this->data);
	if(that->op->usb!=NULL)
		that->op->usb(that);
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
	{
		jbl_stream_push_char_force(this,'0');
		return;
	}
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
	if(in<0)
		in=-in;
	in-=(jbl_uint64)in;
	jbl_uint64 ji=10;
	for(double t=in*ji;(t-(jbl_uint64)t<(-JBL_DOUBLE_PRECISION)||t-(jbl_uint64)t>(JBL_DOUBLE_PRECISION));ji=(ji<<3)+(ji<<1),t=in*ji);
	jbl_stream_push_char_force(this,'.');
	ji=(ji<<3)+(ji<<1);
	jbl_stream_push_uint64(this,((jbl_uint64)((in*ji+0.5)/10)));	
}

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
const jbl_stream_operater jbl_stream_file_operators={jbl_stream_file_operator,NULL,NULL,NULL};
jbl_stream *jbl_stream_stdout;
jbl_stream *jbl_stream_stdin;
#if JBL_VAR_ENABLE==1
const jbl_var_operators jbl_stream_operators={
	(void* (*)(void *))jbl_stream_free,
	(void* (*)(void *))jbl_stream_copy,

#if JBL_STREAM_ENABLE==1
	NULL,
#endif	
};
inline jbl_var * jbl_Vstream_new(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmp)
{
	jbl_var * this=jbl_malloc((sizeof(jbl_stream))+8+((buf==NULL)?size:0));
	jbl_stream_init($bl_stream(this),op,data,size,buf,tmp);
	jbl_gc_set_var($bl_stream(this));
	jbl_var_set_operators(this,&jbl_stream_operators);
	return this;	
}

#endif

#endif
