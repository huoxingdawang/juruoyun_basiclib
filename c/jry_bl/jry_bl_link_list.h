/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_LINK_LIST_H
#define __JRY_BL_LINK_LIST_H
#include "jry_bl_link_list_config.h"
#if JRY_BL_LINK_LIST_ENABLE==1
#include "jry_bl_var.h"
#if JRY_BL_USE_STDARG==1
#include <stdarg.h>
#endif
typedef struct __jry_bl_link_list_node
{
	struct __jry_bl_link_list_node *pre,*nxt;
	jry_bl_var v;
}jry_bl_link_list_node;
typedef struct __jry_bl_link_list
{
	struct __jry_bl_link_list_node *head,*tail;
	jry_bl_link_list_size_type length;
	unsigned char flags;
}jry_bl_link_list;
#define	jry_bl_link_list_get_flag_light_copy(this) 		((this)->flags&(1<<0))
#define	jry_bl_link_list_set_flag_light_copy(this,a)	((this)->flags&=~(1<<0)),((this)->flags|=(1<<0))

void	jry_bl_link_list_init							(jry_bl_link_list *this);
void	jry_bl_link_list_node_init						(jry_bl_link_list_node *this);
void	jry_bl_link_list_free							(jry_bl_link_list *this);
void	jry_bl_link_list_node_free						(jry_bl_link_list_node *this);
void	jry_bl_link_list_node_delink					(jry_bl_link_list *this,jry_bl_link_list_node *node);
void	jry_bl_link_list_insert_node					(jry_bl_link_list *this,jry_bl_link_list_node *node,jry_bl_link_list_node *after);
void	jry_bl_link_list_insert_var						(jry_bl_link_list *this,jry_bl_var *var,jry_bl_link_list_node *after);
void	jry_bl_link_list_insert_var_light				(jry_bl_link_list *this,jry_bl_var *var,jry_bl_link_list_node *after);
void	jry_bl_link_list_insert_var_light_move			(jry_bl_link_list *this,jry_bl_var *var,jry_bl_link_list_node *after);
void	jry_bl_link_list_delete_node					(jry_bl_link_list *this,jry_bl_link_list_node *node);
void	jry_bl_link_list_swap_node						(jry_bl_link_list *this,jry_bl_link_list_node *a,jry_bl_link_list_node *b);
#define jry_bl_link_list_delete_head(x)					jry_bl_link_list_delete_node((x),(x)->head)
#define jry_bl_link_list_delete_tail(x)					jry_bl_link_list_delete_node((x),(x)->tail)
#define jry_bl_link_list_add_node(x,y)					jry_bl_link_list_insert_node((x),(y),(x)->tail)
#define jry_bl_link_list_add_var(x,y)					jry_bl_link_list_insert_var((x),(y),(x)->tail)
#define jry_bl_link_list_add_var_light(x,y)				jry_bl_link_list_insert_var_light((x),(y),(x)->tail)
#define jry_bl_link_list_add_var_light_move(x,y)		jry_bl_link_list_insert_var_light_move((x),(y),(x)->tail)
#define jry_bl_link_list_data(x)						(&((x)->v))
#define jry_bl_link_list_foreach(x,y)					for(jry_bl_link_list_node *(y)=(x)->head;(y)!=NULL;(y)=(y)->nxt)
#define jry_bl_link_list_foreach_del(x,y,z)				for(jry_bl_link_list_node *(y)=(x)->head,*(z)=((y)==NULL?NULL:(y)->nxt);(y)!=NULL;(y)=(z),(z)=((y)==NULL?NULL:(y)->nxt))
char	jry_bl_link_list_space_ship						(jry_bl_link_list *this,jry_bl_link_list *that);
#define	jry_bl_link_list_if_big(x,y)					(jry_bl_link_list_space_ship(x,y)>0)
#define	jry_bl_link_list_if_equal(x,y)					(jry_bl_link_list_space_ship(x,y)==0)
#define	jry_bl_link_list_if_small(x,y) 					(jry_bl_link_list_space_ship(x,y)<0)
#define	jry_bl_link_list_if_equal_small(x,y)			(jry_bl_link_list_space_ship(x,y)<=0)
#define	jry_bl_link_list_if_equal_big(x,y) 				(jry_bl_link_list_space_ship(x,y)>=0)

void	jry_bl_link_list_copy							(jry_bl_link_list *this,jry_bl_link_list *that);	
void	jry_bl_link_list_copy_light						(jry_bl_link_list *this,jry_bl_link_list *that);	
void	jry_bl_link_list_copy_light_move				(jry_bl_link_list *this,jry_bl_link_list *that);	
	
#if JRY_BL_USE_STDIO==1
#define	jry_bl_link_list_view(x,y) 						jry_bl_link_list_view_ex(x,y,#x,__LINE__)
void 	jry_bl_link_list_view_ex						(jry_bl_link_list *this,FILE * file,char*str,int a);
#endif



#if JRY_BL_USE_STDARG==1
void	jry_bl_link_list_inits							(int n,...);
void	jry_bl_link_list_node_inits						(int n,...);
void	jry_bl_link_list_frees							(int n,...);
void	jry_bl_link_list_node_frees						(int n,...);
#endif


#endif
#endif
