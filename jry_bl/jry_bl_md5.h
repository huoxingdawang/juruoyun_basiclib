/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_MD5_H
#define __JRY_BL_MD5_H
#include "jry_bl_string.h"
#define JRY_BL_MD5_F(x,y,z) (((x)&(y))|((~x)&(z)))
#define JRY_BL_MD5_G(x,y,z) (((x)&(z))|((y)&(~z)))
#define JRY_BL_MD5_H(x,y,z) ((x)^(y)^(z))
#define JRY_BL_MD5_I(x,y,z) ((y)^((x)|(~z)))
#define JRY_BL_MD5_ROTATE_LEFT(num,n) ((((unsigned long long)(num))<<(n))|(((unsigned long long)(num))>>(32-(n))))
#define JRY_BL_MD5_FF(a,b,c,d,x,s,ac) {(a)+=JRY_BL_MD5_F((b),(c),(d))+(x)+ac;(a)=JRY_BL_MD5_ROTATE_LEFT((a),(s));(a)+=(b);}
#define JRY_BL_MD5_GG(a,b,c,d,x,s,ac) {(a)+=JRY_BL_MD5_G((b),(c),(d))+(x)+ac;(a)=JRY_BL_MD5_ROTATE_LEFT((a),(s));(a)+=(b);}
#define JRY_BL_MD5_HH(a,b,c,d,x,s,ac) {(a)+=JRY_BL_MD5_H((b),(c),(d))+(x)+ac;(a)=JRY_BL_MD5_ROTATE_LEFT((a),(s));(a)+=(b);}
#define JRY_BL_MD5_II(a,b,c,d,x,s,ac) {(a)+=JRY_BL_MD5_I((b),(c),(d))+(x)+ac;(a)=JRY_BL_MD5_ROTATE_LEFT((a),(s));(a)+=(b);}
const char jry_bl_md5_hex_humbers[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};;
class jry_bl_md5
{
	public:
		jry_bl_md5							(jry_bl_string& message);
		const unsigned char* 	get_digest	();
		jry_bl_string 			get_string	();
		jry_bl_string* 			get_string	(jry_bl_string& str);
	private:
		void 					init		(const unsigned char*input,JRY_BL_STRING_SIZE_TYPE len);
		void 					transform	(const unsigned char block[64]);
		void 					encode		(const unsigned int*input,unsigned char*output,JRY_BL_STRING_SIZE_TYPE length);
		void 					decode		(const unsigned char*input,unsigned int*output,JRY_BL_STRING_SIZE_TYPE length);
		bool 					finished;
		unsigned int 			state[4];
		unsigned int 			count[2];
		unsigned char			buffer[64];
		unsigned char			digest[16];
		static const unsigned char		padding[64];
};
#endif