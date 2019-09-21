/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_STRING_H
#define __JRY_BL_STRING_H

#include "jry_bl_exception.h"
#include "jry_bl_string_config.h"
#include "jry_bl_malloc.h"
#if JRY_BL_STRING_USE_IOSTREAM==1
#include <iostream>
#endif
#if JRY_BL_STRING_USE_CSTDIO==1
#include <cstdio>
#endif

#include <cmath>

class jry_bl_string
{
	private:
		JRY_BL_STRING_SIZE_TYPE	len;
		JRY_BL_STRING_SIZE_TYPE	size;
		char *					s;
	public:
		jry_bl_string							();
		jry_bl_string							(JRY_BL_STRING_SIZE_TYPE sizee);
		jry_bl_string							(const char *in);
		char & 					operator []		(JRY_BL_STRING_SIZE_TYPE i);
		const char & 			operator []		(JRY_BL_STRING_SIZE_TYPE i) const;
		jry_bl_string 			operator +=		(const jry_bl_string& b);
		jry_bl_string 			operator +=		(const char * s2);
		jry_bl_string 			operator +=		(long long in);
		jry_bl_string 			operator =		(const jry_bl_string& b);
#if JRY_BL_STRING_USE_IOSTREAM==1
		friend std::ostream &	operator <<		(std::ostream& out, const jry_bl_string& that);
#endif	
#if JRY_BL_STRING_USE_CSTDIO==1
		void 		view						(FILE * file);
#endif
		void 		free						();
		long long 	getint						();
		long long	getint						(JRY_BL_STRING_SIZE_TYPE start);
};
#endif
