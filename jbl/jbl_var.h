/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_VAR_H
#define __JBL_VAR_H
#include "jbl_var_config.h"
#if JBL_VAR_ENABLE==1
#include "jbl_ying.h"
#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"	
#endif
#if JBL_STRING_ENABLE==1
#include "jbl_string.h"	
#endif
typedef struct __jbl_var_operators
{
	void*	(*free)(void*);
	void*	(*copy)(void*);
	char	(*space_ship)(const void*,const void*);
#if JBL_STRING_ENABLE==1
	jbl_string*	(*json_encode)(const void*,jbl_string *,char,jbl_int32);
#endif	
#if JBL_STREAM_ENABLE==1
	void	(*view_put)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32);
	void	(*json_put)(const void*,jbl_stream *,char,jbl_int32);
#endif
}jbl_var_operators;

typedef struct __jbl_var
{
	const jbl_var_operators *ops;
}jbl_var;
#define jbl_var_set_operators(this,op)	((jbl_var*)(((char*)this)-(sizeof(jbl_var))))->ops=(op)
#define jbl_var_get_operators(this)		(((jbl_var*)(((char*)this)-(sizeof(jbl_var))))->ops)

jbl_var *	jbl_var_free				(jbl_var * this);
jbl_var *	jbl_var_copy				(jbl_var * this);
char        jbl_var_space_ship			(const jbl_var * this,const jbl_var * that);
#if JBL_STREAM_ENABLE==1
void		jbl_var_view_put			(const jbl_var * this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs);
#define		jbl_var_view(x) 			jbl_var_view_put(x,jbl_stream_stdout,__LINE__,#x " @ "__FILE__,jbl_view_default_tabs_num),jbl_stream_push_char(jbl_stream_stdout,'\n')
void 		jbl_var_json_put			(const jbl_var * this,jbl_stream *output_stream,char format,jbl_int32 tabs);
#endif

#if JBL_STRING_ENABLE==1
jbl_string * jbl_var_json_encode		(const jbl_var * this,jbl_string *out,char format,jbl_int32 tabs);

#endif
extern const	jbl_var_operators jbl_uint64_operators;
extern const	jbl_var_operators jbl_int64_operators;
extern const	jbl_var_operators jbl_double_operators;
jbl_var *		jbl_Vuint_new			();
jbl_var *		jbl_Vuint_set			(jbl_var * this,jbl_uint64 data);
jbl_var *		jbl_Vuint_copy			(jbl_var * that);
char			jbl_Vuint_space_ship	(jbl_var * this,jbl_var * that);

jbl_var *		jbl_Vint_new			();
jbl_var *		jbl_Vint_set			(jbl_var * this,jbl_int64 data);
jbl_var *		jbl_Vint_copy			(jbl_var * that);
char			jbl_Vint_space_ship		(jbl_var * this,jbl_var * that);

jbl_var *		jbl_Vdouble_new			();
jbl_var *		jbl_Vdouble_set			(jbl_var * this,double data);
jbl_var *		jbl_Vdouble_copy		(jbl_var * that);
char			jbl_Vdouble_space_ship	(jbl_var * this,jbl_var * that);

#if JBL_STRING_ENABLE==1
jbl_string * 	jbl_Vuint_json_encode	(const jbl_var* this,jbl_string *out,char format,jbl_int32 tabs);
jbl_string * 	jbl_Vint_json_encode	(const jbl_var* this,jbl_string *out,char format,jbl_int32 tabs);
jbl_string * 	jbl_Vdouble_json_encode	(const jbl_var* this,jbl_string *out,char format,jbl_int32 tabs);

#endif
#if JBL_STREAM_ENABLE==1
void 			jbl_Vuint_view_put		(const jbl_var* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs);
void 			jbl_Vint_view_put		(const jbl_var* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs);
void 			jbl_Vdouble_view_put	(const jbl_var* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs);
void 			jbl_Vuint_json_put		(const jbl_var* this,jbl_stream *output_stream,char format,jbl_int32 tabs);
void 			jbl_Vint_json_put		(const jbl_var* this,jbl_stream *output_stream,char format,jbl_int32 tabs);
void 			jbl_Vdouble_json_put	(const jbl_var* this,jbl_stream *output_stream,char format,jbl_int32 tabs);
#endif

#endif
#endif