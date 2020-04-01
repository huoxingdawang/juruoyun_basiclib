/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_cmd.h"
#if JRY_BL_CMD_ENABLE==1
#include <stdio.h>
#include "jry_bl_string.h"
jry_bl_string * jry_bl_execute_cmd(const jry_bl_string *cmd,jry_bl_string *result)
{
	if(cmd==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	char *buf=jry_bl_malloc(1024);
	FILE *ptr;
	if((ptr=popen((char*)jry_bl_string_get_chars(cmd),"r"))!=NULL)
	{
		while(fgets(buf,1024,ptr)!=NULL)
			result=jry_bl_string_add_chars_length(result,(jry_bl_uint8*)buf,jry_bl_strlen(buf));
		pclose(ptr);
	}
	jry_bl_free(buf);
	return result;
}
#endif
