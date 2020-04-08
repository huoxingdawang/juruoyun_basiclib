/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_AES_H
#define __JRY_BL_AES_H
#include "jry_bl_aes_config.h"
#if JRY_BL_AES_128_ENABLE==1
#include "jry_bl_string.h"
#include "jry_bl_ying.h"
typedef unsigned char __jry_bl_aes_128_ex_key[11][4][4];
typedef struct __jry_bl_aes_128_key
{
	jry_bl_gc gc;
	__jry_bl_aes_128_ex_key key;
}jry_bl_aes_128_key;

jry_bl_aes_128_key*	jry_bl_aes_128_extend_key					(unsigned char* key);
jry_bl_aes_128_key*	jry_bl_aes_128_copy_key						(jry_bl_aes_128_key *that);
jry_bl_aes_128_key*	jry_bl_aes_128_free_key						(jry_bl_aes_128_key* w);
#if JRY_BL_STREAM_ENABLE==1
typedef struct __jry_bl_stream_operater jry_bl_stream_operater;
#endif
#if JRY_BL_AES_128_ECB_ENABLE==1
jry_bl_string *	jry_bl_aes_128_ecb_encode					(jry_bl_aes_128_key *w,const jry_bl_string *in,jry_bl_string *out);
jry_bl_string *	jry_bl_aes_128_ecb_decode					(jry_bl_aes_128_key *w,const jry_bl_string *in,jry_bl_string *out);
#if JRY_BL_STREAM_ENABLE==1
extern const jry_bl_stream_operater jry_bl_stream_aes_128_ecb_encode_operators;
extern const jry_bl_stream_operater jry_bl_stream_aes_128_ecb_decode_operators;
#define			jry_bl_stream_aes_128_ecb_encode_new(w)	jry_bl_stream_new(&jry_bl_stream_aes_128_ecb_encode_operators,jry_bl_aes_128_copy_key(w),JRY_BL_STREAM_EXCEED_LENGTH+32,NULL,0)
#define			jry_bl_stream_aes_128_ecb_decode_new(w)	jry_bl_stream_new(&jry_bl_stream_aes_128_ecb_decode_operators,jry_bl_aes_128_copy_key(w),JRY_BL_STREAM_EXCEED_LENGTH+32,NULL,0)
#endif
#endif
#if JRY_BL_AES_128_CBC_ENABLE==1
jry_bl_string *	jry_bl_aes_128_cbc_encode					(jry_bl_aes_128_key *w,unsigned char *vi,const jry_bl_string *in,jry_bl_string *out);
jry_bl_string *	jry_bl_aes_128_cbc_decode					(jry_bl_aes_128_key *w,unsigned char *vi,const jry_bl_string *in,jry_bl_string *out);
#if JRY_BL_STREAM_ENABLE==1
extern const jry_bl_stream_operater jry_bl_stream_aes_128_cbc_encode_operators;
extern const jry_bl_stream_operater jry_bl_stream_aes_128_cbc_decode_operators;
#define			jry_bl_stream_aes_128_cbc_encode_new(w,v)	jry_bl_stream_new(&jry_bl_stream_aes_128_cbc_encode_operators,jry_bl_aes_128_copy_key(w),JRY_BL_STREAM_EXCEED_LENGTH+32,NULL,(jry_bl_uint64)((jry_bl_uint8*)v))
#define			jry_bl_stream_aes_128_cbc_decode_new(w,v)	jry_bl_stream_new(&jry_bl_stream_aes_128_cbc_decode_operators,jry_bl_aes_128_copy_key(w),JRY_BL_STREAM_EXCEED_LENGTH+32,NULL,(jry_bl_uint64)((jry_bl_uint8*)v))

#endif

#endif
#endif
#endif