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
inline void 	jry_bl_string_init	(jry_bl_string *this)			{this->len=this->size=0;this->s=NULL;this->light_copy=false;}
inline void 	jry_bl_string_free	(jry_bl_string *this)			{if(!this->light_copy)jry_bl_free(this->s);this->len=this->size=0;this->s=NULL;this->light_copy=false;}
inline char * jry_bl_string_get(jry_bl_string *this,jry_bl_string_size_type i)
{
	if(i<0)
		jry_bl_exception("ERR try to get too short");
	if(i<this->size)
		return &this->s[i];
	jry_bl_exception("ERR try to get too long");	
}
inline char * jry_bl_string_set(jry_bl_string *this,jry_bl_string_size_type i,char a)
{
	if(i<0)
		jry_bl_exception("ERR try to set too short");
	if(i<this->size)
		return this->s[i]=a,&this->s[i];
	jry_bl_exception("ERR try to get set long");	
}
inline void jry_bl_string_clear(jry_bl_string *this){this->len=0;}
void jry_bl_string_parse(jry_bl_string *this)
{
	if(this->light_copy)
		return;
	if(this->len==0)
		return jry_bl_string_free(this);
	jry_bl_string_size_type size=(ceil((long double)(this->len)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
	char * s=(this->s==NULL?(char *)jry_bl_malloc(size):(char *)jry_bl_realloc(this->s,size));
	if(s!=NULL)
		this->s=s,this->size=size;
}
void jry_bl_string_extend(jry_bl_string *this,jry_bl_string_size_type size)
{
	if(this->light_copy)
		jry_bl_exception("ERR memory error");
	if(size>this->size)
	{
		this->size=(ceil((long double)(size)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		char * s=(this->s==NULL?(char *)jry_bl_malloc(this->size):(char *)jry_bl_realloc(this->s,this->size));
		if(s==NULL)
			jry_bl_exception("ERR memory error");
		this->s=s;
	}		
}
void jry_bl_string_add_string(jry_bl_string *this,jry_bl_string *in)
{
	jry_bl_string_extend(this,this->len+in->len);
	for(jry_bl_string_size_type i=0;i<in->len;i++)
		this->s[this->len+i]=in->s[i];
	this->len=(this->len+in->len);
}
void jry_bl_string_add_char_pointer(jry_bl_string *this,char *in)
{
	jry_bl_string_size_type in_len=0;
	while(in[in_len++]);in_len--;
	jry_bl_string_extend(this,this->len+in_len);
	for(jry_bl_string_size_type i=0;i<in_len;i++)
		this->s[this->len+i]=in[i];
	this->len=(this->len+in_len);
}
void jry_bl_string_add_char(jry_bl_string *this,char in)
{
	jry_bl_string_extend(this,this->len+1);
	this->s[this->len++]=in;
}
inline void jry_bl_string_add_long_long(jry_bl_string *this,long long in)
{
	jry_bl_string_extend(this,this->len+22);
	if(in<0)
		jry_bl_string_add_char(this,'-'),in=-in;
	jry_bl_string_add_unsigned_long_long(this,in);
}
void jry_bl_string_add_unsigned_long_long(jry_bl_string *this,unsigned long long in)
{
	if(in==0)
		return jry_bl_string_add_char(this,'0');
	register int cnt=20;
	char b[21];
	b[cnt--]=0;
	while(in)
		b[cnt--]=in%10+'0',in/=10;
	jry_bl_string_add_char_pointer(this,b+cnt+1);
}
inline void jry_bl_string_add_long_double(jry_bl_string *this,long double in)
{
	jry_bl_string_add_long_double_len(this,in,18);
}
void jry_bl_string_add_long_double_len(jry_bl_string *this,long double in,unsigned char l)
{
	unsigned char len=l;
	if(len>18)
		len=18;
	jry_bl_string_extend(this,this->len+23+l-len);
	register long long inn=in;
	jry_bl_string_add_long_long(this,inn);
	jry_bl_string_add_char(this,'.');
	if(in<0)
		inn=-inn,in=-in;
	in-=inn;
	register unsigned long long ji=10;
	register unsigned char i=0;
	while(!(((in*ji-(unsigned long long)(in*ji))<1e-6)&&((in*ji-(unsigned long long)(in*ji))>-1e-6))&&i<len)
		ji=(ji<<3)+(ji<<1),i++;
	jry_bl_string_add_unsigned_long_long(this,((unsigned long long)((in*ji+0.5)/10)));
	for(unsigned char i=len;i<l;i++)
		jry_bl_string_add_char(this,'0');
}


#if JRY_BL_STRING_USE_STDIO==1
void jry_bl_string_view_ex(jry_bl_string *this,FILE * file,char*str,int a)
{
	if(a>=0)
		fprintf(file,"jry_bl_string %s %d:\n",str,a);
	else
		fprintf(file,"jry_bl_string:\n",str,a);
	fprintf(file,"\tlc:\t%d\n\tlen:\t%lld\n\tsize:\t%lld\n\ts:\t",this->light_copy,(long long)this->len,(long long)this->size);
	for(jry_bl_string_size_type i=0;i<this->len;fprintf(file,"%c",this->s[i++]));
	fprintf(file,"\n");
}
#endif
#if JRY_BL_STRING_USE_STDARG==1
inline void	jry_bl_string_inits(int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_string_init(va_arg(valist,jry_bl_string*));
	va_end(valist);	
}
inline void	jry_bl_string_frees(int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_string_free(va_arg(valist,jry_bl_string*));
	va_end(valist);	
}
inline void	jry_bl_string_clears(int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_string_clear(va_arg(valist,jry_bl_string*));
	va_end(valist);	
}
inline void	jry_bl_string_views(FILE * file,int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_string_view_ex(va_arg(valist,jry_bl_string*),file,"views",i);
	va_end(valist);	
}
#endif
/*
jry_bl_string* jry_bl_string::operator+=(float in){*this+=(long double)in;};
jry_bl_string* jry_bl_string::operator+=(double in){*this+=(long double)in;};
jry_bl_string* jry_bl_string::operator+=(long double in)
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
	return this;
}
jry_bl_string* jry_bl_string::operator=(const jry_bl_string& in){len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(const jry_bl_string* in){len=0;return (*this+=*in);};
jry_bl_string* jry_bl_string::operator=(const char * in)		{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(char in)				{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(int in)					{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(long in)				{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(long long in)			{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(unsigned int in)		{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(unsigned long in)		{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(unsigned long long in)	{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(float in)				{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(double in)				{len=0;return (*this+=in);};
jry_bl_string* jry_bl_string::operator=(long double in)			{len=0;return (*this+=in);};

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
	for(jry_bl_string_size_type i;i<len;i++)
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
	for(jry_bl_string_size_type i=0;i<len;i++)
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
	for(jry_bl_string_size_type i=0;i<len;i++)
		if(s[i]>b.s[i])
			return true;	
	return false;	
}
bool jry_bl_string::operator!=(const jry_bl_string& b){return ((*this==b)==false);}
bool jry_bl_string::operator<=(const jry_bl_string& b){return ((*this>b)==false);}
bool jry_bl_string::operator>=(const jry_bl_string& b){return ((*this<b)==false);}
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
	for(jry_bl_string_size_type i=0;i<that.len;i++)
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
void jry_bl_string::view(std::ostream & out)
{
	out<<"lc:\t"<<light_copy<<"\nlen:\t"<<len<<"\nsize:\t"<<size<<"\ns:\t";
	for(jry_bl_string_size_type i=0;i<len;out<<s[i++]);
	out<<'\n';
}
#endif
void jry_bl_string::add(const char * s2,jry_bl_string_size_type s2_len)
{
	extend(len+s2_len);
	for(jry_bl_string_size_type i=0;i<s2_len;i++)
		s[len+i]=s2[i];
	len=(len+s2_len);
}
long long jry_bl_string::get_int(jry_bl_string_size_type start)
{
	if(len==0&&start==0)
		return 0;
	if(start>=len)
		return 0;
	register bool f;register char c;register unsigned long long x=0;jry_bl_string_size_type i; 
	for(f=0,i=start;(c=s[i])<'0'||c>'9'&&i<len;f=c=='-',++i);
	for(x=c-'0',++i;(c=s[i])>='0'&&c<='9'&&i<len;x=(x<<3)+(x<<1)+c-'0',++i);
	return f?-x:x;
}
long long jry_bl_string::get_int()
{
	return get_int(0);
}
long double jry_bl_string::get_float(jry_bl_string_size_type start)
{
	if(len==0&&start==0)
		return 0;
	if(start>=len)
		return 0;
	register bool f;register char c;register unsigned long long x=0;jry_bl_string_size_type i; 
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
	a.extend(len+2);
	a='"';
	for(jry_bl_string_size_type i=0;i<len;i++)
		a+=(s[i]=='"'?"\\":""),a+=s[i];
	a+='"';
	return a;
}
jry_bl_string* jry_bl_string::to_json(jry_bl_string &a)
{
	a.extend(a.get_length()+len+2);
	a+='"';
	for(jry_bl_string_size_type i=0;i<len;i++)
		a+=(s[i]=='"'?"\\":""),a+=s[i];
	a+='"';
	return &a;	
}
void jry_bl_string::from_json(jry_bl_string &in){(*this).from_json(in,0);}
void jry_bl_string::from_json(jry_bl_string &in,jry_bl_string_size_type start)
{
	len=0;
	register jry_bl_string_size_type i=start,n=in.get_length();
	for(;(i<n)&&(!(in[i]=='"'&&(i==0||in[i-1]!='\\')));++i);
	for(++i;i<n&&!(in[i]=='"'&&in[i-1]!='\\');++i)
		if(!(in[i]=='\\'&&(i+1)<n&&in[i+1]=='"'))
			*this+=in[i];
	if(i==n)
		len=0;
}
const char * 			jry_bl_string::get_s(){return s;}
jry_bl_string_size_type jry_bl_string::get_length(){return len;}
jry_bl_string_size_type jry_bl_string::get_size(){return size;}
*/