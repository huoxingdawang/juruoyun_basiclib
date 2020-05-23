/* Copyright (c) [2019] juruoyun developer team
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
#include "jbl_ying.h"
#include "jbl_malloc.h"
#include "jbl_gc.h"
#include "jbl_exception.h"
typedef struct __jbl_stream_operater jbl_stream_operater;
typedef struct __jbl_stream
{
	jbl_gc gc;						//注意，这个虽然有gc但是仍然是强制拷贝，使用gc是为了支持引用
	const jbl_stream_operater *op;
	struct __jbl_stream *nxt;
	jbl_uint16	en;
	jbl_uint16	size;
	void		*data;
	union
	{
		void const*	tmpp;
		jbl_uint64 tmpv;
	};
	unsigned char	*buf;
}jbl_stream;

typedef struct __jbl_stream_operater
{
	void  (*op)(jbl_stream*,jbl_uint8);
	void  (*free)(void*);
	void* (*scp)(void*);//stream copy
	void  (*usb)(jbl_stream*);// update stream buf
}jbl_stream_operater;
typedef enum
{
	json,
	view
}jbl_put_type;
jbl_stream *	jbl_stream_new						(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmpv,const void* tmpp);
jbl_stream * 	jbl_stream_init						(jbl_stream *this,const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmpv,const void* tmpp);
jbl_stream * 	jbl_stream_copy						(jbl_stream* this);
jbl_stream * 	jbl_stream_free						(jbl_stream* this);
#define 		jbl_stream_do(this,flag)			((jbl_stream*)jbl_refer_pull(this))->op->op(this,flag)
#define 		jbl_stream_connect(this,that)		jbl_stream_disconnect(this),(((jbl_stream*)jbl_refer_pull(this)))->nxt=jbl_stream_copy(that)
#define 		jbl_stream_connect_ref(this,that)	jbl_stream_disconnect(this),(((jbl_stream*)jbl_refer_pull(this)))->nxt=jbl_refer(&that)
#define 		jbl_stream_disconnect(this)			(((jbl_stream*)jbl_refer_pull(this)))->nxt=jbl_stream_free((((jbl_stream*)jbl_refer_pull(this)))->nxt)
#define 		jbl_stream_reset(this)				jbl_stream_disconnect(this),(((jbl_stream*)jbl_refer_pull(this)))->en=0,(((jbl_stream*)jbl_refer_pull(this)))->tmp=0
		
#define 		jbl_stream_force					B0000_0001

void			jbl_stream_push_char				(jbl_stream* this,char c);
#define			jbl_stream_push_char_force(this,c)	(((this)->en+1)>(this)->size)?jbl_stream_do(this,0):0,(this)->buf[(this)->en++]=c
void			jbl_stream_push_chars				(jbl_stream* this,char *str);
void			jbl_stream_push_uint64				(jbl_stream* this,jbl_uint64 in);
void			jbl_stream_push_int64				(jbl_stream* this,jbl_int64 in);
void			jbl_stream_push_double				(jbl_stream* this,double in);

#define			pchars(x)							jbl_stream_push_chars(jbl_stream_stdout,x)
#define			pint(x)								jbl_stream_push_int64(jbl_stream_stdout,x)
#define			puint(x)							jbl_stream_push_uint64(jbl_stream_stdout,x)
#define			pchar(x)							jbl_stream_push_char(jbl_stream_stdout,x)
#define			pn()								pchar('\n')
#define			pf()								jbl_stream_do(jbl_stream_stdout,jbl_stream_force)
#define			pl()								puint(__LINE__),pchars(" @ "__FILE__),pn(),pf()

extern			const jbl_stream_operater jbl_stream_file_operators;
extern			jbl_stream *jbl_stream_stdout;
extern			jbl_stream *jbl_stream_stdin;
#define 		sout	jbl_stream_stdout
#define 		sin		jbl_stream_stdin
#define			jbl_stream_start()	jbl_stream_stdout=jbl_stream_new(&jbl_stream_file_operators,stdout,JBL_STREAM_EXCEED_LENGTH,NULL,0,NULL),	\
									jbl_stream_stdin =jbl_stream_new(&jbl_stream_file_operators,stdin ,0,NULL,0,NULL)
#define 		jbl_stream_stop()	/*不关闭stdout,给malloc留条活路jbl_stream_do(jbl_stream_stdout,jbl_stream_force),jbl_stream_stdout=jbl_stream_free(jbl_stream_stdout),*/	\
									jbl_stream_stdin =jbl_stream_free(jbl_stream_stdin )

#if JBL_VAR_ENABLE==1
typedef	struct	__jbl_var_operators	jbl_var_operators;
typedef	struct	__jbl_var 			jbl_var;
extern	const	jbl_var_operators	jbl_stream_operators;
#define			$jbl_stream(x)							((jbl_stream*)x)
jbl_var *		jbl_Vstream_new							(const jbl_stream_operater *op,void *data,jbl_uint16 size,unsigned char *buf,const jbl_uint64 tmpv,const void *tmpp);
#define 		jbl_Vstream_connect(this,that)			($jbl_stream(this))->nxt=$jbl_stream(that)
#define 		jbl_Vstream_do(this,flag)				($jbl_stream(this))->op->op($jbl_stream(this),flag)

#define			jbl_var_copy_from_stream(x)				((jbl_var*)jbl_stream_copy($jbl_stream(jbl_Vstream_new()),x))
#define			jbl_stream_copy_from_var(x)				jbl_stream_copy(NULL,$jbl_stream(x))

//#define		jbl_var_move_from_string(x)				((jbl_var*)jbl_string_move($jbl_string(jbl_Vstring_new()),x))
//#define		jbl_string_move_from_var(x)				jbl_string_move(NULL,$jbl_string(x))




#endif


#else
#define	jbl_stream_start()	0
#define	jbl_stream_stop()	0
#endif
#endif
