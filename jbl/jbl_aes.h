/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_AES_H
#define __JBL_AES_H
#include "jbl_aes_config.h"
#if JBL_AES_128_ENABLE==1
#include "jbl_string.h"
#include "jbl_ying.h"
typedef unsigned char __jbl_aes_128_ex_key[11][4][4];
typedef struct __jbl_aes_128_key
{
	jbl_gc gc;
	__jbl_aes_128_ex_key key;
}jbl_aes_128_key;

jbl_aes_128_key*	jbl_aes_128_extend_key					(unsigned char* key);			//生成一个aes128加密密钥
jbl_aes_128_key*	jbl_aes_128_key_copy					(jbl_aes_128_key *that);		//复制一个aes128加密密钥
jbl_aes_128_key*	jbl_aes_128_key_free					(jbl_aes_128_key* w);		//释放一个aes128加密密钥
#if JBL_STREAM_ENABLE==1
typedef struct __jbl_stream_operater jbl_stream_operater;									//声明流处理器结构
#endif
#if JBL_AES_128_ECB_ENABLE==1
jbl_string *	jbl_aes_128_ecb_encode					(jbl_aes_128_key *w,const jbl_string *in,jbl_string *out);//进行AES128ECB加密
jbl_string *	jbl_aes_128_ecb_decode					(jbl_aes_128_key *w,const jbl_string *in,jbl_string *out);//进行AES128ECB解密
#if JBL_STREAM_ENABLE==1
extern const jbl_stream_operater jbl_stream_aes_128_ecb_encode_operators;//AES128ECB加密流处理器
extern const jbl_stream_operater jbl_stream_aes_128_ecb_decode_operators;//AES128ECB解密流处理器
#define			jbl_stream_aes_128_ecb_encode_new(w)	jbl_stream_new(&jbl_stream_aes_128_ecb_encode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,NULL)
#define			jbl_stream_aes_128_ecb_decode_new(w)	jbl_stream_new(&jbl_stream_aes_128_ecb_decode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,NULL)
#if JBL_VAR_ENABLE == 1
#define			jbl_vstream_aes_128_ecb_encode_new(w)	jbl_Vstream_new(&jbl_stream_aes_128_ecb_encode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,NULL)
#define			jbl_vstream_aes_128_ecb_decode_new(w)	jbl_Vstream_new(&jbl_stream_aes_128_ecb_decode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,NULL)
#endif

#endif
#endif
#if JBL_AES_128_CBC_ENABLE==1
jbl_string *	jbl_aes_128_cbc_encode					(jbl_aes_128_key *w,unsigned char *vi,const jbl_string *in,jbl_string *out);//进行AES128CBC加密
jbl_string *	jbl_aes_128_cbc_decode					(jbl_aes_128_key *w,unsigned char *vi,const jbl_string *in,jbl_string *out);//进行AES128CBC解密
#if JBL_STREAM_ENABLE==1
extern const jbl_stream_operater jbl_stream_aes_128_cbc_encode_operators;//AES128CBC加密流处理器
extern const jbl_stream_operater jbl_stream_aes_128_cbc_decode_operators;//AES128CBC解密流处理器
#define			jbl_stream_aes_128_cbc_encode_new(w,v)	jbl_stream_new(&jbl_stream_aes_128_cbc_encode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,v)
#define			jbl_stream_aes_128_cbc_decode_new(w,v)	jbl_stream_new(&jbl_stream_aes_128_cbc_decode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,v)
#if JBL_VAR_ENABLE == 1
#define			jbl_vstream_aes_128_cbc_encode_new(w,v)	jbl_Vstream_new(&jbl_stream_aes_128_cbc_encode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,v)
#define			jbl_vstream_aes_128_cbc_decode_new(w,v)	jbl_Vstream_new(&jbl_stream_aes_128_cbc_decode_operators,jbl_aes_128_key_copy(w),JBL_STREAM_EXCEED_LENGTH+32,NULL,0,v)
#endif


#endif

#endif
#endif
#endif