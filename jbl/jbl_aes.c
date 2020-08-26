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


extern void	__jbl_aes_128_encode_16		(__jbl_aes_128_ex_key w,jbl_uint8* a,jbl_uint8* b);
extern void	__jbl_aes_128_decode_16		(__jbl_aes_128_ex_key w,jbl_uint8* a,jbl_uint8 *b);
extern jbl_aes_128_key* jbl_aes_128_key_set(jbl_aes_128_key *this,unsigned char* key);

inline jbl_aes_128_key* jbl_aes_128_key_new()
{
	return jbl_aes_128_key_init(jbl_malloc(sizeof(jbl_aes_128_key)));
}
inline jbl_aes_128_key* jbl_aes_128_key_init(jbl_aes_128_key *this)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);	
	return this;
}

inline jbl_aes_128_key *jbl_aes_128_key_copy(jbl_aes_128_key *that)
{
	if(!that)return NULL;
	jbl_gc_plus(that);
	return that;
}
inline jbl_aes_128_key* jbl_aes_128_key_free(jbl_aes_128_key* this)
{
	if(!this)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		((jbl_gc_is_ref(this)||jbl_gc_is_pvar(this))?jbl_aes_128_key_free((jbl_aes_128_key*)(((jbl_reference*)this)->ptr)):0);
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var(this))
			jbl_free((char*)this-sizeof(jbl_var));
		else
#endif
			jbl_free(this);		
	}
	return NULL;
}
#if JBL_VAR_ENABLE==1
jbl_var_operators_new(jbl_aes_128_key_operators,jbl_aes_128_key_free,jbl_aes_128_key_copy,NULL,NULL,NULL,NULL);
inline jbl_aes_128_key * jbl_Vaes_128_key(jbl_var * this){if(this&&!Vis_jbl_aes_128_key(this))jbl_exception("VAR TYPE ERROR");return((jbl_aes_128_key*)this);}
jbl_var * jbl_Vaes_128_key_new()
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_aes_128_key))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_aes_128_key_init((jbl_aes_128_key*)this);
	jbl_gc_set_var((jbl_aes_128_key*)this);
	jbl_var_set_operators(this,&jbl_aes_128_key_operators);
	return this;
}
#endif


#if JBL_AES_128_ECB_ENABLE==1
#if JBL_STRING_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的aes128ecb加解密操作                   */
/*******************************************************************************************/
jbl_string * jbl_aes_128_ecb_encode(jbl_aes_128_key *w,jbl_string *this,jbl_string *result)
{
	if(!w)jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string *thi=jbl_refer_pull(this);														//this脱离引用
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(w))->key);		
	jbl_string_size_type i=0,len=jbl_string_get_length_force(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len+16,1,&res);jbl_string_hash_clear(res);
	jbl_uint8 tmp[16],*sthi=jbl_string_get_chars_force(thi),*sres=jbl_string_get_chars_force(res);
	for(jbl_string_size_type n=(len>>4)<<4;i<n;i+=16)
		__jbl_aes_128_encode_16(*key,sthi+i,sres+jbl_string_get_length_force(res)),jbl_string_set_length_force(res,jbl_string_get_length_force(res)+16);
	for(jbl_uint8 j=0,x=((len-i)==0?16:(16-(len&15)));j<16;tmp[j]=x,++j);
	for(jbl_uint8 j=0;i<len;tmp[j]=jbl_string_get_force(thi,i),++i,++j);
	__jbl_aes_128_encode_16(*key,tmp,sres+jbl_string_get_length_force(res)),jbl_string_set_length_force(res,jbl_string_get_length_force(res)+16);
	return result;
}
jbl_string * jbl_aes_128_ecb_decode(jbl_aes_128_key *w,jbl_string *this,jbl_string *result)
{
	if(!w)jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string *thi=jbl_refer_pull(this);		
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(w))->key);		
	jbl_string_size_type len=jbl_string_get_length_force(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len,1,&res);jbl_string_hash_clear(res);
	jbl_uint8 *sthi=jbl_string_get_chars_force(thi),*sres=jbl_string_get_chars_force(res);
	for(jbl_string_size_type i=0;i<len;i+=16)
		__jbl_aes_128_decode_16(*key,sthi+i,sres+jbl_string_get_length_force(res)),jbl_string_set_length_force(res,jbl_string_get_length_force(res)+16);
	jbl_string_set_length_force(res,jbl_string_get_length_force(res)-sres[jbl_string_get_length_force(res)-1]);
	return result;
}
#endif
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现stream的aes128ecb加解密操作                    */
/*******************************************************************************************/
void __jbl_aes_128_ecb_seo(jbl_stream* this,jbl_uint8 flags)
{
	if(!this)jbl_exception("NULL POINTER");	
	this=jbl_refer_pull(this);
	jbl_stream *nxt=jbl_refer_pull(this->nxt);			
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(this->data))->key);
	if(nxt!=NULL)
	{
		jbl_stream_buf_size_type i=0,len=(this->en>>4)<<4;
		if(len!=0)
			while(i<len)
			{
				if((nxt->en+16)>=nxt->size)	
					jbl_stream_do(nxt,0);
				__jbl_aes_128_encode_16(*key,this->buf+i,nxt->buf+nxt->en),nxt->en+=16,i+=16;
			}
		if((flags&jbl_stream_force))
		{
			if((nxt->en+16)>=nxt->size)
				jbl_stream_do(nxt,0);
			jbl_uint8 s[16];
			for(jbl_uint8 j=0,x=(this->en==0?16:(16-(this->en&15)));j<16;s[j]=x,++j);
			for(jbl_uint8 j=0;i<this->en;s[j]=this->buf[i],++i,++j);
			__jbl_aes_128_encode_16(*key,s,nxt->buf+nxt->en),nxt->en+=16,i=this->en;
			jbl_stream_do(nxt,flags);
		}
		jbl_memory_copy(this->buf,this->buf+i,this->en-i);
		this->en=this->en-i;
	}
}
void __jbl_aes_128_ecb_sdo(jbl_stream* this,jbl_uint8 flags)
{
	if(!this)jbl_exception("NULL POINTER");
	this=jbl_refer_pull(this);
	jbl_stream *nxt=jbl_refer_pull(this->nxt);			
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(this->data))->key);
	if(nxt!=NULL)
	{
		jbl_stream_buf_size_type i=0,len=(this->en>>4)<<4;
		if(len!=0)
			while(i<len)
			{
				if(nxt->en+16>nxt->size)	
					jbl_stream_do(nxt,0);
				__jbl_aes_128_decode_16(*key,this->buf+i,nxt->buf+nxt->en),nxt->en+=16,i+=16;
			}
		if((flags&jbl_stream_force))
			nxt->en-=nxt->buf[nxt->en-1],jbl_stream_do(nxt,flags);
		jbl_memory_copy(this->buf,this->buf+i,this->en-i);
		this->en=this->en-i;
	}
}
jbl_stream_operators_new(jbl_stream_aes_128_ecb_encode_operators,__jbl_aes_128_ecb_seo,jbl_aes_128_key_free,NULL);
jbl_stream_operators_new(jbl_stream_aes_128_ecb_decode_operators,__jbl_aes_128_ecb_sdo,jbl_aes_128_key_free,NULL);
#endif
#endif
#if JBL_AES_128_CBC_ENABLE==1
#if JBL_STRING_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的aes128cbc加解密操作                   */
/*******************************************************************************************/
jbl_string * jbl_aes_128_cbc_encode(jbl_aes_128_key *w,jbl_uint8 * vi,jbl_string *this,jbl_string *result)
{
	if(!w||!vi)jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string *thi=jbl_refer_pull(this);		
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(w))->key);		
	jbl_string_size_type len=jbl_string_get_length_force(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len+16,1,&res);jbl_string_hash_clear(res);
	jbl_uint8 s[16],*vii=vi,*sres=jbl_string_get_chars_force(res);
	for(jbl_string_size_type i=0;i<len;i+=16)
	{
		for(jbl_uint8 j=0;j<16;j++)
			s[j]=((i+j>=len)?(16-(len&15)):(jbl_string_get_force(thi,i+j)))^vii[j];
		vii=sres+jbl_string_get_length_force(res);
		__jbl_aes_128_encode_16(*key,s,sres+jbl_string_get_length_force(res)),jbl_string_set_length_force(res,jbl_string_get_length_force(res)+16);
	}
	if(len%16==0)
	{
		for(jbl_uint8 j=0;j<16;s[j]=16^vii[j],j++);
		__jbl_aes_128_encode_16(*key,s,sres+jbl_string_get_length_force(res)),jbl_string_set_length_force(res,jbl_string_get_length_force(res)+16);
	}
	jbl_string_hash_clear(result);
	return result;	
}
jbl_string * jbl_aes_128_cbc_decode(jbl_aes_128_key *w,jbl_uint8 * vi,jbl_string *this,jbl_string *result)
{
	if(!w||!vi)jbl_exception("NULL POINTER");
	if(!this)return result;
	jbl_string *thi=jbl_refer_pull(this);		
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(w))->key);		
	jbl_string_size_type len=jbl_string_get_length_force(thi);
	jbl_string *res;result=jbl_string_extend_to(result,len+16,1,&res);jbl_string_hash_clear(res);
	jbl_uint8 *vii=vi,*sthi=jbl_string_get_chars_force(thi),*sres=jbl_string_get_chars_force(res);
	for(jbl_string_size_type i=0;i<len;i+=16)
	{
		__jbl_aes_128_decode_16(*key,sthi+i,sres+jbl_string_get_length_force(res));
		for(jbl_uint8 j=0;j<16;sres[j+jbl_string_get_length_force(res)]^=vii[j],++j);
		vii=sthi+i;
		jbl_string_set_length_force(res,jbl_string_get_length_force(res)+16);
	}
	jbl_string_set_length_force(res,jbl_string_get_length_force(res)-sres[jbl_string_get_length_force(res)-1]);
	jbl_string_hash_clear(result);
	return result;	
}
#endif
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现stream的aes128cbc缓冲更新操作                  */
/*******************************************************************************************/
void jbl_aes_128_cbc_update_stream_buf(jbl_stream *this)
{
	if(this->size==(JBL_STREAM_EXCEED_LENGTH+32))this->size-=16;//占用最后16字节保存vi，所以要减掉
}
/*******************************************************************************************/
/*                            以下函数实现stream的aes128cbc加解密操作                    */
/*******************************************************************************************/
void __jbl_aes_128_cbc_seo(jbl_stream* this,jbl_uint8 flags)
{
	if(!this)jbl_exception("NULL POINTER");
	this=jbl_refer_pull(this);
	jbl_stream *nxt=jbl_refer_pull(this->nxt);			
	jbl_uint8 *vii=(jbl_uint8*)this->extra[0].p;
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(this->data))->key);
	if(nxt!=NULL)
	{
		jbl_stream_buf_size_type i=0,len=(this->en>>4)<<4;
		if(len!=0)
			while(i<len)
			{
				for(jbl_uint8 j=0;j<16;this->buf[i+j]^=vii[j],++j);
				__jbl_aes_128_encode_16(*key,this->buf+i,nxt->buf+nxt->en),nxt->en+=16,i+=16;
				if((nxt->en+16)>=nxt->size)
					jbl_memory_copy(this->buf+this->size,nxt->buf+nxt->en-16,16),vii=this->buf+this->size,jbl_stream_do(nxt,0);//备份vi并下推流
				else
					vii=nxt->buf+nxt->en-16;
			}
		if((flags&jbl_stream_force))
		{
			if((nxt->en+16)>nxt->size)
				jbl_memory_copy(this->buf+this->size,nxt->buf+nxt->en-16,16),vii=this->buf+this->size,jbl_stream_do(nxt,0);//备份vi并下推流
			jbl_uint8 s[16];
			for(jbl_uint8 j=0,x=(this->en==0?16:(16-(this->en&15)));j<16;s[j]=x,++j);
			for(jbl_uint8 j=0;i<this->en;s[j]=this->buf[i],++i,++j);
			for(jbl_uint8 j=0;j<16;s[j]^=vii[j],++j);
			__jbl_aes_128_encode_16(*key,s,nxt->buf+nxt->en),nxt->en+=16,i=this->en;
			jbl_stream_do(nxt,flags);
		}
		this->extra[0].p=vii;
		jbl_memory_copy(this->buf,this->buf+i,this->en-i);
		this->en=this->en-i;
	}
}
void __jbl_aes_128_cbc_sdo(jbl_stream* this,jbl_uint8 flags)
{
	if(!this)jbl_exception("NULL POINTER");	
	this=jbl_refer_pull(this);
	jbl_stream *nxt=jbl_refer_pull(this->nxt);			
	jbl_uint8 *vii=(jbl_uint8*)this->extra[0].p;
	__jbl_aes_128_ex_key *key=&(((jbl_aes_128_key*)jbl_refer_pull(this->data))->key);
	if(nxt!=NULL)
	{
		jbl_stream_buf_size_type i=0,len=(this->en>>4)<<4;
		if(len!=0)
		{
			while(i<len)
			{
				if(nxt->en+16>=nxt->size)jbl_stream_do(nxt,0);
				__jbl_aes_128_decode_16(*key,this->buf+i,nxt->buf+nxt->en);
				for(jbl_uint8 j=0;j<16;nxt->buf[nxt->en+j]^=vii[j],++j);
				vii=this->buf+i,nxt->en+=16,i+=16;
			}
		}
		if((flags&jbl_stream_force))
			nxt->en-=nxt->buf[nxt->en-1],jbl_stream_do(nxt,flags);//处理末尾长度，下推流
		jbl_memory_copy(this->buf+this->size,this->buf+i-16,16);this->extra[0].p=this->buf+this->size;//把最后成功解码的16字节拷到最后面做下一次的vi
		jbl_memory_copy(this->buf,this->buf+i,this->en-i);
		this->en=this->en-i;
	}
}
jbl_stream_operators_new(jbl_stream_aes_128_cbc_encode_operators,__jbl_aes_128_cbc_seo,jbl_aes_128_key_free,jbl_aes_128_cbc_update_stream_buf);
jbl_stream_operators_new(jbl_stream_aes_128_cbc_decode_operators,__jbl_aes_128_cbc_sdo,jbl_aes_128_key_free,jbl_aes_128_cbc_update_stream_buf);
inline jbl_stream * jbl_stream_aes_128_cbc_encode_new(jbl_aes_128_key *w,const unsigned char * v)
{
	jbl_stream *this=jbl_stream_new(&jbl_stream_aes_128_cbc_encode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,1);
	this->extra[0].p=v;
	return this;
}
inline jbl_stream * jbl_stream_aes_128_cbc_decode_new(jbl_aes_128_key *w,const unsigned char * v)
{
	jbl_stream *this=jbl_stream_new(&jbl_stream_aes_128_cbc_decode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,1);
	this->extra[0].p=v;
	return this;
}
#if JBL_VAR_ENABLE == 1
inline jbl_var * jbl_Vstream_aes_128_cbc_encode_new(jbl_aes_128_key *w,const unsigned char * v)
{
	jbl_var *this=jbl_Vstream_new(&jbl_stream_aes_128_cbc_encode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,1);
	((jbl_stream*)this)->extra[0].p=v;
	return this;
}
inline jbl_var * jbl_Vstream_aes_128_cbc_decode_new(jbl_aes_128_key *w,const unsigned char * v)
{
	jbl_var *this=jbl_Vstream_new(&jbl_stream_aes_128_cbc_decode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,1);
	((jbl_stream*)this)->extra[0].p=v;
	return this;
}
#endif
#endif
#endif
#undef ffmul
#endif