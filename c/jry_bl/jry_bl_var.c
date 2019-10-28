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
void jry_bl_var_init(jry_bl_var *a)
{
	a->type=JRY_BL_VAR_TYPE_NULL;
	for(register unsigned char i=0,n=sizeof(a->data);i<n;i++)
		a->data._[i]=0;
}


#if JRY_BL_VAR_USE_STDARG==1
inline void	jry_bl_var_inits(int n,...)
{
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++)
		jry_bl_var_init(va_arg(valist,jry_bl_var*));
	va_end(valist);	
}


#endif
#endif