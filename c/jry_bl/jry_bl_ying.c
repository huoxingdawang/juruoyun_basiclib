/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_ying.h"
#if JRY_BL_YING_ENABLE==1
inline jry_bl_int64 jry_bl_ceil(long double i)
{
	return (((jry_bl_int64)i)==i)?((jry_bl_int64)i):(((jry_bl_int64)i)+1);
}
jry_bl_uint8 jry_bl_get_uint64_length(jry_bl_uint64 tmp)
{
	jry_bl_uint8 len=0;
	do{++len;}while(tmp=(((jry_bl_uint64)tmp)/10));	
	return len;
}
jry_bl_uint8 jry_bl_get_int64_length(jry_bl_int64 tmp)
{
	jry_bl_uint8 len=0;
	if(tmp<0)
		tmp=-tmp,++len;
	do{++len;}while(tmp=(((jry_bl_uint64)tmp)/10));	
	return len;
}
jry_bl_uint8 jry_bl_get_double_length(double tmp)
{
	jry_bl_uint8 len=1;
	len+=jry_bl_get_int64_length(tmp);
	if(tmp<0)
		tmp=-tmp;
	tmp-=(jry_bl_uint64)tmp;
	jry_bl_uint64 ji=10;
	for(double t=tmp*ji;t-(jry_bl_uint64)t<(-0.0000001)||t-(jry_bl_uint64)t>(0.0000001);ji=(ji<<3)+(ji<<1),t=tmp*ji);
	len+=jry_bl_get_uint64_length(tmp*ji);
	return len;
}
jry_bl_uint8 jry_bl_highbit(jry_bl_uint64 a)
{
	jry_bl_uint8 b=-1;
	while(a)++b,a>>=1;
	return b;
}
#endif
