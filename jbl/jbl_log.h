/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_LOG_H
#define __JBL_LOG_H
#include "jbl_log_config.h"
#if JBL_LOG_ENABLE==1
#include "jbl_string.h"
#include "jbl_time.h"
#include "jbl_scanner.h"
#include "jbl_pthread.h"

void	jbl_log_start	();
void	jbl_log_stop	();
void	jbl_log_add_log	(const char * file,const char * func,jbl_uint32 line,unsigned char *s,...);
#define	jbl_log(s,...)		jbl_log_add_log(__FILE__,__FUNCTION__,__LINE__,s,## __VA_ARGS__)




#else
#define	jbl_log_start()
#define	jbl_log_stop()
#define	jbl_log(s,...)

#endif
#endif
