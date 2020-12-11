/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_ll.h"
#if JBL_LL_ENABLE==1
/*******************************************************************************************/
/*                            依赖 jbl_gc jbl_malloc jbl_ying jbl_exception jbl_var        */
/*******************************************************************************************/
#include "jbl_exception.h"
#include "jbl_gc.h"
#include "jbl_malloc.h"
#include "jbl_ying.h"
#include "jbl_var.h"
/*******************************************************************************************/
/*                            联动jbl_stream jbl_string jbl_ht                             */
/*******************************************************************************************/
#include "jbl_string.h"
#include "jbl_stream.h"
#include "jbl_ht.h"
/*******************************************************************************************/
/*                            以下函实现链节点基本操作                                   */
/*******************************************************************************************/
jbl_ll_node * jbl_ll_node_init(jbl_ll_node *node)
{
	node->pre=NULL;
	node->nxt=NULL;
	node->v=NULL;
	return node;
}
jbl_ll_node * jbl_ll_node_new()
{
	return jbl_ll_node_init(jbl_malloc(sizeof(jbl_ll_node)));
}
void jbl_ll_node_free(jbl_ll_node *node)
{
	node->v=jbl_var_free(node->v);
	jbl_free(node);
}
void jbl_ll_node_delink(jbl_ll *this,jbl_ll_node *node)
{
	if(node->nxt==NULL)	this->tail=node->pre;
	else				node->nxt->pre=node->pre;
	if(node->pre==NULL)	this->head=node->nxt;
	else				node->pre->nxt=node->nxt;
	--this->len;
	node->nxt=NULL,node->pre=NULL;
}
void jbl_ll_node_insert(jbl_ll *this,jbl_ll_node *node,jbl_ll_node *after)
{
    if(after==((void *)-1))after=this->tail;
	if(after==NULL)
	{
		node->nxt=this->head;
		node->pre=NULL;
		if(node->nxt==NULL)	this->tail=node;
		else				node->nxt->pre=node;
		this->head=node;
	}
	else
	{
		node->nxt=after->nxt;
		node->pre=after;
		after->nxt=node;
		if(node->nxt==NULL)	this->tail=node;
		else				node->nxt->pre=node;
	}	
	++this->len;
}
void jbl_ll_node_delete(jbl_ll *this,jbl_ll_node *node)
{
	jbl_ll_node_delink(this,node);
	jbl_ll_node_free(node);
}



/*******************************************************************************************/
/*                            以下函实现链表基本操作                                      */
/*******************************************************************************************/
jbl_var_operators_new(jbl_ll_operators,jbl_ll_free,jbl_ll_copy,jbl_ll_space_ship,jbl_ll_json_encode,jbl_ll_view_put,jbl_ll_json_put);
jbl_ll * jbl_ll_new()
{
	jbl_ll *this=jbl_malloc(sizeof(jbl_ll));
	jbl_gc_init(this);
	jbl_gc_plus(this);	
	jbl_pthread_lock_init(this);
	jbl_var_set_operators(this,&jbl_ll_operators);
	this->head=NULL;
    this->tail=NULL;
	this->len=0;
	return this;
}
jbl_ll* jbl_ll_free(jbl_ll *this)
{
	if(!this)return NULL;
    jbl_pthread_lock_wrlock(this);
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		if(jbl_gc_is_ref(this))
			jbl_ll_free((jbl_ll*)(((jbl_reference*)this)->ptr));
		else
			jbl_ll_foreach_del(this,i,j)
				jbl_ll_node_delete(this,i);	
        jbl_pthread_lock_free(this);
		jbl_free(this);
	}
        else{jbl_pthread_lock_unwrlock(this);}
	return NULL;	
}
JBL_INLINE jbl_ll *jbl_ll_copy(jbl_ll *that)
{
	if(!that)return NULL;
    jbl_pthread_lock_wrlock(that);
	jbl_gc_plus(that);
    jbl_pthread_lock_unwrlock(that);    
	return that;
}
jbl_ll *jbl_ll_extend(jbl_ll *this,jbl_ll_node **a,jbl_ll_node **b,jbl_ll **pthi)
{
	if(!this){this=jbl_ll_new();if(pthi)*pthi=this;return this;}
	jbl_reference *ref=NULL;jbl_ll *thi=jbl_refer_pull_keep_father_wrlock(this,&ref);
	if((jbl_gc_refcnt(thi)>1))
    {
        jbl_ll *tmp=jbl_ll_new();
        jbl_pthread_lock_wrlock(tmp);
        jbl_ll_foreach(thi,i)
        {
            jbl_ll_node *node=jbl_ll_node_new();
            node->v=jbl_var_copy(i->v);
            if(a&&(*a==i))*a=node;
            if(b&&(*b==i))*b=node;
            jbl_ll_node_insert(tmp,node,tmp->tail);		
        }
        jbl_pthread_lock_unwrlock(thi);
        jbl_ll_free(thi);
        thi=tmp;
	}
	if(ref)		ref->ptr=thi;
	else		this=thi;
	if(pthi)	*pthi=thi;
    else        {jbl_refer_pull_unwrlock(this);}
    return this;
}
/*******************************************************************************************/
/*                            以下函实现链表插入操作                                     */
/*******************************************************************************************/
jbl_ll * jbl_ll_insert(jbl_ll *this,void *var,jbl_ll_node *after)
{
	jbl_ll *thi;this=jbl_ll_extend(this,&after,NULL,&thi);
	jbl_ll_node *node=jbl_ll_node_new();
	node->v=(var?jbl_var_copy(var):jbl_Vnull_new());
	jbl_ll_node_insert(thi,node,after);
    jbl_refer_pull_unwrlock(this);
	return this;
}
/*******************************************************************************************/
/*                            以下函实现链表合并操作                                     */
/*******************************************************************************************/
jbl_ll *jbl_ll_merge(jbl_ll *this,jbl_ll *that)
{
	if(!that)return this;
	jbl_ll * tha=jbl_refer_pull_rdlock(that);
	jbl_ll_foreach(tha,i)
		this=jbl_ll_add(this,i->v);
    jbl_refer_pull_unrdlock(that);
	return this;
}
#if JBL_HT_ENABLE==1
jbl_ll *jbl_ll_merge_ht(jbl_ll *this,jbl_ht *that)
{
	jbl_ll * tha=jbl_refer_pull_rdlock(that);
#if JBL_HT_SYS_ENABLE==1
	if(tha&&!jbl_ht_is_sys(tha))
#endif
	jbl_ht_foreach(tha,i)
		this=jbl_ll_add(this,i->v);	
    jbl_refer_pull_unrdlock(that);
	return this;
}
#endif
/*******************************************************************************************/
/*                            以下函实现链表删除操作                                     */
/*******************************************************************************************/
jbl_ll * jbl_ll_delete(jbl_ll *this,jbl_ll_node *node)
{
	if(!node)return this;
	jbl_ll *thi;this=jbl_ll_extend(this,&node,NULL,&thi);
    if(node==NULL)node=thi->head;
    if(node==((void *)-1))node=thi->tail;
	jbl_ll_node_delete(thi,node);
    jbl_refer_pull_unwrlock(this);
	return this;
}
/*******************************************************************************************/
/*                            以下函实现链表获取操作                                      */
/*******************************************************************************************/
JBL_INLINE jbl_ll_size_type jbl_ll_get_length(jbl_ll *this)
{
    jbl_ll_size_type ans=0;
	jbl_ll * thi=jbl_refer_pull_rdlock(this);
	if(thi)ans=thi->len;
    jbl_refer_pull_unrdlock(this);
    return ans;
}
JBL_INLINE void* jbl_llv(jbl_ll_node *node){return node->v;}
/*******************************************************************************************/
/*                            以下函实现链表交换操作                                     */
/*******************************************************************************************/
jbl_ll * jbl_ll_swap_node(jbl_ll *this,jbl_ll_node *a,jbl_ll_node *b)
{
	if(a==b)return this;
	this=jbl_ll_extend(this,&a,&b,NULL);
	void *v;
	v=a->v;
	a->v=b->v;
	b->v=v;
    jbl_refer_pull_unwrlock(this);
	return this;
}
/*******************************************************************************************/
/*                            以下函实现链表比较操作                                     */
/*******************************************************************************************/
char jbl_ll_space_ship(jbl_ll *this,jbl_ll *that)
{
    char ans=0;
	jbl_ll *thi=jbl_refer_pull_rdlock(this);
	jbl_ll *tha=jbl_refer_pull_rdlock(that);	
	if(thi==tha){ans=0;goto exit;}if(!thi){ans=-1;goto exit;}if(!tha){ans=1;goto exit;}
	if(thi->len!=tha->len)
        {ans=(thi->len<tha->len)?-1:1;goto exit;}
	for(jbl_ll_node *i=thi->head,*j=tha->head;i!=NULL&&ans==0;ans=jbl_var_space_ship(i->v,j->v),i=i->nxt,j=j->nxt);
exit:;
    jbl_refer_pull_unrdlock(this);
    jbl_refer_pull_unrdlock(that);
	return ans;
}
#if JBL_JSON_ENABLE==1
/*******************************************************************************************/
/*                            以下函实现链表JSON操作                                      */
/*******************************************************************************************/
#if JBL_STRING_ENABLE==1
jbl_string* jbl_ll_json_encode(jbl_ll* this,jbl_string *out,jbl_uint8 format,jbl_uint32 tabs)
{
	jbl_ll *thi=jbl_refer_pull_rdlock(this);
	out=jbl_string_json_put_format(thi,out,format,tabs);
    if(thi)
    {
        out=jbl_string_add_char(out,'[');
        if((format&1)||(format&4))out=jbl_string_add_char(out,'\n');
        ++tabs;
        jbl_uint8 format2=(jbl_uint8)((format&4)|((format&1)<<2));
        jbl_ll_foreach(this,i)
        {
            if(format){for(jbl_uint32 i=0;i<tabs;out=jbl_string_add_char(out,'\t'),++i);}
            out=jbl_var_json_encode(i->v,out,(jbl_uint8)(format2|((i!=this->tail)<<1)),tabs);
        }
        --tabs;if((format&1)||(format&4))for(jbl_uint32 j=0;j<tabs;out=jbl_string_add_char(out,'\t'),++j);//格式化的\t
        out=jbl_string_add_char(out,']');
        if(format&2){out=jbl_string_add_char(out,',');}if((format&1)||(format&4)){out=jbl_string_add_char(out,'\n');}   
    }
    jbl_refer_pull_unwrlock(out);
    jbl_refer_pull_unrdlock(this);
    return out;
}
#endif
#if JBL_STREAM_ENABLE==1
void jbl_ll_json_put(jbl_ll* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs)
{
	jbl_ll *thi=jbl_refer_pull_rdlock(this);
	if(jbl_stream_json_put_format(thi,out,format,tabs))
    {
        jbl_stream_push_char(out,'[');
        if((format&1)||(format&4))jbl_stream_push_char(out,'\n');
        ++tabs;
        jbl_uint8 format2=(jbl_uint8)((format&4)|((format&1)<<2));
        jbl_ll_foreach(this,i)
        {
            if((format&1)||(format&4))for(jbl_uint32 i=0;i<tabs;jbl_stream_push_char(out,'\t'),++i);
            jbl_var_json_put(i->v,out,(jbl_uint8)(format2|((i!=this->tail)<<1)),tabs);
        }	
        --tabs;if((format&1)||(format&4))for(jbl_uint32 i=0;i<tabs;jbl_stream_push_char(out,'\t'),++i);
        jbl_stream_push_char(out,']');
        if(format&2){jbl_stream_push_char(out,',');}if((format&1)||(format&4)){jbl_stream_push_char(out,'\n');}
    }
    jbl_refer_pull_unwrlock(out);
    jbl_refer_pull_unrdlock(this);
}
#endif
#endif
/*******************************************************************************************/
/*                            以下函实现链表插看操作                                      */
/*******************************************************************************************/
#if JBL_STREAM_ENABLE==1
jbl_ll*jbl_ll_view_put(jbl_ll* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * file)
{
	jbl_ll *thi=jbl_refer_pull_rdlock(this);
    if(jbl_stream_view_put_format(thi,out,format,tabs,UC"jbl_ll",line,varname,func,file))
    {
        jbl_stream_push_chars(out,UC"\tlen:");jbl_stream_push_uint(out,thi->len);
        jbl_stream_push_char(out,'\n');
        jbl_ll_size_type j=0;
        ++tabs;
        jbl_ll_foreach(thi,i)
        {
            for(jbl_uint32 i=0;i<tabs;jbl_stream_push_char(out,'\t'),++i);
            jbl_stream_push_uint(out,j++);
            jbl_stream_push_char(out,':');
            jbl_var_view_put(i->v,out,0,tabs,0,NULL,NULL,NULL);
        }
    }
    else
        jbl_stream_push_char(out,'\n');
    jbl_refer_pull_unwrlock(out);
    jbl_refer_pull_unrdlock(this);
	return this;
}
#endif
#endif
