/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_stream.h"
#if JRY_BL_STREAM_ENABLE==1
void jry_bl_stream_file_operator(jry_bl_stream* this,jry_bl_uint8 flags)
{
	if(this->nxt==NULL)
	{
		for(jry_bl_uint16 i=0;i<this->en;fputc(this->buf[i],this->data),++i);
		this->en=0;
	}
	else
		for(;;)
		{
			jry_bl_int8 c=fgetc(this->data);
			if(c==EOF||(c=='\n'&&this->data==stdin))
				return jry_bl_stream_do(this->nxt,flags);
			this->nxt->buf[this->nxt->en++]=c;
			if((this->nxt->en+1)>this->nxt->size)
				jry_bl_stream_do(this->nxt,0);
		}		
}
jry_bl_stream jry_bl_stream_stdout;
jry_bl_stream jry_bl_stream_stdin;
#endif
