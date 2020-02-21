/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_bitset.h"
#if JRY_BL_BITSET_ENABLE==1
jry_bl_uint8 jry_bl_highbit(jry_bl_uint64 a)
{
	jry_bl_uint32 b=-1;
	if(a>=0X80000000)	b+=32	,a>>=32;
	if(a>=0X8000)		b+=16	,a>>=16;
	if(a>=0X80)			b+=8	,a>>=8;
	if(a>=0X8)			b+=4	,a>>=4;
	if(a>=0X4)			b+=2	,a>>=2;
	if(a>=0X2)			b+=1	,a>>=1;
	if(a>=0X1)			b+=1;
//	while(a)++b,a>>=1;
	return b;
}
jry_bl_uint8 jry_bl_highbit0(jry_bl_uint64 a)
{
	a=~a;
	jry_bl_uint32 b=-1;
	if(a>=0X80000000)	b+=32	,a>>=32;
	if(a>=0X8000)		b+=16	,a>>=16;
	if(a>=0X80)			b+=8	,a>>=8;
	if(a>=0X8)			b+=4	,a>>=4;
	if(a>=0X4)			b+=2	,a>>=2;
	if(a>=0X2)			b+=1	,a>>=1;
	if(a>=0X1)			b+=1;
	return b;
}
jry_bl_uint8 jry_bl_highbit32(jry_bl_uint32 a)
{
	jry_bl_uint32 b=-1;
	if(a>=0X8000)		b+=16	,a>>=16;
	if(a>=0X80)			b+=8	,a>>=8;
	if(a>=0X8)			b+=4	,a>>=4;
	if(a>=0X4)			b+=2	,a>>=2;
	if(a>=0X2)			b+=1	,a>>=1;
	if(a>=0X1)			b+=1;
	return b;
}
jry_bl_uint8 jry_bl_highbit320(jry_bl_uint32 a)
{
	a=~a;
	jry_bl_uint32 b=-1;
	if(a>=0X8000)		b+=16	,a>>=16;
	if(a>=0X80)			b+=8	,a>>=8;
	if(a>=0X8)			b+=4	,a>>=4;
	if(a>=0X4)			b+=2	,a>>=2;
	if(a>=0X2)			b+=1	,a>>=1;
	if(a>=0X1)			b+=1;
	return b;
}
#define	slm(a,b)	(((b)>=64)?0:((a)<<(b)))
#if jry_bl_bitset_bits==32
#define hb(x)	jry_bl_highbit32(x)
#define hb0(x)	jry_bl_highbit320(x)
#else 
#define hb(x)	jry_bl_highbit(x)
#define hb0(x)	jry_bl_highbit0(x)
#endif
inline void jry_bl_bitset_init(jry_bl_bitset_type *bitset,jry_bl_uint32 len)
{
	while(len--)
		bitset[len]=0;
}
void jry_bl_bitset_set(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 cnt)
{
	jry_bl_uint32 start_page=(i>>jry_bl_bitset_2bits);
	jry_bl_uint32 end_page=((cnt+i-1)>>jry_bl_bitset_2bits);
	cnt=cnt+i-1-(end_page<<jry_bl_bitset_2bits);
	i-=(start_page<<jry_bl_bitset_2bits);
	if(start_page==end_page)
		{bitset[start_page]|=slm(slm(1LL,(cnt+1-i))-1,(jry_bl_bitset_bits-cnt-1));return;}
	bitset[start_page]|=(slm(1LL,(jry_bl_bitset_bits-i))-1);
	++start_page;
	while(start_page<end_page)bitset[start_page]=-1,++start_page;
	bitset[end_page]|=slm((slm(1LL,(cnt+1))-1),(jry_bl_bitset_bits-cnt-1));	
}
void jry_bl_bitset_reset(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 cnt)
{
	jry_bl_uint32 start_page=(i>>jry_bl_bitset_2bits);
	jry_bl_uint32 end_page=((cnt+i-1)>>jry_bl_bitset_2bits);
	cnt=cnt+i-1-(end_page<<jry_bl_bitset_2bits);
	i-=(start_page<<jry_bl_bitset_2bits);
	if(start_page==end_page)
		{bitset[start_page]&=~slm(slm(1LL,(cnt+1-i))-1,(jry_bl_bitset_bits-cnt-1));return;}
	bitset[start_page]&=~(slm(1LL,(jry_bl_bitset_bits-i))-1);
	++start_page;
	while(start_page<end_page)bitset[start_page]=0,++start_page;
	bitset[end_page]&=~slm((slm(1LL,(cnt+1))-1),(jry_bl_bitset_bits-cnt-1));	
}
jry_bl_uint32 jry_bl_bitset_find0(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 len)
{
	jry_bl_uint32 p=(i>>jry_bl_bitset_2bits);
	i-=(p<<jry_bl_bitset_2bits);	
	jry_bl_bitset_type tmp;
	tmp=bitset[p];
	tmp|=slm((slm(1LL,(i))-1),(jry_bl_bitset_bits-i));
	if(tmp!=-1)
		return ((jry_bl_uint32)p<<jry_bl_bitset_2bits)+jry_bl_bitset_bits-hb0(tmp)-1;
	++p;
	while(bitset[p]==-1&&p<=len)++p;
	if(p>=(len))
		return (len<<jry_bl_bitset_2bits);
	return ((jry_bl_uint32)p<<jry_bl_bitset_2bits)+jry_bl_bitset_bits-hb0(bitset[p])-1;
}
jry_bl_uint32 jry_bl_bitset_find1(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 len)
{
	jry_bl_uint32 p=(i>>jry_bl_bitset_2bits);
	i-=(p<<jry_bl_bitset_2bits);	
	jry_bl_bitset_type tmp;
	tmp=bitset[p];
	tmp&=(slm(1LL,(jry_bl_bitset_bits-i))-1);
	if(tmp!=0)
		return ((jry_bl_uint32)p<<jry_bl_bitset_2bits)+jry_bl_bitset_bits-hb(tmp)-1;
	++p;
	while(bitset[p]==0&&p<=len)++p;	
	if(p>=(len))
		return (len<<jry_bl_bitset_2bits);
	return ((jry_bl_uint32)p<<jry_bl_bitset_2bits)+jry_bl_bitset_bits-hb(bitset[p])-1;
}
#undef slm
#undef hb
#undef hb0
#endif
