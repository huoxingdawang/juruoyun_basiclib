/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_string.h"
jry_bl_string::jry_bl_string()
{
	len=0;
	size=JRY_BL_STRING_BASIC_LENGTH;
	s=(char *)jry_bl_malloc(size);
	if(s==NULL)
		jry_bl_exception("ERR memory error");
}
jry_bl_string::jry_bl_string(JRY_BL_STRING_SIZE_TYPE sizee)
{
	len=0;
	size=sizee;
	s=(char *)jry_bl_malloc(size);
	if(s==NULL)
		jry_bl_exception("ERR memory error");
}
jry_bl_string::jry_bl_string(const char *in)
{
	len=0;
	while(in[len++]);len--;
	size=(ceil((long double)len/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
	s=(char *)jry_bl_malloc(size);
	if(s==NULL)
		jry_bl_exception("ERR memory error");
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<len;s[i]=in[i],i++);
}
char & jry_bl_string::operator[](JRY_BL_STRING_SIZE_TYPE i)
{
	if(i<len)
		return s[i];
	jry_bl_exception("ERR try to get too long");
}
const char & jry_bl_string::operator[](JRY_BL_STRING_SIZE_TYPE i) const
{
	if(i<len)
		return s[i];
	jry_bl_exception("ERR try to get too long");
}
jry_bl_string jry_bl_string::operator+=(const jry_bl_string& s2)
{
	if((len+s2.len)>size)
	{
		size=(ceil((long double)(len+s2.len)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		char * sb=(char *)jry_bl_realloc(s,size);
		if(sb==NULL)
			jry_bl_exception("ERR memory error");
		s=sb;
	}
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<s2.len;i++)
		s[len+i]=s2.s[i];
	len=(len+s2.len);
	s[len]=0;
	return *this;
}
jry_bl_string jry_bl_string::operator+=(const char * s2)
{
	JRY_BL_STRING_SIZE_TYPE s2_len=0;
	while(s2[s2_len++]);s2_len--;
	if((len+s2_len)>size)
	{
		size=(ceil((long double)(len+s2_len)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		char * sb=(char *)jry_bl_realloc(s,size);
		if(sb==NULL)
			jry_bl_exception("ERR memory error");
		s=sb;
	}
	for(int i=0;i<s2_len;i++)
		s[len+i]=s2[i];	
	len=(len+s2_len);
	s[len]=0;
	return *this;
}
jry_bl_string jry_bl_string::operator+=(long long in)
{
	register int f=(in<0),cnt=20;
	char b[21];
	if(f)
		in=-in;
	b[cnt--]=0;
	while(in)
	{
		b[cnt--]=in%10+'0';
		in/=10;
	}
	if(f)
		b[cnt--]='-';
	*this+=(const char *)(b+cnt+1);
	return *this;
}
jry_bl_string jry_bl_string::operator=(const jry_bl_string& s2)
{
	if(size<s2.len)
	{
		size=(ceil((long double)s2.len/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		char * sb=(char *)jry_bl_realloc(s,size);
		if(sb==NULL)
			jry_bl_exception("ERR memory error");
		s=sb;
	}
	for(len=0;len<s2.len;s[len]=s2.s[len],len++);
	return *this;
}
#if JRY_BL_STRING_USE_IOSTREAM==1
std::ostream &operator<< (std::ostream& out, const jry_bl_string& that)
{
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<that.len;i++)
	   out<<that.s[i];
	return out;
}
#endif
#if JRY_BL_STRING_USE_CSTDIO==1
void jry_bl_string::view(FILE * file)
{
	fprintf(file,"len:\t%lld\nsize:\t%lld\ns:\t",(long long)len,(long long)size);
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<len;fprintf(file,"%c",s[i++]));
	fprintf(file,"\n");
}
#endif
void jry_bl_string::free()
{
	len=0;
	size=0;
	jry_bl_free(s);
}
long long jry_bl_string::getint(JRY_BL_STRING_SIZE_TYPE start)
{
	register int f,i;register char c;register long long x=0;
	for (f=0,i=start;(c=s[i])<'0'||c>'9'&&i<len;f=c=='-',++i);
	for (x=c-'0',++i; (c=s[i])>='0'&&c<='9'&&i<len; x=(x<<3)+(x<<1)+c-'0',++i);
	return f?-x:x;
}
long long jry_bl_string::getint()
{
	return getint(0);
}
