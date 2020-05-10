/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_BASE64_H
#define __JBL_BASE64_H
#include "jbl_base64_config.h"
#if JBL_BASE64_ENABLE==1
#include "jbl_string.h"
#include "jbl_ying.h"
jbl_string *	jbl_base64_encode					(const jbl_string *this,jbl_string *result);
jbl_string *	jbl_base64_decode					(const jbl_string *this,jbl_string *result);

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
extern			const jbl_stream_operater jbl_stream_base64_encode_operators;
extern			const jbl_stream_operater jbl_stream_base64_decode_operators;

#define			jbl_stream_base64_encode_new()		jbl_stream_new(&jbl_stream_base64_encode_operators,NULL,JBL_STREAM_EXCEED_LENGTH+8,NULL,0)
#define			jbl_stream_base64_decode_new()		jbl_stream_new(&jbl_stream_base64_decode_operators,NULL,JBL_STREAM_EXCEED_LENGTH+8,NULL,0)


//typedef struct __jbl_stream_operater jbl_stream_operater;
//extern const jbl_stream_operater jbl_stream_base64_encode_operator;
//extern const jbl_stream_operater jbl_stream_base64_decode_operator;
#endif

#endif
#endif