/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_string_cc.h"
#if JBL_STRING_CC_ENABLE==1
#include "jbl_log.h"
//下面这两张表(__jbl_string_gtu_table,__jbl_string_gtu_table)来自fatfs cc936.c
//需要注意的是,在二分计算有效长度的时候,需要/4,unicode 和 gb2312各占两个字节
#if JBL_STRING_CC_INNER_DB_ENABLE==1
#include "jbl_string_cc_table.h"
static const jbl_uint32 __jbl_string_utg_table_len=(const jbl_uint32)((sizeof __jbl_string_utg_table)>>2)-1;//unicode 和 gb2312各占两个字节
static const jbl_uint32 __jbl_string_gtu_table_len=(const jbl_uint32)((sizeof __jbl_string_gtu_table)>>2)-1;//unicode 和 gb2312各占两个字节
#else
jbl_string * __jbl_string_cc_db=NULL;
static jbl_uint16 * __jbl_string_utg_table=NULL; 
static jbl_uint16 * __jbl_string_gtu_table=NULL; 
static jbl_uint32 __jbl_string_utg_table_len=0;
static jbl_uint32 __jbl_string_gtu_table_len=0;
#include "jbl_file.h"
#endif
/*******************************************************************************************/
/*                            以下函数完成字符串编码转换扩展组件启动和停止                         */
/*******************************************************************************************/
void jbl_string_cc_start()
{
#if JBL_STRING_CC_INNER_DB_ENABLE==0
	jbl_file * f1=jbl_file_open_chars(NULL,UC JBL_STRING_CC_OUT_DB_DIR,JBL_FILE_READ);
	__jbl_string_cc_db			=jbl_file_read(f1,NULL,0,-1);
	if((!__jbl_string_cc_db)||(!__jbl_string_cc_db->len))jbl_exception("GB2312 UNICODE DB ERROR");
	__jbl_string_utg_table		=(jbl_uint16*)(__jbl_string_cc_db->s);
	__jbl_string_utg_table_len	=(jbl_file_get_size(f1)>>1)-1;
	__jbl_string_gtu_table		=(jbl_uint16*)(__jbl_string_cc_db->s+(jbl_file_get_size(f1)>>1));
	__jbl_string_gtu_table_len	=(jbl_file_get_size(f1)>>1)-1;
	f1=jbl_file_free(f1);
	if(__jbl_string_utg_table_len!=__jbl_string_gtu_table_len)jbl_exception("GB2312 UNICODE DB ERROR");
	if(__jbl_string_utg_table[0]!=0x00A3||__jbl_string_gtu_table[0]!=0x0080)jbl_exception("GB2312 UNICODE DB ERROR");
	
#endif
}
void jbl_string_cc_stop()
{
#if JBL_STRING_CC_INNER_DB_ENABLE==0
	jbl_string_free(__jbl_string_cc_db);
	__jbl_string_utg_table=NULL; 
	__jbl_string_gtu_table=NULL; 
#endif
}
/*******************************************************************************************/
/*                            以下函数实现utf8 gb2312 unicode互转                         */
/*******************************************************************************************/
jbl_uint8 __jbl_string_utu8(unsigned char *s,jbl_uint32 unicode)//unicode to utf8
{
	jbl_uint8 len=0;
	if(unicode<=0x7F)
		s[len]=(jbl_uint8)(unicode&0x7F)              ,++len;
	else if(unicode>=0x80&&unicode<=0x7FF)
		s[len]=(jbl_uint8)(((unicode>>6)&0x1F)|0xC0)  ,++len,
		s[len]=(jbl_uint8)((unicode&0x3F)|0x80)       ,++len;
	else if(unicode>=0x800&&unicode<=0xFFFF)
		s[len]=(jbl_uint8)(((unicode>>12)&0x0F)|0xE0) ,++len,
		s[len]=(jbl_uint8)(((unicode>>6)&0x3F)|0x80)  ,++len,
		s[len]=(jbl_uint8)((unicode&0x3F)|0x80)       ,++len;
	else if(unicode>=0x10000&&unicode<=0x10FFFF)
		s[len]=(jbl_uint8)(((unicode>>18)&0x7)|0xF0)  ,++len,
		s[len]=(jbl_uint8)(((unicode>>12)&0x3F)|0x80) ,++len,
		s[len]=(jbl_uint8)(((unicode>>6)&0x3F)|0x80)  ,++len,
		s[len]=(jbl_uint8)((unicode&0x3F)|0x80)       ,++len;
	else if(unicode>=0x200000&&unicode<=0x3FFFFFF)
		s[len]=(jbl_uint8)(((unicode>>24)&0x3)|0xF8)  ,++len,
		s[len]=(jbl_uint8)(((unicode>>18)&0x3F)|0x80) ,++len,
		s[len]=(jbl_uint8)(((unicode>>12)&0x3F)|0x80) ,++len,
		s[len]=(jbl_uint8)(((unicode>>6)&0x3F)|0x80)  ,++len,
		s[len]=(jbl_uint8)((unicode&0x3F)|0x80)       ,++len;
	else if(unicode>=0x4000000&&unicode<=0x7FFFFFFF)
		s[len]=(jbl_uint8)(((unicode>>30)&0x1)|0xFC)  ,++len,
		s[len]=(jbl_uint8)(((unicode>>24)&0x3F)|0x80) ,++len,
		s[len]=(jbl_uint8)(((unicode>>18)&0x3F)|0x80) ,++len,
		s[len]=(jbl_uint8)(((unicode>>12)&0x3F)|0x80) ,++len,
		s[len]=(jbl_uint8)(((unicode>>6)&0x3F)|0x80)  ,++len,
		s[len]=(jbl_uint8)((unicode&0x3F)|0x80)		  ,++len;
	return len;
}
jbl_uint32 __jbl_string_u8tu(const unsigned char *s,jbl_uint8 *start,jbl_uint8 len)//utf8 to unicode
{
	jbl_uint8 i=0;
	jbl_uint32 uni=0;
	if(5<len&&(s[i]&0XFC)==0xFC)
		uni|=(((jbl_uint32)s[i])&0x01)<<30	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<24	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<18	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<12	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<6	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)		,++i;
	else if(4<len&&(s[i]&0XF8)==0xF8)
		uni|=(((jbl_uint32)s[i])&0x03)<<24	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<18	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<12	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<6	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)		,++i;
	else if(3<len&&(s[i]&0XF0)==0xF0)
		uni|=(((jbl_uint32)s[i])&0x07)<<18	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<12	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<6	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)		,++i;
	else if(2<len&&(s[i]&0XE0)==0xE0)
		uni|=(((jbl_uint32)s[i])&0x0F)<<12	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)<<6	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)		,++i;
	else if(1<len&&(s[i]&0XC0)==0xC0)
		uni|=(((jbl_uint32)s[i])&0x1F)<<6	,++i,
		uni|=(((jbl_uint32)s[i])&0x3F)		,++i;
	else if(0<len)
		uni|=(((jbl_uint32)s[i])&0x7F)		,++i;
	start?(*start=i):0;
	return uni;
}
jbl_uint16 __jbl_string_utg(jbl_uint16 chr)//unicode to gb2312
{
	jbl_uint32 i,li=0,hi=__jbl_string_utg_table_len;//unicode 和 gb2312各占两个字节
	if(chr<0x80)return chr;
	
	for(jbl_uint8 n=17;n;n--)
	{
		i=li+((hi-li)>>1);
		if(chr==__jbl_string_utg_table[i<<1])	return __jbl_string_utg_table[(i<<1)+1];
		if(chr>__jbl_string_utg_table[i<<1])	li=i;
		else									hi=i;
	}
#if JBL_STRING_CC_DEBUG==1
	jbl_log(UC"Unknow unicode 0X%X",(jbl_uint64)chr);
#endif
	return 0;
}
jbl_uint16 __jbl_string_gtu(jbl_uint16 chr)//gb2312 to utf8
{
	if(chr<0x80)return chr;
	jbl_uint32 i,li=0,hi=__jbl_string_gtu_table_len;//unicode 和 gb2312各占两个字节
	for(jbl_uint8 n=17;n;n--)
	{
		i=li+((hi-li)>>1);
		if(chr==__jbl_string_gtu_table[i<<1])	return __jbl_string_gtu_table[(i<<1)+1];
		if(chr>__jbl_string_gtu_table[i<<1])	li=i;
		else												hi=i;
	}
#if JBL_STRING_CC_DEBUG==1	
	jbl_log(UC"Unknow unicode 0X%X",(jbl_uint64)chr);
#endif
	return 0;
}
jbl_string * jbl_string_add_utf8_from_unicode(jbl_string *this,jbl_uint32 unicode)
{
	jbl_string *thi;this=jbl_string_extend_to(this,6,1,&thi);jbl_string_hash_clear(thi);
	thi->len+=__jbl_string_utu8(thi->s+thi->len,unicode);
	return this;
}
jbl_uint32  jbl_string_get_unicode_from_utf8_start(jbl_string *this,jbl_string_size_type *start)
{
	if(!this)jbl_exception("NULL POINTER");
	jbl_string *thi=jbl_refer_pull(this);
	jbl_uint8 i=0;
	jbl_uint32 uni=__jbl_string_u8tu(thi->s+(start?(*start):0),&i,(jbl_uint8)jbl_min(6,thi->len));
	start?(*start+=i):0;
	return uni;
}
jbl_string* jbl_string_to_gb2312_from_utf8(jbl_string* this,jbl_string* that)
{
	if(!that)jbl_exception("NULL POINTER");
	jbl_string*tha=jbl_refer_pull(that);
	this=jbl_string_extend(this,tha->len);
	for(jbl_string_size_type i=0,j=0;i<tha->len;)
	{
		jbl_uint32 uni=jbl_string_get_unicode_from_utf8_start(that,&i);
		if(i==j)break;
		uni=__jbl_string_utg((jbl_uint16)uni);
		if((uni>>8))this=jbl_string_add_char(this,(uni>>8)&0XFF);
		this=jbl_string_add_char(this,uni&0XFF);
	}
	return this;
}
jbl_string* jbl_string_to_utf8_from_gb2312(jbl_string* this,jbl_string* that)
{
	if(!that)jbl_exception("NULL POINTER");
	jbl_string*tha=jbl_refer_pull(that);
	this=jbl_string_extend(this,tha->len);
	for(jbl_string_size_type i=0;i<tha->len;)
	{
		if(tha->s[i]<0x80||(i+1)>=tha->len)
			jbl_string_add_char(this,tha->s[i]),++i;
		else
		{
			jbl_uint16 gb=(jbl_uint16)((tha->s[i]<<8)|tha->s[i+1]);i+=2;
			gb=__jbl_string_gtu(gb);
			this=jbl_string_add_utf8_from_unicode(this,gb);
		}
	}
	return this;
}
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现stream的转码操作                                     */
/*******************************************************************************************/
void __jbl_string_u8tgso(jbl_stream* thi,jbl_uint8 force)//utf8_to_gb2312_stream_operater
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(nxt);
		jbl_stream_buf_size_type i=0,len=thi->buf->len;
		for(;i<len;)
		{
			if((nxt->buf->len+2)>nxt->buf->size){nxt->op->op(nxt,0);if(1==(thi->stop=nxt->stop))goto backup;}
			jbl_uint8 j=0;
			jbl_uint32 uni=__jbl_string_u8tu(thi->buf->s+i,&j,(jbl_uint8)(len-i));
			if(j==0)break;
			i+=j;
			uni=__jbl_string_utg((jbl_uint16)uni);
			if((uni>>8))nxt->buf->s[nxt->buf->len]=(uni>>8)&0XFF,++nxt->buf->len;
			nxt->buf->s[nxt->buf->len]=uni&0XFF,++nxt->buf->len;
		}
		if(force)
		{
			for(;i<len;nxt->buf->s[nxt->buf->len]=thi->buf->s[i],++nxt->buf->len,++i)
				if((nxt->buf->len+1)>nxt->buf->size)
					{nxt->op->op(nxt,0);if(1==(thi->stop=nxt->stop))goto backup;}
			thi->buf->len=0;
			nxt->op->op(nxt,force);
			goto backup;
		}
backup:;
		jbl_memory_copy(thi->buf->s,thi->buf->s+i,thi->buf->len=len-i);
	}
    jbl_refer_pull_unwrlock(thi->nxt);
}
void __jbl_string_gtu8so(jbl_stream* thi,jbl_uint8 force)//gb2312_to_utf8_stream_operater
{
	if(!thi)jbl_exception("NULL POINTER");	
	jbl_stream* nxt=jbl_refer_pull_wrlock(thi->nxt);
	if(nxt&&(!thi->stop)&&thi->buf)
	{
        jbl_stream_get_buf(nxt);
        jbl_stream_buf_size_type i=0,len=thi->buf->len;		
		for(;i<len;)
		{
			if(thi->buf->s[i]<0x80){nxt->buf->s[nxt->buf->len++]=thi->buf->s[i++];continue;}
			if((i+2)>len)break;
			jbl_uint16 gb=(jbl_uint16)((thi->buf->s[i]<<8)|thi->buf->s[i+1]);i+=2;
			gb=__jbl_string_gtu(gb);
			if((nxt->buf->len+6)>=nxt->buf->size){nxt->op->op(nxt,0);if(1==(thi->stop=nxt->stop))goto backup;}
			nxt->buf->len+=__jbl_string_utu8(nxt->buf->s+nxt->buf->len,gb);
		}
		if(force)
		{
            for(;i<len;nxt->buf->s[nxt->buf->len]=thi->buf->s[i],++nxt->buf->len,++i)
				if((nxt->buf->len+1)>nxt->buf->size)
					{nxt->op->op(nxt,0);if(1==(thi->stop=nxt->stop))goto backup;}
			thi->buf->len=0;
			nxt->op->op(nxt,force);
			goto backup;
		}
backup:;
		jbl_memory_copy(thi->buf->s,thi->buf->s+i,thi->buf->len=len-i);
	}
}
jbl_stream_operators_new(jbl_stream_utf8_to_gb2312_operators,__jbl_string_u8tgso,NULL,NULL,NULL,16,0);
jbl_stream_operators_new(jbl_stream_gb2312_to_utf8_operators,__jbl_string_gtu8so,NULL,NULL,NULL,16,0);
#endif



#endif
