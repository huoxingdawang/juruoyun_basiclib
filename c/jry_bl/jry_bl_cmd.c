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
void jry_bl_execute_cmd(const jry_bl_string *cmd,jry_bl_string *result)
{
	char buf_ps[1024];
	FILE *ptr;
	if((ptr=popen(jry_bl_string_get_chars(cmd),"r"))!=NULL)
	{
		while(fgets(buf_ps,1024,ptr)!=NULL)
			jry_bl_string_add_chars(result,buf_ps);
		pclose(ptr);
	}
}
#endif
