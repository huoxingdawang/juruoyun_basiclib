/* Copyright (c) [2020] juruoyun developer team
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
#include "jbl_string_cc.h"
void jbl_stream_start()
{
	jbl_stream_stdout=jbl_stream_new(&jbl_stream_file_operators,JBL_STREAM_STDOUT,JBL_STREAM_EXCEED_LENGTH,NULL,0);
	jbl_stream_stdin =jbl_stream_new(&jbl_stream_file_operators,JBL_STREAM_STDIN ,0,NULL,0);
	
#ifdef __linux__
	jbl_stream_stdin_link=jbl_stream_copy(jbl_stream_stdin);
#else
	jbl_stream_stdin_link=jbl_stream_gb2312_to_utf8_new();
	jbl_stream_connect(jbl_stream_stdin,jbl_stream_stdin_link);

	jbl_stream * tmp=jbl_stream_stdout;
	jbl_stream_stdout=jbl_stream_utf8_to_gb2312_new();
	jbl_stream_connect(jbl_stream_stdout,tmp);
	jbl_stream_free(tmp);
#endif
}
void jbl_stream_stop()
{
	/*不关闭stdout,给malloc留条活路jbl_stream_do(jbl_stream_stdout,jbl_stream_force),jbl_stream_stdout=jbl_stream_free(jbl_stream_stdout),*/
	jbl_stream_stdin		=jbl_stream_free(jbl_stream_stdin);	
	jbl_stream_stdin_link	=jbl_stream_free(jbl_stream_stdin_link);	
}
inline jbl_stream * jbl_stream_new(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,jbl_uint8 tmplen)
{
	return jbl_stream_init(jbl_malloc(jbl_stream_caculate_size(tmplen)+((buf)?0:size)),op,data,size,buf,tmplen);
}
jbl_stream * jbl_stream_init(jbl_stream *this,const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,jbl_uint8 tmplen)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数		
	this->op	=op;
	this->data	=data;
	this->size	=size;
	this->en	=0;
	this->buf	=((buf)?buf:(((jbl_uint8*)this)+(sizeof(jbl_uint64)*tmplen)+(sizeof(jbl_stream))));
	this->nxt	=NULL;
	while(tmplen--)this->tmp[tmplen].u=0;
	if(this->op->usb)this->op->usb(this);
	return this;
}
jbl_stream * jbl_stream_free(jbl_stream* this)
{
	if(!this)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		((jbl_gc_is_ref(this))?jbl_stream_free((jbl_stream *)jbl_refer_pull(this)):((((this->op->free)?(this->op->free(this->data)):0)),jbl_stream_free(((jbl_stream *)jbl_refer_pull(this))->nxt)));
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
	if(!this)return NULL;
	jbl_gc_plus(this);
	return this;
/*	
	if(jbl_gc_is_ref(this))
	{
		jbl_gc_plus(this);
	}
	jbl_uint16 size=jbl_malloc_size(this);
	jbl_stream *that=jbl_malloc(size);
	jbl_gc_init(that);
	jbl_gc_plus(that);//增加引用计数	
	that->op	=this->op;
	that->tmpv	=this->tmpv;
	that->nxt	=jbl_stream_copy(this->nxt);
	if(that->op->scp)that->data=that->op->scp(this->data);
	if(this->buf==(((jbl_uint8*)this)+(sizeof(jbl_stream))))
	{
		that->en	=this->en;
		that->size	=this->size;
		that->buf	=(((jbl_uint8*)that)+(sizeof(jbl_stream)));
		jbl_memory_copy(that->buf,this->buf,this->en);
	}
	else
		that->en=0,that->size=0,that->buf=NULL;
	if(that->op->usb)that->op->usb(that);
	return that;
*/
}
void jbl_stream_do(jbl_stream* this,jbl_uint8 flag)
{
	if(!this)return;
	void  (*op)(jbl_stream*,jbl_uint8)=this->op->op;
	if(!op)return;
	op(this,flag);
}
jbl_stream* jbl_stream_push_char(jbl_stream* this,unsigned char c)
{
	if(!this)jbl_exception("NULL POINTER");
	jbl_stream*thi=jbl_refer_pull(this);
	((thi->en+1)>thi->size)?jbl_stream_do(thi,0):0;
	thi->buf[thi->en]=c;
	++thi->en;
	return this;
}
jbl_stream* jbl_stream_push_chars(jbl_stream* this,const unsigned char *str)
{
	if(!str)return this;
	if(!this)jbl_exception("NULL POINTER");
	jbl_stream*thi=jbl_refer_pull(this);
	thi=jbl_refer_pull(thi);
	for(;*str;jbl_stream_do(thi,0))for(;*str&&thi->en<thi->size;thi->buf[thi->en]=*str,++str,++thi->en);
	return this;
}
jbl_stream* jbl_stream_push_uint(jbl_stream* this,jbl_uint64 in)
{
	if(in==0)return jbl_stream_push_char(this,'0');
	jbl_stream*thi=jbl_refer_pull(this);
	int cnt=20;
	unsigned char b[21];
	b[cnt--]=0;
	while(in)b[cnt--]=in%10+'0',in/=10;
	jbl_stream_push_chars(thi,b+cnt+1);	
	return this;
}
jbl_stream* jbl_stream_push_int(jbl_stream* this,jbl_int64 in)
{
	jbl_stream*thi=jbl_refer_pull(this);
	if(in<0)
		jbl_stream_push_char(thi,'-'),in=-in;
	jbl_stream_push_uint(thi,in);
	return this;
}
jbl_stream* jbl_stream_push_double(jbl_stream* this,double in)
{
	jbl_stream*thi=jbl_refer_pull(this);
	jbl_stream_push_int(thi,in);
	if(in<0)in=-in;
	in-=(jbl_uint64)in;
	jbl_stream_push_char(thi,'.');
	jbl_uint64 t=(in*1000000+0.5)/10;
	if(t==0)
		return jbl_stream_push_char(thi,'0');
	unsigned char b[21];
	for(register unsigned char i=0;i<21;b[i]='0',++i);
	register unsigned char cnt=20;
	b[cnt--]=0;
	while(t)b[cnt--]=t%10+'0',t/=10;
	jbl_stream_push_chars(thi,b+20-7+2);
	return this;
}
jbl_stream* jbl_stream_push_hex(jbl_stream *this,jbl_uint64 in)
{
	unsigned char n=1;
	while((in>>(n<<2)))++n;
	const char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(;n--;jbl_stream_push_char(this,hex[(in>>(n<<2))&15]));
	return this;
}
jbl_stream* jbl_stream_push_hex_8bits(jbl_stream *this,jbl_uint8 in)
{
	const char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	jbl_stream_push_char(this,hex[(in>>4)&15]),jbl_stream_push_char(this,hex[in&15]);	
	return this;
}
inline char jbl_stream_view_put_format(const void *this,jbl_stream *out,char*name,jbl_int32 format,char*str,jbl_int32 *tabs)
{
	if(out==NULL)jbl_exception("NULL POINTER");
	if(format&&*tabs>=0)for(jbl_int16 i=0;i<*tabs;jbl_stream_push_char(out,'\t'),++i);else *tabs=-*tabs;
	if(this)jbl_stream_push_chars(out,UC(name));
	else	jbl_stream_push_chars(out,UC"null          ");
	if(format&&str)jbl_stream_push_chars(out,UC(str)),jbl_stream_push_char(out,' '),(format!=-1?jbl_stream_push_uint(out,format):0);
	++*tabs;
	return this?0:1;
}
#if JBL_JSON_ENABLE==1
inline char jbl_stream_json_put_format(const void *this,jbl_stream *out,char format,jbl_int32 *tabs)
{
	if(out==NULL)jbl_exception("NULL POINTER");
	if(format&&*tabs>=0)for(jbl_int16 i=0;i<*tabs;jbl_stream_push_char(out,'\t'),++i);else *tabs=-*tabs;	
	++*tabs;
	if(!this)return jbl_stream_push_chars(out,UC"null"),1;
	return 0;
}
#endif
void jbl_stream_file_operator(jbl_stream* this,jbl_uint8 flags)
{
	this=jbl_refer_pull(this);
	jbl_stream* nxt=jbl_refer_pull(this->nxt);
	if(nxt)
		for(;;)
		{
			if((nxt->en+1)>nxt->size)jbl_stream_do(nxt,0);
			jbl_int8 c=fgetc(this->data);
			if(c==EOF||(c=='\n'&&this->data==stdin))
				return jbl_stream_do(nxt,flags);
			nxt->buf[nxt->en++]=c;
		}
	else
	{
		fwrite(this->buf,1,this->en,this->data);
		this->en=0;
	}
}
jbl_stream_operators_new(jbl_stream_file_operators,jbl_stream_file_operator,fclose,NULL);
jbl_stream *jbl_stream_stdout;
jbl_stream *jbl_stream_stdin;
jbl_stream *jbl_stream_stdin_link;
#if JBL_VAR_ENABLE==1
jbl_var_operators_new(jbl_stream_operators,jbl_stream_free,jbl_stream_copy,NULL,NULL,NULL,NULL);
inline jbl_stream * jbl_Vstream(jbl_var * this){if(this&&!Vis_jbl_stream(this))jbl_exception("VAR TYPE ERROR");return((jbl_stream*)this);}
inline jbl_var * jbl_Vstream_new(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,jbl_uint8 tmplen)
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc(jbl_stream_caculate_size(tmplen)+(sizeof(jbl_var))+((buf)?0:size))+(sizeof(jbl_var))));	
	jbl_stream_init((jbl_stream*)this,op,data,size,buf,tmplen);
	jbl_gc_set_var((jbl_stream*)this);
	jbl_var_set_operators(this,&jbl_stream_operators);
	return this;	
}

#endif

#endif
