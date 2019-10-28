/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_VAR_H
#define __JRY_BL_VAR_H
#include "jry_bl_var_config.h"
#if JRY_BL_VAR_ENABLE==1
#include "jry_bl_string.h"
#if JRY_BL_VAR_USE_STDARG==1
#include <stdarg.h>
#endif


#define JRY_BL_VAR_TYPE_NULL				0
#define JRY_BL_VAR_TYPE_INT					1
#define JRY_BL_VAR_TYPE_LONG_LONG			2
#define JRY_BL_VAR_TYPE_UNSIGNED_INT		3
#define JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	4
#define JRY_BL_VAR_TYPE_FLOAT				5
#define JRY_BL_VAR_TYPE_DOUBLE				6
#define JRY_BL_VAR_TYPE_LONG_DOUBLE			7
#define JRY_BL_VAR_TYPE_TRUE				8
#define JRY_BL_VAR_TYPE_FALSE				9
#define JRY_BL_VAR_TYPE_CHAR				10
#define JRY_BL_VAR_TYPE_UNSIGNED_CHAR		11
#if JRY_BL_STRING_ENABLE==1
#define JRY_BL_VAR_TYPE_STRING				12
#endif

typedef struct
{
	unsigned char type;
	union
	{
		char _[32];
		int i;
		long long ll;
		unsigned int ui;
		unsigned long long ull;
		float f;
		double d;
		long double ld;
		char c;
		unsigned char uc;
#if JRY_BL_STRING_ENABLE==1
		jry_bl_string str;
#endif
	}data;
}jry_bl_var;
void	jry_bl_var_init(jry_bl_var *a);


#if JRY_BL_VAR_USE_STDARG==1
void	jry_bl_var_inits(int n,...);
#endif
#endif
#endif