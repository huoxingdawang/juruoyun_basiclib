/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_STREAM_H
#define __JRY_BL_STREAM_H
#include "jry_bl_stream_config.h"
#if JRY_BL_STREAM_ENABLE==1
#include "jry_bl_ying.h"
#include "jry_bl_malloc.h"
#include "jry_bl_exception.h"
#include <stdio.h>
typedef struct __jry_bl_stream_operater jry_bl_stream_operater;
typedef struct __jry_bl_stream
{
	const jry_bl_stream_operater *op;
	struct __jry_bl_stream *nxt;
	jry_bl_uint16	en;
	jry_bl_uint16	size;
	void			*data;
	jry_bl_uint64	tmp;
	unsigned char	*buf;
}jry_bl_stream;

typedef struct __jry_bl_stream_operater
{
	void (*op)(jry_bl_stream*,jry_bl_uint8);
	void (*fd)(void*);
}jry_bl_stream_operater;
typedef enum
{
	json,
	view
}jry_bl_put_type;
jry_bl_stream *	jry_bl_stream_new					(const jry_bl_stream_operater *op,void *data,jry_bl_uint16 size,unsigned char *buf);
#define			jry_bl_stream_free(s)				((((s)->op->fd!=NULL)?((s)->op->fd((s)->data)):0),jry_bl_free(s),NULL)
#define 		jry_bl_stream_do(this,flag)			(this)->op->op(this,flag)
#define 		jry_bl_stream_connect(this,that)	(this)->nxt=that
#define 		jry_bl_stream_reset(this)			(this)->en=0,(this)->tmp=0
		
#define 		jry_bl_stream_force					B0000_0001

#define			jry_bl_stream_push_char(this,c)		(((this)->en+1)>(this)->size)?jry_bl_stream_do(this,0):0,(this)->buf[(this)->en++]=c
void			jry_bl_stream_push_chars			(jry_bl_stream* this,char *str);
void			jry_bl_stream_push_uint64			(jry_bl_stream* this,jry_bl_uint64 in);
void			jry_bl_stream_push_int64			(jry_bl_stream* this,jry_bl_int64 in);
void			jry_bl_stream_push_double			(jry_bl_stream* this,double in);

void			jry_bl_stream_file_operator			(jry_bl_stream* this,jry_bl_uint8 flags);
extern			const jry_bl_stream_operater jry_bl_stream_file_operators;

extern			jry_bl_stream *jry_bl_stream_stdout;
extern			jry_bl_stream *jry_bl_stream_stdin;
#define 		sout	jry_bl_stream_stdout
#define 		sin		jry_bl_stream_stdin
#define			jry_bl_stream_start()	jry_bl_stream_stdout=jry_bl_stream_new(&jry_bl_stream_file_operators,stdout,JRY_BL_STREAM_EXCEED_LENGTH,NULL),	\
										jry_bl_stream_stdin =jry_bl_stream_new(&jry_bl_stream_file_operators,stdin ,0,NULL)
#define 		jry_bl_stream_stop()	jry_bl_stream_do(jry_bl_stream_stdout,jry_bl_stream_force),jry_bl_stream_stdout=jry_bl_stream_free(jry_bl_stream_stdout),	\
										jry_bl_stream_stdin =jry_bl_stream_free(jry_bl_stream_stdin )

#else
#define	jry_bl_stream_start()	0
#define	jry_bl_stream_stop()	0
#endif
#endif
