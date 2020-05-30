/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_HT_H
#define __JBL_HT_H
#include "jbl_ht_config.h"
#if JBL_HT_ENABLE==1
#include "jbl_string.h"
#include "jbl_ying.h"
#include "jbl_var.h"
typedef struct __jbl_ht_data
{
	jbl_string_hash_type	h;
	jbl_ht_size_type		nxt;	
	jbl_string *			k;
	jbl_var *				v;
}jbl_ht_data;
typedef struct __jbl_ht
{
	jbl_gc gc;	
	jbl_ht_size_type size;
	jbl_ht_size_type len;
	jbl_ht_size_type nxt;
	jbl_ht_data		*data;
}jbl_ht;
extern	const			jbl_var_operators			jbl_ht_operators;									//hash table 操作器
jbl_ht  *				jbl_Vht						(jbl_var * this);									//以hash table德格式使用var
#define					Vis_jbl_ht(x)				(jbl_var_get_operators(x)==&jbl_ht_operators)		//判断一个var是不是hash table 
jbl_var *				jbl_htv						(jbl_ht_data *node);								//获取一个node的var
jbl_string * 			jbl_htk						(jbl_ht_data *node);								//获取一个node的key
jbl_string_hash_type	jbl_hth						(jbl_ht_data *node);								//获取一个node的hash
jbl_ht  *				jbl_ht_new					();													//新建一个hash table
jbl_var *				jbl_Vht_new					();													//以var形式新建一个hash table
jbl_ht  *				jbl_ht_init					(jbl_ht *this);										//初始化一个hash table
jbl_ht  *				jbl_ht_free					(jbl_ht *this);										//释放一个hash table
jbl_ht  *				jbl_ht_extend				(jbl_ht *this,jbl_ht_size_type size);				//扩展一个hash table
jbl_ht  *				jbl_ht_extend_to			(jbl_ht *this,jbl_ht_size_type size);				//把一个hash table扩展到size
#define					jbl_ht_foreach(this,i)		for(jbl_ht_data *i=&((jbl_ht *)jbl_refer_pull(this))->data[0],*____i=&(((jbl_ht *)jbl_refer_pull(this)))->data[((jbl_ht *)jbl_refer_pull(this))->nxt];i!=____i;i++)if(i->v!=NULL)//枚举一个hash table
jbl_ht  *				jbl_ht_rehash				(jbl_ht *this);										//重新hash一个hash table
jbl_ht  *				jbl_ht_insert				(jbl_ht *this,jbl_string *k,jbl_var *v);			//插入一个var
jbl_ht  *				jbl_ht_insert_chars			(jbl_ht *this,unsigned char *kk,jbl_var *v);		//以chars为key插入一个var
jbl_ht  *				jbl_ht_insert_int			(jbl_ht *this,jbl_string_hash_type h,jbl_var *v);	//以int为key插入一个var
jbl_var *				jbl_ht_get					(const jbl_ht *this,jbl_string *k);					//获取一个var
jbl_var *				jbl_ht_get_chars			(const jbl_ht *this,unsigned char *kk);				//以chars为key获取一个var
jbl_var *				jbl_ht_get_int				(const jbl_ht *this,jbl_string_hash_type h);		//以chars为int获取一个var
jbl_ht  *				jbl_ht_unset				(jbl_ht *this,jbl_string *k);						//删除一个var
jbl_ht  *				jbl_ht_unset_chars			(jbl_ht *this,unsigned char *kk);					//以chars为key删除一个var
jbl_ht  *				jbl_ht_unset_int			(jbl_ht *this,jbl_string_hash_type h);				//以int为key获取一个var
jbl_ht  *				jbl_ht_copy					(jbl_ht *that);										//复制一个hash table
char					jbl_ht_space_ship			(const jbl_ht *this_,const jbl_ht *that_);			//太空船操作符，参见php的太空船操作符
#define					jbl_ht_if_big(x,y)			(jbl_ht_space_ship(x,y)>0)							//判断两个字符串是否相等
#define					jbl_ht_if_equal(x,y)		(jbl_ht_space_ship(x,y)==0)							//判断this是否>that
#define					jbl_ht_if_small(x,y)		(jbl_ht_space_ship(x,y)<0)							//判断this是否<that
#define					jbl_ht_if_equal_small(x,y)	(jbl_ht_space_ship(x,y)<=0)							//判断this是否>=that
#define					jbl_ht_if_equal_big(x,y)	(jbl_ht_space_ship(x,y)>=0)							//判断this是否<=that
jbl_ht  *				jbl_ht_merge				(jbl_ht *this,jbl_ht *that);						//合并两个hash table 注意this不会复制,而且this，that中key重复的that将覆盖this
jbl_ht  *				jbl_ht_merge_int			(jbl_ht *this);										//把int key合并为string key
#define					jbl_ht_get_length(x)		(((jbl_ht *)jbl_refer_pull(x))->len)				//获取一个hash table的长度

#if JBL_JSON_ENABLE==1
jbl_string *			jbl_ht_json_encode			(const jbl_ht* this,jbl_string *out,char format,jbl_int32 tabs);//JSON 编码
jbl_ht*					jbl_ht_json_decode			(jbl_ht *this,const jbl_string* in,jbl_string_size_type *start);//JSON 解码
#endif

#if JBL_STREAM_ENABLE==1
#include "jbl_stream.h"
void					jbl_ht_view_put				(const jbl_ht* this,jbl_stream *output_stream,jbl_int32 format,char*str,jbl_int32 tabs);//从output_stream浏览一个hash table
#define					jbl_ht_view(x)				jbl_ht_view_put(x,jbl_stream_stdout,__LINE__,#x " @ "__FILE__,jbl_view_default_tabs_num),jbl_stream_push_char(jbl_stream_stdout,'\n')//浏览一个hash table
void					jbl_ht_json_put				(const jbl_ht* this,jbl_stream *output_stream,char format,jbl_int32 tabs);//从output_stream JSON输出一个hash table
#endif
#if JBL_LL_ENABLE==1
typedef struct			__jbl_ll jbl_ll;
jbl_ht *				jbl_ht_merge_ll				(jbl_ht *this,jbl_ll *that);						//合并一个link list
#endif
#endif
#endif