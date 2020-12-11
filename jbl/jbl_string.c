/* Copyright (c) [2020] juruoyun developer team
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
/*******************************************************************************************/
/*                            扩展包含                                                      */
/*******************************************************************************************/
#include "jbl_string_cc.h"
/*******************************************************************************************/
/*                            依赖jbl_gc jbl_malloc jbl_ying jbl_exception                */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_gc.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
/*******************************************************************************************/
/*                            联动jbl_stream jbl_var jbl_ll jbl_ht                         */
/*******************************************************************************************/
#include "jbl_stream.h"
#include "jbl_var.h"
#include "jbl_ll.h"
#include "jbl_ht.h"
#include "jbl_log.h"
/*******************************************************************************************/
/*                            全局变量定义                                                */
/*******************************************************************************************/
#if JBL_HT_ENABLE==1 && JBL_STRING_USE_CACHE==1 && JBL_HT_SYS_ENABLE==1
jbl_ht *__jbl_string_cache=NULL;
#endif
jbl_var_operators_new(jbl_string_operators,jbl_string_free,jbl_string_copy,jbl_string_space_ship,jbl_string_json_encode,jbl_string_view_put,jbl_string_json_put);
/*******************************************************************************************/
/*                            以下函数处理传统字符串                                     */
/*******************************************************************************************/
jbl_string_size_type jbl_strlen(const unsigned char *a){if(!a)return 0;register jbl_string_size_type b=0;while(a[b])++b;return b;}
jbl_string_hash_type jbl_strhash(const unsigned char *s,jbl_string_size_type len)
{
	if(!s)return 0;
	register jbl_string_hash_type h=0;
	if(len)	for(register jbl_string_size_type i=0;i<len;h=(h<<5)+h+((unsigned char*)s)[i],++i);
	else	for(;*s;h=(h<<5)+h+*((unsigned char*)s),++s);
	return h;
}
/*******************************************************************************************/
/*                            以下函数完成字符串组件启动和停止                           */
/*******************************************************************************************/
JBL_INLINE void jbl_string_start()
{
#if JBL_HT_ENABLE==1 && JBL_STRING_USE_CACHE==1 && JBL_HT_SYS_ENABLE==1
	__jbl_string_cache=jbl_ht_new();
	jbl_ht_set_sys(__jbl_string_cache);
#endif
	jbl_string_cc_start();
}
JBL_INLINE void jbl_string_stop()
{
#if JBL_HT_ENABLE==1 && JBL_STRING_USE_CACHE==1 && JBL_HT_SYS_ENABLE==1
#if JBL_STRING_CACHE_DEBUG==1
	jbl_log(UC"%v",__jbl_string_cache);
#endif
	__jbl_string_cache=jbl_ht_free(__jbl_string_cache);
#endif
	jbl_string_cc_stop();
}
/*******************************************************************************************/
/*                            以下函实现字符串基本操作                                   */
/*******************************************************************************************/
jbl_string * jbl_string_new()
{
	jbl_string * this=jbl_malloc(sizeof(jbl_string));
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数
	jbl_pthread_lock_init(this);
	jbl_var_set_operators(this,&jbl_string_operators);
	this->len=0;
	this->h=0;
	this->size=0;
	this->s=NULL;
	return this;	
}
jbl_string* jbl_string_free(jbl_string *this)
{
	if(!this)return NULL;
    jbl_pthread_lock_wrlock(this);
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		if(jbl_gc_is_ref(this))
			jbl_string_free((jbl_string*)(((jbl_reference*)this)->ptr));
		else if (this->size)
			jbl_free(this->s);
        jbl_pthread_lock_free(this);
		jbl_free(this);
	}
    else{jbl_pthread_lock_unwrlock(this);}
	return NULL;
}
JBL_INLINE jbl_string *jbl_string_copy(jbl_string *that)
{
	if(!that)return NULL;
    jbl_pthread_lock_wrlock(that);
	jbl_gc_plus(that);
    jbl_pthread_lock_unwrlock(that);    
	return that;
}
jbl_string *jbl_string_extend_to(jbl_string *this,jbl_string_size_type size,jbl_uint8 add,jbl_string **pthi)
{
	if(!this)this=jbl_string_new();		
	jbl_reference *ref=NULL;jbl_string *thi=jbl_refer_pull_keep_father_wrlock(this,&ref);
	size+=thi->len*(add&1);
	//[0,JBL_STRING_MIN_LENGTH]=>JBL_STRING_MIN_LENGTH,[JBL_STRING_MIN_LENGTH,4K]=>2倍增,(4k,+oo)=>4k对齐
	size=(size<=JBL_STRING_MIN_LENGTH?JBL_STRING_MIN_LENGTH:(1ULL<<(jbl_highbit(size-1)+1)));
	if(jbl_gc_refcnt(thi)==1)
	{
		if(thi->size<thi->len)//如果this->size<thi->len,则该字符串是常量,必须扩容
		{
			unsigned char *s=thi->s;
			thi->s=(unsigned char *)jbl_malloc(thi->size=size);
			jbl_memory_copy(thi->s,s,thi->len);
		}
		else if(size>thi->size)
			thi->size=size,thi->s=(thi->s?(unsigned char *)jbl_realloc(thi->s,thi->size):(unsigned char *)jbl_malloc(thi->size));		
	}
	else
	{
		jbl_string *tmp=jbl_string_new();
        jbl_pthread_lock_wrlock(tmp);
		tmp->size=size;
		tmp->len=thi->len;
		tmp->h=thi->h;
		tmp->s=(unsigned char *)jbl_malloc(tmp->size);
		jbl_memory_copy(tmp->s,thi->s,thi->len);
        jbl_pthread_lock_unwrlock(thi);
		jbl_string_free(thi);
		thi=tmp;
	}
	if(ref)		ref->ptr=thi;
	else		this=thi;
	if(pthi)	*pthi=thi;
    else        {jbl_refer_pull_unwrlock(this);}
	return this;
}
jbl_string *jbl_string_clear(jbl_string *this)
{
	if(!this)return NULL;
	jbl_string *thi;this=jbl_string_extend_to(this,0,0,&thi);
    jbl_string_hash_clear(thi);	
	thi->len=0;
    jbl_refer_pull_unwrlock(this);
	return this;
}
/*******************************************************************************************/
/*                            以下函数实现字符串的缓冲操作                               */
/*******************************************************************************************/
#if JBL_HT_ENABLE==1 && JBL_STRING_USE_CACHE==1 && JBL_HT_SYS_ENABLE==1
jbl_string *jbl_string_cache_get(const unsigned char *in)
{
	if(!in)return NULL;
    jbl_refer_pull_wrlock(__jbl_string_cache);
	jbl_ht_data *data=jbl_ht_get_ht_data_chars(__jbl_string_cache,in);
	jbl_string *str=NULL;
	if(data)
		str=jbl_string_copy(data->k);
    else
    {
        str=jbl_string_add_const(NULL,in);
        if(str->len<=JBL_STRING_CACHE_MAX_LENGTH)
            __jbl_string_cache=jbl_ht_insert_force(__jbl_string_cache,jbl_string_hash(str),str,(void*)1);
	}
    jbl_refer_pull_unwrlock(__jbl_string_cache);
    return str;
}
jbl_string *jbl_string_cache_replace(jbl_string *str)
{
	if(!str)return NULL;
	if(jbl_gc_is_ref(str))return str;
	if(jbl_string_get_length(str)>JBL_STRING_CACHE_MAX_LENGTH)return str;
    jbl_refer_pull_wrlock(__jbl_string_cache);
	jbl_ht_data *data=jbl_ht_get_ht_data(__jbl_string_cache,str);
	if(data)
	{
		str=jbl_string_free(str);
		str=jbl_string_copy(data->k);
	}
    else
        __jbl_string_cache=jbl_ht_insert_force(__jbl_string_cache,jbl_string_hash(str),str,(void *)1);
    jbl_refer_pull_unwrlock(__jbl_string_cache);
    return str;
}
#endif
/*******************************************************************************************/
/*                            以下函数实现字符串的增添类操作                             */
/*******************************************************************************************/
jbl_string *jbl_string_add_const_length(jbl_string *this,const unsigned char *in,jbl_string_size_type len)
{
	if(!in)return this;
	if(this&&(jbl_gc_is_ref(this)||this->s))
        this=jbl_string_add_chars_length(this,in,len);
    else
    {
        if(!this)this=jbl_string_new();
        this->s=(unsigned char*)in;
        this->size=0;
        this->len=len;
	}
    return this;
}
jbl_string *jbl_string_add_chars_length(jbl_string *this,const unsigned char *in,jbl_string_size_type len)
{
	if(!in)return this;
	jbl_string *thi;this=jbl_string_extend_to(this,len,1,&thi);jbl_string_hash_clear(thi);
	jbl_memory_copy(thi->s+thi->len,in,len);
	thi->len=(thi->len+len);
    jbl_refer_pull_unwrlock(this);
	return this;
}
jbl_string *jbl_string_add_string(jbl_string *this,jbl_string *in)
{
	if(!in)return this;
	if(!this)return jbl_string_copy(in);
	in=jbl_refer_pull_rdlock(in);
	jbl_string *thi;this=jbl_string_extend_to(this,in->len,1,&thi);jbl_string_hash_clear(thi);
	jbl_memory_copy(thi->s+thi->len,in->s,in->len);
	thi->len=(thi->len+in->len);
    jbl_refer_pull_unwrlock(this);
    jbl_refer_pull_unrdlock(in);
	return this;
}
JBL_INLINE jbl_string *jbl_string_add_char(jbl_string *this,const unsigned char c)
{
	jbl_string *thi;this=jbl_string_extend_to(this,1,1,&thi);jbl_string_hash_clear(thi);
	thi->s[thi->len]=c,++thi->len;
    jbl_refer_pull_unwrlock(this);
	return this;
}

JBL_INLINE jbl_string * jbl_string_add_int_length(jbl_string *this,jbl_int64 in,jbl_uint8 len,char c)
{
    jbl_string *thi;this=jbl_string_extend_to(this,22,1,&thi);
	if(in<0)
		jbl_string_add_char_force(thi,'-'),in=-in;
	this=jbl_string_add_uint_length(this,(jbl_uint64)in,len,c);
    jbl_refer_pull_unwrlock(this);
    return this;
}
jbl_string * jbl_string_add_uint_length(jbl_string *this,jbl_uint64 in,jbl_uint8 len,char c)
{
	jbl_string *thi;this=jbl_string_extend_to(this,jbl_max(len,21),1,&thi);jbl_string_hash_clear(thi);
    jbl_uint8 cnt=20;
    unsigned char b[21];
    b[cnt--]=0;
	if(!in) b[cnt--]='0';
    else    while(in)b[cnt--]=(jbl_uint8)((in%10)+'0'),in/=10;
    for(jbl_uint8 i=(jbl_uint8)(19-cnt);i<len;jbl_string_add_char_force(thi,c),++i);
    this=jbl_string_add_chars_length(this,b+cnt+1,((jbl_string_size_type)19)-cnt);
    jbl_refer_pull_unwrlock(this);
    return this;
}
jbl_string * jbl_string_add_double_length(jbl_string *this,double in,jbl_uint8 len)
{
    jbl_refer_pull_wrlock(this);
	this=jbl_string_add_int(this,(jbl_int64)in);
	this=jbl_string_add_char(this,'.');
	if(in<0)in=-in;
	in-=((double)((jbl_uint64)in));
	jbl_uint64 ji=1;
	for(register jbl_uint8 i=0,n=(jbl_uint8)(len+2);i<n;++i,ji=(ji<<3)+(ji<<1));
	jbl_uint64 t=(jbl_uint64)((((double)ji)*in+0.5)/10);
	if(t==0)
		this=jbl_string_add_char(this,'0');
    else
    {
        unsigned char b[21];
        for(register jbl_uint8 i=0;i<21;b[i]='0',++i);
        register jbl_uint8 cnt=20;
        b[cnt--]=0;
        while(t)b[cnt--]=(unsigned char)(t%10+'0'),t/=10;
        this=jbl_string_add_chars_length(this,b+20-len-1,len);
    }
    jbl_refer_pull_unwrlock(this);
    return this;
}
jbl_string * jbl_string_add_hex(jbl_string *this,jbl_uint64 in)
{
	jbl_uint64 n=1;
	while((in>>(n<<2)))++n;
	jbl_string *thi;this=jbl_string_extend_to(this,n+1,1,&thi);jbl_string_hash_clear(thi);
	const unsigned char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(;n--;thi->s[thi->len]=(hex[(in>>(n<<2))&15]),++thi->len){}
    jbl_refer_pull_unwrlock(this);
	return this;
}
JBL_INLINE jbl_string * jbl_string_add_hex_8bits(jbl_string *this,jbl_uint8 in)
{
	const unsigned char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	jbl_string *thi;this=jbl_string_extend_to(this,2,1,&thi);jbl_string_hash_clear(thi);
	thi->s[thi->len]=(hex[(in>>4)&15])	,++thi->len;
	thi->s[thi->len]=(hex[in&15])		,++thi->len;	
    jbl_refer_pull_unwrlock(this);
	return this;
}
JBL_INLINE jbl_string* jbl_string_set_tail(jbl_string *this)
{
	if(!this)return NULL;
	jbl_string* thi=jbl_refer_pull_wrlock(this);
	if(thi->s&&thi->size&&thi->len<thi->size)
		thi->s[thi->len]=0;
    jbl_refer_pull_unwrlock(this);
	return this;
}
/*******************************************************************************************/
/*                            以下函数实现字符串的获取类操作                             */
/*******************************************************************************************/
JBL_INLINE unsigned char jbl_string_get(jbl_string *this,jbl_string_size_type i)
{
	if(!this)return 0;
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_uint8 c=(i<thi->len)?thi->s[i]:0;
	jbl_refer_pull_unrdlock(this);
    return c;
}
jbl_int64 jbl_string_get_int_start(jbl_string *this,jbl_string_size_type *start)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=start?(*start):0; 	
    if(i>=thi->len){jbl_refer_pull_unrdlock(this);return 0;}
	unsigned char c,f;jbl_int64 x=0;
	for(f=0;((c=thi->s[i])<'0'||c>'9')&&i<thi->len;f=c=='-',++i);
	for(x=(jbl_int64)(c-'0'),++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;x=(x<<3)+(x<<1)+c-'0',++i);
	start?(*start=i):0;
	jbl_refer_pull_unrdlock(this);
	return f?-x:x;	
}
jbl_uint64 jbl_string_get_uint_start(jbl_string *this,jbl_string_size_type *start)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=start?(*start):0; 	
    if(i>=thi->len){jbl_refer_pull_unrdlock(this);return 0;}
	unsigned char c;jbl_uint64 x=0;
	for(;((c=thi->s[i])<'0'||c>'9')&&i<thi->len;++i);
	for(x=(jbl_uint64)(c-'0'),++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;x=(x<<3)+(x<<1)+c-'0',++i);
	start?(*start=i):0;
	jbl_refer_pull_unrdlock(this);
	return x;	
}
jbl_uint64 jbl_string_get_uint_start_end(jbl_string *this,jbl_string_size_type *start,unsigned char end)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=start?(*start):0; 	
    if(i>=thi->len){jbl_refer_pull_unrdlock(this);return 0;}
	unsigned char c;jbl_uint64 x=0;
	for(;((c=thi->s[i])<'0'||c>'9')&&i<thi->len&&c!=end;++i);
	if(c==end)return 0;
	for(x=(jbl_uint64)(c-'0'),++i;(c=thi->s[i])>='0'&&c<='9'&&c!=end&&i<thi->len;x=(x<<3)+(x<<1)+c-'0',++i);
	start?(*start=i):0;
	jbl_refer_pull_unrdlock(this);
	return x;	
}
double jbl_string_get_double_start(jbl_string *this,jbl_string_size_type *start)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=start?(*start):0; 	
    if(i>=thi->len){jbl_refer_pull_unrdlock(this);return 0;}
	unsigned char c,f;jbl_uint64 x=0;
	for(f=0;((c=thi->s[i])<'0'||c>'9')&&i<thi->len;f=c=='-',++i);
	for(x=(jbl_uint64)(c-'0'),++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;x=(x<<3)+(x<<1)+c-'0',++i);
	start?(*start=i):0;
	if(thi->s[i]!='.'||i==thi->len)
    {
        jbl_refer_pull_unrdlock(this);
		return (f?-(double)x:(double)x);
	}
    jbl_uint64 ji=10,y;++i;
	for(c=thi->s[i],y=(jbl_uint64)(c-'0'),++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	start?(*start=i):0;
	jbl_refer_pull_unrdlock(this);
	return ((((double)y)/((double)ji))+(double)(x))*(f?-1:1);
}
static jbl_uint8  ok16 (jbl_uint8 c){return ((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'));}
static jbl_uint64 get16(jbl_uint8 c){return (jbl_uint64)((c>='A'&&c<='F')?(c-'A'+10):((c>='a'&&c<='f')?(c-'a'+10):(c-'0')));}
jbl_uint64 jbl_string_get_hex_start(jbl_string *this,jbl_string_size_type *start)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=start?(*start):0; 	
    if(i>=thi->len){jbl_refer_pull_unrdlock(this);return 0;}
	jbl_uint64 x=0;
	for(;i<thi->len&&(!ok16(thi->s[i]));++i);
	for(x=get16(thi->s[i]),++i;i<thi->len&&ok16(thi->s[i]);x=(x<<4)+get16(thi->s[i]),++i){}
	start?(*start=i):0;
	jbl_refer_pull_unrdlock(this);
	return x;
}
jbl_uint64 jbl_string_get_hex_start_len(jbl_string *this,jbl_string_size_type *start,jbl_string_size_type len)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);		
	jbl_string_size_type i=start?(*start):0;
    if(i>=thi->len){jbl_refer_pull_unrdlock(this);return 0;}
	jbl_uint64 x=0;
	for(;i<thi->len&&(!ok16(thi->s[i]));++i);
	for(x=get16(thi->s[i]),++i;(--len)&&i<thi->len&&ok16(thi->s[i]);x=(x<<4)+get16(thi->s[i]),++i){}
	start?(*start=i):0;
	jbl_refer_pull_unrdlock(this);
	return x;
}
/*******************************************************************************************/
/*                            以下函数实现字符串的比较类操作                             */
/*******************************************************************************************/
char jbl_string_space_ship(jbl_string *this,jbl_string *that)
{
    char ans=0;
	jbl_string *thi=jbl_refer_pull_rdlock(this);
	jbl_string *tha=jbl_refer_pull_rdlock(that);	
	if(thi==tha){ans=0;goto exit;}if(!thi){ans=-1;goto exit;}if(!tha){ans=1;goto exit;}
	if(thi->len!=tha->len)
        {ans=(thi->len<tha->len)?-1:1;goto exit;}
    for(jbl_string_size_type i=0;i<thi->len;++i)
		if(thi->s[i]<tha->s[i])
            {ans=-1;goto exit;}
        else if(thi->s[i]>tha->s[i])
            {ans=1;goto exit;}
    ans=0;
exit:;
    jbl_refer_pull_unrdlock(this);
    jbl_refer_pull_unrdlock(that);
	return ans;
}
char jbl_string_space_ship_chars(jbl_string *this,const char *that)
{
    char ans=0;
	jbl_string *thi=jbl_refer_pull_rdlock(this);
	if(!thi){ans=-1;goto exit;}if(!that){ans=1;goto exit;}
	register jbl_string_size_type i=0;
	for(;i<thi->len;++i)
	{
		if(thi->s[i]<that[i])
            {ans=-1;goto exit;}
		else if(!that[i]||thi->s[i]>that[i])
            {ans=1;goto exit;}
	}
    ans=that[i]?-1:0;
exit:;
    jbl_refer_pull_unrdlock(this);
	return ans;
}
char jbl_string_if_equal(jbl_string *this,jbl_string *that)
{	
    char ans=0;
	jbl_string *thi=jbl_refer_pull_rdlock(this);	
	jbl_string *tha=jbl_refer_pull_rdlock(that);	
	if(thi==tha){ans=1;goto exit;}if(!thi||!tha){ans=0;goto exit;}
	if(thi->h!=0&&thi->h!=tha->h){ans=0;goto exit;}
	if(thi->len!=tha->len){ans=0;goto exit;}
	for(jbl_string_size_type i=0;i<thi->len;i++)
		if(thi->s[i]!=tha->s[i])
			{ans=0;goto exit;}
	ans=1;
exit:;
    jbl_refer_pull_unrdlock(this);
    jbl_refer_pull_unrdlock(that);
	return ans;
}
/*******************************************************************************************/
/*                            以下函数实现字符串的查找类操作                             */
/*******************************************************************************************/
jbl_string_size_type jbl_string_find_char_start(jbl_string *this,unsigned char in,jbl_string_size_type start)
{
	if(!this)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_rdlock(this);			
	for(;start<thi->len&&thi->s[start]!=in;++start){}
    jbl_refer_pull_unrdlock(this);
	return (start);
}
/*******************************************************************************************/
/*                            以下函数实现字符串的hash操作                               */
/*******************************************************************************************/
jbl_string_hash_type jbl_string_hash(jbl_string *this)
{
	if(!this)       return 0;
	jbl_string *thi=jbl_refer_pull_rdlock(this);			
	if(thi->h==0)  thi->h=jbl_strhash(thi->s,thi->len);
    jbl_refer_pull_unrdlock(this);
	return thi->h;
}
/*******************************************************************************************/
/*                            以下函数实现字符串的修改操作                               */
/*******************************************************************************************/
jbl_string * jbl_string_to_upper_case(jbl_string *this)
{
	jbl_string *thi;this=jbl_string_extend_to(this,0,1,&thi);jbl_string_hash_clear(thi);
	for(jbl_string_size_type i=0;i<thi->len;++i)
		if(thi->s[i]>='a'&&thi->s[i]<='z')
			thi->s[i]=(jbl_uint8)(thi->s[i]-'a'+'A');
    jbl_refer_pull_unwrlock(this);
	return  this;
}
jbl_string * jbl_string_to_lower_case(jbl_string *this)
{
	jbl_string *thi;this=jbl_string_extend_to(this,0,1,&thi);jbl_string_hash_clear(thi);
	for(jbl_string_size_type i=0;i<thi->len;++i)
		if(thi->s[i]>='A'&&thi->s[i]<='Z')
			thi->s[i]=(jbl_uint8)(thi->s[i]-'A'+'a');
    jbl_refer_pull_unwrlock(this);
	return  this;
}
#if JBL_JSON_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的JSON操作                               */
/*******************************************************************************************/
jbl_string* jbl_string_json_encode(jbl_string* this,jbl_string *out,jbl_uint8 format,jbl_uint32 tabs)
{
	jbl_string *thi=jbl_refer_pull_rdlock(this);
	out=jbl_string_json_put_format(thi,out,format,tabs);
    if(thi)
    {
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
        if(format&2){out=jbl_string_add_char(out,',');}if((format&1)||(format&4)){out=jbl_string_add_char(out,'\n');}
    }
    jbl_refer_pull_unwrlock(out);
    jbl_refer_pull_unrdlock(this);
    return out;
}
jbl_string* jbl_string_json_put_format(const void* this,jbl_string *out,jbl_uint8 format,jbl_uint32 tabs)
{
	if(!out)out=jbl_string_new();
    jbl_refer_pull_wrlock(out);
	if(format&1)for(jbl_uint32 i=0;i<tabs;out=jbl_string_add_char(out,'\t'),++i);
	if(!this)out=jbl_string_add_chars_length(out,UC"null",4);
	return out;
}
#if JBL_STREAM_ENABLE==1
void jbl_string_json_put(jbl_string* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs)
{
	jbl_string *thi=jbl_refer_pull_rdlock(this);
	if(jbl_stream_json_put_format(thi,out,format,tabs))
    {
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
                    default  :jbl_stream_push_chars(out,UC"u00"),jbl_stream_push_hex_8bits(out,token);break;
                }
            }		
        }
        jbl_stream_push_char(out,'"');
        if(format&2){jbl_stream_push_char(out,',');}if((format&1)||(format&4)){jbl_stream_push_char(out,'\n');}
    }
    jbl_refer_pull_unwrlock(out);
    jbl_refer_pull_unrdlock(this);
}
#endif
#endif
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的浏览操作                               */
/*******************************************************************************************/
jbl_string* jbl_string_view_put(jbl_string* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * file)
{
	jbl_string *thi=jbl_refer_pull_rdlock(this);
    if(jbl_stream_view_put_format(thi,out,format,tabs,UC"jbl_string",line,varname,func,file))
    {
        jbl_stream_push_chars(out,UC" size:");
        jbl_stream_push_uint(out,thi->size);
        jbl_stream_push_chars(out,UC"\tlen:");
        jbl_stream_push_uint(out,thi->len);
        jbl_stream_push_chars(out,UC"\ts:");	
        for(jbl_string_size_type i=0;i<thi->len;++i)
            jbl_stream_push_char(out,thi->s[i]);
    }
    jbl_stream_push_char(out,'\n');
    jbl_refer_pull_unwrlock(out);
    jbl_refer_pull_unrdlock(this);
	return this;
}
#endif
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的STREAM操作                             */
/*******************************************************************************************/
jbl_stream * jbl_string_stream_new(jbl_string *str)
{
	jbl_stream * stream=jbl_stream_new(&jbl_stream_string_operators);
    stream->data[0].p=jbl_string_copy(str);
    return stream;
}
static void __fb(jbl_stream_buf* thi){jbl_free(thi);}
void __ssop(jbl_stream* thi,jbl_uint8 force)
{
	if(!thi)jbl_exception("NULL POINTER");
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
    if(thi->buf)
    {
        if(thi->buf->forthis)
        {
            jbl_string_size_type len=thi->buf->len-thi->buf->sta;
            if(thi->buf->free_buf==__fb)
            {
                jbl_string *str;thi->data[0].p=jbl_string_extend_to((jbl_string*)thi->data[0].p,128+len,1,&str);jbl_string_hash_clear(str);
                str->len+=len;
                thi->buf->size=(jbl_stream_buf_size_type)(str->size-str->len);
                thi->buf->s=str->s+str->len;
                thi->buf->sta=0;
                thi->buf->len=0;
                jbl_refer_pull_unwrlock((jbl_string*)thi->data[0].p);
            }
            else
            {
                thi->data[0].p=jbl_string_add_chars_length((jbl_string*)thi->data[0].p,thi->buf->s+thi->buf->sta,len);
                thi->buf->sta=thi->buf->len;
            }
        }
    }
    if(nxt)
    {
        jbl_stream_get_buf(thi,1);
        jbl_string *str=jbl_refer_pull_rdlock((jbl_string*)thi->data[0].p);
        if(nxt->buf->free_buf==__fb)
        {
            thi->data[1].u+=nxt->buf->sta;
            nxt->buf->sta=0;
            nxt->buf->size=(jbl_stream_buf_size_type)(str->len-thi->data[1].u);
            nxt->buf->len=(jbl_stream_buf_size_type)(str->len-thi->data[1].u);
            nxt->buf->s=str->s+thi->data[1].u;
        }
        else
        {
            while(thi->data[1].u<str->len)
            {
                jbl_stream_buf_size_type len=(jbl_stream_buf_size_type)jbl_min((str->len-thi->data[1].u),(nxt->buf->size-nxt->buf->len));	
                jbl_memory_copy(nxt->buf->s+nxt->buf->len,str->s+thi->data[1].u,len);
                thi->data[1].u+=len;
                nxt->buf->len+=len;
                jbl_stream_push_down(nxt,0);
                jbl_stream_move_unhandle_buf(nxt->buf);
                if(1==(thi->stop=nxt->stop))break;
            }
        }
        jbl_refer_pull_unrdlock((jbl_string*)thi->data[0].p);
        nxt->op->op(nxt,force);
    }        
    jbl_refer_pull_unwrlock(thi->nxt);
}
static void __sff(jbl_stream* thi){jbl_string_free((jbl_string*)thi->data[0].p);}
static jbl_stream_buf * __pb(jbl_stream* thi,jbl_uint8 forthis)
{
 	jbl_string *str;thi->data[0].p=jbl_string_extend_to((jbl_string*)thi->data[0].p,128*(forthis?1:0),1,&str);
    jbl_stream_buf *buf=jbl_malloc(sizeof(jbl_stream_buf));
    buf->sta=0;
    buf->free_buf=__fb;
    buf->forthis=forthis;
    if(buf->forthis)
    {
        buf->size=(jbl_stream_buf_size_type)(str->size-str->len);
        buf->len=0;
        buf->s=str->s+str->len;
    }
    else
    {
        buf->size=(jbl_stream_buf_size_type)(str->len-thi->data[1].u);
        buf->len=(jbl_stream_buf_size_type)(str->len-thi->data[1].u);
        buf->s=str->s+thi->data[1].u;
    }
    jbl_refer_pull_unwrlock((jbl_string*)thi->data[0].p);   
    return buf;
}
jbl_stream_operators_new(jbl_stream_string_operators,__ssop,__sff,__pb,128,2);
jbl_string*  jbl_stream_push_string_start_end(jbl_stream *out,jbl_string* this,jbl_string_size_type i,jbl_string_size_type end)
{
	if(!this)return this;
 	jbl_string *thi=jbl_refer_pull_rdlock(this);
    jbl_min_update(end,thi->len);
    jbl_min_update(i,end);
    jbl_stream_push_chars_length(out,thi->s+i,end-i);
    jbl_refer_pull_unrdlock(this);	
	return this;
}
jbl_string *jbl_string_read(jbl_string *this,const unsigned char *c)
{
    jbl_refer_pull_wrlock(jbl_stream_stdout);
    jbl_refer_pull_wrlock(jbl_stream_stdin);
	jbl_stream_push_chars(jbl_stream_stdout,c);
	jbl_stream_do(jbl_stream_stdout,true);
	if(!this)this=jbl_string_new();
    jbl_refer_pull_wrlock(this);
	jbl_stream *tmp=jbl_string_stream_new(this);
    this=jbl_string_free(this);
	jbl_stream_connect(jbl_stream_stdin_link,tmp);
	jbl_stream_do(jbl_stream_stdin,false);
	jbl_stream_do(tmp,true);
	jbl_stream_disconnect(jbl_stream_stdin_link);
    this=jbl_string_copy((jbl_string *)tmp->data[0].p);
	tmp=jbl_stream_free(tmp);
    jbl_refer_pull_unwrlock(this);
    jbl_refer_pull_unwrlock(jbl_stream_stdout);
    jbl_refer_pull_unwrlock(jbl_stream_stdin);
	return this;
}
#endif
#if JBL_VAR_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现字符串的var操作                                */
/*******************************************************************************************/
jbl_var_data * jbl_string_get_number_start(jbl_string *this,jbl_string_size_type *start)
{
	if(!this||!start)jbl_exception("NULL POINTER");	
	jbl_string *thi=jbl_refer_pull_unrdlock(this);
	jbl_string_size_type i=*start;
	unsigned char c,f;jbl_uint64 x=0;
	jbl_uint64 ji=10,y=0;
	if(i>=thi->len)
    {
        jbl_refer_pull_unrdlock(this);
		return NULL;
    }
    for(f=0;((c=thi->s[i])<'0'||c>'9')&&i<thi->len;f=c=='-',++i){}
	for(x=(jbl_uint8)(c-'0'),++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;x=(x<<3)+(x<<1)+c-'0',++i){}
	*start=i;
	if(thi->s[i]=='e')
		goto e;
	if(thi->s[i]!='.'||i==thi->len)
    {
        jbl_refer_pull_unrdlock(this);
		return (f?jbl_Vint_set(NULL,(jbl_int64)(-x)):jbl_Vuint_set(NULL,x));
	}
    ++i;
	for(c=thi->s[i],y=(jbl_uint8)(c-'0'),++i;(c=thi->s[i])>='0'&&c<='9'&&i<thi->len;y=(y<<3)+(y<<1)+c-'0',ji=(ji<<3)+(ji<<1),++i);
	*start=i;
	if(thi->s[i]=='e')
		goto e;
    jbl_refer_pull_unrdlock(this);
	return jbl_Vdouble_set(NULL,((((double)y)/((double)ji))+(double)(x))*(f?-1:1));
e:;
	jbl_uint64 e=jbl_string_get_uint_start(this,start),ji2=1;
	while(e--)ji2=(ji2<<3)+(ji2<<1);
    jbl_refer_pull_unrdlock(this);
	return jbl_Vdouble_set(NULL,((((double)y)/((double)ji))+(double)(x))*(f?-1:1)*((double)ji2));
}
#endif
/*******************************************************************************************/
/*                            以下函数实现字符串的切割操作                               */
/*******************************************************************************************/
#if JBL_LL_ENABLE==1
jbl_string *jbl_string_delete(jbl_string *this,jbl_string_size_type start,jbl_string_size_type end)
{
	if(start>=end)return this;
	jbl_string *thi;this=jbl_string_extend_to(this,0,1,&thi);jbl_string_hash_clear(thi);
	jbl_min_update(end,thi->len);
	for(jbl_string_size_type j=end,i=start;j<thi->len;thi->s[i]=thi->s[j],++j,++i);
	thi->len-=(end-start);
    jbl_refer_pull_unwrlock(this);
	return this;
}
jbl_ll * jbl_string_cut_start(jbl_string *this,jbl_ll *list,char cut,jbl_string_size_type start)
{
	if(!this)return list;
	this=jbl_refer_pull_rdlock(this);
	for(jbl_string *v=NULL;start<this->len;(v?list=jbl_ll_add(list,v):0),v=jbl_var_free(v),++start)
		for(;start<this->len&&this->s[start]!=cut;v=jbl_string_add_char(v,this->s[start]),++start);
    jbl_refer_pull_unrdlock(this);
	return (list);	
}
#endif
#endif