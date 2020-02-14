/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
	  http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_rand.h"
#if JRY_BL_RAND_ENABLE==1
#if JRY_BL_RAND_MERSENN==1
jry_bl_uint16 __jry_bl_rand_index;
jry_bl_uint32 __jry_bl_rand_buf[624];

void jry_bl_rand_srand(jry_bl_uint32 seed)
{
	__jry_bl_rand_buf[__jry_bl_rand_index=0]=seed;
	for(jry_bl_uint16 i=1;i<624;++i)
		__jry_bl_rand_buf[i]=(1812433253*(__jry_bl_rand_buf[i-1]^(__jry_bl_rand_buf[i-1]>>30))+i)&0xffffffff;
}

void __jry_bl_rand_generate()
{
	for(jry_bl_uint16 i=0;i<624;i++)
	{
		jry_bl_uint32 y=(__jry_bl_rand_buf[i]&0x80000000)+(__jry_bl_rand_buf[(i+1)%624]&0x7fffffff);
		__jry_bl_rand_buf[i]=__jry_bl_rand_buf[(i+397)%624]^(y>>1);
		if(y&1)__jry_bl_rand_buf[i]^=2567483615;
	}
}

jry_bl_uint32 jry_bl_rand()
{
	if(__jry_bl_rand_index==0)
		__jry_bl_rand_generate();
	jry_bl_uint32 y=__jry_bl_rand_buf[__jry_bl_rand_index];
	y=y^(y>>11);
	y=y^((y<<7)&2636928640);
	y=y^((y<<15)&4022730752);
	y=y^(y>>18);
	__jry_bl_rand_index=(__jry_bl_rand_index+1)%624;
	return y;
}
#else
jry_bl_uint32 __jry_bl_rand_next;
void jry_bl_rand_srand(jry_bl_uint32 seed){__jry_bl_rand_next=seed;}
jry_bl_uint32 jry_bl_rand()
{
	__jry_bl_rand_next=__jry_bl_rand_next*1103515245+12345;
	return((jry_bl_uint32)(__jry_bl_rand_next/65536)%32768);
}
#endif
#endif
