/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_BITSET_H
#define __JRY_BL_BITSET_H
#include "jry_bl_bitset_config.h"
#if JRY_BL_BITSET_ENABLE==1
#include "jry_bl_ying.h"
#if  jry_bl_bitset_bits!=32 && jry_bl_bitset_bits!=64
	#error jry_bl_bitset_bits is not 32 or 64
#endif
#if  jry_bl_bitset_bits==32
#define jry_bl_bitset_2bits		5
typedef jry_bl_uint32 jry_bl_bitset_type;
#else
#define jry_bl_bitset_2bits		6
typedef jry_bl_uint64 jry_bl_bitset_type;
#endif
 


#define			jry_bl_bitset_view(bitset,len)	for(int i=0;i<(len);printf("%0 *llX ",jry_bl_bitset_bits/4,(jry_bl_uint64)bitset[i]),++i);putchar('\n')
jry_bl_uint8	jry_bl_highbit				(jry_bl_uint64 a);
jry_bl_uint8	jry_bl_highbit0				(jry_bl_uint64 a);
jry_bl_uint8	jry_bl_highbit32			(jry_bl_uint32 a);
jry_bl_uint8	jry_bl_highbit320			(jry_bl_uint32 a);
void			jry_bl_bitset_init(jry_bl_bitset_type *bitset,jry_bl_uint32 len);
void			jry_bl_bitset_set(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 cnt);
void			jry_bl_bitset_reset(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 cnt);
jry_bl_uint32	jry_bl_bitset_find0(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 len);
jry_bl_uint32	jry_bl_bitset_find1(jry_bl_bitset_type *bitset,jry_bl_uint32 i,jry_bl_uint32 len);


#endif
#endif
