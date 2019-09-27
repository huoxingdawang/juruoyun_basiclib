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
		bool 					light_copy;
	public:
		jry_bl_string							();
		jry_bl_string							(JRY_BL_STRING_SIZE_TYPE sizee);
		jry_bl_string							(const char *in);
		char & 					operator []		(JRY_BL_STRING_SIZE_TYPE i);
		const char & 			operator []		(JRY_BL_STRING_SIZE_TYPE i) const;

		jry_bl_string 			operator +=		(const jry_bl_string& b);
		jry_bl_string 			operator +=		(const char * s2);
		jry_bl_string 			operator +=		(char c);
		jry_bl_string 			operator +=		(int in);
		jry_bl_string 			operator +=		(long in);
		jry_bl_string 			operator +=		(long long in);
		jry_bl_string 			operator +=		(unsigned int in);
		jry_bl_string 			operator +=		(unsigned long in);
		jry_bl_string 			operator +=		(unsigned long long in);
		jry_bl_string 			operator +=		(float in);
		jry_bl_string 			operator +=		(double in);
		jry_bl_string 			operator +=		(long double in);
		
		jry_bl_string 			operator =		(const jry_bl_string& in);	//深拷贝
		jry_bl_string 			operator =		(const char * in);
		jry_bl_string 			operator =		(char in);
		jry_bl_string 			operator =		(int in);
		jry_bl_string 			operator =		(long in);
		jry_bl_string 			operator =		(long long in);
		jry_bl_string 			operator =		(unsigned int in);
		jry_bl_string 			operator =		(unsigned long in);
		jry_bl_string 			operator =		(unsigned long long in);
		jry_bl_string 			operator =		(float in);
		jry_bl_string 			operator =		(double in);
		jry_bl_string 			operator =		(long double in);
		
		jry_bl_string 			operator +		(const jry_bl_string& in);	//深拷贝
		jry_bl_string 			operator +		(const char * in);
		jry_bl_string 			operator +		(char in);
		jry_bl_string 			operator +		(int in);
		jry_bl_string 			operator +		(long in);
		jry_bl_string 			operator +		(long long in);
		jry_bl_string 			operator +		(unsigned int in);
		jry_bl_string 			operator +		(unsigned long in);
		jry_bl_string 			operator +		(unsigned long long in);
		jry_bl_string 			operator +		(float in);
		jry_bl_string 			operator +		(double in);
		jry_bl_string 			operator +		(long double in);
		
		friend jry_bl_string	operator +		(const char * in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(char in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(int in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(long in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(long long in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(unsigned int in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(unsigned long in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(unsigned long long in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(float in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(double in,jry_bl_string &in2);
		friend jry_bl_string	operator +		(long double in,jry_bl_string &in2);
		
		jry_bl_string 			operator <<		(const jry_bl_string& b);	//浅拷贝 b拷贝到自身，如果可能，light_copy标记不被放到b，内存管理权被放到自身
		jry_bl_string 			operator <<		(jry_bl_string& b);			//浅拷贝 b拷贝到自身，如果可能，light_copy标记被放到b，内存管理权被放到自身
		jry_bl_string 			operator >>		(jry_bl_string& b);			//浅拷贝 自身拷贝到b，如果可能，light_copy标记被放到b，内存管理权被放到自身

#if JRY_BL_STRING_USE_IOSTREAM==1
		friend std::ostream &	operator <<		(std::ostream& out, const jry_bl_string& that);
#endif	
#if JRY_BL_STRING_USE_CSTDIO==1
		void 			view						(FILE * file);
#endif
		void 			free						();
		void 			parse						();
		void 			extend						(JRY_BL_STRING_SIZE_TYPE sizee);
		long long 		get_int						();
		long long		get_int						(JRY_BL_STRING_SIZE_TYPE start);
		long double 	get_float					();
		long double		get_float					(JRY_BL_STRING_SIZE_TYPE start);
		bool			get_is_light_copy			();
		jry_bl_string 	to_json						();
		void 			from_json					(jry_bl_string &in,JRY_BL_STRING_SIZE_TYPE start);
		JRY_BL_STRING_SIZE_TYPE get_length			();
};
#endif
