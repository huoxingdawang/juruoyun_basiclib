/* Copyright (c) [2020] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_file.h"
#if JBL_FILE_ENABLE==1
#include <sys/stat.h>
#include "jbl_log.h"
#include "jbl_string.h"
#include "jbl_string_cc.h"
#include <errno.h>

jbl_file * jbl_file_new()
{
	return jbl_file_init(jbl_malloc(sizeof(jbl_file)));
}
jbl_file * jbl_file_init(jbl_file* this)
{
	if(!this)jbl_exception("NULL POINTER");
	jbl_gc_init(this);
	jbl_gc_plus(this);
	this->dir					=NULL;
	this->handle				=NULL;
	this->type					=JBL_FILE_CLOSE;
	this->status.size			=0;
	this->status.time_access	=NULL;
	this->status.time_modify	=NULL;
	this->status.time_creat		=NULL;
	return this;
}
jbl_file* jbl_file_free(jbl_file *this)
{
	if(!this)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_refcnt(this))
	{
		if(jbl_gc_is_ref(this)||jbl_gc_is_pvar(this))
			jbl_file_free((jbl_file*)(((jbl_reference*)this)->ptr));
		else
			this=jbl_file_close(this);
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var(this))
			jbl_free((char*)this-sizeof(jbl_var));
		else
#endif
			jbl_free(this);
	}
	return NULL;
}
inline jbl_file *jbl_file_copy(jbl_file *that)
{
	if(!that)return NULL;
	jbl_gc_plus(that);
	return that;
}
jbl_file* jbl_file_close(jbl_file *this)
{
	if(!this)jbl_exception("NULL POINTER");
	jbl_file *thi=jbl_refer_pull(this);	
	thi->dir=jbl_string_free(thi->dir);
	if(thi->handle||this->type!=JBL_FILE_CLOSE)fclose(thi->handle),thi->handle=NULL,this->type=JBL_FILE_CLOSE;
#if JBL_TIME_ENABLE==1
	thi->status.time_access=jbl_time_free(thi->status.time_access);
	thi->status.time_modify=jbl_time_free(thi->status.time_modify);
	thi->status.time_creat =jbl_time_free(thi->status.time_creat);
#endif	

	return this;
}
jbl_file* jbl_file_open(jbl_file *this,jbl_string * dir,jbl_file_handle_type type)
{
	if(!this)this=jbl_file_new();
	jbl_file *thi=jbl_refer_pull(this);
	if(thi->dir)
		thi=jbl_refer_pull(this=jbl_file_close(this));
	thi->dir=jbl_string_copy(dir);
	thi->dir=jbl_string_set_tail(thi->dir);
#ifdef _WIN32
	struct __stat64 buf;
	jbl_string * gb2312name=jbl_string_to_gb2312_from_utf8(NULL,thi->dir);//windows的系统要求gb2312
	gb2312name=jbl_string_set_tail(gb2312name);
	if(_stat64((char*)jbl_string_get_chars(gb2312name),&buf))
	{
		thi->dir=jbl_string_free(thi->dir);
		gb2312name=jbl_string_free(gb2312name);	
		jbl_log(UC"open file %j failed with errno %d",jbl_gc_minus(jbl_string_copy_as_var(dir)),errno);
		return this;
	}
	switch(thi->type=type)
	{
		case JBL_FILE_CLOSE:break;
		case JBL_FILE_READ :thi->handle=fopen((char*)jbl_string_get_chars(gb2312name),"rb");break;
		case JBL_FILE_WRITE:thi->handle=fopen((char*)jbl_string_get_chars(gb2312name),"wb");break;
	}
	gb2312name=jbl_string_free(gb2312name);	
#elif defined(__APPLE__) || defined(__linux__)
	struct stat buf;
	if(stat((char*)jbl_string_get_chars(thi->dir),&buf))
	{
		jbl_log(UC"open file %j failed with errno %d",jbl_gc_minus(jbl_string_copy_as_var(dir)),errno);
		thi->dir=jbl_string_free(thi->dir);
		return this;
	}
	switch(thi->type=type)
	{
		case JBL_FILE_CLOSE:break;
		case JBL_FILE_READ :thi->handle=fopen((char*)jbl_string_get_chars(thi->dir),"rb");break;
		case JBL_FILE_WRITE:thi->handle=fopen((char*)jbl_string_get_chars(thi->dir),"wb");break;
	}
#endif	
	this->status.size		=buf.st_size;
	this->status.time_access=jbl_time_set(this->status.time_access,buf.st_atime*1000);
	this->status.time_modify=jbl_time_set(this->status.time_modify,buf.st_mtime*1000);
	this->status.time_creat	=jbl_time_set(this->status.time_creat ,buf.st_ctime*1000);
	
	return this;
}
inline jbl_file* jbl_file_open_chars(jbl_file *this,unsigned char * dir,jbl_file_handle_type type)
{
	return jbl_file_open(this,jbl_gc_minus(jbl_string_add_const(NULL,dir)),type);
}



#if JBL_STREAM_ENABLE==1
/*******************************************************************************************/
/*                            以下函数实现文件的浏览操作                               */
/*******************************************************************************************/
jbl_file* jbl_file_view_put(jbl_file* this,jbl_stream *out,jbl_uint8 format,jbl_uint32 tabs,jbl_uint32 line,unsigned char * varname,unsigned char * func,unsigned char * file)
{
	jbl_file *thi;if(jbl_stream_view_put_format(thi=jbl_refer_pull(this),out,format,tabs,UC"jbl_file",line,varname,func,file)){jbl_stream_push_char(out,'\n');return this;}
	jbl_stream_push_char(out,'\n');
	++tabs;
	char * type		[]={"close","read","write"};
	for(jbl_int32 j=0;j<tabs;jbl_stream_push_char(out,'\t'),++j){}	jbl_stream_push_chars(out,UC"handle type  :");jbl_stream_push_chars(out,UC type[thi->type])							;jbl_stream_push_char(out,'\n');
	for(jbl_int32 j=0;j<tabs;jbl_stream_push_char(out,'\t'),++j){}	jbl_stream_push_chars(out,UC"dir          :");jbl_stream_push_string(out,this->dir)									;jbl_stream_push_char(out,'\n');
	for(jbl_int32 j=0;j<tabs;jbl_stream_push_char(out,'\t'),++j){}	jbl_stream_push_chars(out,UC"size         :");jbl_stream_push_uint(out,this->status.size)							;jbl_stream_push_char(out,'\n');
#if JBL_TIME_ENABLE==1
	for(jbl_int32 j=0;j<tabs;jbl_stream_push_char(out,'\t'),++j){}	jbl_stream_push_chars(out,UC"time_creat   :");jbl_stream_push_time(out,this->status.time_creat ,UC"Y-m-d H:i:s.u")	;jbl_stream_push_char(out,'\n');
	for(jbl_int32 j=0;j<tabs;jbl_stream_push_char(out,'\t'),++j){}	jbl_stream_push_chars(out,UC"time_modify  :");jbl_stream_push_time(out,this->status.time_modify,UC"Y-m-d H:i:s.u")	;jbl_stream_push_char(out,'\n');
	for(jbl_int32 j=0;j<tabs;jbl_stream_push_char(out,'\t'),++j){}	jbl_stream_push_chars(out,UC"time_access  :");jbl_stream_push_time(out,this->status.time_access,UC"Y-m-d H:i:s.u")	;jbl_stream_push_char(out,'\n');
#endif

	return this;
}
#endif
#endif
