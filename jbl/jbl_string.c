/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_string.h"
#if JBL_STRING_ENABLE==1
#if JBL_USE_STDARG==1
#include <stdarg.h>
#endif
#include "jbl_exception.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
#if JBL_VAR_ENABLE==1
#include "jbl_var.h"
#endif
#if JBL_LL_ENABLE==1
#include "jbl_ll.h"
#endif
jbl_string_size_type jbl_strlen(char *a){jbl_string_size_type b=0;while(a[b++]);return b-1;}
inline jbl_string * jbl_string_new()
{
	return jbl_string_init(jbl_malloc((sizeof(jbl_string))));
}
jbl_string * jbl_string_init(jbl_string *this)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数
	this->len=0;
	this->h=0;
	this->size=0;
	this->s=NULL;
	return this;	
}
jbl_string* jbl_string_free(jbl_string *this)
{
//	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	if(this==NULL)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_reference_cnt(this))
	{
		((jbl_gc_is_ref(this))?jbl_string_free((jbl_string *)jbl_refer_pull(this)):(this->s?jbl_free(this->s):0));
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var(this))
			jbl_free((char*)this-sizeof(jbl_var));
		else
#endif
			jbl_free(this);
	}
	return NULL;
}
jbl_string *jbl_string_extend_to(jbl_string *this,jbl_string_size_type size)
{
	jbl_max_update(size,JBL_STRING_BASIC_LENGTH);
	if(this==NULL)this=jbl_string_new();		
	size=1LL<<(jbl_highbit(size-1)+1);
	jbl_reference *ref=NULL;
	if(jbl_gc_is_ref(this))
		ref=(jbl_reference*)this,this=((jbl_reference*)this)->ptr;
	if(jbl_gc_reference_cnt(this)==1)
	{
		if(size>this->size)
			this->size=size,this->s=(this->s==NULL?(unsigned char *)jbl_malloc(this->size):(unsigned char *)jbl_realloc(this->s,this->size));		
	}
	else
	{
		jbl_string *tmp;
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var(this))
			tmp=$jbl_string(jbl_Vstring_new());
		else
#endif		
			tmp=jbl_string_new();
		tmp->size=size;
		tmp->len=this->len;
		tmp->h=this->h;
		tmp->s=(unsigned char *)jbl_malloc(tmp->size);
		jbl_memory_copy(tmp->s,this->s,this->len);
		jbl_string_free(this);
		this=tmp;
	}
	if(ref)
		ref->ptr=this,this=(jbl_string*)ref;
	return this;
}
jbl_string *jbl_string_clear(jbl_string *this)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	this=jbl_string_extend_to(this,0);
	jbl_string *this_=jbl_refer_pull(this);
	jbl_string_hash_clear(this);	
	this_->len=0;
	return this;
}
inline jbl_string *jbl_string_copy(jbl_string *that)
{
	if(that==NULL)return NULL;
	jbl_gc_plus(that);
	return that;
}
jbl_string * jbl_string_copy_force(jbl_string *this,const jbl_string *that)
{
	that=jbl_refer_pull(that);
	if(this==NULL)this=jbl_string_new();
	this->size=that->size;
	this->len=that->len;
	this->h=that->h;
	this->s=jbl_malloc(this->size);
	jbl_memory_copy(this->s,that->s,this->len);
	return this;
}
jbl_string * jbl_string_move(jbl_string *this,jbl_string *that)
{
	that=jbl_refer_pull(that);
	if(this==NULL)this=jbl_string_new();
	if(jbl_gc_reference_cnt(that)!=1)
		return jbl_string_copy_force(this,that);
	this->s=that->s;
	this->h=that->h;
	this->len=that->len;
	this->size=that->size;
	that->s=0;
	that->h=0;
	that->len=0;
	that->size=0;
	return this;
}
jbl_string *jbl_string_equal(jbl_string *this,jbl_string *that)
{
	if(this!=NULL)jbl_string_free(this);	
	jbl_gc_plus(that);
	return that;
}
jbl_string_hash_type jbl_string_hash(jbl_string *this)
{
	jbl_string *this_=jbl_refer_pull(this);
	if(this_->h==0)
		for(jbl_string_size_type i=0;i<this_->len;i++)
			this_->h=(this_->h<<5)+this_->h+this_->s[i];
	return this_->h;
}
jbl_string *jbl_string_add_chars_length(jbl_string *this,unsigned char *in,jbl_string_size_type len)
{
	this=jbl_string_extend(this,len);
	jbl_string *this_=jbl_refer_pull(this);
	jbl_memory_copy(this_->s+this_->len,in,len);
	this_->len=(this_->len+len);
	jbl_string_hash_clear(this);	
	return this;
}
jbl_string *jbl_string_add_string(jbl_string *this,const jbl_string *in)
{
	const jbl_string *in_=jbl_refer_pull(in);
	this=jbl_string_extend(this,in_->len);
	jbl_string *this_=jbl_refer_pull(this);
	jbl_memory_copy(this_->s+this_->len,in_->s,in_->len);
	this_->len=(this_->len+in_->len);
	jbl_string_hash_clear(this);	
	return this;
}
inline jbl_string *jbl_string_add_char(jbl_string *this,const char c)
{
	this=jbl_string_extend(this,1);
	jbl_string *this_=jbl_refer_pull(this);
	jbl_string_add_char_force(this_,c);
	jbl_string_hash_clear(this);
	return this;
}
inline jbl_string * jbl_string_add_int64_length(jbl_string *this,jbl_int64 in,jbl_uint8 len,char c)
{
	this=jbl_string_extend(this,22);
	jbl_string *this_=jbl_refer_pull(this);
	if(in<0)
		jbl_string_add_char_force(this_,'-'),in=-in;
	return jbl_string_add_uint64_length(this,in,len,c);
}
jbl_string * jbl_string_add_uint64_length(jbl_string *this,jbl_uint64 in,jbl_uint8 len,char c)
{
	this=jbl_string_extend(this,(len>21?len:21));
	jbl_string *this_=jbl_refer_pull(this);
	if(in==0)
	{
		for(jbl_uint8 i=1;i<len;jbl_string_add_char_force(this_,c),++i);
		return jbl_string_add_char_force(this_,'0'),this_;
	}
	int cnt=20;
	unsigned char b[21];
	b[cnt--]=0;
	while(in)b[cnt--]=in%10+'0',in/=10;
	for(jbl_uint8 i=19-cnt;i<len;jbl_string_add_char_force(this_,c),++i);
	return jbl_string_add_chars_length(this,b+cnt+1,19-cnt);
}
jbl_string * jbl_string_add_double_length(jbl_string *this,double in,unsigned char len)
{
	this=jbl_string_extend(this,jbl_max(len,40));
	jbl_string *this_=jbl_refer_pull(this);	
	jbl_int64 inn=in;
	this_=jbl_string_add_int64(this_,inn);
	jbl_string_add_char_force(this_,'.');
	if(in<0)
		inn=-inn,in=-in;
	in-=inn;
	jbl_uint64 ji=10;
	unsigned char i=0;
	for(double t=in*ji;i<len&&(t-(jbl_uint64)t<(-JBL_DOUBLE_PRECISION)||t-(jbl_uint64)t>(JBL_DOUBLE_PRECISION));ji=(ji<<3)+(ji<<1),t=in*ji,++i);
	return jbl_string_add_uint64(this,((jbl_uint64)((in*ji+0.5)/10)));
}
jbl_string * jbl_string_add_unicode_as_utf8(jbl_string *this,unsigned long unicode)
{
	this=jbl_string_extend(this,6);
	jbl_string *this_=jbl_refer_pull(this);	
	if(unicode<=0x7F)
		jbl_string_add_char_force(this_,unicode&0x7F);
	else if(unicode>=0x80&&unicode<=0x7FF)
		jbl_string_add_char_force(this_,((unicode>>6)&0x1F)|0xC0),jbl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x800&&unicode<=0xFFFF)
		jbl_string_add_char_force(this_,((unicode>>12)&0x0F)|0xE0),jbl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jbl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x10000&&unicode<=0x10FFFF)
		jbl_string_add_char_force(this_,((unicode>>18)&0x7)|0xF0),jbl_string_add_char_force(this_,((unicode>>12)&0x3F)|0x80),jbl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jbl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x200000&&unicode<=0x3FFFFFF)
		jbl_string_add_char_force(this_,((unicode>>24)&0x3)|0xF8),jbl_string_add_char_force(this_,((unicode>>18)&0x3F)|0x80),jbl_string_add_char_force(this_,((unicode>>12)&0x3F)|0x80),jbl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jbl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	else if(unicode>=0x4000000&&unicode<=0x7FFFFFFF)
		jbl_string_add_char_force(this_,((unicode>>30)&0x1)|0xFC),jbl_string_add_char_force(this_,((unicode>>24)&0x3F)|0x80),jbl_string_add_char_force(this_,((unicode>>18)&0x3F)|0x80),jbl_string_add_char_force(this_,((unicode>>12)&0x3F)|0x80),jbl_string_add_char_force(this_,((unicode>>6)&0x3F)|0x80),jbl_string_add_char_force(this_,(unicode&0x3F)|0x80);
	return this;
}
jbl_string * jbl_string_add_hex(jbl_string *this,jbl_uint64 in)
{
	unsigned char n=1;
	while((in>>(n<<2)))++n;
	this=jbl_string_extend(this,n+1);
	jbl_string *this_=jbl_refer_pull(this);	
	const char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(unsigned char i=0;i<n;++i)
		jbl_string_add_char_force(this_,hex[(in>>(i<<2))&15]);
	jbl_string_hash_clear(this);		
	return this;
}
inline jbl_string * jbl_string_add_hex_8bits(jbl_string *this,jbl_uint8 in)
{
	const char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	this=jbl_string_extend(this,2);
	jbl_string *this_=jbl_refer_pull(this);	
	jbl_string_add_char_force(this_,hex[in>>4]),jbl_string_add_char_force(this_,hex[in&15]);	
	return this;
}
char jbl_string_space_ship(const jbl_string *this_,const jbl_string *that_)
{
	if(this_==that_){return 0;}if(this_==NULL){return -1;}if(that_==NULL){return 1;}
	const jbl_string *this=jbl_refer_pull(this_);	
	const jbl_string *that=jbl_refer_pull(that_);	
	if(this==that){return 0;}if(this==NULL){return -1;}if(that==NULL){return 1;}
	if(this->len!=that->len)
		return (this->len<that->len)?-1:1;
	for(jbl_string_size_type i=0;i<this->len;i++)
		if(this->s[i]<that->s[i])
			return -1;
		else if(this->s[i]>that->s[i])
			return 1;
	return 0;
}
char jbl_string_if_equal(const jbl_string *this_,const jbl_string *that_)
{	
	if(this_==that_){return 1;}if(this_==NULL||that_==NULL){return 0;}
	const jbl_string *this=jbl_refer_pull(this_);	
	const jbl_string *that=jbl_refer_pull(that_);	
	if(this==that){return 1;}if(this==NULL||that==NULL){return 0;}
	if(this->h!=0&&this->h!=that->h)return 0;
	if(this->len!=that->len)return 0;
	for(jbl_string_size_type i=0;i<this->len;i++)
		if(this->s[i]!=that->s[i])
			return 0;
	return 1;
}
jbl_int64 jbl_string_get_int64_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL||start==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);		
	jbl_string_size_type i=*start; 	
	if(i>=this_->len)
		return 0;
	unsigned char c,f;jbl_uint64 x=0;
	for(f=0;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	*start=i;
	return f?-x:x;	
}
inline jbl_int64 jbl_string_get_int64_start_v(const jbl_string *this,jbl_string_size_type start){return jbl_string_get_int64_start(this,&start);};
jbl_uint64 jbl_string_get_uint64_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL||start==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);		
	jbl_string_size_type i=*start; 	
	if(i>=this_->len)
		return 0;
	unsigned char c;jbl_uint64 x=0;
	for(;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	*start=i;
	return x;	
}
inline jbl_uint64 jbl_string_get_uint64_start_v(const jbl_string *this,jbl_string_size_type start){return jbl_string_get_uint64_start(this,&start);};
double jbl_string_get_double_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL||start==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);		
	jbl_string_size_type i=*start;
	if(i>=this_->len)
		return 0;
	unsigned char c,f;jbl_uint64 x=0;
	for(f=0;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	*start=i;
	if(this_->s[i]!='.'||i==this_->len)
		return (f?-(double)x:(double)x);
	jbl_uint64 ji=10,y;++i;
	for(c=this_->s[i],y=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	*start=i;
	return f?(-((long double)x+((long double)y/ji))):((long double)x+((long double)y/ji));
}
inline double jbl_string_get_double_start_v(const jbl_string *this,jbl_string_size_type start){return jbl_string_get_double_start(this,&start);};
jbl_uint64 jbl_string_get_hex_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL||start==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);			
	jbl_string_size_type i=*start; 	
	if(i>=this_->len)
		return 0;
	unsigned char c;jbl_uint64 x=0;
	for(;((c=this_->s[i])<'0'||c>'9')&&(c<'a'||c>'f')&&(c<'A'||c>'F')&&i<this_->len;++i);
	for(x=((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i;(((c=this_->s[i])>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))&&i<this_->len;x=(x<<4)+((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i);
	*start=i;
	return x;
}
inline jbl_uint64 jbl_string_get_hex_start_v(const jbl_string *this,jbl_string_size_type start){return jbl_string_get_hex_start(this,&start);};
jbl_string_size_type	jbl_string_find_char_start(const jbl_string *this,unsigned char in,jbl_string_size_type start)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);			
	for(;start<this_->len&&this_->s[start]!=in;++start);
	return (start);
}
jbl_string* jbl_string_json_encode(const jbl_string* this,jbl_string *out,char format,jbl_int32 tabs)
{
	if(out==NULL)out=jbl_string_new();
	this=jbl_refer_pull(this);
	out=jbl_refer_pull(out);
	out=jbl_string_extend(out,((format&&tabs>=0)?tabs:0)+2+this->len);
	if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;out=jbl_string_add_char(out,'\t'),++i);	
	if(!this)return jbl_string_add_chars_length(out,(unsigned char *)"null",4);	
	out=jbl_string_add_char(out,'"');
	for(jbl_string_size_type i=0;i<this->len;++i)
		(this->s[i]=='"'?out=jbl_string_add_char(out,'\\'):0),out=jbl_string_add_char(out,this->s[i]);
	out=jbl_string_add_char(out,'"');
	return out;
}

// jbl_string_size_type jbl_string_from_json_start(jbl_string *this,const jbl_string *in,jbl_string_size_type start)
// {
	// if(this==NULL||in==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	// jbl_string_size_type i=start,n=in->len,no=this->len,st,en;
	// for(;(i<n)&&(!(in->s[i]=='"'&&(i==0||in->s[i-1]!='\\')));++i)if(in->s[i]!=' '&&in->s[i]!='\r'&&in->s[i]!='\t'&&in->s[i]!='\n')return start;++i;st=i;
	// for(;i<n&&!(in->s[i]=='"'&&in->s[i-1]!='\\');++i);en=i;++i;
	// if((i-1)>=n)
		// return start;
	// jbl_string_extend(this,en-st);
	// for(i=st;i<en;i++)
	// {
		// if(((i+1)<en)&&in->s[i]=='\\'&&in->s[i+1]=='u')
			// i+=2,jbl_string_add_unicode_as_utf8(this,jbl_string_get_hex_start(in,&i)),--i;
		// else
			// jbl_string_add_char_force(this,in->s[i]);
	// }
	// return en+1;
// }
// inline void jbl_string_print(const jbl_string *this,FILE * file)
// {
	// if(this==NULL||file==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	// jbl_string_size_type i=0;
	// i+=fwrite(this->s+i,1<<10,(this->len-i)>>10,file)<<10;
	// for(;i<this->len;fputc(this->s[i++],file));
// }
// void jbl_string_add_file(jbl_string *this,FILE * file)
// {
	// if(this==NULL||file==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	// /*clock_t __start=clock();*/
	// fseek(file,0L,SEEK_END);
	// unsigned char c;
	// jbl_string_size_type size=ftell(file),i=0;
	// jbl_string_extend(this,size);
	// fseek(file,0L,SEEK_SET);
	// i+=fread(this->s+this->len+i,1<<10,(size-i)>>10,file)<<10;this->len+=i;
	// while(i<size)
		// ++i,jbl_string_add_char(this,fgetc(file));
	// /*fprintf(stderr,"\n\nUse Time:%fs\n",((double)(clock()-__start)/CLOCKS_PER_SEC));*/
// }
// void jbl_string_add_file_end_by(jbl_string *this,FILE * file,unsigned char end)
// {
	// if(this==NULL||file==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	// fseek(file,0L,SEEK_END);
	// unsigned char c;
	// jbl_string_size_type size=ftell(file),i=0;
	// jbl_string_extend(this,size);
	// fseek(file,0L,SEEK_SET);
	// while(i<size&&((c=fgetc(file))!=end))
		// ++i,jbl_string_add_char(this,c);
// }

// #if JBL_VAR_ENABLE==1
// #include "jbl_var.h"	
// inline void				jbl_var_equal_string				(jbl_var *this,jbl_string *that,jbl_uint8 copytype){jbl_var_init_as(this,JBL_VAR_TYPE_STRING);jbl_string_copy(this->data.p,that,copytype);}
// inline void				jbl_var_equal_string_pointer		(jbl_var *this,jbl_string *that){jbl_var_free(this);jbl_var_flag_pointer(this)=true;this->type=JBL_VAR_TYPE_STRING,this->data.p=that;}
// inline void	jbl_string_add_var(jbl_string *this,jbl_var *that)
// {
	// long double tmp;	
	// switch(jbl_var_get_type(that))
	// {
		// case JBL_VAR_TYPE_INT64	:tmp=that->data.ll	;jbl_string_add_int64	(this,tmp)	;break;
		// case JBL_VAR_TYPE_UINT64	:tmp=that->data.ull	;jbl_string_add_uint64	(this,tmp)	;break;
		// case JBL_VAR_TYPE_DOUBLE	:tmp=that->data.d	;jbl_string_add_double	(this,tmp)	;break;
		// case JBL_VAR_TYPE_TRUE	:					;jbl_string_add_int64	(this,1)	;break;
		// case JBL_VAR_TYPE_FALSE	:					;jbl_string_add_int64	(this,0)	;break;
		// case JBL_VAR_TYPE_CHAR	:tmp=that->data.c	;jbl_string_add_char		(this,tmp)	;break;
		// case JBL_VAR_TYPE_STRING	:jbl_string_add_string(this,jbl_var_get_string(that))	;break;
// #if JBL_STREAM_ENABLE==1		
		// default:
			// jbl_var_to_json(that,this);
// #endif			
	// }	
// }
// inline void	jbl_string_equal_var(jbl_string *this,jbl_var *that,jbl_uint8 cpt)
// {
	// long double tmp;	
	// switch(jbl_var_get_type(that))
	// {
		// case JBL_VAR_TYPE_INT64	:tmp=that->data.ll	;jbl_string_equal_int64	(this,tmp)	;break;
		// case JBL_VAR_TYPE_UINT64	:tmp=that->data.ull	;jbl_string_equal_uint64	(this,tmp)	;break;
		// case JBL_VAR_TYPE_DOUBLE	:tmp=that->data.d	;jbl_string_equal_double	(this,tmp)	;break;
		// case JBL_VAR_TYPE_TRUE	:					;jbl_string_equal_int64	(this,1)	;break;
		// case JBL_VAR_TYPE_FALSE	:					;jbl_string_equal_int64	(this,0)	;break;
		// case JBL_VAR_TYPE_CHAR	:tmp=that->data.c	;jbl_string_equal_char	(this,tmp)	;break;
		// case JBL_VAR_TYPE_STRING	:jbl_string_copy(this,jbl_var_get_string(that),cpt)	;break;
// #if JBL_STREAM_ENABLE==1		
		// default:
			// jbl_string_clear(this);
			// jbl_var_to_json(that,this);
// #endif			
	// }	
// }
// #endif
#if JBL_STREAM_ENABLE==1
jbl_stream * jbl_string_stream_new(jbl_string *str)
{
	str=jbl_string_extend(str,128);
	jbl_string *str_=jbl_refer_pull(str);
	return jbl_stream_new(&jbl_stream_string_operators,str,str_->size-str_->len,str_->s+str_->len,0,NULL);
}
#if JBL_VAR_ENABLE==1
jbl_var * jbl_string_Vstream_new(jbl_string *str)
{
	str=jbl_string_extend(str,128);
	jbl_string *str_=jbl_refer_pull(str);
	return jbl_Vstream_new(&jbl_stream_string_operators,str,str_->size-str_->len,str_->s+str_->len,0,NULL);
}
#endif
void jbl_string_stream_operater(jbl_stream* this,jbl_uint8 flags)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	this=jbl_refer_pull(this);
	jbl_stream* nxt=(this->nxt!=NULL?jbl_refer_pull(this->nxt):NULL);
	jbl_string *str=((jbl_string*)this->data);
	jbl_string *str_=jbl_refer_pull(str);
	str_->len+=this->en;
	jbl_string_hash_clear(str_);
	str=jbl_string_extend(str,128);
	str_=jbl_refer_pull(str_);
	this->buf=str_->s+str_->len;
	this->size=str_->size-str_->len;
	this->en=0;
	if(nxt!=NULL)
	{
		while(this->tmpv<str_->len)
		{
			jbl_uint16 len=jbl_min((str_->len-this->tmpv),(nxt->size-nxt->en));
			jbl_memory_copy(nxt->buf+nxt->en,str_->s+this->tmpv,len);
			this->tmpv+=len;
			nxt->en+=len;
			jbl_stream_do(nxt,0);
		}
		jbl_stream_do(nxt,flags);
	}
}
jbl_string *jbl_string_copy_for_stream(jbl_string *that)
{
	if(that==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	return jbl_string_copy(jbl_refer_pull(that));
}
void jbl_string_stream_update_buf(jbl_stream* this)
{
	this=jbl_refer_pull(this);	
	this->data=jbl_string_extend_to((jbl_string*)this->data,0);
	jbl_string *str_=jbl_refer_pull(((jbl_string*)this->data));	
	this->buf=str_->s+str_->len;
}
const jbl_stream_operater jbl_stream_string_operators={
	jbl_string_stream_operater,
	(void (*)(void *))jbl_string_free,
	(void* (*)(void *))jbl_string_copy_for_stream,
	jbl_string_stream_update_buf
};
void jbl_string_view_put(const jbl_string* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs)
{
	if(output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	output_stream=jbl_refer_pull(output_stream);
	this=jbl_refer_pull(this);
	if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char_force(output_stream,'\t'),++i);	
	if(this)jbl_stream_push_chars(output_stream,"jbl_string    ");
	else	jbl_stream_push_chars(output_stream,"null          ");
	if(format&&str)jbl_stream_push_chars(output_stream,str),jbl_stream_push_char_force(output_stream,' '),(format!=-1?jbl_stream_push_uint64(output_stream,format):0);
	if(!this)return;
	jbl_stream_push_chars(output_stream,":size:");
	jbl_stream_push_uint64(output_stream,this->size);
	jbl_stream_push_chars(output_stream,"\tlen:");
	jbl_stream_push_uint64(output_stream,this->len);
	jbl_stream_push_chars(output_stream,"\ts:");
	for(jbl_string_size_type i=0;i<this->len;jbl_stream_push_char_force(output_stream,this->s[i]),++i);
}
void jbl_string_json_put(const jbl_string* this,jbl_stream *output_stream,char format,jbl_int32 tabs)
{
	if(output_stream==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	output_stream=jbl_refer_pull(output_stream);
	this=jbl_refer_pull(this);
	if(format&&tabs>=0)for(jbl_int16 i=0;i<tabs;jbl_stream_push_char_force(output_stream,'\t'),++i);	
	if(!this)return jbl_stream_push_chars(output_stream,"null");
	jbl_stream_push_char_force(output_stream,'"');
	for(jbl_string_size_type i=0;i<this->len;++i)
		(this->s[i]=='"'?jbl_stream_push_char_force(output_stream,'\\'):0),jbl_stream_push_char_force(output_stream,this->s[i]);
	jbl_stream_push_char_force(output_stream,'"');
}
#endif
#if JBL_VAR_ENABLE==1
const jbl_var_operators jbl_string_operators={
	(void* (*)(void *))jbl_string_free,
	(void* (*)(void *))jbl_string_copy,
	(char  (*)(const void*,const void*))jbl_string_space_ship,
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_string_json_encode,
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_string_view_put,
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_string_json_put,
#endif
};
jbl_var * jbl_Vstring_new()
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_string))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_string_init($jbl_string(this));
	jbl_gc_set_var($jbl_string(this));
	jbl_var_set_operators(this,&jbl_string_operators);
	return this;
}
#endif
#if JBL_LL_ENABLE==1
#include "jbl_ll.h"
jbl_ll * jbl_string_cut_start(jbl_string *this,jbl_ll *list,char cut,jbl_string_size_type start)
{
	if(this==NULL)return list;
	this=jbl_refer_pull(this);
	for(jbl_var *v=NULL;start<this->len;list=jbl_ll_add(list,v),v=jbl_var_free(v),++start)
		for(v=jbl_Vstring_new();start<this->len&&this->s[start]!=cut;jbl_string_add_char($jbl_string(v),this->s[start]),++start);
	return (list);	
}
#endif
#endif