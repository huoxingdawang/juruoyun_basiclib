/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_EXCEPTION_H
#define __JBL_EXCEPTION_H
#include "jbl_exception_config.h"
#if JBL_EXCEPTION_ENABLE==1
#include "jbl_ying.h"
#define JBL_ERROR_NO_ERROR		1000000
#define JBL_ERROR_NULL_POINTER	1000001
#define JBL_ERROR_MEMORY_ERROR	1000002
#define JBL_ERROR_FILE_NOT_EXIST	1000003
#define JBL_ERROR_STREAM_ERROR	1000004



#define jbl_exception(x) __jbl_exception(__FILE__,__LINE__,x)
void __jbl_exception(const char * file,int line,int x);
#endif
#endif
