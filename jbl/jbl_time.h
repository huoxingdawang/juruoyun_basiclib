/* Copyrigtime (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      timetp://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_TIME_H
#define __JBL_TIME_H
#include "jbl_time_config.h"
#if JBL_TIME_ENABLE==1
#include "jbl_gc.h"

#define JBL_TIME_ZONE_ASIA_SHANGHAI 1

extern jbl_int8 jbl_time_time_zone;
typedef struct __jbl_time
{
	jbl_gc gc;
	jbl_uint64 t;
}jbl_time;
typedef struct __jbl_time_decoded
{
	int year,month,day,hour,minute,second,ms;
}jbl_time_decoded;
jbl_time *			jbl_time_new					();																		//新建一个时间
jbl_time *			jbl_time_init					(jbl_time *this);														//初始化一个时间
jbl_time *			jbl_time_free					(jbl_time *this);														//释放一个时间
jbl_time *			jbl_time_set					(jbl_time *that,jbl_uint64 time);										//设置一个unix时间戳
jbl_time *			jbl_time_copy					(jbl_time *that);														//复制一个时间
jbl_time *			jbl_time_now					(jbl_time *this);														//把this设置为当前时间
#define				jbl_time_minus(x,y)				(jbl_time_to_unix(x)-jbl_time_to_unix(y))								//计算两个时间的差
char				jbl_time_space_ship				(jbl_time *this,jbl_time *that);										//比较两个时间
#define				jbl_time_if_equal(x,y)			(jbl_time_space_ship(x,y)==0)											//判断this是否=that
#define				jbl_time_if_big(x,y)			(jbl_time_space_ship(x,y)>0)											//判断this是否>that
#define				jbl_time_if_small(x,y)			(jbl_time_space_ship(x,y)<0)											//判断this是否<that
#define				jbl_time_if_equal_small(x,y)	(jbl_time_space_ship(x,y)<=0)											//判断this是否>=that
#define				jbl_time_if_equal_big(x,y)		(jbl_time_space_ship(x,y)>=0)											//判断this是否<=that

jbl_uint8			jbl_time_if_leap_year			(jbl_uint32 year);														//判断year是不是闰年
jbl_uint8			jbl_time_get_day_of_month		(jbl_uint8 month,jbl_uint32 year);										//获取一个月份的天数
jbl_uint8			jbl_time_get_weekday			(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year);						//获取今天是周几
jbl_uint8			jbl_time_if_dst					(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year);						//判断夏令时
#define				jbl_time_to_unix(x)				(((jbl_time *)(jbl_refer_pull(x)))->t)									//转换为unix实践出
void				jbl_time_decode					(const jbl_time *this,jbl_time_decoded *tt);							//格式化一个时间戳


#if JBL_STRING_ENABLE==1
typedef	struct		__jbl_string					jbl_string;
jbl_string *		jbl_time_to_string				(const jbl_time *this,jbl_string *result);								//把time格式化成字符串时间戳
#if JBL_JSON_ENABLE==1
jbl_string *		jbl_time_json_encode			(const jbl_time* this,jbl_string *out,char format,jbl_int32 tabs);		//把time格式化成JSON
#endif

#if JBL_VAR_ENABLE==1
#define				jbl_Vtime_to_string(x,y)		(jbl_time_to_string(jbl_Vtime(x),y))	
#endif

#endif
#if JBL_VAR_ENABLE==1
typedef	struct		__jbl_var_operators				jbl_var_operators;
typedef	struct		__jbl_var						jbl_var;
extern	const		jbl_var_operators				jbl_time_operators;															//time 操作器
jbl_time  *			jbl_Vtime						(jbl_var * this);															//以time的格式使用var
#define				Vis_jbl_time(x)					(jbl_var_get_operators(x)==&jbl_time_operators)								//判断一个var是不是time 

jbl_var *			jbl_Vtime_new					();																			//新建一个time类型的var

#endif




#endif
#endif
