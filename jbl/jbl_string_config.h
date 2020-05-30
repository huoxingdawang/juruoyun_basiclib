/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_STRING_CONFIG_H
#define __JBL_STRING_CONFIG_H
#include "jbl_config.h"
#if JBL_STRING_ENABLE==1
#include "jbl_ying.h"
#if __SIZEOF_POINTER__ == 8
	typedef jbl_uint64 			jbl_string_size_type;		//字符串长度类型
	typedef jbl_uint64 			jbl_string_hash_type;		//字符串哈希类型
#else
	typedef jbl_uint32 			jbl_string_size_type;		//字符串长度类型
	typedef jbl_uint32 			jbl_string_hash_type;		//字符串哈希类型
#endif

#define JBL_STRING_BASIC_LENGTH	32								//步进长度


#endif
#endif
