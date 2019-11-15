/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/   
#include "jry_bl_var.h"
#if JRY_BL_VAR_ENABLE==1
#define	jry_bl_var_get_flag_pointer(this) 	((this)->f.f.flags&(1<<0))
#define	jry_bl_var_set_flag_pointer(this,a)	((this)->f.f.flags&=~(1<<0)),((this)->f.f.flags|=(1<<0))
inline void jry_bl_var_init(jry_bl_var *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	this->f.f.type=JRY_BL_VAR_TYPE_NULL;
	this->f.f.flags=0;
}
inline void jry_bl_var_init_as(jry_bl_var *this,jry_bl_var_type_type type)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->f.f.type!=JRY_BL_VAR_TYPE_NULL)
		jry_bl_var_free(this);
	this->f.f.flags=0;
	this->f.f.type=type;
	if(this->f.f.type==JRY_BL_VAR_TYPE_VAR)
		this->data.var=jry_bl_malloc(sizeof(jry_bl_var)),jry_bl_var_init(this->data.var);
#if JRY_BL_STRING_ENABLE==1	
	else if(this->f.f.type==JRY_BL_VAR_TYPE_STRING)
		this->data.str=jry_bl_malloc(sizeof(jry_bl_string)),jry_bl_string_init(this->data.str);
#endif
}
void jry_bl_var_free(jry_bl_var *this)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->f.f.type==JRY_BL_VAR_TYPE_VAR)
		jry_bl_var_free(this->data.var),jry_bl_free(this->data.var);
#if JRY_BL_STRING_ENABLE==1	
	else if(this->f.f.type==JRY_BL_VAR_TYPE_STRING)
		jry_bl_string_free(this->data.str),((jry_bl_var_get_flag_pointer(this))?(1):(jry_bl_free(this->data.str)));
#endif
	this->f.f.type=JRY_BL_VAR_TYPE_NULL;
	this->f.f.flags=0;
}
void jry_bl_var_equal(jry_bl_var *this,jry_bl_var *that)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->f.f.type<=8)
	{
		jry_bl_var_free(this);
		this->f.f.type=that->f.f.type;
		memcpy(&this->data,&that->data,sizeof that->data);
	}	
	else
	{
		if(this->f.f.type!=JRY_BL_VAR_TYPE_NULL)
			jry_bl_var_free(this);		
		if(this->f.f.type==JRY_BL_VAR_TYPE_VAR)
			jry_bl_var_equal(this->data.var,that->data.var);
#if JRY_BL_STRING_ENABLE==1	
		else if(this->f.f.type==JRY_BL_VAR_TYPE_STRING)
			jry_bl_string_equal_string(this->data.str,that->data.str);
#endif		
		this->f.ff=that->f.ff;
	}
}
void jry_bl_var_equal_light(jry_bl_var *this,jry_bl_var *that)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->f.f.type<=8)
	{
		jry_bl_var_free(this);
		this->f.f.type=that->f.f.type;
		memcpy(&this->data,&that->data,sizeof that->data);
	}	
	else
	{
		if(this->f.f.type!=JRY_BL_VAR_TYPE_NULL)
			jry_bl_var_free(this);		
		if(this->f.f.type==JRY_BL_VAR_TYPE_VAR)
			jry_bl_var_equal_light(this->data.var,that->data.var);
#if JRY_BL_STRING_ENABLE==1	
		else if(this->f.f.type==JRY_BL_VAR_TYPE_STRING)
			jry_bl_string_equal_string_light(this->data.str,that->data.str);
#endif		
		this->f.ff=that->f.ff;
	}
}
void jry_bl_var_equal_light_move(jry_bl_var *this,jry_bl_var *that)
{
	if(this==NULL||that==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->f.f.type<=8)
	{
		jry_bl_var_free(this);
		this->f.f.type=that->f.f.type;
		memcpy(&this->data,&that->data,sizeof that->data);
	}	
	else
	{
		if(this->f.f.type!=JRY_BL_VAR_TYPE_NULL)
			jry_bl_var_free(this);		
		if(this->f.f.type==JRY_BL_VAR_TYPE_VAR)
			jry_bl_var_equal_light_move(this->data.var,that->data.var);
#if JRY_BL_STRING_ENABLE==1	
		else if(this->f.f.type==JRY_BL_VAR_TYPE_STRING)
			jry_bl_string_equal_string_light_move(this->data.str,that->data.str);
#endif		
		this->f.ff=that->f.ff;
	}
}
char jry_bl_var_space_ship(jry_bl_var *this,jry_bl_var *that)
{
	if(this->f.f.type==that->f.f.type)
	{
		switch(this->f.f.type)
		{
			case JRY_BL_VAR_TYPE_LONG_LONG			:return ((this->data.ll<that->data.ll)?(-1):((this->data.ll>that->data.ll)));break;
			case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:return ((this->data.ll<that->data.ull)?(-1):((this->data.ll>that->data.ull)));break;
			case JRY_BL_VAR_TYPE_DOUBLE				:return ((this->data.d<that->data.d)?(-1):((this->data.d>that->data.d)));break;
			case JRY_BL_VAR_TYPE_CHAR				:return ((this->data.c<that->data.c)?(-1):((this->data.c>that->data.c)));break;
#if JRY_BL_STRING_ENABLE==1	
			case JRY_BL_VAR_TYPE_STRING				:return jry_bl_string_space_ship(this->data.str,that->data.str);break;
#endif
			default:
				return 0;
		}		
		
	}
	else
		return (this->f.f.type>that->f.f.type)?1:-1;
}

#if JRY_BL_STRING_ENABLE==1	
inline void				jry_bl_var_equal_string				(jry_bl_var *this,jry_bl_string *that){jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_string(this->data.str,that);}
inline void				jry_bl_var_equal_string_light		(jry_bl_var *this,jry_bl_string *that){jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_string_light(this->data.str,that);}
inline void				jry_bl_var_equal_string_light_move	(jry_bl_var *this,jry_bl_string *that){jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_string_light_move(this->data.str,that);}
inline void				jry_bl_var_equal_string_pointer		(jry_bl_var *this,jry_bl_string *that){jry_bl_var_free(this);jry_bl_var_set_flag_pointer(this,1);this->f.f.type=JRY_BL_VAR_TYPE_STRING,this->data.str=that;}
inline jry_bl_string*	jry_bl_var_get_string				(jry_bl_var *this){if(this->f.f.type!=JRY_BL_VAR_TYPE_STRING)jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);return this->data.str;}
inline void				jry_bl_string_equal_var				(jry_bl_string *this,jry_bl_var *that){jry_bl_var_turn(that,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_string(this,that->data.str);}
inline void				jry_bl_string_equal_var_light		(jry_bl_string *this,jry_bl_var *that){jry_bl_var_turn(that,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_string_light(this,that->data.str);}
inline void				jry_bl_string_equal_var_light_move	(jry_bl_string *this,jry_bl_var *that){jry_bl_var_turn(that,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_string_light_move(this,that->data.str);}
#endif
void jry_bl_var_turn(jry_bl_var *this,jry_bl_var_type_type type)
{
	if(this->f.f.type==type)
		return;
	long double tmp;
	switch(type)
	{
			case JRY_BL_VAR_TYPE_NULL:
				jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				break;
			case JRY_BL_VAR_TYPE_LONG_LONG:
				switch(this->f.f.type)
				{
					case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:this->f.f.type=JRY_BL_VAR_TYPE_LONG_LONG;this->data.ll=this->data.ull	;break;
					case JRY_BL_VAR_TYPE_DOUBLE				:this->f.f.type=JRY_BL_VAR_TYPE_LONG_LONG;this->data.ll=this->data.d	;break;
					case JRY_BL_VAR_TYPE_TRUE				:this->f.f.type=JRY_BL_VAR_TYPE_LONG_LONG;this->data.ll=1				;break;
					case JRY_BL_VAR_TYPE_FALSE				:this->f.f.type=JRY_BL_VAR_TYPE_LONG_LONG;this->data.ll=0				;break;
					case JRY_BL_VAR_TYPE_CHAR				:this->f.f.type=JRY_BL_VAR_TYPE_LONG_LONG;this->data.ll=this->data.c	;break;
#if JRY_BL_STRING_ENABLE==1	
					case JRY_BL_VAR_TYPE_STRING				:tmp=jry_bl_string_get_long_long(this->data.str);jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_LONG_LONG);this->data.ll=tmp;break;
#endif
					default:
						jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				}
				break;
			case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG:
				switch(this->f.f.type)
				{
					case JRY_BL_VAR_TYPE_LONG_LONG			:this->f.f.type=JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG;this->data.ull=this->data.ll	;break;
					case JRY_BL_VAR_TYPE_DOUBLE				:this->f.f.type=JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG;this->data.ull=this->data.d	;break;
					case JRY_BL_VAR_TYPE_TRUE				:this->f.f.type=JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG;this->data.ull=1				;break;
					case JRY_BL_VAR_TYPE_FALSE				:this->f.f.type=JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG;this->data.ull=0				;break;
					case JRY_BL_VAR_TYPE_CHAR				:this->f.f.type=JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG;this->data.ull=this->data.c	;break;
#if JRY_BL_STRING_ENABLE==1	
					case JRY_BL_VAR_TYPE_STRING				:tmp=jry_bl_string_get_unsigned_long_long(this->data.str);jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG);this->data.ull=tmp;break;
#endif
					default:
						jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				}
				break;
			case JRY_BL_VAR_TYPE_DOUBLE:
				switch(this->f.f.type)
				{
					case JRY_BL_VAR_TYPE_LONG_LONG			:this->f.f.type=JRY_BL_VAR_TYPE_DOUBLE;this->data.d=this->data.ll	;break;
					case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:this->f.f.type=JRY_BL_VAR_TYPE_DOUBLE;this->data.d=this->data.ull	;break;
					case JRY_BL_VAR_TYPE_TRUE				:this->f.f.type=JRY_BL_VAR_TYPE_DOUBLE;this->data.d=1				;break;
					case JRY_BL_VAR_TYPE_FALSE				:this->f.f.type=JRY_BL_VAR_TYPE_DOUBLE;this->data.d=0				;break;
					case JRY_BL_VAR_TYPE_CHAR				:this->f.f.type=JRY_BL_VAR_TYPE_DOUBLE;this->data.d=this->data.c	;break;
#if JRY_BL_STRING_ENABLE==1	
					case JRY_BL_VAR_TYPE_STRING				:tmp=jry_bl_string_get_double(this->data.str);jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_DOUBLE);this->data.d=tmp;break;
#endif
					default:
						jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				}
				break;
			case JRY_BL_VAR_TYPE_TRUE:
			case JRY_BL_VAR_TYPE_FALSE:
				switch(this->f.f.type)
				{
					case JRY_BL_VAR_TYPE_LONG_LONG			:this->f.f.type=(this->data.ll==0?JRY_BL_VAR_TYPE_FALSE:JRY_BL_VAR_TYPE_TRUE)	;break;
					case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:this->f.f.type=(this->data.ull==0?JRY_BL_VAR_TYPE_FALSE:JRY_BL_VAR_TYPE_TRUE)	;break;
					case JRY_BL_VAR_TYPE_TRUE				:;break;
					case JRY_BL_VAR_TYPE_FALSE				:;break;
					case JRY_BL_VAR_TYPE_CHAR				:this->f.f.type=(this->data.c==0?JRY_BL_VAR_TYPE_FALSE:JRY_BL_VAR_TYPE_TRUE)	;break;
#if JRY_BL_STRING_ENABLE==1	
					case JRY_BL_VAR_TYPE_STRING				:tmp=jry_bl_string_get_long_long(this->data.str);jry_bl_var_init_as(this,(tmp==0?JRY_BL_VAR_TYPE_FALSE:JRY_BL_VAR_TYPE_TRUE));break;
#endif
					default:
						jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				}
				break;
			case JRY_BL_VAR_TYPE_CHAR:
				switch(this->f.f.type)
				{
					case JRY_BL_VAR_TYPE_LONG_LONG			:this->f.f.type=JRY_BL_VAR_TYPE_CHAR;this->data.c=this->data.ll	;break;
					case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:this->f.f.type=JRY_BL_VAR_TYPE_CHAR;this->data.c=this->data.ull;break;
					case JRY_BL_VAR_TYPE_DOUBLE				:this->f.f.type=JRY_BL_VAR_TYPE_CHAR;this->data.c=this->data.d	;break;
					case JRY_BL_VAR_TYPE_TRUE				:this->f.f.type=JRY_BL_VAR_TYPE_CHAR;this->data.c=1				;break;
					case JRY_BL_VAR_TYPE_FALSE				:this->f.f.type=JRY_BL_VAR_TYPE_CHAR;this->data.c=0				;break;
#if JRY_BL_STRING_ENABLE==1	
					case JRY_BL_VAR_TYPE_STRING				:tmp=jry_bl_string_get1(this->data.str,0);jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_CHAR);this->data.c=tmp;break;
#endif
					default:
						jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				}
				break;
			case JRY_BL_VAR_TYPE_POINTER:
				jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				break;
				
#if JRY_BL_STRING_ENABLE==1				
			case JRY_BL_VAR_TYPE_STRING:
				switch(this->f.f.type)
				{
					case JRY_BL_VAR_TYPE_LONG_LONG			:tmp=this->data.ll	;jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_long_long			(this->data.str,tmp);break;
					case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:tmp=this->data.ull	;jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_unsigned_long_long	(this->data.str,tmp);break;
					case JRY_BL_VAR_TYPE_DOUBLE				:tmp=this->data.d	;jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_double		(this->data.str,tmp);break;
					case JRY_BL_VAR_TYPE_TRUE				:					;jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_long_long			(this->data.str,1)	;break;
					case JRY_BL_VAR_TYPE_FALSE				:					;jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_long_long			(this->data.str,0)	;break;
					case JRY_BL_VAR_TYPE_CHAR				:tmp=this->data.c	;jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);jry_bl_string_equal_char				(this->data.str,tmp);break;
					default:
						jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
				}				
				break;
#endif
			default:
				jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
	}
	
}
#if JRY_BL_STRING_ENABLE==1
void jry_bl_var_to_json(jry_bl_var *this,jry_bl_string *result)
{
	long double tmp;	
	switch(this->f.f.type)
	{
		case JRY_BL_VAR_TYPE_NULL				:					;jry_bl_string_add_char_pointer			(result,"null")	;break;
		case JRY_BL_VAR_TYPE_LONG_LONG			:tmp=this->data.ll	;jry_bl_string_add_long_long			(result,tmp)	;break;
		case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:tmp=this->data.ull	;jry_bl_string_add_unsigned_long_long	(result,tmp)	;break;
		case JRY_BL_VAR_TYPE_DOUBLE				:tmp=this->data.d	;jry_bl_string_add_double			(result,tmp)	;break;
		case JRY_BL_VAR_TYPE_TRUE				:					;jry_bl_string_add_unsigned_long_long	(result,1)		;break;
		case JRY_BL_VAR_TYPE_FALSE				:					;jry_bl_string_add_unsigned_long_long	(result,0)		;break;
		case JRY_BL_VAR_TYPE_CHAR				:tmp=this->data.c	;jry_bl_string_add_char					(result,tmp)	;break;
		default:
			jry_bl_exception(JRY_BL_ERROR_TYPE_ERROR);
	}
}
jry_bl_string_size_type jry_bl_var_from_json_start(jry_bl_var *this,jry_bl_string *in,jry_bl_string_size_type i)
{
	jry_bl_string_size_type n=jry_bl_string_get_length(in);
	while(i<n)
	{
		register unsigned char c=jry_bl_string_get1(in,i);
		if(c=='"'&&(i==0||jry_bl_string_get1(in,i-1)!='\\'))
		{
			jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_STRING);
			return jry_bl_string_from_json_start(this->data.str,in,i);
		}
		else if(c=='{')
		{
			return i;
		}
		else if(c=='[')
		{
			return i;
		}
		else if(c=='-')
		{
			jry_bl_string_size_type i1=i,i2=i;
			long long	t1=jry_bl_string_get_long_long_start(in,&i1);
			double		t2=jry_bl_string_get_double_start(in,&i2);
			if(i1==i2)
				return jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_LONG_LONG),this->data.ll=t1,i1;
			else if(i1<i2)
				return jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_DOUBLE),this->data.d=t2,i2;
		}
		else if(c>='0'&&c<='9')
		{
			jry_bl_string_size_type i1=i,i2=i;
			unsigned long long	t1=jry_bl_string_get_unsigned_long_long_start(in,&i1);
			double				t2=jry_bl_string_get_double_start(in,&i2);
			if(i1==i2)
				jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG),this->data.ull=t1,i1;
			else if(i1<i2)
				jry_bl_var_init_as(this,JRY_BL_VAR_TYPE_DOUBLE),this->data.d=t2,i2;
		}
		++i;
	}
	return i;
}
#endif
#if JRY_BL_USE_STDIO==1
void jry_bl_var_view_ex(jry_bl_var *this,FILE * file,char*str,int a)
{
	if(this==NULL||file==NULL||str==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	if(this->f.f.type<=8)
	{
		char ss[20];
		switch(this->f.f.type)
		{		
			case JRY_BL_VAR_TYPE_NULL				:fprintf(file,"NULL")									;break;
			case JRY_BL_VAR_TYPE_LONG_LONG			:fprintf(file,"LONG LONG:%lld",this->data.ll)			;break;
			case JRY_BL_VAR_TYPE_UNSIGNED_LONG_LONG	:fprintf(file,"UNSIGNED LONG LONG:%lld",this->data.ull)	;break;
			case JRY_BL_VAR_TYPE_DOUBLE				:fprintf(file,"DOUBLE:%lf",this->data.d)				;break;
			case JRY_BL_VAR_TYPE_TRUE				:fprintf(file,"TRUE")									;break;
			case JRY_BL_VAR_TYPE_FALSE				:fprintf(file,"FALSE")									;break;
			case JRY_BL_VAR_TYPE_CHAR				:fprintf(file,"CHAR:%c",this->data.c)					;break;
			case JRY_BL_VAR_TYPE_POINTER			:fprintf(file,"POINTER:0X%X",this->data.p)				;break;
		}
		fputc('\n',file);		
	}
	else if(this->f.f.type==JRY_BL_VAR_TYPE_VAR)
		fprintf(file,"(jry_bl_var%s)",(jry_bl_var_get_flag_pointer(this)?"pointer":"")),jry_bl_var_view_ex(this->data.var,file,str,a);
	else if(this->f.f.type==JRY_BL_VAR_TYPE_STRING)
		fprintf(file,"(jry_bl_var%s)",(jry_bl_var_get_flag_pointer(this)?"_pointer":"")),jry_bl_string_view_ex(this->data.str,file,str,a);
}
#endif
#if JRY_BL_USE_STDARG==1
inline void	jry_bl_var_inits(int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_var_init(va_arg(valist,jry_bl_var*));
	va_end(valist);	
}
inline void	jry_bl_var_frees(int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_var_free(va_arg(valist,jry_bl_var*));
	va_end(valist);	
}
#if JRY_BL_USE_STDIO==1
inline void	jry_bl_var_views(FILE * file,int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_var_view_ex(va_arg(valist,jry_bl_var*),file,"views",i);
	va_end(valist);	
}
#endif
#endif
#endif