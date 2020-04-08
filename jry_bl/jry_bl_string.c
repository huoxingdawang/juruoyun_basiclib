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
#if JRY_BL_USE_STDARG==1
#include <stdarg.h>
#endif
#include "jry_bl_exception.h"
#include "jry_bl_malloc.h"
#include "jry_bl_ying.h"
jry_bl_string_size_type jry_bl_strlen(char *a){jry_bl_string_size_type b=0;while(a[b++]);return b-1;}
jry_bl_string * jry_bl_string_new()
{
	jry_bl_string *this=jry_bl_malloc((sizeof(jry_bl_string)));
	jry_bl_gc_init(this);
	jry_bl_gc_plus(this);//增加引用计数
	this->len=0;
	this->h=0;
	this->size=0;
	this->s=NULL;
	return this;
}
jry_bl_string* jry_bl_string_free(jry_bl_string *this)
{
//	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	if(this==NULL)return NULL;
	jry_bl_gc_minus(this);
	if(!jry_bl_gc_reference_cnt(this))
		((jry_bl_gc_is_ref(this))?jry_bl_string_free((jry_bl_string *)jry_bl_refer_pull(this)):jry_bl_free(this->s)),jry_bl_free(this);
	return NULL;
}
jry_bl_string *jry_bl_string_extend_to(jry_bl_string *this,jry_bl_string_size_type size)
{
	jry_bl_max_update(size,JRY_BL_STRING_BASIC_LENGTH);
	if(this==NULL)this=jry_bl_string_new();		
	size=1LL<<(jry_bl_highbit(size-1)+1);
	jry_bl_reference *ref=NULL;
	if(jry_bl_gc_is_ref(this))
		ref=(jry_bl_reference*)this,this=((jry_bl_reference*)this)->ptr;
	if(jry_bl_gc_reference_cnt(this)==1)
	{
		if(size>this->size)
			this->size=size,this->s=(this->s==NULL?(unsigned char *)jry_bl_malloc(this->size):(unsigned char *)jry_bl_realloc(this->s,this->size));		
	}
	else
	{
		jry_bl_string *tmp=jry_bl_string_new();
		tmp->size=size;
		tmp->len=this->len;
		tmp->h=this->h;
		tmp->s=(unsigned char *)jry_bl_malloc(tmp->size);
		jry_bl_memory_copy(tmp->s,this->s,this->len);
		jry_bl_string_free(this);
		this=tmp;
	}
	if(ref)
		ref->ptr=this,this=(jry_bl_string*)ref;
	return this;
}
jry_bl_string *jry_bl_string_clear(jry_bl_string *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	this=jry_bl_string_extend_to(this,0);
	jry_bl_string *this_=jry_bl_refer_pull(this);
	this_->len=0;
	this_->h=0;	
	return this;
}
inline jry_bl_string *jry_bl_string_copy(jry_bl_string *that)
{
	if(that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	jry_bl_gc_plus(that);
	return that;
}
inline jry_bl_string *jry_bl_string_rcopy(jry_bl_string *that)
{
	if(that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	return jry_bl_string_copy(jry_bl_refer_pull(that));
}
jry_bl_string *jry_bl_string_equal(jry_bl_string *this,jry_bl_string *that)
{
	if(this!=NULL)jry_bl_string_free(this);	
	jry_bl_gc_plus(that);
	return that;
}
jry_bl_uint32 jry_bl_string_hash(jry_bl_string *this)
{
	jry_bl_string *this_=jry_bl_refer_pull(this);
	if(this_->h==0)
		for(jry_bl_string_size_type i=0;i<this_->len;i++)
			this_->h=(this_->h<<5)+this_->h+this_->s[i];
	return this_->h;
}
jry_bl_string *jry_bl_string_add_chars_length(jry_bl_string *this,unsigned char *in,jry_bl_string_size_type len)
{
	this=jry_bl_string_extend(this,len);
	jry_bl_string *this_=jry_bl_refer_pull(this);
	this_->h=0;	
	jry_bl_memory_copy(this_->s+this_->len,in,len);
	this_->len=(this_->len+len);
	return this;
}
jry_bl_string *jry_bl_string_add_string(jry_bl_string *this,const jry_bl_string *in)
{
	const jry_bl_string *in_=jry_bl_refer_pull(in);
	this=jry_bl_string_extend(this,in_->len);
	jry_bl_string *this_=jry_bl_refer_pull(this);
	jry_bl_memory_copy(this_->s+this_->len,in_->s,in_->len);
	this_->len=(this_->len+in_->len);
	return this;
}
inline jry_bl_string *jry_bl_string_add_char(jry_bl_string *this,const char c)
{
	this=jry_bl_string_extend(this,1);
	jry_bl_string *this_=jry_bl_refer_pull(this);
	jry_bl_string_add_char_force(this_,c);
	return this;
}
inline jry_bl_string * jry_bl_string_add_int64_length(jry_bl_string *this,jry_bl_int64 in,jry_bl_uint8 len,char c)
{
	this=jry_bl_string_extend(this,22);
	jry_bl_string *this_=jry_bl_refer_pull(this);
	if(in<0)
		jry_bl_string_add_char_force(this_,'-'),in=-in;
	return jry_bl_string_add_uint64_length(this,in,len,c);
}
jry_bl_string * jry_bl_string_add_uint64_length(jry_bl_string *this,jry_bl_uint64 in,jry_bl_uint8 len,char c)
{
	this=jry_bl_string_extend(this,(len>21?len:21));
	jry_bl_string *this_=jry_bl_refer_pull(this);
	if(in==0)
	{
		for(jry_bl_uint8 i=1;i<len;jry_bl_string_add_char_force(this_,c),++i);
		return jry_bl_string_add_char_force(this_,'0'),this_;
	}
	int cnt=20;
	unsigned char b[21];
	b[cnt--]=0;
	while(in)b[cnt--]=in%10+'0',in/=10;
	for(jry_bl_uint8 i=19-cnt;i<len;jry_bl_string_add_char_force(this_,c),++i);
	return jry_bl_string_add_chars_length(this,b+cnt+1,19-cnt);
}
jry_bl_string * jry_bl_string_add_double_length(jry_bl_string *this,double in,unsigned char len)
{
	this=jry_bl_string_extend(this,jry_bl_max(len,40));
	jry_bl_string *this_=jry_bl_refer_pull(this);	
	jry_bl_int64 inn=in;
	this_=jry_bl_string_add_int64(this_,inn);
	jry_bl_string_add_char_force(this_,'.');
	if(in<0)
		inn=-inn,in=-in;
	in-=inn;
	jry_bl_uint64 ji=10;
	unsigned char i=0;
	for(double t=in*ji;i<len&&(t-(jry_bl_uint64)t<(-JRY_BL_DOUBLE_PRECISION)||t-(jry_bl_uint64)t>(JRY_BL_DOUBLE_PRECISION));ji=(ji<<3)+(ji<<1),t=in*ji,++i);
	return jry_bl_string_add_uint64(this,((jry_bl_uint64)((in*ji+0.5)/10)));
}
jry_bl_string * jry_bl_string_add_unicode_as_utf8(jry_bl_string *this,unsigned long unicode)
{
	this=jry_bl_string_extend(this,6);
	jry_bl_string *this_=jry_bl_refer_pull(this);	
	if(unicode<=0x7F)
		jry_bl_string_add_char_force(this_,unicode&0x7F);
	else if(unicode>=0x80&&unicode<=0x7FF)
		jry_bl_string_add_char_force(this_,((unicode>>6)&0x1F)|0xC0),jry_bl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x800&&unicode<=0xFFFF)
		jry_bl_string_add_char_force(this_,((unicode>>12)&0x0F)|0xE0),jry_bl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jry_bl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x10000&&unicode<=0x10FFFF)
		jry_bl_string_add_char_force(this_,((unicode>>18)&0x7)|0xF0),jry_bl_string_add_char_force(this_,((unicode>>12)&0x3F)|0x80),jry_bl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jry_bl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x200000&&unicode<=0x3FFFFFF)
		jry_bl_string_add_char_force(this_,((unicode>>24)&0x3)|0xF8),jry_bl_string_add_char_force(this_,((unicode>>18)&0x3F)|0x80),jry_bl_string_add_char_force(this_,((unicode>>12)&0x3F)|0x80),jry_bl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jry_bl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x4000000&&unicode<=0x7FFFFFFF)
		jry_bl_string_add_char_force(this_,((unicode>>30)&0x1)|0xFC),jry_bl_string_add_char_force(this_,((unicode>>24)&0x3F)|0x80),jry_bl_string_add_char_force(this_,((unicode>>18)&0x3F)|0x80),jry_bl_string_add_char_force(this_,((unicode>>12)&0x3F)|0x80),jry_bl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jry_bl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	return this;
}
jry_bl_string * jry_bl_string_add_hex(jry_bl_string *this,jry_bl_uint64 in)
{
	unsigned char n=1;
	while((in>>(n<<2)))++n;
	this=jry_bl_string_extend(this,n+1);
	jry_bl_string *this_=jry_bl_refer_pull(this);	
	const char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(unsigned char i=0;i<n;++i)
		jry_bl_string_add_char_force(this_,hex[(in>>(i<<2))&15]);
	return this;
}
inline jry_bl_string * jry_bl_string_add_hex_8bits(jry_bl_string *this,jry_bl_uint8 in)
{
	const char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	this=jry_bl_string_extend(this,2);
	jry_bl_string *this_=jry_bl_refer_pull(this);	
	jry_bl_string_add_char_force(this_,hex[in>>4]),jry_bl_string_add_char_force(this_,hex[in&15]);	
	return this;
}
char jry_bl_string_space_ship(const jry_bl_string *this,const jry_bl_string *that)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	const jry_bl_string *this_=jry_bl_refer_pull(this);	
	const jry_bl_string *that_=jry_bl_refer_pull(that);	
	if(this_==that_||this_->s==that_->s)
		return 0;
	if(this_->len!=that_->len)
		return (this_->len<that_->len)?-1:1;
	for(jry_bl_string_size_type i=0;i<this_->len;i++)
		if(this_->s[i]<that_->s[i])
			return -1;
		else if(this_->s[i]>that_->s[i])
			return 1;
	return 0;
}
jry_bl_int64 jry_bl_string_get_int64_start(const jry_bl_string *this,jry_bl_string_size_type *start)
{
	if(this==NULL||start==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	const jry_bl_string *this_=jry_bl_refer_pull(this);		
	jry_bl_string_size_type i=*start; 	
	if(i>=this_->len)
		return 0;
	unsigned char c,f;jry_bl_uint64 x=0;
	for(f=0;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	*start=i;
	return f?-x:x;	
}
inline jry_bl_int64 jry_bl_string_get_int64_start_v(const jry_bl_string *this,jry_bl_string_size_type start){return jry_bl_string_get_int64_start(this,&start);};
jry_bl_uint64 jry_bl_string_get_uint64_start(const jry_bl_string *this,jry_bl_string_size_type *start)
{
	if(this==NULL||start==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	const jry_bl_string *this_=jry_bl_refer_pull(this);		
	jry_bl_string_size_type i=*start; 	
	if(i>=this_->len)
		return 0;
	unsigned char c;jry_bl_uint64 x=0;
	for(;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	*start=i;
	return x;	
}
inline jry_bl_uint64 jry_bl_string_get_uint64_start_v(const jry_bl_string *this,jry_bl_string_size_type start){return jry_bl_string_get_uint64_start(this,&start);};
double jry_bl_string_get_double_start(const jry_bl_string *this,jry_bl_string_size_type *start)
{
	if(this==NULL||start==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	const jry_bl_string *this_=jry_bl_refer_pull(this);		
	jry_bl_string_size_type i=*start;
	if(i>=this_->len)
		return 0;
	unsigned char c,f;jry_bl_uint64 x=0;
	for(f=0;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	*start=i;
	if(this_->s[i]!='.'||i==this_->len)
		return (f?-(double)x:(double)x);
	jry_bl_uint64 ji=10,y;++i;
	for(c=this_->s[i],y=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	*start=i;
	return f?(-((long double)x+((long double)y/ji))):((long double)x+((long double)y/ji));
}
inline double jry_bl_string_get_double_start_v(const jry_bl_string *this,jry_bl_string_size_type start){return jry_bl_string_get_double_start(this,&start);};
jry_bl_uint64 jry_bl_string_get_hex_start(const jry_bl_string *this,jry_bl_string_size_type *start)
{
	if(this==NULL||start==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	const jry_bl_string *this_=jry_bl_refer_pull(this);			
	jry_bl_string_size_type i=*start; 	
	if(i>=this_->len)
		return 0;
	unsigned char c;jry_bl_uint64 x=0;
	for(;((c=this_->s[i])<'0'||c>'9')&&(c<'a'||c>'f')&&(c<'A'||c>'F')&&i<this_->len;++i);
	for(x=((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i;(((c=this_->s[i])>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))&&i<this_->len;x=(x<<4)+((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i);
	*start=i;
	return x;
}
inline jry_bl_uint64 jry_bl_string_get_hex_start_v(const jry_bl_string *this,jry_bl_string_size_type start){return jry_bl_string_get_hex_start(this,&start);};
jry_bl_string_size_type	jry_bl_string_find_char_start(const jry_bl_string *this,unsigned char in,jry_bl_string_size_type start)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	const jry_bl_string *this_=jry_bl_refer_pull(this);			
	for(;start<this_->len&&this_->s[start]!=in;++start);
	return (start);
}
// jry_bl_string_size_type jry_bl_string_from_json_start(jry_bl_string *this,const jry_bl_string *in,jry_bl_string_size_type start)
// {
	// if(this==NULL||in==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	// jry_bl_string_size_type i=start,n=in->len,no=this->len,st,en;
	// for(;(i<n)&&(!(in->s[i]=='"'&&(i==0||in->s[i-1]!='\\')));++i)if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')return start;++i;st=i;
	// for(;i<n&&!(in->s[i]=='"'&&in->s[i-1]!='\\');++i);en=i;++i;
	// if((i-1)>=n)
		// return start;
	// jry_bl_string_extend(this,en-st);
	// for(i=st;i<en;i++)
	// {
		// if(((i+1)<en)&&in->s[i]=='\\'&&in->s[i+1]=='u')
			// i+=2,jry_bl_string_add_unicode_as_utf8(this,jry_bl_string_get_hex_start(in,&i)),--i;
		// else
			// jry_bl_string_add_char_force(this,in->s[i]);
	// }
	// return en+1;
// }
// inline void jry_bl_string_print(const jry_bl_string *this,FILE * file)
// {
	// if(this==NULL||file==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	// jry_bl_string_size_type i=0;
	// i+=fwrite(this->s+i,1<<10,(this->len-i)>>10,file)<<10;
	// for(;i<this->len;fputc(this->s[i++],file));
// }
// void jry_bl_string_add_file(jry_bl_string *this,FILE * file)
// {
	// if(this==NULL||file==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	// /*clock_t __start=clock();*/
	// fseek(file,0L,SEEK_END);
	// unsigned char c;
	// jry_bl_string_size_type size=ftell(file),i=0;
	// jry_bl_string_extend(this,size);
	// fseek(file,0L,SEEK_SET);
	// i+=fread(this->s+this->len+i,1<<10,(size-i)>>10,file)<<10;this->len+=i;
	// while(i<size)
		// ++i,jry_bl_string_add_char(this,fgetc(file));
	// /*fprintf(stderr,"\n\nUse Time:%fs\n",((double)(clock()-__start)/CLOCKS_PER_SEC));*/
// }
// void jry_bl_string_add_file_end_by(jry_bl_string *this,FILE * file,unsigned char end)
// {
	// if(this==NULL||file==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	// fseek(file,0L,SEEK_END);
	// unsigned char c;
	// jry_bl_string_size_type size=ftell(file),i=0;
	// jry_bl_string_extend(this,size);
	// fseek(file,0L,SEEK_SET);
	// while(i<size&&((c=fgetc(file))!=end))
		// ++i,jry_bl_string_add_char(this,c);
// }

// #if JRY_BL_VAR_ENABLE==1
// #include "jry_bl_var.h"	
// inline void				jry_bl_var_equal_string				(jry_bl_var *this,jry_bl_string *that,jry_bl_uint8 copytype){jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_copy(this->data.p,that,copytype);}
// inline void				jry_bl_var_equal_string_pointer		(jry_bl_var *this,jry_bl_string *that){jry_bl_var_free(this);jry_bl_var_flag_pointer(this)=true;this->type=JRY_BL_VAR_TYPE_STRING,this->data.p=that;}
// inline void	jry_bl_string_add_var(jry_bl_string *this,jry_bl_var *that)
// {
	// long double tmp;	
	// switch(jry_bl_var_get_type(that))
	// {
		// case JRY_BL_VAR_TYPE_INT64	:tmp=that->data.ll	;jry_bl_string_add_int64	(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_UINT64	:tmp=that->data.ull	;jry_bl_string_add_uint64	(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_DOUBLE	:tmp=that->data.d	;jry_bl_string_add_double	(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_TRUE	:					;jry_bl_string_add_int64	(this,1)	;break;
		// case JRY_BL_VAR_TYPE_FALSE	:					;jry_bl_string_add_int64	(this,0)	;break;
		// case JRY_BL_VAR_TYPE_CHAR	:tmp=that->data.c	;jry_bl_string_add_char		(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_STRING	:jry_bl_string_add_string(this,jry_bl_var_get_string(that))	;break;
// #if JRY_BL_STREAM_ENABLE==1		
		// default:
			// jry_bl_var_to_json(that,this);
// #endif			
	// }	
// }
// inline void	jry_bl_string_equal_var(jry_bl_string *this,jry_bl_var *that,jry_bl_uint8 cpt)
// {
	// long double tmp;	
	// switch(jry_bl_var_get_type(that))
	// {
		// case JRY_BL_VAR_TYPE_INT64	:tmp=that->data.ll	;jry_bl_string_equal_int64	(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_UINT64	:tmp=that->data.ull	;jry_bl_string_equal_uint64	(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_DOUBLE	:tmp=that->data.d	;jry_bl_string_equal_double	(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_TRUE	:					;jry_bl_string_equal_int64	(this,1)	;break;
		// case JRY_BL_VAR_TYPE_FALSE	:					;jry_bl_string_equal_int64	(this,0)	;break;
		// case JRY_BL_VAR_TYPE_CHAR	:tmp=that->data.c	;jry_bl_string_equal_char	(this,tmp)	;break;
		// case JRY_BL_VAR_TYPE_STRING	:jry_bl_string_copy(this,jry_bl_var_get_string(that),cpt)	;break;
// #if JRY_BL_STREAM_ENABLE==1		
		// default:
			// jry_bl_string_clear(this);
			// jry_bl_var_to_json(that,this);
// #endif			
	// }	
// }
// #endif
#if JRY_BL_STREAM_ENABLE==1
jry_bl_stream * jry_bl_string_stream_new(jry_bl_string *str)
{
	str=jry_bl_string_extend(str,128);
	jry_bl_string *str_=jry_bl_refer_pull(str);
	return jry_bl_stream_new(&jry_bl_stream_string_operators,str,str_->size-str_->len,str_->s+str_->len);
}
void jry_bl_string_stream_operater(jry_bl_stream* this,jry_bl_uint8 flags)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	this=jry_bl_refer_pull(this);
	jry_bl_stream* nxt=(this->nxt!=NULL?jry_bl_refer_pull(this->nxt):NULL);
	jry_bl_string *str=((jry_bl_string*)this->data);
	jry_bl_string *str_=jry_bl_refer_pull(str);
	str_->len+=this->en;
	str=jry_bl_string_extend(str,128);
	str_=jry_bl_refer_pull(str_);
	this->buf=str_->s+str_->len;
	this->size=str_->size-str_->len;
	this->en=0;
	if(nxt!=NULL)
	{
		while(this->tmp<str_->len)
		{
			jry_bl_uint16 len=jry_bl_min((str_->len-this->tmp),(nxt->size-nxt->en));
			jry_bl_memory_copy(nxt->buf+nxt->en,str_->s+this->tmp,len);
			this->tmp+=len;
			nxt->en+=len;
			jry_bl_stream_do(nxt,0);
		}
		jry_bl_stream_do(nxt,flags);
	}
}
void jry_bl_string_stream_update_buf(jry_bl_stream* this)
{
	this=jry_bl_refer_pull(this);	
	this->data=jry_bl_string_extend_to((jry_bl_string*)this->data,0);
	jry_bl_string *str_=jry_bl_refer_pull(((jry_bl_string*)this->data));	
	this->buf=str_->s+str_->len;
}
const jry_bl_stream_operater jry_bl_stream_string_operators={
	jry_bl_string_stream_operater,
	(void (*)(void *))jry_bl_string_free,
	(void* (*)(void *))jry_bl_string_rcopy,
	jry_bl_string_stream_update_buf
};
void jry_bl_string_put(const jry_bl_string* this,jry_bl_stream *output_stream,jry_bl_put_type type,jry_bl_uint32 format,char*str)
{
	if(this==NULL||output_stream==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);	
	const jry_bl_string *this_=jry_bl_refer_pull(this);		
	jry_bl_int16 tabs=(format>>16);	
	if(format&1)
		if(tabs>=0)
		{
			for(jry_bl_int16 i=0;i<tabs;jry_bl_stream_push_char_force(output_stream,'\t'),++i);
			tabs=-tabs;
		}
	if(type==json)
	{
		jry_bl_stream_push_char_force(output_stream,'"');
		for(jry_bl_string_size_type i=0;i<this_->len;++i)
			(this_->s[i]=='"'?jry_bl_stream_push_char_force(output_stream,'\\'):0),jry_bl_stream_push_char_force(output_stream,this_->s[i]);
		jry_bl_stream_push_char_force(output_stream,'"');
	}
	else if(type==view)
	{
		jry_bl_stream_push_chars(output_stream,"jry_bl_string    ");
		if(((jry_bl_uint16)format>>1)!=0)
			jry_bl_stream_push_chars(output_stream,str),jry_bl_stream_push_char_force(output_stream,' '),jry_bl_stream_push_uint64(output_stream,((jry_bl_uint16)format>>1));
		jry_bl_stream_push_chars(output_stream,":size:");
		jry_bl_stream_push_uint64(output_stream,this_->size);
		jry_bl_stream_push_chars(output_stream,"\tlen:");
		jry_bl_stream_push_uint64(output_stream,this_->len);
		jry_bl_stream_push_chars(output_stream,"\ts:");
		for(jry_bl_string_size_type i=0;i<this_->len;jry_bl_stream_push_char_force(output_stream,this_->s[i]),++i);		
	} 
}
void jry_bl_string_to_json(const jry_bl_string *this,jry_bl_string *result)
{
	// if(this==NULL||result==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	// jry_bl_stream output_stream;
	// jry_bl_string_stream_init(&output_stream,result);
	// jry_bl_string_put(this,&output_stream,json,0,NULL);
	// jry_bl_stream_do(&output_stream,jry_bl_stream_force);
	// jry_bl_string_stream_free(&output_stream);
}
#endif
// #if JRY_BL_LINK_LIST_ENABLE==1
// #include "jry_bl_link_list.h"
// jry_bl_string_size_type jry_bl_string_cut_start(jry_bl_string *this,jry_bl_link_list *list,char cut,jry_bl_string_size_type start)
// {
	// if(this==NULL||list==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	// jry_bl_var var;jry_bl_var_init(&var);jry_bl_var_init_as(&var,JRY_BL_VAR_TYPE_STRING);
	// for(;start<this->len;++start,jry_bl_link_list_add_var_move(list,&var),jry_bl_string_clear(jry_bl_var_get_string(&var)))
		// for(;start<this->len&&this->s[start]!=cut;jry_bl_string_add_char(jry_bl_var_get_string(&var),this->s[start]),++start);
	// jry_bl_var_free(&var);
	// return (start);	
// }
// #endif
#endif