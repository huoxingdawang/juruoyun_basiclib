/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_PTHREAD_H
#define __JBL_PTHREAD_H
#include "jbl_pthread_config.h"
#if JBL_PTHREAD_ENABLE==1
#include <pthread.h>
void __jbl_pthread_lock_init(pthread_mutex_t *lock);
#define				jbl_pthread_lock_define			pthread_mutex_t __lock
#define				jbl_pthread_lock_init(this)		__jbl_pthread_lock_init(&((this)->__lock))
#define				jbl_pthread_lock_rdlock(this)	pthread_mutex_lock(&((this)->__lock))
#define				jbl_pthread_lock_wrlock(this)	pthread_mutex_lock(&((this)->__lock))
#define				jbl_pthread_lock_unrdlock(this)	pthread_mutex_unlock(&((this)->__lock))
#define				jbl_pthread_lock_unwrlock(this)	pthread_mutex_unlock(&((this)->__lock))
#define				jbl_pthread_lock_free(this)	    pthread_mutex_destroy(&((this)->__lock))
#include "jbl_gc.h"
#include "jbl_var.h"
typedef struct __jbl_pthread
{
	pthread_t thread;
    void *(*func)(void *);
    void *data;
    jbl_pthreads_size_type i;
    const char *name;
}jbl_pthread;
typedef struct __jbl_pthreads
{
	jbl_gc_define           ;
	jbl_var_ops_define		;
	jbl_pthread_lock_define	;
    struct __jbl_pthreads   *pre,*nxt;
	jbl_pthreads_size_type	len;
	jbl_pthreads_size_type	size;
	jbl_pthread             threads[];
}jbl_pthreads;
void             jbl_pthread_start              ();
void             jbl_pthread_stop               ();
jbl_uint64       jbl_pthread_get_id             ();
void             jbl_pthread_check_exit         ();
jbl_pthreads *   jbl_pthreads_new               (jbl_pthreads_size_type size);
jbl_pthreads *   jbl_pthreads_free              (jbl_pthreads *this);
jbl_pthreads *   jbl_pthreads_copy              (jbl_pthreads *that);
jbl_pthreads *   jbl_pthreads_stop              (jbl_pthreads *this);
jbl_pthreads *   jbl_pthreads_wait              (jbl_pthreads *this);
jbl_pthreads *   __jbl_pthreads_creat_thread    (jbl_pthreads *this,void *(*func)(void *),jbl_pthreads_size_type n,const char * name,void * data);
#define          jbl_pthreads_creat_thread(this,func,n,data)    __jbl_pthreads_creat_thread(this,((void*(*)(void*))(func)),n,#func,data)
#if JBL_STREAM_ENABLE==1
jbl_pthreads*		jbl_pthreads_view_put					(jbl_pthreads* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * pthreads);	//从out浏览一个字符串
#define				jbl_pthreads_view(x)					jbl_pthreads_view_put(x,jbl_stream_stdout,1,JBL_VIEW_DEFAULT_TABS,__LINE__,UC #x,UC __FUNCTION__,UC __FILE__)//浏览一个字符串
#endif

#else
#define         jbl_pthread_start()
#define         jbl_pthread_stop()
typedef void jbl_pthreads;
#define			jbl_pthread_lock_define
#define			jbl_pthread_lock_init(this)
#define			jbl_pthread_lock_rdlock(this)
#define			jbl_pthread_lock_wrlock(this)
#define			jbl_pthread_lock_unrdlock(this)
#define			jbl_pthread_lock_unwrlock(this)
#define			jbl_pthread_lock_free(this)
#define			jbl_pthread_check_exit()
#define			jbl_pthread_get_id()            (0)
#define			jbl_pthreads_new(n)             (NULL)
#define			jbl_pthreads_free(this)         (NULL)
#define			jbl_pthreads_copy(this)         (NULL)
#define		    jbl_pthreads_stop(this)         (NULL)
#define		    jbl_pthreads_wait(this)         (NULL)
#define		    jbl_pthreads_view(this)         (NULL)
jbl_pthreads *  __jbl_pthreads_creat_thread     (jbl_pthreads *this,void *(*func)(void *),jbl_pthreads_size_type n,const char * name,void * data);
#define         jbl_pthreads_creat_thread(this,func,n,data)     __jbl_pthreads_creat_thread(this,(void*(*)(void*))(func),n,#func,data)



#endif
#endif
