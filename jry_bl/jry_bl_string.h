#ifndef __JRY_BL_STRING_H
#define __JRY_BL_STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#define JRY_BL_STRING_BASIC_LENGTH	1024
#define JRY_BL_STRING_SIZE_TYPE		long long
#define JRY_BL_STRING_LENGTH_TYPE	long long

typedef struct
{
	JRY_BL_STRING_SIZE_TYPE		len;
	JRY_BL_STRING_LENGTH_TYPE	size;
	char *						s;
}jry_bl_string;

int 		jry_bl_string_init				(jry_bl_string *s);
int 		jry_bl_string_init_by_length	(jry_bl_string *s,JRY_BL_STRING_SIZE_TYPE size);
int 		jry_bl_string_init_by_string	(jry_bl_string *s,char *in);
int 		jry_bl_string_deinit			(jry_bl_string *s);
int 		jry_bl_string_link				(jry_bl_string *s,jry_bl_string *s2);
int 		jry_bl_string_view				(jry_bl_string *s,FILE * file);
int 		jry_bl_string_add				(jry_bl_string *s,char * s2);
long long	jry_bl_string_string_to_int		(jry_bl_string *s,int start);
int			jry_bl_string_int_to_string		(jry_bl_string *s,long long in);
#endif
