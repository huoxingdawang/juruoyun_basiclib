/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_stream.h"
#if JRY_BL_STREAM_ENABLE==1
jry_bl_stream * jry_bl_stream_new(const jry_bl_stream_operater *op,void *data,jry_bl_uint16 size,unsigned char *buf)
{
	jry_bl_stream *this=jry_bl_malloc((sizeof(jry_bl_stream))+((buf==NULL)?size:0));
	jry_bl_gc_init(this);
	jry_bl_gc_plus(this);//增加引用计数		
	this->op	=op;
	this->data	=data;
	this->size	=size;
	this->en	=0;
	this->tmp	=0;
	this->buf	=((buf==NULL)?(((jry_bl_uint8*)this)+(sizeof(jry_bl_stream))):buf);
	return this;
}
jry_bl_stream * jry_bl_stream_free(jry_bl_stream* this)
{
	jry_bl_gc_minus(this);
	if(!jry_bl_gc_reference_cnt(this))
		((jry_bl_gc_is_ref(this))?jry_bl_stream_free((jry_bl_stream *)jry_bl_refer_pull(this)):((((this->op->free!=NULL)?(this->op->free(this->data)):0)))),jry_bl_free(this);
	return NULL;
}
jry_bl_stream * jry_bl_stream_copy(jry_bl_stream* this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(jry_bl_gc_is_ref(this))
	{
		jry_bl_gc_plus(this);
		return this;
	}
	jry_bl_uint16 size=jry_bl_malloc_size(this);
	jry_bl_stream *that=jry_bl_malloc(size);
	jry_bl_gc_init(that);
	jry_bl_gc_plus(that);//增加引用计数	
	that->op	=this->op;
	that->size	=this->size;
	that->en	=this->en;
	that->tmp	=this->tmp;
	if(that->op->scp!=NULL)
		that->data	=that->op->scp(this->data);
	if(that->op->usb!=NULL)
		that->op->usb(that);
	return that;
}
inline void jry_bl_stream_push_char(jry_bl_stream* this,char c)
{
	this=jry_bl_refer_pull(this);
	jry_bl_stream_push_char_force(this,c);
}
void jry_bl_stream_push_chars(jry_bl_stream* this,char *str)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	this=jry_bl_refer_pull(this);
	for(;*str;jry_bl_stream_push_char_force(this,*str),++str);
}
void jry_bl_stream_push_uint64(jry_bl_stream* this,jry_bl_uint64 in)
{
	this=jry_bl_refer_pull(this);
	if(in==0)
	{
		jry_bl_stream_push_char_force(this,'0');
		return;
	}
	int cnt=20;
	char b[21];
	b[cnt--]=0;
	while(in)b[cnt--]=in%10+'0',in/=10;
	jry_bl_stream_push_chars(this,b+cnt+1);	
}
inline void jry_bl_stream_push_int64(jry_bl_stream* this,jry_bl_int64 in)
{
	this=jry_bl_refer_pull(this);
	if(in<0)
		jry_bl_stream_push_char_force(this,'-'),in=-in;
	jry_bl_stream_push_uint64(this,in);
}
inline void jry_bl_stream_push_double(jry_bl_stream* this,double in)
{
	this=jry_bl_refer_pull(this);
	jry_bl_stream_push_int64(this,in);
	if(in<0)
		in=-in;
	in-=(jry_bl_uint64)in;
	jry_bl_uint64 ji=10;
	for(double t=in*ji;(t-(jry_bl_uint64)t<(-JRY_BL_DOUBLE_PRECISION)||t-(jry_bl_uint64)t>(JRY_BL_DOUBLE_PRECISION));ji=(ji<<3)+(ji<<1),t=in*ji);
	jry_bl_stream_push_char_force(this,'.');
	ji=(ji<<3)+(ji<<1);
	jry_bl_stream_push_uint64(this,((jry_bl_uint64)((in*ji+0.5)/10)));	
}

void jry_bl_stream_file_operator(jry_bl_stream* this,jry_bl_uint8 flags)
{
	this=jry_bl_refer_pull(this);
	jry_bl_stream* nxt=(this->nxt!=NULL?jry_bl_refer_pull(this->nxt):NULL);
	if(nxt==NULL)
	{
		for(jry_bl_uint16 i=0;i<this->en;fputc(this->buf[i],this->data),++i);
		this->en=0;
	}
	else
		for(;;)
		{
			if((nxt->en+1)>nxt->size)jry_bl_stream_do(nxt,0);
			jry_bl_int8 c=fgetc(this->data);
			if(c==EOF||(c=='\n'&&this->data==stdin))
				return jry_bl_stream_do(nxt,flags);
			nxt->buf[nxt->en++]=c;
		}		
}
const jry_bl_stream_operater jry_bl_stream_file_operators={jry_bl_stream_file_operator,NULL,NULL,NULL};
jry_bl_stream *jry_bl_stream_stdout;
jry_bl_stream *jry_bl_stream_stdin;
#endif
