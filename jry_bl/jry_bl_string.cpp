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
	len=size=0;s=NULL;light_copy=false;
}
jry_bl_string::jry_bl_string(JRY_BL_STRING_SIZE_TYPE sizee)
{
	len=size=0;s=NULL;light_copy=false;
	extend(sizee);
	s=(char *)jry_bl_malloc(size);
	if(s==NULL)
		jry_bl_exception("ERR memory error");
}
jry_bl_string::jry_bl_string(const char *in)
{
	len=size=0;s=NULL;light_copy=false;
	while(in[len++]);len--;
	extend(len);
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
	extend(len+s2.len);
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
	extend(len+s2_len);
	for(int i=0;i<s2_len;i++)
		s[len+i]=s2[i];	
	len=(len+s2_len);
	s[len]=0;
	return *this;
}
jry_bl_string jry_bl_string::operator+=(char c)
{
	extend(len+1);
	s[len++]=c;
}
jry_bl_string jry_bl_string::operator +=(int in){*this+=(long long)in;};
jry_bl_string jry_bl_string::operator +=(long in){*this+=(long long)in;};
jry_bl_string jry_bl_string::operator +=(long long in){if(in<0)*this+='-',in=-in;*this+=(unsigned long long)in;}
jry_bl_string jry_bl_string::operator +=(unsigned int in){*this+=(unsigned long long)in;};
jry_bl_string jry_bl_string::operator +=(unsigned long in){*this+=(unsigned long long)in;};
jry_bl_string jry_bl_string::operator +=(unsigned long long in)
{
	if(in==0)
		return (*this+='0');
	register int cnt=20;
	char b[21];
	b[cnt--]=0;
	while(in)
	{
		b[cnt--]=in%10+'0';
		in/=10;
	}
	*this+=(const char *)(b+cnt+1);
	return *this;
}
jry_bl_string jry_bl_string::operator+=(float in){*this+=(long double)in;};
jry_bl_string jry_bl_string::operator+=(double in){*this+=(long double)in;};
jry_bl_string jry_bl_string::operator+=(long double in)
{
	long long inn=in;
	*this+=inn;
	*this+='.';
	if(in<0)
		inn=-inn,in=-in;
	in-=inn;
	unsigned long long ji=10;
	while(!(((in*ji-(unsigned long long)(in*ji))<1e-6)&&((in*ji-(unsigned long long)(in*ji))>-1e-6))&&ji<1e10)
		ji=(ji<<3)+(ji<<1);
	*this+=((unsigned long long)(in*ji));
	return *this;
}
jry_bl_string jry_bl_string::operator=(const jry_bl_string& in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(const char * in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(char in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(int in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(long in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(long long in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(unsigned int in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(unsigned long in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(unsigned long long in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(float in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(double in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(long double in){len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator<<(jry_bl_string& b)
{
	free();
	len=b.len;
	size=b.size;
	s=b.s;
	light_copy=b.light_copy;
	b.light_copy=true;
}
jry_bl_string jry_bl_string::operator>>(jry_bl_string& b)
{
	b.free();
	b.len=len;
	b.size=size;
	b.s=s;
	b.light_copy=true;
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
	fprintf(file,"lc:\t%d\nlen:\t%lld\nsize:\t%lld\ns:\t",light_copy,(long long)len,(long long)size);
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<len;fprintf(file,"%c",s[i++]));
	fprintf(file,"\n");
}
#endif
void jry_bl_string::free()
{
	if(!light_copy)
		jry_bl_free(s);
	len=size=0;s=NULL;light_copy=false;
}
void jry_bl_string::parse()
{
	if(light_copy)
		return;
	if(len==0)
		return free();
	JRY_BL_STRING_SIZE_TYPE sizee=(ceil((long double)(len)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
	char * sb=(s==NULL?(char *)jry_bl_malloc(sizee):(char *)jry_bl_realloc(s,sizee));
	if(sb!=NULL)
		s=sb,size=sizee;
}
void jry_bl_string::extend(JRY_BL_STRING_SIZE_TYPE sizee)
{
	if(light_copy)
		jry_bl_exception("ERR memory error");
	if(sizee>size)
	{
		size=(ceil((long double)(sizee)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		char * sb=(s==NULL?(char *)jry_bl_malloc(size):(char *)jry_bl_realloc(s,size));
		if(sb==NULL)
			jry_bl_exception("ERR memory error");
		s=sb;
	}	
}
long long jry_bl_string::get_int(JRY_BL_STRING_SIZE_TYPE start)
{
	if(len==0&&start==0)
		return 0;
	if(start>=len)
		jry_bl_exception("ERR try to get too long");
	register bool f;register char c;register unsigned long long x=0;JRY_BL_STRING_SIZE_TYPE i; 
	for(f=0,i=start;(c=s[i])<'0'||c>'9'&&i<len;f=c=='-',++i);
	for(x=c-'0',++i;(c=s[i])>='0'&&c<='9'&&i<len;x=(x<<3)+(x<<1)+c-'0',++i);
	return f?-x:x;
}
long long jry_bl_string::get_int()
{
	return get_int(0);
}
long double jry_bl_string::get_float(JRY_BL_STRING_SIZE_TYPE start)
{
	if(len==0&&start==0)
		return 0;
	if(start>=len)
		jry_bl_exception("ERR try to get too long");	
	register bool f;register char c;register unsigned long long x=0;JRY_BL_STRING_SIZE_TYPE i; 
	for(f=0,i=start;(c=s[i])<'0'||c>'9'&&i<len;f=c=='-',++i);
	for(x=c-'0',++i;(c=s[i])>='0'&&c<='9'&&i<len;x=(x<<3)+(x<<1)+c-'0',++i);
	if(s[i]!='.'||i==len)
		return f?-x:x;
	register unsigned long long ji=10,y;++i;
	for(c=s[i],y=c-'0',++i;(c=s[i])>='0'&&c<='9'&&i<len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	return f?-(x+((long double)y/ji)):(x+((long double)y/ji));
}
long double jry_bl_string::get_float()
{
	return get_float(0);
}
bool jry_bl_string::get_is_light_copy()
{
	return light_copy;
}
