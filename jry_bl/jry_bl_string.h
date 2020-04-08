/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_STRING_H
#define __JRY_BL_STRING_H
#include "jry_bl_string_config.h"
#if JRY_BL_STRING_ENABLE==1
#include "jry_bl_gc.h"
#include "jry_bl_ying.h"

typedef struct __jry_bl_string
{
	jry_bl_gc gc;
	jry_bl_string_size_type	len;
	jry_bl_string_size_type	size;
	unsigned char *s;
	jry_bl_uint32 h;
}jry_bl_string;
jry_bl_string_size_type	jry_bl_strlen										(char *a);																	//获取一个传统char*字符串第一个'\0'所在的位置(即字符串长度)
jry_bl_string *			jry_bl_string_new									();																			//新建一个字符串
jry_bl_string *			jry_bl_string_free									(jry_bl_string *this);														//释放一个字符串
#define					jry_bl_string_extend(a,b)							jry_bl_string_extend_to((a),(jry_bl_string_get_length((a))+(b)))			//扩展字符串ab字节
jry_bl_string *			jry_bl_string_extend_to								(jry_bl_string *this,jry_bl_string_size_type size);							//扩展字符串this到size字节
jry_bl_string *			jry_bl_string_clear									(jry_bl_string *this);														//清空一个字符串
jry_bl_string *			jry_bl_string_copy									(jry_bl_string *that);														//复制一个字符串
jry_bl_string *			jry_bl_string_rcopy									(jry_bl_string *that);														//复制一个字符串(将脱去refer复制)
jry_bl_string *			jry_bl_string_equal									(jry_bl_string *this,jry_bl_string *that);									//释放that并复制this

jry_bl_uint32			jry_bl_string_hash									(jry_bl_string *this);														//hash一个字符串
#define					jry_bl_string_get_length(a)							(a==NULL?0:((jry_bl_string*)jry_bl_refer_pull(a))->len)						//获取一个字符串长度
#define					jry_bl_string_get_length_force(a)					((a)->len)																	//强制获取一个字符串长度，当字符串为NULL或引用类型时将直接导致RE
#define					jry_bl_string_set_length(a,l)						(((jry_bl_string*)jry_bl_refer_pull(a))->len=l)								//设置一个字符串长度
#define					jry_bl_string_set_length_force(a,l)					((a)->len=l)																//强制获取一个字符串长度，当字符串为NULL或引用类型时将直接导致RE
#define					jry_bl_string_get_chars(a)							(((jry_bl_string*)jry_bl_refer_pull(a))->s)									//获取一个字符串的传统字符串部分
#define					jry_bl_string_get_chars_force(a)					((a)->s)																	//强制获取一个字符串的传统字符串部分，当字符串为NULL或引用类型时将直接导致RE
#define					jry_bl_string_get_size(a) 							(((jry_bl_string*)jry_bl_refer_pull(a))->size)								//获取一个字符串大小
#define					jry_bl_string_get_size_force(a) 					((a)->size)																	//强制获取一个字符串大小，当字符串为NULL或引用类型时将直接导致RE
#define					jry_bl_string_get(a,i)								(((i)<0||(i)>=jry_bl_string_get_length(a))?0:jry_bl_string_get_force(((jry_bl_string*)jry_bl_refer_pull(a)),i))	//获取字符串a的第i位的内容(当越界时返回0)
#define					jry_bl_string_get_force(a,i)						((a)->s[(i)])																//强制获取字符串a的第i位的内容，当字符串为NULL或引用类型或越界时将直接导致RE

#define					jry_bl_string_get_int64(this)						jry_bl_string_get_int64_start_v(this,0)										//获取一个64位整数
jry_bl_int64			jry_bl_string_get_int64_start						(const jry_bl_string *this,jry_bl_string_size_type *start);					//从start位置开始获取一个64位整数
jry_bl_int64			jry_bl_string_get_int64_start_v						(const jry_bl_string *this,jry_bl_string_size_type start);					//从start位置开始获取一个64位整数
#define					jry_bl_string_get_uint64(this)						jry_bl_string_get_uint64_start_v(this,0)									//获取一个64位无符号整数
jry_bl_uint64			jry_bl_string_get_uint64_start						(const jry_bl_string *this,jry_bl_string_size_type *start);					//从start位置开始获取一个64位无符号整数
jry_bl_uint64			jry_bl_string_get_uint64_start_v					(const jry_bl_string *this,jry_bl_string_size_type start);					//从start位置开始获取一个64位无符号整数
#define					jry_bl_string_get_double(this)						jry_bl_string_get_double_start_v(this,0)									//获取一个浮点数
double					jry_bl_string_get_double_start						(const jry_bl_string *this,jry_bl_string_size_type *start);					//从start位置开始获取一个浮点数
double					jry_bl_string_get_double_start_v					(const jry_bl_string *this,jry_bl_string_size_type start);					//从start位置开始获取一个浮点数
#define					jry_bl_string_get_hex(this)							jry_bl_string_get_hex_start_v(this,0)										//获取一个16进制表示的64位无符号整数
jry_bl_uint64			jry_bl_string_get_hex_start							(const jry_bl_string *this,jry_bl_string_size_type *start);					//从start位置开始获取一个16进制表示的64位无符号整数						
jry_bl_uint64			jry_bl_string_get_hex_start_v						(const jry_bl_string *this,jry_bl_string_size_type start);					//从start位置开始获取一个16进制表示的64位无符号整数


#define					jry_bl_string_set(a,i,c)							((i<0?0:(a=jry_bl_string_extend_to(a,i),jry_bl_string_set_force(((jry_bl_string*)jry_bl_refer_pull(a)),i,c))),a)//设置字符串a的第i位的内容(当越界时将自动扩容)
#define					jry_bl_string_set_force(a,i,c)						(((a)->s[(i)]=c))															//强制获取字符串a的第i位的内容，当字符串为NULL或引用类型或越界时将直接导致RE
#define					jry_bl_string_set_tail0(a)							jry_bl_string_set(a,jry_bl_string_get_length(a),0)							//设置字符串末尾0(当越界时将自动扩容)
#define					jry_bl_string_add_chars(x,y)						jry_bl_string_add_chars_length(x,y,jry_bl_strlen(y))						//添加一个char*字符串
jry_bl_string *			jry_bl_string_add_chars_length						(jry_bl_string *this,unsigned char *in,jry_bl_string_size_type len);		//添加一个长度已知的char*字符串
jry_bl_string *			jry_bl_string_add_string							(jry_bl_string *this,const jry_bl_string *in);								//添加一个string
jry_bl_string *			jry_bl_string_add_char								(jry_bl_string *this,const char c);											//添加一个char
#define					jry_bl_string_add_char_force(this,in)				(this->s[this->len++]=(in))													//强制添加一个char，当字符串为NULL或引用类型时将直接导致RE
#define					jry_bl_string_add_int64(this,in)					jry_bl_string_add_int64_length(this,in,0,0)									//添加一个64位整数
jry_bl_string *			jry_bl_string_add_int64_length						(jry_bl_string *this,jry_bl_int64 in,jry_bl_uint8 len,char c);				//添加一个length位的64位整数，不足用c补齐	
#define					jry_bl_string_add_uint64(this,in)					jry_bl_string_add_uint64_length(this,in,0,0)								//添加一个64位无符号整数
jry_bl_string *			jry_bl_string_add_uint64_length						(jry_bl_string *this,jry_bl_uint64 in,jry_bl_uint8 len,char c);				//添加一个length位64位无符号整数，不足用c补齐
#define					jry_bl_string_add_double(this,in)					jry_bl_string_add_double_length(this,in,10)									//添加一个浮点数
jry_bl_string *			jry_bl_string_add_double_length						(jry_bl_string *this,double in,unsigned char len);							//添加一个浮点数，保留len位小数
jry_bl_string *			jry_bl_string_add_unicode_as_utf8					(jry_bl_string *this,unsigned long unicode);								//把unicode转换成utf8并添加到字符串末尾
jry_bl_string *			jry_bl_string_add_hex								(jry_bl_string *this,jry_bl_uint64 in);										//把一个64位无符号整数以16进制形式添加(无前导0)
jry_bl_string *			jry_bl_string_add_hex_8bits							(jry_bl_string *this,jry_bl_uint8 in);										//把一个 8位无符号整数以16进制形式添加(有前导0)
#define					jry_bl_string_delete_1_force(this)					(((this->len)>0?(--(this)->len):(0)))										//强制删除一个字符串的最后一位，当字符串为NULL或引用类型时将直接导致RE
#define					jry_bl_string_delete_1(this)						(this=jry_bl_string_extend_to(this,0),jry_bl_string_delete_1_force(((jry_bl_string*)jry_bl_refer_pull(this))),this)//删除一个字符串的最后一位

char					jry_bl_string_space_ship							(const jry_bl_string *this,const jry_bl_string *that);						//太空船操作符，参见php的太空船操作符
#define					jry_bl_string_if_big(x,y)							(jry_bl_string_space_ship(x,y)>0)
#define					jry_bl_string_if_equal(x,y)							(jry_bl_string_space_ship(x,y)==0)
#define					jry_bl_string_if_small(x,y) 						(jry_bl_string_space_ship(x,y)<0)
#define					jry_bl_string_if_equal_small(x,y)					(jry_bl_string_space_ship(x,y)<=0)
#define					jry_bl_string_if_equal_big(x,y) 					(jry_bl_string_space_ship(x,y)>=0)

#define					jry_bl_string_find_char(this,in)					jry_bl_string_find_char_start(this,in,0)									//寻找第一个in
jry_bl_string_size_type	jry_bl_string_find_char_start						(const jry_bl_string *this,unsigned char in,jry_bl_string_size_type start);	//从start位开始寻找第一个in




// #define					jry_bl_string_from_json(this,in)					jry_bl_string_from_json_start(this,in,0)
// jry_bl_string_size_type	jry_bl_string_from_json_start						(jry_bl_string *this,const jry_bl_string *in,jry_bl_string_size_type start);
// void 					jry_bl_string_print									(const jry_bl_string *this,FILE * file);

// void					jry_bl_string_add_file								(jry_bl_string *this,FILE * file);
// void					jry_bl_string_add_file_end_by						(jry_bl_string *this,FILE * file,unsigned char end);
// #define					jry_bl_string_equal_file(this,file)					jry_bl_string_clear(this),jry_bl_string_add_file(this,file)
// #define					jry_bl_string_equal_file_end_by(this,file,end)		jry_bl_string_clear(this),jry_bl_string_add_file_end_by(this,file,end)

// #if JRY_BL_VAR_ENABLE==1
// typedef struct __jry_bl_var jry_bl_var;
// #define 				jry_bl_var_get_string(this)							((jry_bl_string*)(this)->data.p)
// void					jry_bl_var_equal_string								(jry_bl_var *this,jry_bl_string *that,jry_bl_uint8 copytype);
// void					jry_bl_var_equal_string_pointer						(jry_bl_var *this,jry_bl_string *that);
// void					jry_bl_string_add_var								(jry_bl_string *this,jry_bl_var *that);
// void					jry_bl_string_equal_var								(jry_bl_string *this,jry_bl_var *that,jry_bl_uint8 cpt);
// #endif
#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_stream.h"
void					jry_bl_string_put									(const jry_bl_string* this,jry_bl_stream *output_stream,jry_bl_put_type type,jry_bl_uint32 format,char*str);//format bit0 表示是否格式化 [1,16]位表示另一个整数 [17,31]位表示格式化tab个数
#define					jry_bl_string_view(x) 								jry_bl_string_put(x,jry_bl_stream_stdout,view,(jry_bl_view_default_tabs_num<<16)|(__LINE__<<1)|1,#x " @ "__FILE__),jry_bl_stream_push_char(jry_bl_stream_stdout,'\n'),jry_bl_stream_do(jry_bl_stream_stdout,1)
void					jry_bl_string_to_json								(const jry_bl_string *this,jry_bl_string *result);

extern	const jry_bl_stream_operater jry_bl_stream_string_operators;
jry_bl_stream *			jry_bl_string_stream_new							(jry_bl_string *str);

#define					jry_bl_string_stream_reset(a)						jry_bl_stream_reset(a),(a)->buf=((jry_bl_string *)(a)->data)->s+((jry_bl_string *)(a)->data)->len,(a)->size=((jry_bl_string *)(a)->data)->size-((jry_bl_string *)(a)->data)->len
#define					jry_bl_string_stream_free(a)						jry_bl_stream_free(a)
#endif
// #if JRY_BL_LINK_LIST_ENABLE==1
// typedef struct __jry_bl_link_list jry_bl_link_list;
// jry_bl_string_size_type	jry_bl_string_cut_start								(jry_bl_string *this,jry_bl_link_list *list,char cut,jry_bl_string_size_type start);
// #define					jry_bl_string_cut(x,y,z)							jry_bl_string_cut_start(x,y,z,0)
// #endif

#endif	
#endif
