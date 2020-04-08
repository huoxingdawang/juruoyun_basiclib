/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_BASE64_H
#define __JRY_BL_BASE64_H
#include "jry_bl_base64_config.h"
#if JRY_BL_BASE64_ENABLE==1
#include "jry_bl_string.h"
#include "jry_bl_ying.h"
jry_bl_string *	jry_bl_base64_encode					(const jry_bl_string *this,jry_bl_string *result);
jry_bl_string *	jry_bl_base64_decode					(const jry_bl_string *this,jry_bl_string *result);

#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_stream.h"
extern			const jry_bl_stream_operater jry_bl_stream_base64_encode_operators;
extern			const jry_bl_stream_operater jry_bl_stream_base64_decode_operators;

#define			jry_bl_base64_encode_stream_init()		jry_bl_stream_new(&jry_bl_stream_base64_encode_operators,NULL,JRY_BL_STREAM_EXCEED_LENGTH+8,NULL)
#define			jry_bl_base64_decode_stream_init()		jry_bl_stream_new(&jry_bl_stream_base64_decode_operators,NULL,JRY_BL_STREAM_EXCEED_LENGTH+8,NULL)


//typedef struct __jry_bl_stream_operater jry_bl_stream_operater;
//extern const jry_bl_stream_operater jry_bl_stream_base64_encode_operator;
//extern const jry_bl_stream_operater jry_bl_stream_base64_decode_operator;
#endif

#endif
#endif