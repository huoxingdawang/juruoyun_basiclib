/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_file.h"
#if JRY_BL_FILE_ENABLE==1
void jry_bl_file_init(jry_bl_file *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	this->type=JRY_BL_FILE_TYPE_UNKNOW;
	this->f=NULL;
	this->light_copy=0;
	jry_bl_string_init(&this->name);
}
void jry_bl_file_init_as(jry_bl_file *this,jry_bl_uint8 type)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	jry_bl_string_clear(&this->name);
	this->f=NULL;
	this->light_copy=0;
	if(this->type==type)
	{
		if(type==JRY_BL_FILE_TYPE_FILE)
			if(this->file.handle!=NULL)
				fclose(this->file.handle),this->file.handle=NULL;		
		else if(type==JRY_BL_FILE_TYPE_DIR)
			jry_bl_hash_table_clear(&this->dir.child);
	}
	else if(this->type==JRY_BL_FILE_TYPE_UNKNOW)
	{
		if(type==JRY_BL_FILE_TYPE_FILE)
			this->file.handle=NULL;
		else if(type==JRY_BL_FILE_TYPE_DIR)
			jry_bl_hash_table_init(&this->dir.child);
		this->type=type;		
	}
	else
	{
		if(this->type==JRY_BL_FILE_TYPE_FILE)
			if(this->file.handle!=NULL)
				fclose(this->file.handle),this->file.handle=NULL;
		else if(this->type==JRY_BL_FILE_TYPE_DIR)
			jry_bl_hash_table_free(&this->dir.child);			
		this->type=type;		
	}
}
void jry_bl_file_clear(jry_bl_file *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->f!=NULL)
		return;
	if(this->type==JRY_BL_FILE_TYPE_FILE)
	{
		if(this->file.handle!=NULL)
			fclose(this->file.handle),this->file.handle=NULL;
	}
	else if(this->type==JRY_BL_FILE_TYPE_DIR)
		jry_bl_hash_table_free(&this->dir.child);
	this->light_copy=0;
	this->type=JRY_BL_FILE_TYPE_UNKNOW;
	jry_bl_string_clear(&this->name);	
}
void jry_bl_file_free(jry_bl_file *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->type==JRY_BL_FILE_TYPE_FILE)
	{
		if(this->file.handle!=NULL&&this->light_copy==0)
			fclose(this->file.handle),this->file.handle=NULL;
	}
	else if(this->type==JRY_BL_FILE_TYPE_DIR)
		jry_bl_hash_table_free(&this->dir.child);	
	this->type=JRY_BL_FILE_TYPE_UNKNOW;
	jry_bl_string_free(&this->name);
	this->f=NULL;
}
void jry_bl_file_copy(jry_bl_file *this,jry_bl_file *that,jry_bl_copy_type cpt)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	jry_bl_file_clear(this);
	jry_bl_file_init_as(this,that->type);
	this->f=that->f;
	jry_bl_string_copy(&this->name,&that->name,cpt);
	if(that->type==JRY_BL_FILE_TYPE_FILE)
	{
		if(cpt==copy)
			this->file.handle=fopen(jry_bl_string_get_chars(&that->name),"rb+"),this->light_copy=0;
		else
			this->light_copy=that->light_copy,this->file.handle=that->file.handle,((cpt==move)?that:this)->light_copy=1;
	}
	else if(that->type==JRY_BL_FILE_TYPE_DIR)
		jry_bl_hash_table_copy(&this->dir.child,&that->dir.child,cpt);
}
inline char jry_bl_file_space_ship(const jry_bl_file *this,const jry_bl_file *that)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	return jry_bl_string_space_ship(&this->name,&that->name);
}
void jry_bl_file_view_ex(const jry_bl_file *this,FILE * file,char*str,int a,int tabs)
{
	if(this==NULL||file==NULL||str==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(tabs>=0)
		for(register int i=0;i<tabs;++i,putc('\t',file));
	else
		tabs=-tabs;
	if(a>=0)
		fprintf(file,"jry_bl_%s    %s %d:",((this->type==JRY_BL_FILE_TYPE_FILE)?"file  ":((this->type==JRY_BL_FILE_TYPE_DIR)?"dir   ":"filenw")),str,a);
	else
		fprintf(file,"jry_bl_%s     \t:",((this->type==JRY_BL_FILE_TYPE_FILE)?"file  ":((this->type==JRY_BL_FILE_TYPE_DIR)?"dir   ":"filenw")));
	fprintf(file,"\tname:");
	jry_bl_string_print(&this->name,file);
	fputc('\t',file);
	if(this->type==JRY_BL_FILE_TYPE_FILE)
	{
		fputc('\n',file);
	}
	else if(this->type==JRY_BL_FILE_TYPE_DIR)
	{
		fputc('\n',file);
		jry_bl_hash_table_foreach(&this->dir.child,i)
			jry_bl_file_view_ex(jry_bl_var_get_file(jry_bl_hash_table_get_var(i)),file,"",-1,tabs+1);
	}
}
void jry_bl_file_file_open_ex(jry_bl_file *this,jry_bl_file *f,jry_bl_string *name,jry_bl_copy_type ncpt,jry_bl_uint32 recursive_time)
{
	if(this==NULL||name==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	jry_bl_file_clear(this);
	jry_bl_string_set(name,jry_bl_string_get_length(name),'\0');
	FILE	*file	=fopen(jry_bl_string_get_chars(name),"rb+");
	DIR		*dir	=opendir(jry_bl_string_get_chars(name));
	if(file!=NULL)
	{
		if(dir!=NULL)closedir(dir);	
		jry_bl_file_init_as(this,JRY_BL_FILE_TYPE_FILE);
		jry_bl_string_copy(&this->name,name,ncpt);this->f=f;
		this->file.handle=file;
	}
	else if(dir!=NULL)
	{
		jry_bl_file_init_as(this,JRY_BL_FILE_TYPE_DIR);
		jry_bl_string_copy(&this->name,name,ncpt);this->f=f;
		if(recursive_time>0)
		{	
			struct dirent *dirp;
			jry_bl_string tmp1,tmp2;jry_bl_string_init(&tmp1);jry_bl_string_init(&tmp2);jry_bl_string_equal_string(&tmp1,&this->name);
#ifdef __linux__
				jry_bl_string_add_char(&tmp1,'/');
#else
				jry_bl_string_add_char(&tmp1,'\\');
#endif
			jry_bl_string_size_type nn=jry_bl_string_get_length(&tmp1);
			jry_bl_hash_table_size_type cnt=0;
			jry_bl_var tv;jry_bl_var_init(&tv);
			while((dirp=readdir(dir)))++cnt;
			jry_bl_hash_table_extend(&this->dir.child,cnt);
			rewinddir(dir);
			while((dirp=readdir(dir)))
			{
				jry_bl_string_equal_chars(&tmp2,dirp->d_name);
				if(jry_bl_string_get1(&tmp2,0)=='.'||(2<jry_bl_string_get_length(&tmp2)&&jry_bl_string_get1(&tmp2,0)=='.'&&jry_bl_string_get1(&tmp2,1)=='.'))
					continue;
				jry_bl_var_init_as(&tv,JRY_BL_VAR_TYPE_FILE);
				jry_bl_string_add_chars(&tmp1,dirp->d_name);
				jry_bl_file_file_open_ex(jry_bl_var_get_file(&tv),this,&tmp1,move,recursive_time-1);
				jry_bl_hash_table_insert(&this->dir.child,&tmp2,&tv,move,move);
				jry_bl_string_get_length(&tmp1)=nn;
			}
			jry_bl_var_free(&tv);
			jry_bl_string_free(&tmp1);
			jry_bl_string_free(&tmp2);
		}
		closedir(dir);
	}
	else
		jry_bl_string_print(name,stderr),jry_bl_file_clear(this),jry_bl_exception(JRY_BL_ERROR_FILE_NOT_EXIST);
}
void jry_bl_file_file_cd(jry_bl_file *this,jry_bl_file *that,jry_bl_string *name,jry_bl_copy_type ncpt)
{
	
	
}

#endif
