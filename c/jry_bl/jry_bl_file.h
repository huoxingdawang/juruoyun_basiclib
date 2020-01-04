/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_FILE_H
#define __JRY_BL_FILE_H
#include "jry_bl_file_config.h"
#if JRY_BL_FILE_ENABLE==1
#include "jry_bl_string.h"
#include "jry_bl_var.h"
#include "jry_bl_ying.h"
#include "jry_bl_hash_table.h"
#include <dirent.h>
#define JRY_BL_FILE_TYPE_UNKNOW	0
#define JRY_BL_FILE_TYPE_FILE	1
#define JRY_BL_FILE_TYPE_DIR	2
typedef struct __jry_bl_file
{
	jry_bl_uint8 type:2;
	jry_bl_string name;
	struct __jry_bl_file *f;
	union
	{
		struct
		{
			FILE *handle; 
			
			
		}file;
		struct
		{
			jry_bl_hash_table child;
			
		}dir;
	}d;
}jry_bl_file;

void	jry_bl_file_init					(jry_bl_file *this);
void	jry_bl_file_clear					(jry_bl_file *this);
void	jry_bl_file_free					(jry_bl_file *this);
void	jry_bl_file_copy					(jry_bl_file *this,jry_bl_file *that,jry_bl_uint8 cpt);
#define	jry_bl_file_equal(x,y)				jry_bl_file_copy(x,y,JRY_BL_COPY)
#define	jry_bl_file_equal_light(x,y)		jry_bl_file_copy(x,y,JRY_BL_COPY_LIGHT)
#define	jry_bl_file_equal_light_move(x,y)	jry_bl_file_copy(x,y,JRY_BL_COPY_LIGHT_MOVE)
char	jry_bl_file_space_ship				(const jry_bl_file *this,const jry_bl_file *that);
#define	jry_bl_file_view(x,y)			 	jry_bl_file_view_ex(x,y,#x " @ "__FILE__,__LINE__,jry_bl_view_default_tabs_num)
void 	jry_bl_file_view_ex					(const jry_bl_file *this,FILE * file,char*str,int a,int tabs);
#define	jry_bl_file_open(x,y,z)				jry_bl_file_file_open_ex(x,NULL,y,z,-1)
void	jry_bl_file_file_open_ex			(jry_bl_file *this,jry_bl_file *f,jry_bl_string *name,jry_bl_uint8 ncpt,jry_bl_uint32 recursive_time);



#define jry_bl_var_get_file(this)			((jry_bl_file*)(this)->data.p)

#endif
#endif
