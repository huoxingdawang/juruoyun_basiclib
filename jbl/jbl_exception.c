/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_exception.h"
#if JBL_EXCEPTION_ENABLE==1
#include <stdio.h>
#include <stdlib.h>
#include "jbl_include.h"
void __jbl_exception(const char * funtion,const char * file,int line,int x)
{
	jbl_stop();
	fprintf(stderr,"-------------------------------------------------------\n");
	jbl_print_colorful(stderr,"ERROR!",JBL_PRINT_COLORFUL_BLACK,JBL_PRINT_COLORFUL_RED);
	fprintf(stderr,"\nAT\tfile:");
	jbl_print_colorful(stderr,file,JBL_PRINT_COLORFUL_BLACK,JBL_PRINT_COLORFUL_YELLOW);
	fprintf(stderr,"\n\tfuntion:");
	jbl_print_colorful(stderr,funtion,JBL_PRINT_COLORFUL_BLACK,JBL_PRINT_COLORFUL_YELLOW);
	fprintf(stderr,"\n  \tline:");
	char ss[40];
	sprintf(ss,"%d",line);jbl_print_colorful(stderr,ss,JBL_PRINT_COLORFUL_BLACK,JBL_PRINT_COLORFUL_YELLOW);
	fprintf(stderr,"\nBecause:");
	sprintf(ss,"%d",x);jbl_print_colorful(stderr,ss,JBL_PRINT_COLORFUL_BLACK,JBL_PRINT_COLORFUL_YELLOW);
	switch(x)
	{
		case JBL_ERROR_NO_ERROR			:fprintf(stderr,":JBL_ERROR_NO_ERROR")			;break;
		case JBL_ERROR_NULL_POINTER		:fprintf(stderr,":JBL_ERROR_NULL_POINTER")		;break;
		case JBL_ERROR_MEMORY_ERROR		:fprintf(stderr,":JBL_ERROR_MEMORY_ERROR")		;break;
		case JBL_ERROR_FILE_NOT_EXIST	:fprintf(stderr,":JBL_ERROR_FILE_NOT_EXIST")	;break;
		case JBL_ERROR_STREAM_ERROR		:fprintf(stderr,":JBL_ERROR_STREAM_ERROR")		;break;
		case JBL_ERROR_VAR_TYPE_ERROR	:fprintf(stderr,":JBL_ERROR_VAR_TYPE_ERROR")	;break;
	}
	putc('\n',stderr);
	exit(0);
}
#endif