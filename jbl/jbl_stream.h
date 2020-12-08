/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_STREAM_H
#define __JBL_STREAM_H
#include "jbl_stream_config.h"
#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            依赖 jbl_gc jbl_malloc jbl_ying jbl_exception jbl_pthread    */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_gc.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
#include "jbl_pthread.h"
/*******************************************************************************************/
/*                            联动 jbl_var                                                */
/*******************************************************************************************/
#include "jbl_var.h"
/*******************************************************************************************/
/*                            结构体定义                                                  */
/*******************************************************************************************/
typedef struct __jbl_stream jbl_stream;
typedef struct __jbl_stream_buf
{
	jbl_stream_buf_size_type	len;
	jbl_stream_buf_size_type	size;
    jbl_uint8 *                 s;
	void                        (*free_buf)           (struct __jbl_stream_buf*);      //释放buf
}jbl_stream_buf;
typedef union
{
	void const *			p;
	jbl_uint64				u;
	jbl_uint8				c8[8];
}jbl_stream_extra_struct;
typedef struct
{
//所有函数直接响应加锁脱引用op
	void                        (*op)                 (jbl_stream*,jbl_uint8);      //主操作器
	void                        (*free)               (jbl_stream*);                //辅助释放函数
	jbl_stream_buf *            (*provide_buf)        (jbl_stream*);          //提供buf，为null表示不方便提供
	void                        (*free_buf)           (jbl_stream_buf*);      //释放buf
    jbl_stream_buf_size_type    except_buf_size;
    jbl_stream_data_size_type   except_data_size;
}jbl_stream_operater;
typedef struct __jbl_stream
{
	jbl_gc_define               ;
	jbl_var_ops_define			;
	jbl_pthread_lock_define		;
    
	const jbl_stream_operater *	op;
	struct __jbl_stream *		nxt;
    jbl_stream_buf *            buf;
    
	jbl_uint8					stop:1;
	jbl_stream_extra_struct		data[0];
}jbl_stream;
#define			jbl_stream_operators_new(name,op,free,pb,fb,ebs,eds)	\
				const jbl_stream_operater name={	\
					op,								\
					free,				            \
					pb,							    \
					fb,							    \
					ebs,							\
					eds,							\
				}
/*******************************************************************************************/
/*                            全局变量定义                                                */
/*******************************************************************************************/
extern			jbl_stream *						jbl_stream_stdout;
extern			jbl_stream *						jbl_stream_stdin;
extern			jbl_stream *						jbl_stream_stdin_link;
/*******************************************************************************************/
/*                            以下函数完成流处理器组件启动和停止                         */
/*******************************************************************************************/
void			            jbl_stream_start					();                                     //启动stream
void			            jbl_stream_stop						();                                     //关闭stream
/*******************************************************************************************/
/*                            以下函实现流处理器基本操作                                 */
/*******************************************************************************************/
jbl_stream *	            jbl_stream_new						(const jbl_stream_operater *op);        //新建一个流处理器
jbl_stream * 	            jbl_stream_free						(jbl_stream* this);                     //释放一个流处理器
void                        jbl_stream_get_buf                  (jbl_stream *thi);                      //确保一个流处理器的buf存在
jbl_stream_buf *            jbl_stream_free_buf                 (jbl_stream_buf * buf);                 //释放一个流处理器的buf
jbl_stream * 	            jbl_stream_copy						(jbl_stream* this);                     //复制一个流处理器			            jbl_stream_do						(jbl_stream* this,jbl_uint8 flag);      //
void                        jbl_stream_do                       (jbl_stream* this,jbl_uint8 force);     //处理一个流处理器
jbl_stream *	            jbl_stream_connect					(jbl_stream* this,jbl_stream* next);    //连接一个流处理器
jbl_stream *	            jbl_stream_disconnect				(jbl_stream* this);                     //断开一个流处理器
/*******************************************************************************************/
/*                            以下函实现流处理器推入操作                                 */
/*******************************************************************************************/
void			            jbl_stream_push_char				(jbl_stream * this,unsigned char c);                                //向this流推入一个char
void			            jbl_stream_push_chars				(jbl_stream * this,const unsigned char *str);                       //向this流推入一个字符串
void                        jbl_stream_push_chars_length        (jbl_stream * this,const unsigned char *str,jbl_uint64 n);          //向this流推入一个长度为n的字符串
#define			            jbl_stream_push_uint(this,in)		jbl_stream_push_uint_length(this,in,0,0)                            //向this流推入一个64位整数
void			            jbl_stream_push_uint_length			(jbl_stream * this,jbl_uint64 in,jbl_uint8 len,unsigned char c);    //向this流推入一个length位的64位整数，不足用c补齐	
#define			            jbl_stream_push_int(this,in)		jbl_stream_push_int_length(this,in,0,0)                             //向this流推入一个64位无符号整数
void                        jbl_stream_push_int_length          (jbl_stream * this,jbl_int64 in,jbl_uint8 len,unsigned char c);     //向this流推入一个length位64位无符号整数，不足用c补齐
void			            jbl_stream_push_double				(jbl_stream * this,double in);                                      //向this流推入一个浮点数
void			            jbl_stream_push_hex					(jbl_stream * this,jbl_uint64 in);                                  //向this流推入一个16进制形式的64位无符号整数(无前导0)
void			            jbl_stream_push_hex_8bits			(jbl_stream * this,jbl_uint8 in);                                   //向this流推入一个16进制形式的 8位无符号整数(有前导0)
/*******************************************************************************************/
/*                            以下宏实现面向jbl_stream_stdout的快捷操作                  */
/*******************************************************************************************/
#define			            pchars(x)							jbl_stream_push_chars(jbl_stream_stdout,UC(x))
#define			            pint(x)								jbl_stream_push_int(jbl_stream_stdout,(jbl_int64)x)
#define			            puint(x)							jbl_stream_push_uint(jbl_stream_stdout,(jbl_uint64)x)
#define			            pchar(x)							jbl_stream_push_char(jbl_stream_stdout,(unsigned char)x)
#define			            pdouble(x)							jbl_stream_push_double(jbl_stream_stdout,(double)x)
#define			            phex(x)								jbl_stream_push_hex(jbl_stream_stdout,(jbl_uint64)x)
#define			            phex8(x)							jbl_stream_push_hex_8bits(jbl_stream_stdout,(jbl_uint8)x)
#define			            pn()								pchar('\n')
#define			            pt()								pchar('\t')
#define			            pf()								jbl_stream_do(jbl_stream_stdout,true)
#define			            pl()								puint(__LINE__),pchars(" @ "__FILE__),pn(),pf()
#define                     lo()                                jbl_refer_pull_wrlock(jbl_stream_stdout)
#define                     ulo()                               jbl_refer_pull_unwrlock(jbl_stream_stdout)
#define                     li()                                jbl_refer_pull_wrlock(jbl_stream_stdin)
#define                     uli()                               jbl_refer_pull_unwrlock(jbl_stream_stdin)
/*******************************************************************************************/
/*                            以下函实现流处理器格式化操作                               */
/*******************************************************************************************/
char			            jbl_stream_view_put_format			(const void *this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,unsigned char * typename,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * file);         //注意！out只加锁不解锁
#if JBL_JSON_ENABLE==1
//char			            jbl_stream_json_put_format			(const void *this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs);
#endif

#else
#define			jbl_stream_start()
#define			jbl_stream_stop()
#include <stdio.h>
#define			pchars(x)							printf("%s",(x))
#ifdef _WIN32
#define			pint(x)								printf("%I64d",(long long)(x))
#define			puint(x)							printf("%I64d",(unsigned long long)(x))
#elif defined(__APPLE__) || defined(__linux__)
#define			pint(x)								printf("%lld",(long long)(x))
#define			puint(x)							printf("%lld",(unsigned long long)(x))
#endif
#define			pchar(x)							printf("%c",(x))
#define			pdouble(x)							printf("%lf",(x))
#define			phex(x)								printf("%llX",(x))
#define			phex8(x)							printf("%2X",(x))
#define			pn()								pchar('\n')
#define			pt()								pchar('\t')
#define			pf()								printf("%s","")
#define			pl()								puint(__LINE__),pchars(" @ "__FILE__),pn(),pf()


#endif
#endif
