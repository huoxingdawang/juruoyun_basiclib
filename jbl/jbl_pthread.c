/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_pthread.h"
#if JBL_PTHREAD_ENABLE==1
#include "jbl_ying.h"
#include "jbl_malloc.h"
#include "jbl_gc.h"
static struct
{
	jbl_pthread_lock_define	;
    jbl_pthreads            *head;
}__jbl_pthreads_polls;
void jbl_pthread_start()
{
	jbl_pthread_lock_init(&__jbl_pthreads_polls);
    __jbl_pthreads_polls.head=NULL;
}
void jbl_pthread_stop()
{
	jbl_pthread_lock_wrlock(&__jbl_pthreads_polls);
#if defined(__APPLE__) || defined(__linux__)
    for(jbl_pthreads* thi=__jbl_pthreads_polls.head;thi;thi=thi->nxt)
    {
        jbl_pthread_lock_wrlock(thi);
        for(jbl_pthreads_size_type i=0;i<thi->len;++i)
            pthread_cancel(thi->threads[i].thread),
            pthread_join(thi->threads[i].thread,NULL);
        thi->len=0;
    }
#endif
	jbl_pthread_lock_unwrlock(&__jbl_pthreads_polls);
	jbl_pthread_lock_free(&__jbl_pthreads_polls);
}
void __jbl_pthread_lock_init(pthread_mutex_t *lock)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
#if defined(_WIN32) || defined(__linux__)
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
#elif defined(__APPLE__)
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
#endif
    pthread_mutex_init(lock,&attr);  
    pthread_mutexattr_destroy(&attr);
}


jbl_uint64  jbl_pthread_get_id    (){return (jbl_uint64)pthread_self();}
void        jbl_pthread_check_exit(){pthread_testcancel();}
jbl_pthreads * jbl_pthreads_new(jbl_pthreads_size_type size)
{
    if(size==0)size=8;
    size=1U<<(jbl_highbit(size-1)+1);
	jbl_pthreads * this=jbl_malloc(sizeof(jbl_pthreads)+sizeof(jbl_pthread)*size);
	jbl_gc_init(this);
	jbl_gc_plus(this);//增加引用计数
	jbl_var_set_operators(this,&jbl_pthreads_operators);
	jbl_pthread_lock_init(this);
	this->len=0;
	this->size=size;
	this->pre=NULL;
	this->nxt=__jbl_pthreads_polls.head;
    __jbl_pthreads_polls.head=this;	
    return this;	
}
jbl_pthreads* jbl_pthreads_free(jbl_pthreads *this)
{
	if(!this)return NULL;
    jbl_pthread_lock_wrlock(this);
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		if(jbl_gc_is_ref(this))
			jbl_pthreads_free((jbl_pthreads*)(((jbl_reference*)this)->ptr));
        else
        {
            for(jbl_pthreads_size_type i=0;i<this->len;++i)
                pthread_cancel(this->threads[i].thread),pthread_join(this->threads[i].thread,NULL);            
            if(this->pre)
            {
                jbl_pthread_lock_wrlock(this->pre);
                this->pre->nxt=this->nxt;
                jbl_pthread_lock_unwrlock(this->pre);
            }
            else
            {
                jbl_pthread_lock_wrlock(&__jbl_pthreads_polls);
                __jbl_pthreads_polls.head=this->nxt;
                jbl_pthread_lock_unwrlock(&__jbl_pthreads_polls);
            }
            if(this->nxt)
            {
                jbl_pthread_lock_wrlock(this->nxt);
                this->nxt->pre=this->pre;
                jbl_pthread_lock_unwrlock(this->nxt);
            }
		}
        jbl_pthread_lock_free(this);
        jbl_free(this);
	}
    else
        jbl_pthread_lock_unwrlock(this);
	return NULL;
}
JBL_INLINE jbl_pthreads *jbl_pthreads_copy(jbl_pthreads *that)
{
	if(!that)return NULL;
    jbl_pthread_lock_wrlock(that);
	jbl_gc_plus(that);
    jbl_pthread_lock_unwrlock(that);    
	return that;
}
jbl_pthreads *jbl_pthreads_extend_to(jbl_pthreads *this,jbl_pthreads_size_type size,jbl_uint8 add,jbl_pthreads **pthi)
{
	if(!this)
    {
        this=jbl_pthreads_new(size);
        if(pthi)	*pthi=this;
        return this;
	}
    jbl_reference *ref=NULL;jbl_pthreads *thi=jbl_refer_pull_keep_father_wrlock(this,&ref);
	size+=thi->len*(add&1);
    if(size==0)size=8;
	size=1U<<(jbl_highbit(size-1)+1);
    if((size>thi->size)||(jbl_gc_refcnt(thi)!=1))
    {
        jbl_pthreads *tmp=jbl_pthreads_new(size);
        jbl_pthread_lock_wrlock(tmp);
        jbl_memory_copy(&tmp->threads,&thi->threads,sizeof(jbl_pthread)*thi->len);
        jbl_pthread_lock_unwrlock(thi);
        jbl_pthreads_free(thi);
        thi=tmp;
        if(ref)		ref->ptr=thi;
        else		this=thi;
	}
    if(pthi)	*pthi=thi;
    else         jbl_refer_pull_unwrlock(this);
    return this;
}
static void * __jbl_pthread_child_start(jbl_pthread *thread)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);  
    return thread->func(thread->data);
}
jbl_pthreads * __jbl_pthreads_creat_thread(jbl_pthreads *this,void *(*func)(void *),jbl_pthreads_size_type n,const char * name,void * data)
{
    jbl_pthreads *thi;this=jbl_pthreads_extend_to(this,1,1,&thi);
    for(jbl_pthreads_size_type i=0;i<n;++i)
    {
        thi->threads[thi->len].func=func;
        thi->threads[thi->len].data=data;
        thi->threads[thi->len].i=i;
        thi->threads[thi->len].name=name;
        pthread_create(&thi->threads[thi->len].thread,NULL,(void*(*)(void*))__jbl_pthread_child_start,&thi->threads[thi->len]);
        ++thi->len;
    }
    jbl_refer_pull_unwrlock(this);
    return this;
}
jbl_pthreads * jbl_pthreads_stop(jbl_pthreads *this)
{
	if(!this)return NULL;
    jbl_pthreads *thi;this=jbl_pthreads_extend_to(this,0,1,&thi);
    for(jbl_pthreads_size_type i=0;i<thi->len;++i)
        pthread_cancel(thi->threads[i].thread),
        pthread_join(thi->threads[i].thread,NULL);
    thi->len=0;   
    jbl_refer_pull_unwrlock(this);
    return this;
}
jbl_pthreads * jbl_pthreads_wait(jbl_pthreads *this)
{
	if(!this)return NULL;
    jbl_pthreads *thi;this=jbl_pthreads_extend_to(this,0,1,&thi);
    for(jbl_pthreads_size_type i=0;i<thi->len;++i)
        pthread_join(thi->threads[i].thread,NULL);
    thi->len=0;
    jbl_refer_pull_unwrlock(this);
    return this;
}
#else
jbl_pthreads * __jbl_pthreads_creat_thread(jbl_pthreads *this,void *(*func)(void *),jbl_pthreads_size_type n,const char * name,void * data)
{
    name++;
    for(jbl_pthreads_size_type i=0;i<n;++i)
        func(data);
    return this;
}
#endif
