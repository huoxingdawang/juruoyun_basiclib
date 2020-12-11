/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/   
#include "jbl_var.h"
#if JBL_VAR_ENABLE==1
#include "jbl_exception.h"
#include "jbl_malloc.h"
#include "jbl_string.h"
#include "jbl_stream.h"
#include "jbl_pthread.h"

struct __jbl_var
{
	jbl_gc_define           ;
	jbl_var_ops_define      ;
	jbl_pthread_lock_define	;
};
JBL_INLINE void * jbl_var_set_operators(void * this,const jbl_var_operators *ops)
{
	if(this)
    {	
        jbl_pthread_lock_wrlock(((struct __jbl_var *)this));
        ((struct __jbl_var *)this)->var_ops=((jbl_var_operators *)ops);
        jbl_pthread_lock_unwrlock(((struct __jbl_var *)this));
	}
    return this;
}
JBL_INLINE const jbl_var_operators * jbl_var_get_operators(void * this)
{
	const jbl_var_operators * ops=NULL;
    if(this)
    {
        jbl_pthread_lock_rdlock(((struct __jbl_var *)this));
        ops=((struct __jbl_var *)this)->var_ops;
        jbl_pthread_lock_unrdlock(((struct __jbl_var *)this));
    }
    return ops;
}
JBL_INLINE void * jbl_var_free(void * this)
{
    if(this)
    {
        jbl_pthread_lock_wrlock(((struct __jbl_var *)this));
        const jbl_var_operators * ops=jbl_var_get_operators(this);
        if(ops&&ops->free)ops->free(this);
        jbl_pthread_lock_unwrlock(((struct __jbl_var *)this));
	}
    return NULL;
}
JBL_INLINE void * jbl_var_copy(void * this)
{
    void * that=NULL;
    if(this)
    {
        jbl_pthread_lock_wrlock(((struct __jbl_var *)this));
        const jbl_var_operators * ops=jbl_var_get_operators(this);
        if(ops&&ops->copy)that=ops->copy(this);
        jbl_pthread_lock_unwrlock(((struct __jbl_var *)this));
	}
    return that;
}
JBL_INLINE char jbl_var_space_ship(void * this,void * that)
{
    char ans=0;
    if(this&&that)
    {
        jbl_pthread_lock_rdlock(((struct __jbl_var *)this));
        jbl_pthread_lock_rdlock(((struct __jbl_var *)that));
        const jbl_var_operators * ops1=jbl_var_get_operators(this);
        const jbl_var_operators * ops2=jbl_var_get_operators(that);
        if(this==that)           ans=0;
        else if(!ops1)           ans=-1;
        else if(!ops2)           ans=1;
        else if(ops1<ops2)       ans=-1;
        else if(ops1>ops2)       ans=1;
        else if(ops1->space_ship)ans=ops1->space_ship(this,that);
        else                     ans=-1;
        jbl_pthread_lock_unrdlock(((struct __jbl_var *)this));
        jbl_pthread_lock_unrdlock(((struct __jbl_var *)that));
	}
    return ans;
}
#if JBL_STRING_ENABLE==1 && JBL_JSON_ENABLE==1
jbl_string * jbl_var_json_encode(void * this,jbl_string *out,jbl_uint8 format,jbl_uint32 tabs)
{
    if(this)
    {
        jbl_pthread_lock_rdlock(((struct __jbl_var *)this));
        const jbl_var_operators * ops=jbl_var_get_operators(this);
        if(!ops||!ops->json_encode)
            out=jbl_string_json_put_format(NULL,out,format,tabs);
        else
            out=ops->json_encode(this,out,format,tabs);
        jbl_pthread_lock_unrdlock(((struct __jbl_var *)this));
    }
    else
        out=jbl_string_json_put_format(NULL,out,format,tabs);
    return out;
}
#endif




#if JBL_STREAM_ENABLE==1
void* jbl_var_view_put(void* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * file)
{
	if(!this)goto print;
    jbl_pthread_lock_rdlock(((struct __jbl_var *)this));
	const jbl_var_operators * ops=jbl_var_get_operators(this);
	if(ops&&ops->view_put)ops->view_put(this,out,format,tabs,line,varname,func,file);
    jbl_pthread_lock_unrdlock(((struct __jbl_var *)this));
	if(!(ops&&ops->view_put))goto print;
    return this;
print:;
	jbl_stream_view_put_format(this,out,format,tabs,UC"unprintable var",line,varname,func,file);jbl_stream_push_char(out,'\n');
    jbl_refer_pull_unwrlock(out);
	return this;
}
#if JBL_JSON_ENABLE==1
void jbl_var_json_put(void * this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs)
{
    if(this)
    {
        jbl_pthread_lock_rdlock(((struct __jbl_var *)this));
        const jbl_var_operators * ops=jbl_var_get_operators(this);
        if(!ops||!ops->json_encode)
           jbl_stream_json_put_format(NULL,out,format,tabs);
        else
            ops->json_put(this,out,format,tabs);
        jbl_pthread_lock_unrdlock(((struct __jbl_var *)this));
    }
    else
       jbl_stream_json_put_format(NULL,out,format,tabs);
}
#endif
#endif

#endif