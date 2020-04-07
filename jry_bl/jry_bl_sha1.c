/* Copyright (c) [2019] juruoyun developer team
	 Juruoyun basic lib is licensed under the Mulan PSL v1.
	 You can use this software according to the terms and conditions of the Mulan PSL v1.
	 You may obtain a copy of Mulan PSL v1 at:
			http://license.coscl.org.cn/MulanPSL
	 THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
	 IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
	 PURPOSE.
	 See the Mulan PSL v1 for more details.*/
#include "jry_bl_sha1.h"
#if JRY_BL_SHA1_ENABLE==1
#include "jry_bl_exception.h"
#include "jry_bl_malloc.h"
#include "jry_bl_string.h"
#include "jry_bl_ying.h"
void __jry_bl_sha1_process(jry_bl_uint32 hb[5],jry_bl_uint32 *mbc,jry_bl_uint8 mb[64])
{
	const jry_bl_uint32 K[]={0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6};
	jry_bl_uint32 W[80],A,B,C,D,E,tmp;
	for(register jry_bl_uint8 t=0;t<16;W[t]=mb[t*4]<<24,W[t]|=mb[t*4+1]<<16,W[t]|=mb[t*4+2]<<8,W[t]|=mb[t*4+3],++t);
	for(register jry_bl_uint8 t=16;t<80;tmp=W[t-3]^W[t-8]^W[t-14]^W[t-16],W[t]=((tmp<<1)|(tmp>>31)),++t);
	A=hb[0],B=hb[1],C=hb[2],D=hb[3],E=hb[4];
	for(register jry_bl_uint8 t=0;t<20;tmp=((A<<5)|(A>>27))+((B&C)|((~B)&D))+E+W[t]+K[0],E=D,D=C,C=((B<<30)|(B>>2)),B=A,A=tmp,++t);	
	for(register jry_bl_uint8 t=20;t<40;tmp=((A<<5)|(A>>27))+(B^C^D)+E+W[t]+K[1],E=D,D=C,C=((B<<30)|(B>>2)),B=A,A=tmp,++t);
	for(register jry_bl_uint8 t=40;t<60;tmp=((A<<5)|(A>>27))+((B&C)|(B&D)|(C&D))+E+W[t]+K[2],E=D,D=C,C=((B<<30)|(B>>2)),B=A,A=tmp,++t);
	for(register jry_bl_uint8 t=60;t<80;tmp=((A<<5)|(A>>27))+(B^C^D)+E+W[t]+K[3],E=D,D=C,C=((B<<30)|(B>>2)),B=A,A=tmp,++t);
	hb[0]+=A,hb[1]+=B,hb[2]+=C,hb[3]+=D,hb[4]+=E;
	(*mbc)=0;
}
jry_bl_string* jry_bl_sha1(const jry_bl_string* this,jry_bl_string* out)
{
	if(this==NULL)jry_bl_exception(JRY_BL_ERROR_NULL_POINTER);
	const jry_bl_string *this_=jry_bl_refer_pull(this);	
	jry_bl_string_size_type	size=jry_bl_string_get_length(this_);
	jry_bl_uint8 			*input=jry_bl_string_get_chars(this_),mb[64];
	jry_bl_uint32			hb[5]={0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476,0xC3D2E1F0},mbc=0,ll=0,lh=0;
	out=jry_bl_string_extend(out,40);
	while(size--)
	{
		mb[mbc++]=(*input&0xFF);
		ll+=8;
		if(ll==0)
			lh++;
		if(mbc==64)
			__jry_bl_sha1_process(hb,&mbc,mb);
		input++;
	}
	if(mbc>55)
	{
		mb[mbc++]=0x80;
		while(mbc<64)
			mb[mbc++]=0;
		__jry_bl_sha1_process(hb,&mbc,mb);
		while(mbc<56)
			mb[mbc++]=0;
	}
	else
	{
		mb[mbc++]=0x80;
		while(mbc<56)
			mb[mbc++]=0;
	}
	mb[56]=lh>>24,mb[57]=lh>>16,mb[58]=lh>>8,mb[59]=lh;
	mb[60]=ll>>24,mb[61]=ll>>16,mb[62]=ll>>8,mb[63]=ll;
	__jry_bl_sha1_process(hb,&mbc,mb);
	for(register jry_bl_uint8 i=0;i<20;mbc=hb[i>>2]>>8*(3-(i&0x03)),out=jry_bl_string_add_hex_8bits(out,mbc),++i);
	return out;
}

#endif