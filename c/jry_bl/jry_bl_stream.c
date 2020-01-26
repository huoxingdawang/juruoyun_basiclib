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
void jry_bl_stream_push_char_pointer(jry_bl_stream* this,jry_bl_uint8 *str)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);		
	for(;*str;jry_bl_stream_push_char(this,*str),++str);
}
void jry_bl_stream_push_uint64(jry_bl_stream* this,jry_bl_uint64 in)
{
	if(in==0)
	{
		jry_bl_stream_push_char(this,'0');
		return;
	}
	int cnt=20;
	unsigned char b[21];
	b[cnt--]=0;
	while(in)b[cnt--]=in%10+'0',in/=10;
	jry_bl_stream_push_char_pointer(this,b+cnt+1);	
}
inline void jry_bl_stream_push_int64(jry_bl_stream* this,jry_bl_int64 in)
{
	if(in<0)
		jry_bl_stream_push_char(this,'-'),in=-in;
	jry_bl_stream_push_uint64(this,in);
}
inline void jry_bl_stream_push_double(jry_bl_stream* this,double in)
{
	jry_bl_stream_push_int64(this,in);
	if(in<0)
		in=-in;
	in-=(jry_bl_uint64)in;
	jry_bl_uint64 ji=10;
	for(double t=in*ji;(t-(jry_bl_uint64)t<(-0.0000001)||t-(jry_bl_uint64)t>(0.0000001));ji=(ji<<3)+(ji<<1),t=in*ji);
	jry_bl_stream_push_char(this,'.');
	ji=(ji<<3)+(ji<<1);
	jry_bl_stream_push_uint64(this,((jry_bl_uint64)((in*ji+0.5)/10)));	
}
void jry_bl_stream_file_operator(jry_bl_stream* this,jry_bl_uint8 flags)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);		
	if(this->nxt==NULL)
	{
		for(jry_bl_uint16 i=0;i<this->en;fputc(this->buf[i],this->data),++i);
		this->en=0;
	}
	else
		for(;;)
		{
			if((this->nxt->en+1)>this->nxt->size)jry_bl_stream_do(this->nxt,0);
			jry_bl_int8 c=fgetc(this->data);
			if(c==EOF||(c=='\n'&&this->data==stdin))
				return jry_bl_stream_do(this->nxt,flags);
			this->nxt->buf[this->nxt->en++]=c;
		}		
}
jry_bl_stream jry_bl_stream_stdout;
jry_bl_stream jry_bl_stream_stdin;
#endif
