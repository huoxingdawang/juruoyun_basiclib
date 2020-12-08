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
/*******************************************************************************************/
/*                            依赖 jbl_gc jbl_malloc jbl_ying jbl_exception jbl_pthread    */
/*                            依赖 stdio                                                   */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_gc.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
#include "jbl_pthread.h"
#include <stdio.h>
/*******************************************************************************************/
/*                            联动 jbl_var jbl_string_cc                                   */
/*******************************************************************************************/
#include "jbl_var.h"
#include "jbl_string_cc.h"
/*******************************************************************************************/
/*                            全局变量定义                                                */
/*******************************************************************************************/
jbl_stream *jbl_stream_stdout;
jbl_stream *jbl_stream_stdin;
jbl_stream *jbl_stream_stdin_link;
static const jbl_stream_operater __sfos;
jbl_var_operators_new(jbl_stream_operators,jbl_stream_free,jbl_stream_copy,NULL,NULL,NULL,NULL);
/*******************************************************************************************/
/*                            以下函数完成流处理器组件启动和停止                         */
/*******************************************************************************************/
void jbl_stream_start()
{
	jbl_stream_stdout=jbl_stream_new(&__sfos);jbl_stream_stdout->data[0].p=JBL_STREAM_STDOUT;
	jbl_stream_stdin =jbl_stream_new(&__sfos);jbl_stream_stdin ->data[0].p=JBL_STREAM_STDIN;
#ifdef _WIN32
#if JBL_STRING_CC_ENABLE ==1
	jbl_stream_stdin_link=jbl_stream_gb2312_to_utf8_new();
	jbl_stream_connect(jbl_stream_stdin,jbl_stream_stdin_link);

	jbl_stream * tmp=jbl_stream_stdout;
	jbl_stream_stdout=jbl_stream_utf8_to_gb2312_new();
	jbl_stream_connect(jbl_stream_stdout,tmp);
	jbl_stream_free(tmp);
#else
	jbl_stream_stdin_link=jbl_stream_copy(jbl_stream_stdin);
#endif
#elif defined(__APPLE__) || defined(__linux__)
	jbl_stream_stdin_link=jbl_stream_copy(jbl_stream_stdin);
#endif
}
void jbl_stream_stop()
{
	/*不关闭stdout,给malloc留条活路jbl_stream_do(jbl_stream_stdout,true),jbl_stream_stdout=jbl_stream_free(jbl_stream_stdout),*/
	jbl_stream_stdin		=jbl_stream_free(jbl_stream_stdin);	
	jbl_stream_stdin_link	=jbl_stream_free(jbl_stream_stdin_link);	
}
/*******************************************************************************************/
/*                            以下函实现流处理器基本操作                                 */
/*******************************************************************************************/
jbl_stream * jbl_stream_new(const jbl_stream_operater *op)
{
	jbl_stream* this=jbl_malloc((sizeof(jbl_stream))+(sizeof(jbl_stream_extra_struct)*(op->except_data_size)));
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数		
	jbl_var_set_operators(this,&jbl_stream_operators);
	jbl_pthread_lock_init(this);
	this->op	=op;
	this->nxt	=NULL;
	this->buf	=NULL;
	this->stop	=0;
    for(jbl_stream_data_size_type i=0;i<op->except_data_size;++i)this->data[i].u=0;
//	if(this->op->usb)this->op->usb(this);
	return this;
}
jbl_stream * jbl_stream_free(jbl_stream* this)
{
	if(!this)return NULL;
    jbl_pthread_lock_wrlock(this);
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		if(jbl_gc_is_ref(this))
			jbl_stream_free((jbl_stream*)(((jbl_reference*)this)->ptr));
		else
		{
            this->op->op(this,1);            
            this->buf=jbl_stream_free_buf(this->buf);
			jbl_stream_free(this->nxt);
		}
        jbl_pthread_lock_free(this);
		jbl_free(this);
	}
    else
        jbl_pthread_lock_unwrlock(this);
	return NULL;
}
void jbl_stream_get_buf(jbl_stream *thi) 
{
    if(!thi)return;
    jbl_stream_buf *buf=NULL;
    if(thi->buf)buf=thi->buf;
    if((!buf)&&thi->op->provide_buf)
    {
        buf=thi->op->provide_buf(thi);
        buf->free_buf=thi->op->free_buf;
    }
    jbl_stream_buf_size_type size=1024;
    size=jbl_max(size,thi->op->except_buf_size);
    if(thi->nxt)
    {
        jbl_stream* tha=jbl_refer_pull_rdlock(thi->nxt);
        size=jbl_max(size,tha->op->except_buf_size);
        if((!buf)&&tha->op->provide_buf)
        {
            buf=tha->op->provide_buf(tha);
            buf->free_buf=tha->op->free_buf;
        }
        jbl_refer_pull_unrdlock(thi->nxt);
    }
    if(!buf)
    {
        buf=jbl_malloc(sizeof(jbl_stream_buf)+(sizeof(jbl_uint8)*size));
        buf->len=0;
        buf->size=size;
        buf->free_buf=NULL;
        buf->s=((jbl_uint8*)buf)+sizeof(jbl_stream_buf);
    }
    thi->buf=buf;
}
jbl_stream_buf * jbl_stream_free_buf(jbl_stream_buf * buf)
{
    if(!buf)return NULL;
    if(buf->free_buf)   buf->free_buf(buf);
    else                jbl_free(buf);
    return NULL;
}
jbl_stream * jbl_stream_copy(jbl_stream* this)
{
	if(!this)return NULL;
    jbl_pthread_lock_wrlock(this);
	jbl_gc_plus(this);
    jbl_pthread_lock_unwrlock(this);
	return this;
}
void jbl_stream_do(jbl_stream* this,jbl_uint8 force)
{
    jbl_stream* thi=jbl_refer_pull_wrlock(this);
	if(thi)thi->op->op(this,force);
    jbl_refer_pull_unwrlock(this);
}


jbl_stream * jbl_stream_connect(jbl_stream* this,jbl_stream* next)
{
	jbl_stream* thi=jbl_refer_pull_wrlock(this);
	jbl_stream_disconnect(thi);
	thi->nxt=jbl_stream_copy(next);
    jbl_refer_pull_unwrlock(this);
	return this;
}
JBL_INLINE jbl_stream * jbl_stream_disconnect(jbl_stream* this)
{
	jbl_stream* thi=jbl_refer_pull_wrlock(this);
	thi->nxt=jbl_stream_free(thi->nxt);
    jbl_refer_pull_unwrlock(this);
	return this;
}
/*******************************************************************************************/
/*                            以下函实现流处理器推入操作                                 */
/*******************************************************************************************/
void jbl_stream_push_char(jbl_stream* this,unsigned char c)
{
	if(!this)jbl_exception("NULL POINTER");
	jbl_stream*thi=jbl_refer_pull_wrlock(this);
	if(thi->stop)goto exit;
    jbl_stream_get_buf(thi);
	thi->buf->s[thi->buf->len]=c;
	++thi->buf->len;
	if(thi->buf->len>=thi->buf->size)thi->op->op(thi,0);
exit:;
    jbl_pthread_lock_unwrlock(this);
}
void jbl_stream_push_chars(jbl_stream* this,const unsigned char *str)
{
	if(!str)return;
	if(!this)jbl_exception("NULL POINTER");
	jbl_stream*thi=jbl_refer_pull_wrlock(this);
	if(thi->stop)goto exit;
    jbl_stream_get_buf(thi);
	for(;*str;)
	{
		for(;*str&&thi->buf->len<thi->buf->size;thi->buf->s[thi->buf->len]=*str,++str,++thi->buf->len);
		thi->op->op(thi,0);
        if(thi->stop)goto exit;;
	}
exit:;
    jbl_pthread_lock_unwrlock(this);
}
void jbl_stream_push_chars_length(jbl_stream* this,const unsigned char *str,jbl_uint64 n)
{
	if(!str)return;
	if(!this)jbl_exception("NULL POINTER");
	jbl_stream*thi=jbl_refer_pull_wrlock(this);
	if(thi->stop)goto exit;
    jbl_stream_get_buf(thi);
	for(jbl_uint64 i=0;i<n;++i)
	{
		for(;i<n&&thi->buf->len<thi->buf->size;thi->buf->s[thi->buf->len]=str[i],++i,++thi->buf->len);
		thi->op->op(thi,0);
        if(thi->stop)goto exit;;
	}
exit:;
    jbl_pthread_lock_unwrlock(this);
}
void jbl_stream_push_uint_length(jbl_stream *this,jbl_uint64 in,jbl_uint8 len,unsigned char c)
{
	if(in==0)return jbl_stream_push_char(this,'0');
    jbl_refer_pull_wrlock(this);
	int cnt=20;
	unsigned char b[21];
	b[cnt--]=0;
	while(in)b[cnt--]=(jbl_uint8)(in%10+'0'),in/=10;
	for(jbl_uint8 i=(jbl_uint8)(19-cnt);i<len;jbl_stream_push_char(this,c),++i);
	jbl_stream_push_chars(this,b+cnt+1);	
    jbl_pthread_lock_unwrlock(this);
}
void jbl_stream_push_int_length(jbl_stream* this,jbl_int64 in,jbl_uint8 len,unsigned char c)
{
    jbl_refer_pull_wrlock(this);
	if(in<0)jbl_stream_push_char(this,'-'),in=-in;
	jbl_stream_push_uint_length(this,(jbl_uint64)in,len,c);
    jbl_pthread_lock_unwrlock(this);
}
void jbl_stream_push_double(jbl_stream* this,double in)
{
    jbl_refer_pull_wrlock(this);
	if(in<0)jbl_stream_push_char(this,'-'),in=-in;
	jbl_stream_push_uint(this,(jbl_uint64)in);
	in-=((double)((jbl_uint64)in));
	jbl_stream_push_char(this,'.');
	jbl_uint64 t=(jbl_uint64)((in*1000000+0.5)/10);
	if(t==0)
    {
		jbl_stream_push_char(this,'0');
        goto exit;
	}
    unsigned char b[21];
	for(register unsigned char i=0;i<21;b[i]='0',++i);
	register unsigned char cnt=20;
	b[cnt--]=0;
	while(t)b[cnt--]=(jbl_uint8)(t%10+'0'),t/=10;
	jbl_stream_push_chars(this,b+20-7+2);
exit:;
    jbl_pthread_lock_unwrlock(this);
}
void jbl_stream_push_hex(jbl_stream *this,jbl_uint64 in)
{
	jbl_stream*thi=jbl_refer_pull_wrlock(this);
    jbl_uint8 n=1;
	while((in>>(n<<2)))++n;
	const unsigned char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(;n--;thi->buf->s[thi->buf->len]=hex[(in>>(n<<2))&15],++thi->buf->len){}
    jbl_pthread_lock_unwrlock(this);
}
void jbl_stream_push_hex_8bits(jbl_stream *this,jbl_uint8 in)
{
	jbl_stream*thi=jbl_refer_pull_wrlock(this);
	const unsigned char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	thi->buf->s[thi->buf->len]=hex[(in>>4)&15]  ;++thi->buf->len;
	thi->buf->s[thi->buf->len]=hex[in&15]       ;++thi->buf->len;    
    jbl_pthread_lock_unwrlock(this);
}
/*
JBL_INLINE char jbl_stream_view_put_format(const void *this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,unsigned char * typename,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * file)
{
	if(!out)jbl_exception("NULL POINTER");
	if(format)for(jbl_uint32 i=0;i<tabs;jbl_stream_push_char(out,'\t'),++i);
	if(!this)typename=UC"null";
	jbl_stream_push_chars(out,typename);
	int i=0;while(typename[i])++i;
	if(i<JBL_VIEW_NAME_LENGTH)
		for(;i<JBL_VIEW_NAME_LENGTH;++i,jbl_stream_push_char(out,' '));
#if JBL_VIEW_DISPLAY_VARNAME == 1
	if(format)jbl_stream_push_chars(out,varname);
#endif
#if JBL_VIEW_DISPLAY_FUNC == 1
	if(format&&func)jbl_stream_push_chars(out,UC" in func:"),jbl_stream_push_chars(out,func);
#endif
#if JBL_VIEW_DISPLAY_FILE == 1
	if(format&&file)jbl_stream_push_chars(out,UC" at file:"),jbl_stream_push_chars(out,file);
#endif
#if JBL_VIEW_DISPLAY_LINE == 1
	if(format&&file)jbl_stream_push_chars(out,UC" on line:"),jbl_stream_push_uint(out,line);
#endif
	return this?0:1;
}
#if JBL_JSON_ENABLE==1
JBL_INLINE char jbl_stream_json_put_format(const void *this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs)
{
	if(!out)jbl_exception("NULL POINTER");
	if(format&1)for(jbl_uint32 i=0;i<tabs;jbl_stream_push_char(out,'\t'),++i);
	if(!this)return jbl_stream_push_chars(out,UC"null"),1;
	return 0;
}
#endif
*/
static void __sfo(jbl_stream* thi,jbl_uint8 force)
{
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
	if(nxt)
		for(;!force;)
		{
            jbl_stream_get_buf(nxt);
			if((nxt->buf->len+1)>nxt->buf->size){nxt->op->op(nxt,false);if(nxt->stop)break;}
			int c=fgetc((FILE*)thi->data[0].p);
			if(c==EOF||(c=='\n'&&((FILE*)thi->data[0].p)==stdin)){nxt->op->op(nxt,force);break;}
			nxt->buf->s[nxt->buf->len]=(jbl_uint8)c;
            ++nxt->buf->len;
		}
	else
	{
        if(thi->buf)
        {
            fwrite(thi->buf->s,1,thi->buf->len,(FILE*)thi->data[0].p);
            thi->buf->len=0;
        }
	}
    jbl_refer_pull_unwrlock(thi->nxt);
}
static void __sff(jbl_stream* thi){fclose((FILE*)thi->data[0].u);}
static jbl_stream_operators_new(__sfos,__sfo,__sff,NULL,NULL,512,1);
#endif
