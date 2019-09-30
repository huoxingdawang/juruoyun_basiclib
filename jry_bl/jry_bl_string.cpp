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
jry_bl_string::jry_bl_string()						{len=size=0;s=NULL;light_copy=false;}
jry_bl_string::jry_bl_string(const char *in)		{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(int in)				{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(long in)				{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(long long in)			{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(unsigned int in)		{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(unsigned long in)		{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(unsigned long long in)	{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(float in)				{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(double in)				{len=size=0;s=NULL;light_copy=false;*this+=in;}
jry_bl_string::jry_bl_string(long double in)		{len=size=0;s=NULL;light_copy=false;*this+=in;}
char & jry_bl_string::operator[](JRY_BL_STRING_SIZE_TYPE i)
{
	if(i<0)
		jry_bl_exception("ERR try to get too short");
	if(i<size)
		return s[i];
	jry_bl_exception("ERR try to get too long");
}
const char & jry_bl_string::operator[](JRY_BL_STRING_SIZE_TYPE i) const
{
	if(i<0)
		jry_bl_exception("ERR try to get too short");
	if(i<size)
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
	register char b[21];
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
	register long long inn=in;
	*this+=inn;
	*this+='.';
	if(in<0)
		inn=-inn,in=-in;
	in-=inn;
	register unsigned long long ji=10;
	while(!(((in*ji-(unsigned long long)(in*ji))<1e-6)&&((in*ji-(unsigned long long)(in*ji))>-1e-6))&&ji<1e10)
		ji=(ji<<3)+(ji<<1);
	*this+=((unsigned long long)(in*ji));
	return *this;
}
jry_bl_string jry_bl_string::operator=(const jry_bl_string& in)	{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(const char * in)			{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(char in)					{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(int in)					{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(long in)					{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(long long in)			{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(unsigned int in)			{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(unsigned long in)		{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(unsigned long long in)	{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(float in)				{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(double in)				{len=0;return (*this+=in);};
jry_bl_string jry_bl_string::operator=(long double in)			{len=0;return (*this+=in);};

jry_bl_string jry_bl_string::operator+(const jry_bl_string& in)	{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(const char * in)			{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(char in)					{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(int in)					{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(long in)					{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(long long in)			{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(unsigned int in)			{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(unsigned long in)		{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(unsigned long long in)	{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(float in)				{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(double in)				{jry_bl_string a;a=*this;a+=in;return a;};
jry_bl_string jry_bl_string::operator+(long double in)			{jry_bl_string a;a=*this;a+=in;return a;};

jry_bl_string operator+(const char *in,jry_bl_string &in2)			{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(char in,jry_bl_string &in2)					{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(int in,jry_bl_string &in2)					{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(long in,jry_bl_string &in2)					{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(long long in,jry_bl_string &in2)			{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(unsigned int in,jry_bl_string &in2)			{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(unsigned long in,jry_bl_string &in2)		{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(unsigned long long in,jry_bl_string &in2)	{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(float in,jry_bl_string &in2)				{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(double in,jry_bl_string &in2)				{jry_bl_string a;a=in;a+=in2;return a;}
jry_bl_string operator+(long double in,jry_bl_string &in2)			{jry_bl_string a;a=in;a+=in2;return a;}
bool jry_bl_string::operator==(const jry_bl_string& b)
{
	if((s)==(b.s))
		return true;
	if(len!=b.len)
		return false;
	for(JRY_BL_STRING_SIZE_TYPE i;i<len;i++)
		if(s[i]!=b.s[i])
			return false;
	return true;
}
bool jry_bl_string::operator<(const jry_bl_string& b)
{
	if((s)==(b.s))
		return false;	
	if(len!=b.len)
		return len<b.len;
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<len;i++)
		if(s[i]<b.s[i])
			return true;
	return false;	
}
bool jry_bl_string::operator>(const jry_bl_string& b)
{
	if((s)==(b.s))
		return false;	
	if(len!=b.len)
		return len>b.len;
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<len;i++)
		if(s[i]>b.s[i])
			return true;	
	return false;	
}
bool jry_bl_string::operator!=(const jry_bl_string& b){return ((*this==b)==false);}
bool jry_bl_string::operator<=(const jry_bl_string& b){return ((*this>b)==false);}
bool jry_bl_string::operator>=(const jry_bl_string& b){return ((*this<b)==false);}
jry_bl_string jry_bl_string::operator<<(const jry_bl_string& b)
{
	free();
	len=b.len;
	size=b.size;
	s=b.s;
	light_copy=b.light_copy;
}
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
std::ostream &operator<< (std::ostream& out,const jry_bl_string& that)
{
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<that.len;i++)
	   out<<that.s[i];
	return out;
}
std::istream &operator>> (std::istream& in,jry_bl_string& that)
{
	register char a;
	that.free();
	for(;;)
	{
		in>>std::noskipws>>a;
		if(a==' '||a=='\n'||a=='\t')
			return in;
		that+=a;
	}
	return in;
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
void jry_bl_string::clear(){len=0;}
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
		return 0;
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
		return 0;
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
jry_bl_string jry_bl_string::to_json()
{
	jry_bl_string a;
	a='"';
	for(JRY_BL_STRING_SIZE_TYPE i=0;i<len;i++)
		a+=(s[i]=='"'?"\\":""),a+=s[i];
	a+='"';
	return a;
}
void jry_bl_string::from_json(jry_bl_string &in){(*this).from_json(in,0);}
void jry_bl_string::from_json(jry_bl_string &in,JRY_BL_STRING_SIZE_TYPE start)
{
	len=0;
	register JRY_BL_STRING_SIZE_TYPE i=start,n=in.get_length();
	for(;(i<n)&&(!(in[i]=='"'&&(i==0||in[i-1]!='\\')));++i);
	for(++i;i<n&&!(in[i]=='"'&&in[i-1]!='\\');++i)
		if(!(in[i]=='\\'&&(i+1)<n&&in[i+1]=='"'))
			*this+=in[i];
	if(i==n)
		len=0;
}
const char * 			jry_bl_string::get_s(){return s;}
JRY_BL_STRING_SIZE_TYPE jry_bl_string::get_length(){return len;}
JRY_BL_STRING_SIZE_TYPE jry_bl_string::get_size(){return size;}