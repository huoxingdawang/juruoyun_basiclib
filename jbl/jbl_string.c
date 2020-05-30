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
#include "jbl_malloc.h"
#include "jbl_ying.h"
#if JBL_VAR_ENABLE==1
#include "jbl_var.h"
#endif
#if JBL_LL_ENABLE==1
#include "jbl_ll.h"
#endif
jbl_string_size_type jbl_strlen(const char *a){jbl_string_size_type b=0;while(a[b++]);return b-1;}
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
			tmp=jbl_Vstring(jbl_Vstring_new());
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
	this=jbl_string_add_int64(this,in);
	this=jbl_string_add_char(this,'.');
	if(in<0)in=-in;
	in-=(jbl_uint64)in;
	
	jbl_uint64 ji=1;
	for(register unsigned char i=0,n=len+2;i<n;++i,ji=(ji<<3)+(ji<<1));
	jbl_uint64 t=(in*ji+0.5)/10;
	if(t==0)
		return jbl_string_add_char(this,'0');

	unsigned char b[21];
	for(register unsigned char i=0;i<21;b[i]='0',++i);
	register unsigned char cnt=20;
	b[cnt--]=0;
	while(t)b[cnt--]=t%10+'0',t/=10;
	return jbl_string_add_chars_length(this,b+20-len-1,len);	
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
#include <stdio.h>
jbl_string* jbl_string_add_file(jbl_string *this,FILE * file)
{
	if(file==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
#if __SIZEOF_POINTER__ == 8 && !defined __linux__
	_fseeki64(file,0L,SEEK_END);
	jbl_string_size_type size=_ftelli64(file);	
	_fseeki64(file,0L,SEEK_SET);
#else
	fseek(file,0L,SEEK_END);
	jbl_string_size_type size=ftell(file);	
	fseek(file,0L,SEEK_SET);
#endif	
	this=jbl_string_extend(this,size);
	jbl_string_hash_clear(this);	
	jbl_string *thi=jbl_refer_pull(this);	
	thi->len+=fread(thi->s+thi->len,1,size,file);
	return this;
}
inline void jbl_string_print(const jbl_string *this,FILE * file)
{
	if(!this)return;
	if(!file)jbl_exception(JBL_ERROR_NULL_POINTER);
	this=jbl_refer_pull(this);
	fwrite(this->s,1,this->len,file);
}
char jbl_string_space_ship(const jbl_string *this,const jbl_string *that)
{
	if(this==that){return 0;}if(this==NULL){return -1;}if(that==NULL){return 1;}
	const jbl_string *thi=jbl_refer_pull(this);	
	const jbl_string *tha=jbl_refer_pull(that);	
	if(thi==tha){return 0;}if(thi==NULL){return -1;}if(tha==NULL){return 1;}
	if(thi->len!=tha->len)
		return (thi->len<tha->len)?-1:1;
	for(jbl_string_size_type i=0;i<thi->len;++i)
		if(thi->s[i]<tha->s[i])
			return -1;
		else if(thi->s[i]>tha->s[i])
			return 1;
	return 0;
}
char jbl_string_space_ship_chars(const jbl_string *this,const char *that)
{
	const jbl_string *thi=jbl_refer_pull(this);
	jbl_string_size_type n=jbl_strlen(that);
	if(thi->len!=n)
		return (thi->len<n)?-1:1;
	for(jbl_string_size_type i=0;i<thi->len;++i)
		if(thi->s[i]<that[i])
			return -1;
		else if(thi->s[i]>that[i])
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
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);		
	jbl_string_size_type i=start?(*start):0; 	
	if(i>=this_->len)
		return 0;
	unsigned char c,f;jbl_uint64 x=0;
	for(f=0;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	start?(*start=i):0;
	return f?-x:x;	
}
jbl_uint64 jbl_string_get_uint64_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);		
	jbl_string_size_type i=start?(*start):0; 	
	if(i>=this_->len)
		return 0;
	unsigned char c;jbl_uint64 x=0;
	for(;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	start?(*start=i):0;
	return x;	
}
double jbl_string_get_double_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);		
	jbl_string_size_type i=start?(*start):0; 	
	if(i>=this_->len)
		return 0;
	unsigned char c,f;jbl_uint64 x=0;
	for(f=0;((c=this_->s[i])<'0'||c>'9')&&i<this_->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;x=(x<<3)+(x<<1)+c-'0',++i);
	start?(*start=i):0;
	if(this_->s[i]!='.'||i==this_->len)
		return (f?-(double)x:(double)x);
	jbl_uint64 ji=10,y;++i;
	for(c=this_->s[i],y=c-'0',++i;(c=this_->s[i])>='0'&&c<='9'&&i<this_->len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	start?(*start=i):0;
	return f?(-(((double)y/ji)+x)):(((double)y/ji)+x);
}
jbl_uint64 jbl_string_get_hex_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);			
	jbl_string_size_type i=start?(*start):0; 	
	if(i>=this_->len)
		return 0;
	unsigned char c;jbl_uint64 x=0;
	for(;((c=this_->s[i])<'0'||c>'9')&&(c<'a'||c>'f')&&(c<'A'||c>'F')&&i<this_->len;++i);
	for(x=((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i;(((c=this_->s[i])>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))&&i<this_->len;x=(x<<4)+((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i);
	start?(*start=i):0;
	return x;
}
jbl_uint64 jbl_string_get_hex_start_len(const jbl_string *this,jbl_string_size_type *start,jbl_string_size_type len)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);			
	jbl_string_size_type i=start?(*start):0; 	
	if(i>=this_->len)
		return 0;
	unsigned char c;jbl_uint64 x=0;
	for(;((c=this_->s[i])<'0'||c>'9')&&(c<'a'||c>'f')&&(c<'A'||c>'F')&&i<this_->len;++i);
	for(x=((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i;(--len)&&(((c=this_->s[i])>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))&&i<this_->len;x=(x<<4)+((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0'))),++i);
	start?(*start=i):0;
	return x;
}
jbl_string_size_type	jbl_string_find_char_start(const jbl_string *this,unsigned char in,jbl_string_size_type start)
{
	if(this==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *this_=jbl_refer_pull(this);			
	for(;start<this_->len&&this_->s[start]!=in;++start);
	return (start);
}
#if JBL_JSON_ENABLE==1
jbl_string* jbl_string_json_encode(const jbl_string* this,jbl_string *out,char format,jbl_int32 tabs)
{
	out=jbl_string_json_put_format(this=jbl_refer_pull(this),out,format,&tabs);if(!this)return out;
	out=jbl_string_add_char(out,'"');
	for(jbl_string_size_type i=0;i<this->len;++i)
	{
		if(this->s[i]>31&&this->s[i]!='\"' &&this->s[i]!='\\')
			out=jbl_string_add_char(out,this->s[i]);
		else
		{
			out=jbl_string_add_char(out,'\\');
			jbl_uint8 token;
			switch(token=this->s[i])
			{
				case '\\':out=jbl_string_add_char(out,'\\');	break;
				case '\"':out=jbl_string_add_char(out,'\"');	break;
				case '\b':out=jbl_string_add_char(out,'b');	break;
				case '\f':out=jbl_string_add_char(out,'f');	break;
				case '\n':out=jbl_string_add_char(out,'n');	break;
				case '\r':out=jbl_string_add_char(out,'r');	break;
				case '\t':out=jbl_string_add_char(out,'t');	break;
				default  :out=jbl_string_add_chars_length(out,(unsigned char*)"u00",3),out=jbl_string_add_hex_8bits(out,token);break;
			}
		}				
	}
	out=jbl_string_add_char(out,'"');
	return out;
}
jbl_string* jbl_string_json_put_format(const void* this,jbl_string *out,char format,jbl_int32 *tabs)
{
	if(out==NULL)out=jbl_string_new();
	if(format&&*tabs>=0)for(jbl_int16 i=0;i<*tabs;out=jbl_string_add_char(out,'\t'),++i);else *tabs=-*tabs;	
	++*tabs;
	if(!this)out=jbl_string_add_chars_length(out,(unsigned char *)"null",4);
	return out;
}
jbl_string* jbl_string_json_decode(jbl_string *this,const jbl_string* in,jbl_string_size_type *start)
{
	in=jbl_refer_pull(in);	
	jbl_string_size_type i=start?(*start):0,n=in->len;
	for(;i<n&&in->s[i]<=32;++i);
//	pchar(in->s[i]);pn();
	if(in->s[i]!='"')
		goto fail;
	for(++i;i<n;)
	{
		switch(in->s[i])
		{
			case '"':
				{++i;goto success;}
				break;
			case '\\':
				switch(in->s[i+1])
				{
					case '\\':
						i+=2;this=jbl_string_add_char(this,'\\');
						break;
					case '"':
						i+=2;this=jbl_string_add_char(this,'"');
						break;
					case 'b':
						i+=2;this=jbl_string_add_char(this,'\b');
						break;
					case 'f':
						i+=2;this=jbl_string_add_char(this,'\f');
						break;
					case 'n':
						i+=2;this=jbl_string_add_char(this,'\n');
						break;
					case 'r':
						i+=2;this=jbl_string_add_char(this,'\r');
						break;
					case 't':
						i+=2;this=jbl_string_add_char(this,'\t');
						break;
					case 'u':
						i+=2;this=jbl_string_add_unicode_as_utf8(this,jbl_string_get_hex_start_len(in,&i,4));		
						break;
					default:
						i+=2;this=jbl_string_add_char(this,'\\');
						break;
				}
				break;
			default :
				this=jbl_string_add_char(this,in->s[i]),++i;
		}
	}
	goto fail;
success:;
	if(!this)this=jbl_string_new();
	start?(*start=i):0;
	return this;
fail:;
	return NULL;
}

#endif
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
	str=jbl_string_extend(str,128);
	str=jbl_refer_pull(str);
	str->len+=this->en;
	jbl_string_hash_clear(str);
	str=jbl_refer_pull(str);
	this->buf=str->s+str->len;
	this->size=str->size-str->len;
	this->en=0;
	if(nxt!=NULL)
	{
		while(this->tmpv<str->len)
		{
			jbl_uint16 len=jbl_min((str->len-this->tmpv),(nxt->size-nxt->en));
			jbl_memory_copy(nxt->buf+nxt->en,str->s+this->tmpv,len);
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
void jbl_string_view_put(const jbl_string* this,jbl_stream *out,jbl_int32 format,char*str,jbl_int32 tabs)
{
	if(jbl_stream_view_put_format(this=jbl_refer_pull(this),out,"jbl_string    ",format,str,&tabs))return;
	jbl_stream_push_chars(out,":size:");
	jbl_stream_push_uint64(out,this->size);
	jbl_stream_push_chars(out,"\tlen:");
	jbl_stream_push_uint64(out,this->len);
	jbl_stream_push_chars(out,"\ts:");
	for(jbl_string_size_type i=0;i<this->len;jbl_stream_push_char(out,this->s[i]),++i);
}
void jbl_stream_push_string(jbl_stream *out,const jbl_string* this)
{
	if(out==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);
	out=jbl_refer_pull(out);
	this=jbl_refer_pull(this);
	for(jbl_string_size_type i=0;i<this->len;++i)
		jbl_stream_push_char_force(out,this->s[i]);
}
#if JBL_JSON_ENABLE==1
void jbl_string_json_put(const jbl_string* this,jbl_stream *out,char format,jbl_int32 tabs)
{
	if(jbl_stream_json_put_format(this=jbl_refer_pull(this),out,format,&tabs))return;
	jbl_stream_push_char(out,'"');
	for(jbl_string_size_type i=0;i<this->len;++i)
	{
		if(this->s[i]>31&&this->s[i]!='\"' &&this->s[i]!='\\')
			jbl_stream_push_char(out,this->s[i]);
		else
		{
			jbl_stream_push_char(out,'\\');
			jbl_uint8 token;
			switch(token=this->s[i])
			{
				case '\\':jbl_stream_push_char(out,'\\');	break;
				case '\"':jbl_stream_push_char(out,'\"');	break;
				case '\b':jbl_stream_push_char(out,'b');	break;
				case '\f':jbl_stream_push_char(out,'f');	break;
				case '\n':jbl_stream_push_char(out,'n');	break;
				case '\r':jbl_stream_push_char(out,'r');	break;
				case '\t':jbl_stream_push_char(out,'t');	break;
				default  :jbl_stream_push_chars(out,"u00"),jbl_stream_push_hex_8bits(out,token);break;
			}
		}		
	}
	jbl_stream_push_char(out,'"');
}
#endif
#endif
#if JBL_VAR_ENABLE==1
const jbl_var_operators jbl_string_operators={
	(void* (*)(void *))jbl_string_free,
	(void* (*)(void *))jbl_string_copy,
	(char  (*)(const void*,const void*))jbl_string_space_ship,
#if JBL_JSON_ENABLE==1
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_string_json_encode,
#endif
#if JBL_STREAM_ENABLE==1
	(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_string_view_put,
#if JBL_JSON_ENABLE==1
	(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_string_json_put,
#endif
#endif
};
jbl_var * jbl_Vstring_new()
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_string))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_var_set_operators(this,&jbl_string_operators);
	jbl_string_init(jbl_Vstring(this));
	jbl_gc_set_var(jbl_Vstring(this));
	return this;
}
inline jbl_string * jbl_Vstring(jbl_var * this){if(!Vis_jbl_string(this))jbl_exception(JBL_ERROR_VAR_TYPE_ERROR);return((jbl_string*)this);}
jbl_var * jbl_string_get_number_start(const jbl_string *this,jbl_string_size_type *start)
{
	if(this==NULL||start==NULL)jbl_exception(JBL_ERROR_NULL_POINTER);	
	const jbl_string *thi=jbl_refer_pull(this);		
	jbl_string_size_type i=*start;
	if(i>=thi->len)
		return NULL;
	unsigned char c,f;jbl_uint64 x=0;
	for(f=0;((c=thi->s[i])<'0'||c>'9')&&i<thi->len;f=c=='-',++i);
	for(x=c-'0',++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;x=(x<<3)+(x<<1)+c-'0',++i);
	*start=i;
	if(thi->s[i]=='e')
		goto e;
	if(thi->s[i]!='.'||i==thi->len)
		return (f?jbl_Vint_set(NULL,-x):jbl_Vuint_set(NULL,x));
	jbl_uint64 ji=10,y;++i;
	for(c=thi->s[i],y=c-'0',++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	*start=i;
	if(thi->s[i]=='e')
		goto e;
	return jbl_Vdouble_set(NULL,f?(-(((double)y/ji)+x)):(((double)y/ji)+x));
e:;
	jbl_uint64 e=jbl_string_get_uint64_start(this,start),ji2=1;
	while(e--)ji2=(ji2<<3)+(ji2<<1);
	return jbl_Vdouble_set(NULL,(f?(-(((double)y/ji)+x)):(((double)y/ji)+x))*ji2);
}
#endif
#if JBL_LL_ENABLE==1
#include "jbl_ll.h"
jbl_ll * jbl_string_cut_start(jbl_string *this,jbl_ll *list,char cut,jbl_string_size_type start)
{
	if(this==NULL)return list;
	this=jbl_refer_pull(this);
	for(jbl_var *v=NULL;start<this->len;((jbl_string_get_length(jbl_Vstring(v))!=0)?list=jbl_ll_add(list,v):0),v=jbl_var_free(v),++start)
		for(v=jbl_Vstring_new();start<this->len&&this->s[start]!=cut;jbl_string_add_char(jbl_Vstring(v),this->s[start]),++start);
	return (list);	
}
#endif
#endif