/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_base64.h"
jry_bl_string jry_bl_base64_encode(jry_bl_string &a)
{
	jry_bl_string result;
	jry_bl_base64_encode(result,a);
	return result;
}
jry_bl_string* jry_bl_base64_encode(jry_bl_string &result,jry_bl_string &a)
{
	register jry_bl_string_size_type i=0,len=a.get_length();
	const char table[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
	while(len>2)
	{
		result+=table[a[i+0]>>2];
		result+=table[((a[i+0]&0x03)<<4)+(a[i+1]>>4)];
		result+=table[((a[i+1]&0x0f)<<2)+(a[i+2]>>6)];
		result+=table[a[i+2]&0x3f];
		i+=3;
		len-=3;
	}
	if(len>0)
	{
		result+=table[a[i+0]>>2];
		if(len%3==1)
		{
			result+=table[(a[i+0]&0x03)<<4];
			result+="==";
		}
		else if(len%3==2)
		{
			result+=table[((a[i+0]&0x03)<<4)+(a[i+1]>>4)];
			result+=table[(a[i+1]&0x0f)<<2];
			result+="=";
		}
	}
	return &result;	
}
jry_bl_string jry_bl_base64_decode(jry_bl_string &a)
{
	jry_bl_string result;
	jry_bl_base64_decode(result,a);
	return result;
}
jry_bl_string* jry_bl_base64_decode(jry_bl_string &result,jry_bl_string &a)
{
	const char table[]={-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-2,-2,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,62,-2,-2,-2,63,52,53,54,55,56,57,58,59,60,61,-2,-2,-2,-2,-2,-2,-2,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,-2,-2,-2,-2,-2,-2,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};
	register jry_bl_string_size_type i=0,len=a.get_length();
	register char bin=0,ch;
	while(len-->0)
	{
		ch=a[i];
		if (ch=='=')
		{
			if (a[i+1]!='='&&(i%4)==1)
			{
				result.clear();
				return &result;
			}
			continue;
		}
		ch=table[ch];
		if (ch<0)
			continue;
		switch(i%4)
		{
			case 0:
				bin=ch<<2;
				break;
			case 1:
				bin|=ch>>4;
				result+=bin;
				bin=(ch&0x0f)<<4;
				break;
			case 2:
				bin|=ch>>2;
				result+=bin;
				bin=(ch&0x03)<<6;
				break;
			case 3:
				bin|=ch;
				result+=bin;
				break;
		}
		i++;
	}	
	return &result;
}