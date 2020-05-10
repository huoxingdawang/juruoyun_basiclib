/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_TIME_H
#define __JBL_TIME_H
#include "jbl_time_config.h"
#if JBL_TIME_ENABLE==1
#include <sys/timeb.h>
#if JBL_USE_STDARG==1
#include <stdarg.h>
#endif
#define JBL_TIME_ZONE_ASIA_SHANGHAI 1

extern jbl_int8 jbl_time_time_zone;
typedef jbl_int64 jbl_time;
void	jbl_time_init			(jbl_time *this);
void	jbl_time_free			(jbl_time *this);
void	jbl_time_clear			(jbl_time *this);
void	jbl_time_now				(jbl_time *this);
#define	jbl_time_to_unix(x)		(*(x))
#define	jbl_time_from_unix(x,y)	((*(x))=(y))
#define	jbl_time_minus(x,y)		((*(x))-(*(y)))


#if JBL_STRING_ENABLE==1
#include "jbl_string.h"
void	jbl_time_to_string		(jbl_time *this,jbl_string *result);
#endif

#if JBL_USE_STDARG==1
void	jbl_time_inits		(int n,...);
void	jbl_time_frees		(int n,...);
void	jbl_time_clears		(int n,...);
#endif

#endif
#endif
