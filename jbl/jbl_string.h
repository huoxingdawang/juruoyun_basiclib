/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_STRING_H
#define __JBL_STRING_H
#include "jbl_string_config.h"
#if JBL_STRING_ENABLE==1
#include "jbl_gc.h"
#include "jbl_ying.h"

typedef struct __jbl_string
{
	jbl_gc 					gc;
	jbl_string_size_type	len;
	jbl_string_size_type	size;
	jbl_string_hash_type 	h;
	unsigned char 			*s;
}jbl_string;
jbl_string_size_type	jbl_strlen								(const char *a);														//获取一个传统char*字符串第一个'\0'所在的位置(即字符串长度)
jbl_string *			jbl_string_new							();																		//新建一个字符串
jbl_string * 			jbl_string_init							(jbl_string *this);														//初始化一个字符串
jbl_string *			jbl_string_free							(jbl_string *this);														//释放一个字符串
#define					jbl_string_extend(a,b)					jbl_string_extend_to((a),(jbl_string_get_length((a))+(b)))				//扩展字符串ab字节
jbl_string *			jbl_string_extend_to					(jbl_string *this,jbl_string_size_type size);							//扩展字符串this到size字节
jbl_string *			jbl_string_clear						(jbl_string *this);														//清空一个字符串
jbl_string *			jbl_string_copy							(jbl_string *that);														//复制一个字符串
jbl_string *			jbl_string_copy_force					(jbl_string *this,const jbl_string *that);								//强制复制一个字符串
jbl_string *			jbl_string_move							(jbl_string *this,jbl_string *that);									//移动一个字符串
jbl_string *			jbl_string_equal						(jbl_string *this,jbl_string *that);									//释放that并复制this

jbl_string_hash_type	jbl_string_hash							(jbl_string *this);														//hash一个字符串
#define					jbl_string_hash_clear(x)				((((jbl_string*)jbl_refer_pull(x))->h=0))								//清楚hash缓存
#define					jbl_string_get_length(a)				(a==NULL?0:((jbl_string*)jbl_refer_pull(a))->len)						//获取一个字符串长度
#define					jbl_string_get_length_force(a)			((a)->len)																//强制获取一个字符串长度，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_set_length(a,l)				(((jbl_string*)jbl_refer_pull(a))->len=l)								//设置一个字符串长度
#define					jbl_string_set_length_force(a,l)		((a)->len=l)															//强制获取一个字符串长度，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_get_chars(a)					(((jbl_string*)jbl_refer_pull(a))->s)									//获取一个字符串的传统字符串部分
#define					jbl_string_get_chars_force(a)			((a)->s)																//强制获取一个字符串的传统字符串部分，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_get_size(a)					(((jbl_string*)jbl_refer_pull(a))->size)								//获取一个字符串大小
#define					jbl_string_get_size_force(a)			((a)->size)																//强制获取一个字符串大小，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_get(a,i)						(((i)<0||(i)>=jbl_string_get_length(a))?0:jbl_string_get_force(((jbl_string*)jbl_refer_pull(a)),i))	//获取字符串a的第i位的内容(当越界时返回0)
#define					jbl_string_get_force(a,i)				((a)->s[(i)])															//强制获取字符串a的第i位的内容，当字符串为NULL或引用类型或越界时将直接导致RE

#define					jbl_string_get_int64(this)				jbl_string_get_int64_start(this,0)										//获取一个64位整数
jbl_int64				jbl_string_get_int64_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个64位整数
#define					jbl_string_get_uint64(this)				jbl_string_get_uint64_start(this,0)										//获取一个64位无符号整数
jbl_uint64				jbl_string_get_uint64_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个64位无符号整数
#define					jbl_string_get_double(this)				jbl_string_get_double_start(this,0)										//获取一个浮点数
double					jbl_string_get_double_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个浮点数
#define					jbl_string_get_hex(this)				jbl_string_get_hex_start(this,0)										//获取一个16进制表示的64位无符号整数
jbl_uint64				jbl_string_get_hex_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个16进制表示的64位无符号整数						
jbl_uint64				jbl_string_get_hex_start_len			(const jbl_string *this,jbl_string_size_type *start,jbl_string_size_type len);	//从start位置开始获取一个16进制表示的,长度为len的64位无符号整数


#define					jbl_string_set(a,i,c)					((i<0?0:(a=jbl_string_extend_to(a,i),jbl_string_set_force(((jbl_string*)jbl_refer_pull(a)),i,c))),a)	//设置字符串a的第i位的内容(当越界时将自动扩容)
#define					jbl_string_set_force(a,i,c)				(((a)->s[(i)]=c))														//强制获取字符串a的第i位的内容，当字符串为NULL或引用类型或越界时将直接导致RE
#define					jbl_string_set_tail0(a)					jbl_string_set(a,jbl_string_get_length(a),0)							//设置字符串末尾0(当越界时将自动扩容)
#define					jbl_string_add_chars(x,y)				jbl_string_add_chars_length(x,y,jbl_strlen((char*)y))					//添加一个char*字符串
jbl_string *			jbl_string_add_chars_length				(jbl_string *this,unsigned char *in,jbl_string_size_type len);			//添加一个长度已知的char*字符串
jbl_string *			jbl_string_add_string					(jbl_string *this,const jbl_string *in);								//添加一个string
jbl_string *			jbl_string_add_char						(jbl_string *this,const char c);										//添加一个char
#define					jbl_string_add_char_force(this,in)		(this->s[this->len++]=(in))												//强制添加一个char，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_add_int64(this,in)			jbl_string_add_int64_length(this,in,0,0)								//添加一个64位整数
jbl_string *			jbl_string_add_int64_length				(jbl_string *this,jbl_int64 in,jbl_uint8 len,char c);					//添加一个length位的64位整数，不足用c补齐	
#define					jbl_string_add_uint64(this,in)			jbl_string_add_uint64_length(this,in,0,0)								//添加一个64位无符号整数
jbl_string *			jbl_string_add_uint64_length			(jbl_string *this,jbl_uint64 in,jbl_uint8 len,char c);					//添加一个length位64位无符号整数，不足用c补齐
#define					jbl_string_add_double(this,in)			jbl_string_add_double_length(this,in,5)									//添加一个浮点数
jbl_string *			jbl_string_add_double_length			(jbl_string *this,double in,unsigned char len);							//添加一个浮点数，保留len位小数
jbl_string *			jbl_string_add_unicode_as_utf8			(jbl_string *this,unsigned long unicode);								//把unicode转换成utf8并添加到字符串末尾
jbl_string *			jbl_string_add_hex						(jbl_string *this,jbl_uint64 in);										//把一个64位无符号整数以16进制形式添加(无前导0)
jbl_string *			jbl_string_add_hex_8bits				(jbl_string *this,jbl_uint8 in);										//把一个 8位无符号整数以16进制形式添加(有前导0)

#include <stdio.h>
jbl_string *			jbl_string_add_file						(jbl_string *this,FILE * file);
void					jbl_string_print						(const jbl_string *this,FILE * file);


#define					jbl_string_delete_1_force(this)			(((this->len)>0?(--(this)->len):(0)))									//强制删除一个字符串的最后一位，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_delete_1(this)				(this=jbl_string_extend_to(this,0),jbl_string_delete_1_force(((jbl_string*)jbl_refer_pull(this))),this)	//删除一个字符串的最后一位

char					jbl_string_space_ship					(const jbl_string *this_,const jbl_string *that_);						//太空船操作符，参见php的太空船操作符
char					jbl_string_space_ship_chars				(const jbl_string *this,const char *that);								//和char*字符串的太空船操作符，参见php的太空船操作符
char					jbl_string_if_equal						(const jbl_string *this_,const jbl_string *that_);						//判断两个字符串是否相等，这里使用了hash进行判断(如果存在)
#define					jbl_string_if_big(x,y)					(jbl_string_space_ship(x,y)>0)											//判断this是否>that
#define					jbl_string_if_small(x,y)				(jbl_string_space_ship(x,y)<0)											//判断this是否<that
#define					jbl_string_if_equal_small(x,y)			(jbl_string_space_ship(x,y)<=0)											//判断this是否>=that
#define					jbl_string_if_equal_big(x,y)			(jbl_string_space_ship(x,y)>=0)											//判断this是否<=that

#define					jbl_string_find_char(this,in)			jbl_string_find_char_start(this,in,0)									//寻找第一个in
jbl_string_size_type	jbl_string_find_char_start				(const jbl_string *this,unsigned char in,jbl_string_size_type start);	//从start位开始寻找第一个in

#if JBL_JSON_ENABLE==1
jbl_string*				jbl_string_json_encode					(const jbl_string* this,jbl_string *out,char format,jbl_int32 tabs);	//JSON编码
jbl_string*				jbl_string_json_put_format				(const void* this,jbl_string *out,char format,jbl_int32 *tabs);			//输出JSON格式头
jbl_string*				jbl_string_json_decode					(jbl_string *this,const jbl_string* in,jbl_string_size_type *start);	//JSON解码
#endif


// #define				jbl_string_from_json(this,in)					jbl_string_from_json_start(this,in,0)
// jbl_string_size_type	jbl_string_from_json_start						(jbl_string *this,const jbl_string *in,jbl_string_size_type start);
// void 				jbl_string_print									(const jbl_string *this,FILE * file);

// void					jbl_string_add_file								(jbl_string *this,FILE * file);
// void					jbl_string_add_file_end_by						(jbl_string *this,FILE * file,unsigned char end);
// #define				jbl_string_equal_file(this,file)					jbl_string_clear(this),jbl_string_add_file(this,file)
// #define				jbl_string_equal_file_end_by(this,file,end)		jbl_string_clear(this),jbl_string_add_file_end_by(this,file,end)

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void					jbl_string_view_put						(const jbl_string* this,jbl_stream *out,jbl_int32 format,char*str,jbl_int32 tabs);	//从out浏览一个字符串
#define					jbl_string_view(x)							jbl_string_view_put(x,jbl_stream_stdout,__LINE__,#x " @ "__FILE__,jbl_view_default_tabs_num),jbl_stream_push_char(jbl_stream_stdout,'\n')	//浏览一个字符串
void					jbl_stream_push_string					(jbl_stream *out,const jbl_string* this);
#if JBL_JSON_ENABLE==1
void					jbl_string_json_put						(const jbl_string* this,jbl_stream *out,char format,jbl_int32 tabs);	//从从out JSON格式化一个字符串
#endif

extern const 			jbl_stream_operater						jbl_stream_string_operators;											//string的流处理器
jbl_stream *			jbl_string_stream_new					(jbl_string *str);														//新建一个字符串流(不进行复制操作)
#define					jbl_string_stream_free(a)				jbl_stream_free(a)														//释放一个字符串流
#if JBL_VAR_ENABLE==1
jbl_var * 				jbl_string_Vstream_new					(jbl_string *str);														//新建一个var格式的字符串流(不进行复制操作)
#endif
#endif

#if JBL_VAR_ENABLE==1
typedef	struct		__jbl_var_operators							jbl_var_operators;
typedef	struct		__jbl_var 									jbl_var;
extern	const		jbl_var_operators							jbl_string_operators;													//string 操作器
jbl_string *		jbl_Vstring									(jbl_var * this);														//以string的格式使用var
#define				Vis_jbl_string(x)							(jbl_var_get_operators(x)==&jbl_string_operators)						//判断一个var是不是string
jbl_var *			jbl_Vstring_new								();																		//新建一个字符串类型的var
jbl_var *			jbl_string_get_number_start					(const jbl_string *this,jbl_string_size_type *start);					//获取一个数字，支持无符号整数，有符号整数，浮点数，e表示的浮点数

#define				jbl_var_copy_from_string(x)					((jbl_var*)jbl_string_copy_force(jbl_Vstring(jbl_Vstring_new()),x))
#define				jbl_string_copy_from_var(x)					jbl_string_copy_force(NULL,jbl_Vstring(x))

#define				jbl_var_move_from_string(x)					((jbl_var*)jbl_string_move(jbl_Vstring(jbl_Vstring_new()),x))

#endif

#if JBL_LL_ENABLE==1
typedef	struct		__jbl_ll									jbl_ll;
jbl_ll*				jbl_string_cut_start						(jbl_string *this,jbl_ll *list,char cut,jbl_string_size_type start);	//从start开始用cut切割一个字符串
#define				jbl_string_cut(x,y,z)						jbl_string_cut_start(x,y,z,0)											//用cut切割一个字符串
#endif

#endif	
#endif
