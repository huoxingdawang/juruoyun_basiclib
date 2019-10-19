/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_AES_H
#define __JRY_BL_AES_H
#include "jry_bl_string.h"
class jry_bl_aes
{
	public:
		jry_bl_aes						(unsigned char* key);
		unsigned char* 	encode			(unsigned char* a);
		unsigned char* 	encode			(const unsigned char* a,unsigned char* b);
		unsigned char* 	decode			(unsigned char* a);
		unsigned char*	decode			(const unsigned char* a,unsigned char *b);	
		jry_bl_string 	encode			(jry_bl_string a);
		jry_bl_string* 	encode			(jry_bl_string &out,jry_bl_string a);
		jry_bl_string 	decode			(jry_bl_string a);
		jry_bl_string* 	decode			(jry_bl_string &out,jry_bl_string a);
	private:
		unsigned char 	w[11][4][4];
		void 			add_round_key	(unsigned char state[][4], unsigned char k[][4]);
		unsigned char	ffmul			(unsigned char a,unsigned char b);
};
#endif