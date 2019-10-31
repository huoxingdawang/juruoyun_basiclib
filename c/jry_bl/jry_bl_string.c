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
#if JRY_BL_STRING_ENABLE==1
inline void 	jry_bl_string_init	(jry_bl_string *this)			{this->len=this->size=0;this->s=NULL;this->light_copy=false;}
inline void 	jry_bl_string_free	(jry_bl_string *this)			{if(!this->light_copy)jry_bl_free(this->s);this->len=this->size=0;this->s=NULL;this->light_copy=false;}
inline unsigned char jry_bl_string_get(jry_bl_string *this,jry_bl_string_size_type i)
{
	if(i<0)
		return 0;
	if(i<this->len)
		return this->s[i];
	return 0;
}
inline unsigned char jry_bl_string_set(jry_bl_string *this,jry_bl_string_size_type i,unsigned char a)
{
	if(i<0)
		return 0;
	jry_bl_string_extend(this,i);
	return this->s[i]=a;
}
inline void jry_bl_string_clear(jry_bl_string *this){this->len=0;if(this->light_copy)this->size=0,this->s=NULL,this->light_copy=false;}
void jry_bl_string_parse(jry_bl_string *this)
{
	if(this->light_copy)
		return;
	if(this->len==0)
		return jry_bl_string_free(this);
	jry_bl_string_size_type size=(ceil((long double)(this->len)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
	unsigned char * s=(this->s==NULL?(unsigned char *)jry_bl_malloc(size):(unsigned char *)jry_bl_realloc(this->s,size));
	if(s!=NULL)
		this->s=s,this->size=size;
}
inline void jry_bl_string_extend(jry_bl_string *this,jry_bl_string_size_type size)
{
	if(size>this->size)
	{
		if(this->light_copy)
			jry_bl_exception("ERR memory error");
//		printf("\n\textend\n");
		this->size=(ceil((long double)(size)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		unsigned char * s=(this->s==NULL?(unsigned char *)jry_bl_malloc(this->size):(unsigned char *)jry_bl_realloc(this->s,this->size));
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
void jry_bl_string_add_char_pointer(jry_bl_string *this,unsigned char *in)
{
	jry_bl_string_size_type in_len=0;
	while(in[in_len++]);in_len--;
	jry_bl_string_extend(this,this->len+in_len);
	for(jry_bl_string_size_type i=0;i<in_len;i++)
		this->s[this->len+i]=in[i];
	this->len=(this->len+in_len);
}
void jry_bl_string_add_char_pointer_length(jry_bl_string *this,unsigned char *in,jry_bl_string_size_type len)
{
	jry_bl_string_extend(this,this->len+len);
	for(jry_bl_string_size_type i=0;i<len;i++)
		this->s[this->len+i]=in[i];
	this->len=(this->len+len);	
}
inline void jry_bl_string_add_char(jry_bl_string *this,unsigned char in)
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
	unsigned char b[21];
	b[cnt--]=0;
	while(in)
		b[cnt--]=in%10+'0',in/=10;
	jry_bl_string_add_char_pointer(this,b+cnt+1);
}
inline void jry_bl_string_add_long_double(jry_bl_string *this,long double in)
{
	jry_bl_string_equal_long_double_length(this,in,15);
}
void jry_bl_string_equal_long_double_length(jry_bl_string *this,long double in,unsigned char len)
{
	if(len>15)
		len=15;
	jry_bl_string_extend(this,this->len+40);
	register long long inn=in;
	jry_bl_string_add_long_long(this,inn);
	jry_bl_string_add_char(this,'.');
	if(in<0)
		inn=-inn,in=-in;
	in-=inn;
	register unsigned long long ji=10;
	register unsigned char i=0;
	while(i<len&&(in*ji!=(unsigned long long)(in*ji)))
		ji=(ji<<3)+(ji<<1),i++;
	jry_bl_string_add_unsigned_long_long(this,((unsigned long long)((in*ji+0.5)/10)));
}
inline void	jry_bl_string_equal_string				(jry_bl_string *this,jry_bl_string *in)								{jry_bl_string_clear(this);jry_bl_string_add_string(this,in);}
inline void jry_bl_string_equal_string_light		(jry_bl_string *this,jry_bl_string *in)								{jry_bl_string_free(this);this->len=in->len;this->size=in->size;this->s=in->s;this->light_copy=true;}
inline void jry_bl_string_equal_string_light_move	(jry_bl_string *this,jry_bl_string *in)								{jry_bl_string_free(this);this->len=in->len;this->size=in->size;this->s=in->s;this->light_copy=in->light_copy;in->light_copy=true;}
inline void	jry_bl_string_equal_char_pointer		(jry_bl_string *this,unsigned char *in)								{jry_bl_string_clear(this);jry_bl_string_add_char_pointer(this,in);}
inline void	jry_bl_string_equal_char_pointer_length	(jry_bl_string *this,unsigned char *in,jry_bl_string_size_type len)	{jry_bl_string_clear(this);jry_bl_string_add_char_pointer_length(this,in,len);}
inline void	jry_bl_string_equal_char				(jry_bl_string *this,unsigned char in)								{jry_bl_string_clear(this);jry_bl_string_add_char(this,in);}
inline void	jry_bl_string_equal_long_long			(jry_bl_string *this,long long in)									{jry_bl_string_clear(this);jry_bl_string_add_long_long(this,in);}
inline void	jry_bl_string_equal_unsigned_long_long	(jry_bl_string *this,unsigned long long in)							{jry_bl_string_clear(this);jry_bl_string_add_unsigned_long_long(this,in);}
inline void	jry_bl_string_equal_long_double			(jry_bl_string *this,long double in)								{jry_bl_string_clear(this);jry_bl_string_add_long_double(this,in);}
inline void	jry_bl_string_equal_long_double_len		(jry_bl_string *this,long double in,unsigned char l)				{jry_bl_string_clear(this);jry_bl_string_add_long_double_len(this,in,l);}
char jry_bl_string_space_ship(jry_bl_string *this,jry_bl_string *that)
{
	if(this->s==that->s)
		return 0;
	if(this->len!=that->len)
		return (this->len<that->len)?-1:1;
	for(jry_bl_string_size_type i=0;i<this->len;i++)
		if(this->s[i]<that->s[i])
			return -1;
		else if(this->s[i]>that->s[i])
			return 1;
	return 0;
}
inline long long			jry_bl_string_get_long_long(jry_bl_string *this)			{return jry_bl_string_get_long_long_start			(this,0);}
inline unsigned long long	jry_bl_string_get_unsigned_long_long(jry_bl_string *this)	{return jry_bl_string_get_unsigned_long_long_start	(this,0);}
inline long double			jry_bl_string_get_long_double(jry_bl_string *this)			{return jry_bl_string_get_long_double_start			(this,0);}
long long jry_bl_string_get_long_long_start(jry_bl_string *this,jry_bl_string_size_type start)
{
	if(this->len==0&&start==0)
		return 0;
	if(start>=this->len)
		return 0;
	register unsigned char c,f;register unsigned long long x=0;jry_bl_string_size_type i; 
	for(f=0,i=start;(c=this->s[i])<'0'||c>'9'&&i<this->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this->s[i])>='0'&&c<='9'&&i<this->len;x=(x<<3)+(x<<1)+c-'0',++i);
	return f?-x:x;	
}
unsigned long long jry_bl_string_get_unsigned_long_long_start(jry_bl_string *this,jry_bl_string_size_type start)
{
	if(this->len==0&&start==0)
		return 0;
	if(start>=this->len)
		return 0;
	register unsigned char c;register unsigned long long x=0;jry_bl_string_size_type i; 
	for(i=start;(c=this->s[i])<'0'||c>'9'&&i<this->len;++i);
	for(x=c-'0',++i;(c=this->s[i])>='0'&&c<='9'&&i<this->len;x=(x<<3)+(x<<1)+c-'0',++i);
	return x;	
}
long double	jry_bl_string_get_long_double_start(jry_bl_string *this,jry_bl_string_size_type start)
{
	if(this->len==0&&start==0)
		return 0;
	if(start>=this->len)
		return 0;
	register unsigned char c,f;register unsigned long long x=0;jry_bl_string_size_type i; 
	for(f=0,i=start;(c=this->s[i])<'0'||c>'9'&&i<this->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this->s[i])>='0'&&c<='9'&&i<this->len;x=(x<<3)+(x<<1)+c-'0',++i);
	if(this->s[i]!='.'||i==this->len)
		return (f?-x:x);
	register unsigned long long ji=10,y;++i;
	for(c=this->s[i],y=c-'0',++i;(c=this->s[i])>='0'&&c<='9'&&i<this->len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	return f?-(x+((long double)y/ji)):(x+((long double)y/ji));
}
void jry_bl_string_to_json(jry_bl_string *this,jry_bl_string *result)
{
	jry_bl_string_extend(this,result->len+this->len+2);
	jry_bl_string_add_char(result,'"');
	for(jry_bl_string_size_type i=0;i<this->len;i++)
		(this->s[i]=='"'?jry_bl_string_add_char(result,'\\'):' '),jry_bl_string_add_char(result,this->s[i]);
	jry_bl_string_add_char(result,'"');	
}
inline void	jry_bl_string_from_json(jry_bl_string *this,jry_bl_string *in){jry_bl_string_from_json_start(this,in,0);}
void jry_bl_string_from_json_start(jry_bl_string *this,jry_bl_string *in,jry_bl_string_size_type start)
{
	jry_bl_string_clear(this);
	register jry_bl_string_size_type i=start,n=in->len;
	for(;(i<n)&&(!(in->s[i]=='"'&&(i==0||in->s[i-1]!='\\')));++i);
	for(++i;i<n&&!(in->s[i]=='"'&&in->s[i-1]!='\\');++i)
		if(!(in->s[i]=='\\'&&(i+1)<n&&in->s[i+1]=='"'))
			jry_bl_string_add_char(this,in->s[i]);
	if(i==n)
		jry_bl_string_clear(this);
}
#if JRY_BL_STRING_USE_STDIO==1
/*#include <time.h>*/
inline void jry_bl_string_print(jry_bl_string *this,FILE * file)
{
	register jry_bl_string_size_type i=0;
	/*clock_t __start=clock();*/
	i+=fwrite(this->s+i,1<<10,(this->len-i)>>10,file)<<10;
	for(;i<this->len;fputc(this->s[i++],file));
	/*fprintf(stderr,"\n\nUse Time:%fs\n",((double)(clock()-__start)/CLOCKS_PER_SEC));*/
}
void jry_bl_string_view_ex(jry_bl_string *this,FILE * file,char*str,int a)
{
	if(a>=0)
		fprintf(file,"jry_bl_string %s %d:\n",str,a);
	else
		fprintf(file,"jry_bl_string:\n");
	fprintf(file,"\tlc:\t%d\n\tlen:\t%lld\n\tsize:\t%lld\n\ts:\t",this->light_copy,(long long)this->len,(long long)this->size);
	jry_bl_string_print(this,file);
	fputc('\n',file);
}
void jry_bl_string_add_file(jry_bl_string *this,FILE * file)
{
	/*clock_t __start=clock();*/
	fseek(file,0L,SEEK_END);
	register unsigned char c;
	register jry_bl_string_size_type size=ftell(file),i=0;
	jry_bl_string_extend(this,this->len+size);
	fseek(file,0L,SEEK_SET);
	i+=fread(this->s+this->len+i,1<<10,(size-i)>>10,file)<<10;this->len+=i;
	while(i<size)
		++i,jry_bl_string_add_char(this,fgetc(file));
	/*fprintf(stderr,"\n\nUse Time:%fs\n",((double)(clock()-__start)/CLOCKS_PER_SEC));*/
}
void jry_bl_string_add_file_end_by(jry_bl_string *this,FILE * file,unsigned char end)
{
	fseek(file,0L,SEEK_END);
	register unsigned char c;
	register jry_bl_string_size_type size=ftell(file),i=0;
	jry_bl_string_extend(this,this->len+size);
	fseek(file,0L,SEEK_SET);
	while(i<size&&((c=fgetc(file))!=end))
		++i,jry_bl_string_add_char(this,c);
}
inline void jry_bl_string_equal_file		(jry_bl_string *this,FILE * file)					{jry_bl_string_clear(this);jry_bl_string_add_file		(this,file);}
inline void jry_bl_string_equal_file_end_by	(jry_bl_string *this,FILE * file,unsigned char end)	{jry_bl_string_clear(this);jry_bl_string_add_file_end_by(this,file,end);}
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
#endif