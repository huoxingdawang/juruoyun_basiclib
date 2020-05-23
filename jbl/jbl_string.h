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
jbl_string_size_type	jbl_strlen								(char *a);																//获取一个传统char*字符串第一个'\0'所在的位置(即字符串长度)
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
#define					jbl_string_get_size(a) 					(((jbl_string*)jbl_refer_pull(a))->size)								//获取一个字符串大小
#define					jbl_string_get_size_force(a) 			((a)->size)																//强制获取一个字符串大小，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_get(a,i)						(((i)<0||(i)>=jbl_string_get_length(a))?0:jbl_string_get_force(((jbl_string*)jbl_refer_pull(a)),i))	//获取字符串a的第i位的内容(当越界时返回0)
#define					jbl_string_get_force(a,i)				((a)->s[(i)])															//强制获取字符串a的第i位的内容，当字符串为NULL或引用类型或越界时将直接导致RE

#define					jbl_string_get_int64(this)				jbl_string_get_int64_start_v(this,0)									//获取一个64位整数
jbl_int64				jbl_string_get_int64_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个64位整数
jbl_int64				jbl_string_get_int64_start_v			(const jbl_string *this,jbl_string_size_type start);					//从start位置开始获取一个64位整数
#define					jbl_string_get_uint64(this)				jbl_string_get_uint64_start_v(this,0)									//获取一个64位无符号整数
jbl_uint64				jbl_string_get_uint64_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个64位无符号整数
jbl_uint64				jbl_string_get_uint64_start_v			(const jbl_string *this,jbl_string_size_type start);					//从start位置开始获取一个64位无符号整数
#define					jbl_string_get_double(this)				jbl_string_get_double_start_v(this,0)									//获取一个浮点数
double					jbl_string_get_double_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个浮点数
double					jbl_string_get_double_start_v			(const jbl_string *this,jbl_string_size_type start);					//从start位置开始获取一个浮点数
#define					jbl_string_get_hex(this)				jbl_string_get_hex_start_v(this,0)										//获取一个16进制表示的64位无符号整数
jbl_uint64				jbl_string_get_hex_start				(const jbl_string *this,jbl_string_size_type *start);					//从start位置开始获取一个16进制表示的64位无符号整数						
jbl_uint64				jbl_string_get_hex_start_v				(const jbl_string *this,jbl_string_size_type start);					//从start位置开始获取一个16进制表示的64位无符号整数


#define					jbl_string_set(a,i,c)					((i<0?0:(a=jbl_string_extend_to(a,i),jbl_string_set_force(((jbl_string*)jbl_refer_pull(a)),i,c))),a)//设置字符串a的第i位的内容(当越界时将自动扩容)
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
#define					jbl_string_add_double(this,in)			jbl_string_add_double_length(this,in,10)								//添加一个浮点数
jbl_string *			jbl_string_add_double_length			(jbl_string *this,double in,unsigned char len);							//添加一个浮点数，保留len位小数
jbl_string *			jbl_string_add_unicode_as_utf8			(jbl_string *this,unsigned long unicode);								//把unicode转换成utf8并添加到字符串末尾
jbl_string *			jbl_string_add_hex						(jbl_string *this,jbl_uint64 in);										//把一个64位无符号整数以16进制形式添加(无前导0)
jbl_string *			jbl_string_add_hex_8bits				(jbl_string *this,jbl_uint8 in);										//把一个 8位无符号整数以16进制形式添加(有前导0)
#define					jbl_string_delete_1_force(this)			(((this->len)>0?(--(this)->len):(0)))									//强制删除一个字符串的最后一位，当字符串为NULL或引用类型时将直接导致RE
#define					jbl_string_delete_1(this)				(this=jbl_string_extend_to(this,0),jbl_string_delete_1_force(((jbl_string*)jbl_refer_pull(this))),this)//删除一个字符串的最后一位

char					jbl_string_space_ship					(const jbl_string *this_,const jbl_string *that_);						//太空船操作符，参见php的太空船操作符
char					jbl_string_if_equal						(const jbl_string *this_,const jbl_string *that_);						//判断两个字符串是否相等，这里使用了hash进行判断(如果存在)
#define					jbl_string_if_big(x,y)					(jbl_string_space_ship(x,y)>0)											//判断this是否>that
#define					jbl_string_if_small(x,y) 				(jbl_string_space_ship(x,y)<0)											//判断this是否<that
#define					jbl_string_if_equal_small(x,y)			(jbl_string_space_ship(x,y)<=0)											//判断this是否>=that
#define					jbl_string_if_equal_big(x,y) 			(jbl_string_space_ship(x,y)>=0)											//判断this是否<=that

#define					jbl_string_find_char(this,in)			jbl_string_find_char_start(this,in,0)									//寻找第一个in
jbl_string_size_type	jbl_string_find_char_start				(const jbl_string *this,unsigned char in,jbl_string_size_type start);	//从start位开始寻找第一个in
jbl_string*				jbl_string_json_encode					(const jbl_string* this,jbl_string *out,char format,jbl_int32 tabs);	//JSON编码



// #define				jbl_string_from_json(this,in)					jbl_string_from_json_start(this,in,0)
// jbl_string_size_type	jbl_string_from_json_start						(jbl_string *this,const jbl_string *in,jbl_string_size_type start);
// void 				jbl_string_print									(const jbl_string *this,FILE * file);

// void					jbl_string_add_file								(jbl_string *this,FILE * file);
// void					jbl_string_add_file_end_by						(jbl_string *this,FILE * file,unsigned char end);
// #define				jbl_string_equal_file(this,file)					jbl_string_clear(this),jbl_string_add_file(this,file)
// #define				jbl_string_equal_file_end_by(this,file,end)		jbl_string_clear(this),jbl_string_add_file_end_by(this,file,end)

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void					jbl_string_view_put						(const jbl_string* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs);//从output_stream浏览一个字符串
#define					jbl_string_view(x) 						jbl_string_view_put(x,jbl_stream_stdout,__LINE__,#x " @ "__FILE__,jbl_view_default_tabs_num),jbl_stream_push_char(jbl_stream_stdout,'\n')//浏览一个字符串
void					jbl_string_json_put						(const jbl_string* this,jbl_stream *output_stream,char format,jbl_int32 tabs);//从从output_stream JSON格式化一个字符串

extern const 			jbl_stream_operater 					jbl_stream_string_operators;											//string的流处理器
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
#define				$jbl_string(x)								((jbl_string*)x)														//以string德格式使用var
jbl_var *			jbl_Vstring_new								();																		//新建一个字符串类型的var
#define				jbl_var_copy_from_string(x)					((jbl_var*)jbl_string_copy_force($jbl_string(jbl_Vstring_new()),x))
#define				jbl_string_copy_from_var(x)					jbl_string_copy_force(NULL,$jbl_string(x))

#define				jbl_var_move_from_string(x)					((jbl_var*)jbl_string_move($jbl_string(jbl_Vstring_new()),x))
#define				jbl_string_move_from_var(x)					jbl_string_move(NULL,$jbl_string(x))


// #define			jbl_Vstring_extend(a,b)							jbl_Vstring_extend_to((a),(jbl_Vstring_get_length((a))+(b)))			//扩展字符串ab字节
// #define			jbl_Vstring_extend_to(this,size);							//扩展字符串this到size字节
// #define			jbl_Vstring_clear									(#define		this);														//清空一个字符串
// #define			jbl_Vstring_copy									(#define		that);														//复制一个字符串
// #define			jbl_Vstring_rcopy									(#define		that);														//复制一个字符串(将脱去refer复制)
// #define			jbl_Vstring_equal									(#define		this,#define		that);									//释放that并复制this

#define				jbl_Vstring_hash(this)							jbl_string_hash($jbl_string(this))														//hash一个字符串
// #define			jbl_Vstring_get_length(a)							(a==NULL?0:((jbl_string*)jbl_refer_pull(a))->len)						//获取一个字符串长度
// #define			jbl_Vstring_get_length_force(a)					((a)->len)																	//强制获取一个字符串长度，当字符串为NULL或引用类型时将直接导致RE
// #define			jbl_Vstring_set_length(a,l)						(((jbl_string*)jbl_refer_pull(a))->len=l)								//设置一个字符串长度
// #define			jbl_Vstring_set_length_force(a,l)					((a)->len=l)																//强制获取一个字符串长度，当字符串为NULL或引用类型时将直接导致RE
// #define			jbl_Vstring_get_chars(a)							(((jbl_string*)jbl_refer_pull(a))->s)									//获取一个字符串的传统字符串部分
// #define			jbl_Vstring_get_chars_force(a)					((a)->s)																	//强制获取一个字符串的传统字符串部分，当字符串为NULL或引用类型时将直接导致RE
// #define			jbl_Vstring_get_size(a) 							(((jbl_string*)jbl_refer_pull(a))->size)								//获取一个字符串大小
// #define			jbl_Vstring_get_size_force(a) 					((a)->size)																	//强制获取一个字符串大小，当字符串为NULL或引用类型时将直接导致RE
// #define			jbl_Vstring_get(a,i)								(((i)<0||(i)>=jbl_Vstring_get_length(a))?0:jbl_Vstring_get_force(((jbl_string*)jbl_refer_pull(a)),i))	//获取字符串a的第i位的内容(当越界时返回0)
// #define			jbl_Vstring_get_force(a,i)						((a)->s[(i)])																//强制获取字符串a的第i位的内容，当字符串为NULL或引用类型或越界时将直接导致RE

// #define			jbl_Vstring_get_int64(this)						jbl_Vstring_get_int64_start_v(this,0)										//获取一个64位整数
// jbl_int64	jbl_Vstring_get_int64_start						(const #define		this,jbl_Vstring_size_type *start);					//从start位置开始获取一个64位整数
// jbl_int64	jbl_Vstring_get_int64_start_v						(const #define		this,jbl_Vstring_size_type start);					//从start位置开始获取一个64位整数
// #define			jbl_Vstring_get_uint64(this)						jbl_Vstring_get_uint64_start_v(this,0)									//获取一个64位无符号整数
// jbl_uint64	jbl_Vstring_get_uint64_start						(const #define		this,jbl_Vstring_size_type *start);					//从start位置开始获取一个64位无符号整数
// jbl_uint64	jbl_Vstring_get_uint64_start_v					(const #define		this,jbl_Vstring_size_type start);					//从start位置开始获取一个64位无符号整数
// #define			jbl_Vstring_get_double(this)						jbl_Vstring_get_double_start_v(this,0)									//获取一个浮点数
// double			jbl_Vstring_get_double_start						(const #define		this,jbl_Vstring_size_type *start);					//从start位置开始获取一个浮点数
// double			jbl_Vstring_get_double_start_v					(const #define		this,jbl_Vstring_size_type start);					//从start位置开始获取一个浮点数
// #define			jbl_Vstring_get_hex(this)							jbl_Vstring_get_hex_start_v(this,0)										//获取一个16进制表示的64位无符号整数
// jbl_uint64	jbl_Vstring_get_hex_start							(const #define		this,jbl_Vstring_size_type *start);					//从start位置开始获取一个16进制表示的64位无符号整数						
// jbl_uint64	jbl_Vstring_get_hex_start_v						(const #define		this,jbl_Vstring_size_type start);					//从start位置开始获取一个16进制表示的64位无符号整数


// #define			jbl_Vstring_set(a,i,c)							((i<0?0:(a=jbl_Vstring_extend_to(a,i),jbl_Vstring_set_force(((jbl_string*)jbl_refer_pull(a)),i,c))),a)//设置字符串a的第i位的内容(当越界时将自动扩容)
// #define			jbl_Vstring_set_force(a,i,c)						(((a)->s[(i)]=c))															//强制获取字符串a的第i位的内容，当字符串为NULL或引用类型或越界时将直接导致RE
// #define			jbl_Vstring_set_tail0(a)							jbl_Vstring_set(a,jbl_Vstring_get_length(a),0)							//设置字符串末尾0(当越界时将自动扩容)
#define			jbl_Vstring_add_chars(x,y)							jbl_Vstring_add_chars_length(x,y,jbl_strlen(y))						//添加一个char*字符串
#define			jbl_Vstring_add_chars_length(this,in,len)			((jbl_var*)jbl_string_add_chars_length($jbl_string(this),in,len))
#define			jbl_string_add_vstring(x,y)							jbl_string_add_string(x,$jbl_string(y))
#define			jbl_Vstring_add_string(x,y)							((jbl_var*)jbl_string_add_string($jbl_string(x),y))
#define			jbl_Vstring_add_vstring(x,y)							((jbl_var*)jbl_string_add_string($jbl_string(x),$jbl_string(y)))

// #define			jbl_Vstring_add_char								(#define		this,const char c);											//添加一个char
// #define			jbl_Vstring_add_char_force(this,in)				(this->s[this->len++]=(in))													//强制添加一个char，当字符串为NULL或引用类型时将直接导致RE
// #define			jbl_Vstring_add_int64(this,in)					jbl_Vstring_add_int64_length(this,in,0,0)									//添加一个64位整数
// #define			jbl_Vstring_add_int64_length						(#define		this,jbl_int64 in,jbl_uint8 len,char c);				//添加一个length位的64位整数，不足用c补齐	
// #define			jbl_Vstring_add_uint64(this,in)					jbl_Vstring_add_uint64_length(this,in,0,0)								//添加一个64位无符号整数
// #define			jbl_Vstring_add_uint64_length						(#define		this,jbl_uint64 in,jbl_uint8 len,char c);				//添加一个length位64位无符号整数，不足用c补齐
// #define			jbl_Vstring_add_double(this,in)					jbl_Vstring_add_double_length(this,in,10)									//添加一个浮点数
// #define			jbl_Vstring_add_double_length						(#define		this,double in,unsigned char len);							//添加一个浮点数，保留len位小数
// #define			jbl_Vstring_add_unicode_as_utf8					(#define		this,unsigned long unicode);								//把unicode转换成utf8并添加到字符串末尾
// #define			jbl_Vstring_add_hex								(#define		this,jbl_uint64 in);										//把一个64位无符号整数以16进制形式添加(无前导0)
// #define			jbl_Vstring_add_hex_8bits							(#define		this,jbl_uint8 in);										//把一个 8位无符号整数以16进制形式添加(有前导0)
// #define			jbl_Vstring_delete_1_force(this)					(((this->len)>0?(--(this)->len):(0)))										//强制删除一个字符串的最后一位，当字符串为NULL或引用类型时将直接导致RE
// #define			jbl_Vstring_delete_1(this)						(this=jbl_Vstring_extend_to(this,0),jbl_Vstring_delete_1_force(((jbl_string*)jbl_refer_pull(this))),this)//删除一个字符串的最后一位

// char			jbl_Vstring_space_ship							(const #define		this,const #define		that);						//太空船操作符，参见php的太空船操作符
// #define			jbl_Vstring_if_big(x,y)							(jbl_Vstring_space_ship(x,y)>0)
// #define			jbl_Vstring_if_equal(x,y)							(jbl_Vstring_space_ship(x,y)==0)
// #define			jbl_Vstring_if_small(x,y) 						(jbl_Vstring_space_ship(x,y)<0)
// #define			jbl_Vstring_if_equal_small(x,y)					(jbl_Vstring_space_ship(x,y)<=0)
// #define			jbl_Vstring_if_equal_big(x,y) 					(jbl_Vstring_space_ship(x,y)>=0)
// #define					jbl_Vstring_find_char(this,in)					jbl_Vstring_find_char_start(this,in,0)									//寻找第一个in
// y_bl_vstring_size_type	jbl_Vstring_find_char_start						(const #define		this,unsigned char in,jbl_Vstring_size_type start);	//从start位开始寻找第一个in


#endif

#if JBL_LL_ENABLE==1
typedef	struct		__jbl_ll 									jbl_ll;
jbl_ll*				jbl_string_cut_start						(jbl_string *this,jbl_ll *list,char cut,jbl_string_size_type start);
#define				jbl_string_cut(x,y,z)						jbl_string_cut_start(x,y,z,0)
#endif

#endif	
#endif
