/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_aes.h"
#if JBL_AES_128_ENABLE==1
/*******************************************************************************************/
/*                            依赖jbl_malloc jbl_ying jbl_exception                        */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
/*******************************************************************************************/
/*                            联动jbl_stream jbl_string jbl_var                            */
/*******************************************************************************************/
#include "jbl_string.h"
#include "jbl_stream.h"
#include "jbl_var.h"
jbl_var_operators_new(jbl_aes_128_key_operators,jbl_aes_128_key_free,jbl_aes_128_key_copy,NULL,NULL,NULL,NULL);


extern void	__jbl_aes_128_encode_16		(__jbl_aes_128_ex_key w,jbl_uint8* a,jbl_uint8* b);
extern void	__jbl_aes_128_decode_16		(__jbl_aes_128_ex_key w,jbl_uint8* a,jbl_uint8 *b);
extern jbl_aes_128_key* jbl_aes_128_key_set(jbl_aes_128_key *this,unsigned char* key);

jbl_aes_128_key* jbl_aes_128_key_new()
{
	jbl_aes_128_key * this=jbl_malloc(sizeof(jbl_aes_128_key));
	jbl_gc_init(this);
	jbl_gc_plus(this);
	jbl_var_set_operators(this,&jbl_aes_128_key_operators);
	jbl_pthread_lock_init(this);
	return this;
}
JBL_INLINE jbl_aes_128_key *jbl_aes_128_key_copy(jbl_aes_128_key *that)
{
	if(!that)return NULL;
    jbl_pthread_lock_wrlock(that);
	jbl_gc_plus(that);
    jbl_pthread_lock_unwrlock(that);    
	return that;
}
jbl_aes_128_key* jbl_aes_128_key_free(jbl_aes_128_key *this)
{
	if(!this)return NULL;
    jbl_pthread_lock_wrlock(this);
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		if(jbl_gc_is_ref(this))
			jbl_aes_128_key_free((jbl_aes_128_key*)(((jbl_reference*)this)->ptr));
        jbl_pthread_lock_free(this);
		jbl_free(this);
	}
    else{jbl_pthread_lock_unwrlock(this);}
	return NULL;
}
#define gsl(x)    jbl_string_get_length_force(x)
#define ssl(x,y)  jbl_string_set_length_force(x,y)
#define gscs(x)   jbl_string_get_chars_force(x)
#if JBL_AES_128_ECB_ENABLE==1
#if JBL_STRING_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的aes128ecb加解密操作                   */
/*******************************************************************************************/
jbl_string * jbl_aes_128_ecb_encode(jbl_aes_128_key *key,jbl_string *this,jbl_string *result)
{
	if(!key)jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string      *thi=jbl_refer_pull_rdlock(this);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock(key);
	jbl_string_size_type i=0,len=gsl(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len+16,1,&res);jbl_string_hash_clear(res);
	jbl_uint8 tmp[16];
	for(jbl_string_size_type n=(len>>4)<<4;i<n;i+=16)
		__jbl_aes_128_encode_16(ke->key,gscs(thi)+i,gscs(res)+gsl(res)),ssl(res,gsl(res)+16);
	for(jbl_uint8 j=0,x=(jbl_uint8)((len-i)==0?16:(16-(len&15)));j<16;tmp[j]=x,++j);
	for(jbl_uint8 j=0;i<len;tmp[j]=jbl_string_get_force(thi,i),++i,++j);
	__jbl_aes_128_encode_16(ke->key,tmp,gscs(res)+gsl(res));
    ssl(res,gsl(res)+16);
    jbl_refer_pull_unwrlock(result);
    jbl_refer_pull_unrdlock(key);
    jbl_refer_pull_unrdlock(this);
    return result;
}
jbl_string * jbl_aes_128_ecb_decode(jbl_aes_128_key *key,jbl_string *this,jbl_string *result)
{
	if(!key)jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string      *thi=jbl_refer_pull_rdlock(this);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock(key);
	jbl_string_size_type len=gsl(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len,1,&res);jbl_string_hash_clear(res);
	for(jbl_string_size_type i=0;i<len;i+=16)
		__jbl_aes_128_decode_16(ke->key,gscs(thi)+i,gscs(res)+gsl(res)),ssl(res,gsl(res)+16);
	ssl(res,gsl(res)-gscs(res)[gsl(res)-1]);
    jbl_refer_pull_unwrlock(result);
    jbl_refer_pull_unrdlock(key);
    jbl_refer_pull_unrdlock(this);
	return result;
}
#endif
#if JBL_STREAM_ENABLE==1
static void __128_ecb_sff(jbl_stream* thi){jbl_aes_128_key_free((jbl_aes_128_key*)thi->data[0].p);}
/*******************************************************************************************/
/*                            以下函数实现stream的aes128ecb加解密操作                    */
/*******************************************************************************************/
static void __128_ecb_seo(jbl_stream* thi,jbl_uint8 force)
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock((jbl_aes_128_key*)thi->data[0].p);
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(thi,1);
		jbl_stream_buf_size_type len=(((thi->buf->len-thi->buf->sta)>>4)<<4)+thi->buf->sta;
        while(thi->buf->sta<len)
        {
            jbl_stream_push_down(nxt,16);
            jbl_stream_move_unhandle_buf(nxt->buf);
            if(1==(thi->stop=nxt->stop))break;
            __jbl_aes_128_encode_16(ke->key,thi->buf->s+thi->buf->sta,nxt->buf->s+nxt->buf->len);
            nxt->buf->len+=16;
            thi->buf->sta+=16;
        }
        if(force)
        {
            jbl_stream_push_down(nxt,16);
            jbl_stream_move_unhandle_buf(nxt->buf);
            if(1==(thi->stop=nxt->stop))goto exit;
            jbl_uint8 s[16];
            for(jbl_uint8 j=0,x=(jbl_uint8)(16-(thi->buf->len&15));j<16;s[j]=x,++j);
            for(jbl_uint8 j=0;thi->buf->sta<thi->buf->len;s[j]=thi->buf->s[thi->buf->sta],++thi->buf->sta,++j);
            __jbl_aes_128_encode_16(ke->key,s,nxt->buf->s+nxt->buf->len);
            nxt->buf->len+=16;
        }
        nxt->op->op(nxt,force);
	}
exit:;
    jbl_refer_pull_unwrlock(thi->nxt);
    jbl_refer_pull_unrdlock((jbl_aes_128_key*)thi->data[0].p);
}
static void __128_ecb_sdo(jbl_stream* thi,jbl_uint8 force)
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock((jbl_aes_128_key*)thi->data[0].p);
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(thi,1);
		jbl_stream_buf_size_type len=(((thi->buf->len-thi->buf->sta)>>4)<<4)+thi->buf->sta;
        if(!(len&15)&&!force&&len)len-=16;
		if((len-thi->buf->sta))
        {
			while(thi->buf->sta<len)
			{
				jbl_stream_push_down(nxt,16);
                jbl_stream_move_unhandle_buf(nxt->buf);
                if(1==(thi->stop=nxt->stop))break;
				__jbl_aes_128_decode_16(ke->key,thi->buf->s+thi->buf->sta,nxt->buf->s+nxt->buf->len);
                nxt->buf->len+=16;
                thi->buf->sta+=16;
			}
            if(force)
            {
                nxt->buf->len-=nxt->buf->s[nxt->buf->len-1];
                nxt->op->op(nxt,force);
            }
        }
    }
}
jbl_stream_operators_new(jbl_stream_aes_128_ecb_encode_operators,__128_ecb_seo,__128_ecb_sff,NULL,64,1);
jbl_stream_operators_new(jbl_stream_aes_128_ecb_decode_operators,__128_ecb_sdo,__128_ecb_sff,NULL,64,1);
JBL_INLINE jbl_stream * jbl_stream_aes_128_ecb_encode_new(jbl_aes_128_key *w)
{
	jbl_stream *this=jbl_stream_new(&jbl_stream_aes_128_ecb_encode_operators);
	this->data[0].p=jbl_aes_128_key_copy(w);
	return this;
}
JBL_INLINE jbl_stream * jbl_stream_aes_128_ecb_decode_new(jbl_aes_128_key *w)
{
	jbl_stream *this=jbl_stream_new(&jbl_stream_aes_128_ecb_decode_operators);
	this->data[0].p=jbl_aes_128_key_copy(w);
	return this;
}

#endif
#endif
#if JBL_AES_128_CBC_ENABLE==1
#if JBL_STRING_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的aes128cbc加解密操作                   */
/*******************************************************************************************/
jbl_string * jbl_aes_128_cbc_encode(jbl_aes_128_key *key,jbl_uint8 * vi,jbl_string *this,jbl_string *result)
{
	if(!key)jbl_exception("NULL POINTER");
	if(!vi) jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string      *thi=jbl_refer_pull_rdlock(this);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock(key);
	jbl_string_size_type len=gsl(thi),i=0;
	jbl_string *res;result=jbl_string_extend_to(result,len+16,1,&res);jbl_string_hash_clear(res);
	jbl_uint8 s[16],*vii=vi;
	for(i=0;i<len;++i)
	{
        s[i&15]=jbl_string_get_force(thi,i)^vii[i&15];
		if(!((i+1)&15))
        {
            __jbl_aes_128_encode_16(ke->key,s,gscs(res)+gsl(res));
            vii=gscs(res)+gsl(res);
            ssl(res,gsl(res)+16);
        }
	}
    for(jbl_uint8 j=i&15;j<16;++j)s[j]=(jbl_uint8)((16-(len&15))^vii[j]);
    __jbl_aes_128_encode_16(ke->key,s,gscs(res)+gsl(res));
    ssl(res,gsl(res)+16);

    jbl_refer_pull_unwrlock(result);
    jbl_refer_pull_unrdlock(key);
    jbl_refer_pull_unrdlock(this);
	return result;	
}
jbl_string * jbl_aes_128_cbc_decode(jbl_aes_128_key *key,jbl_uint8 * vi,jbl_string *this,jbl_string *result)
{
	if(!key)jbl_exception("NULL POINTER");
	if(!vi) jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string      *thi=jbl_refer_pull_rdlock(this);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock(key);
	jbl_string_size_type len=gsl(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len+16,1,&res);jbl_string_hash_clear(res);    
	jbl_uint8 *vii=vi;
	for(jbl_string_size_type i=0;i<len;i+=16)
	{
		__jbl_aes_128_decode_16(ke->key,gscs(thi)+i,gscs(res)+gsl(res));
		for(jbl_uint8 j=0;j<16;gscs(res)[j+gsl(res)]^=vii[j],++j);
		vii=gscs(thi)+i;
		ssl(res,gsl(res)+16);
	}
	ssl(res,gsl(res)-gscs(res)[gsl(res)-1]);
    jbl_refer_pull_unwrlock(result);
    jbl_refer_pull_unrdlock(key);
    jbl_refer_pull_unrdlock(this);
	return result;	
}
#endif
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现stream的aes128cbc缓冲更新操作                  */
/*******************************************************************************************/
static void __128_cbc_sff(jbl_stream* thi){jbl_aes_128_key_free((jbl_aes_128_key*)thi->data[0].p);jbl_free((void*)thi->data[1].p);}
/*******************************************************************************************/
/*                            以下函数实现stream的aes128cbc加解密操作                    */
/*******************************************************************************************/
static void __128_cbc_seo(jbl_stream* thi,jbl_uint8 force)
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock((jbl_aes_128_key*)thi->data[0].p);
	jbl_uint8 *vii=(jbl_uint8*)thi->data[1].p;
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(thi,1);
		jbl_stream_buf_size_type len=(((thi->buf->len-thi->buf->sta)>>4)<<4)+thi->buf->sta;
		if((len-thi->buf->sta))
        {
			while(thi->buf->sta<len)
			{
                jbl_stream_push_down(nxt,16);
                jbl_stream_move_unhandle_buf(nxt->buf);
                if(1==(thi->stop=nxt->stop))break;
                jbl_uint8 s[16];
                for(jbl_uint8 j=0;j<16;s[j]=thi->buf->s[thi->buf->sta+j]^vii[j],++j){}
				__jbl_aes_128_encode_16(ke->key,s,nxt->buf->s+nxt->buf->len);
                jbl_memory_copy(vii,nxt->buf->s+nxt->buf->len,16);
                nxt->buf->len+=16;
                thi->buf->sta+=16;
			}
		}
        if(force)
        {
            jbl_stream_push_down(nxt,16);
            jbl_stream_move_unhandle_buf(nxt->buf);
            if(1==(thi->stop=nxt->stop))goto exit;
            jbl_uint8 s[16];
            for(jbl_uint8 j=0,x=(jbl_uint8)(16-(thi->buf->len&15));j<16;s[j]=x,++j){}
            for(jbl_uint8 j=0;thi->buf->sta<thi->buf->len;s[j]=thi->buf->s[thi->buf->sta],++thi->buf->sta,++j){}
            for(jbl_uint8 j=0;j<16;s[j]^=vii[j],++j){}
            __jbl_aes_128_encode_16(ke->key,s,nxt->buf->s+nxt->buf->len);
            jbl_memory_copy(vii,nxt->buf->s+nxt->buf->len,16);
            nxt->buf->len+=16;
        }
        nxt->op->op(nxt,force);
	}
exit:;
    jbl_refer_pull_unwrlock(thi->nxt);
    jbl_refer_pull_unrdlock((jbl_aes_128_key*)thi->data[0].p);
}
static void __128_cbc_sdo(jbl_stream* thi,jbl_uint8 force)
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
    jbl_aes_128_key *ke =jbl_refer_pull_rdlock((jbl_aes_128_key*)thi->data[0].p);
	jbl_uint8 *vii=(jbl_uint8*)thi->data[1].p;
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(thi,1);
		jbl_stream_buf_size_type len=(((thi->buf->len-thi->buf->sta)>>4)<<4);
        if(!(len&15)&&!force&&len)len-=16;
        len+=thi->buf->sta;
        while(thi->buf->sta<len)
        {
            jbl_stream_push_down(nxt,16);
            jbl_stream_move_unhandle_buf(nxt->buf);
            if(1==(thi->stop=nxt->stop))break;
            __jbl_aes_128_decode_16(ke->key,thi->buf->s+thi->buf->sta,nxt->buf->s+nxt->buf->len);
            for(jbl_uint8 j=0;j<16;nxt->buf->s[nxt->buf->len+j]^=vii[j],++j);
            vii=thi->buf->s+thi->buf->sta;
            nxt->buf->len+=16;
            thi->buf->sta+=16;
        }
        jbl_memory_copy((jbl_uint8*)thi->data[1].p,vii,16);
        if(force)
        {
            nxt->buf->len-=nxt->buf->s[nxt->buf->len-1];
            nxt->op->op(nxt,force);
        }
        nxt->op->op(nxt,force);
	}
    jbl_refer_pull_unwrlock(thi->nxt);
    jbl_refer_pull_unrdlock((jbl_aes_128_key*)thi->data[0].p);
}
jbl_stream_operators_new(jbl_stream_aes_128_cbc_encode_operators,__128_cbc_seo,__128_cbc_sff,NULL,64,2);
jbl_stream_operators_new(jbl_stream_aes_128_cbc_decode_operators,__128_cbc_sdo,__128_cbc_sff,NULL,64,2);
JBL_INLINE jbl_stream * jbl_stream_aes_128_cbc_encode_new(jbl_aes_128_key *w,const unsigned char * v)
{
	jbl_stream *this=jbl_stream_new(&jbl_stream_aes_128_cbc_encode_operators);
	this->data[0].p=jbl_aes_128_key_copy(w);
	this->data[1].p=jbl_malloc(16);
    jbl_memory_copy((void*)this->data[1].p,v,16);
	return this;
}

JBL_INLINE jbl_stream * jbl_stream_aes_128_cbc_decode_new(jbl_aes_128_key *w,const unsigned char * v)
{
	jbl_stream *this=jbl_stream_new(&jbl_stream_aes_128_cbc_decode_operators);
	this->data[0].p=jbl_aes_128_key_copy(w);
	this->data[1].p=jbl_malloc(16);
    jbl_memory_copy((void*)this->data[1].p,v,16);
	return this;
}


#endif
#endif
#endif