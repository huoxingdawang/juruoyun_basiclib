/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JBL_BITSET_H
#define __JBL_BITSET_H
#include "jbl_bitset_config.h"
#if JBL_BITSET_ENABLE==1
#include "jbl_ying.h"
#if  jbl_bitset_bits!=32 && jbl_bitset_bits!=64
	#error jbl_bitset_bits is not 32 or 64
#endif
#if  jbl_bitset_bits==32
#define jbl_bitset_2bits		5
typedef jbl_uint32 jbl_bitset_type;
#else
#define jbl_bitset_2bits		6
typedef jbl_uint64 jbl_bitset_type;
#endif
 


#define			jbl_bitset_view(bitset,len)	for(int i=0;i<(len);printf("%0*llX ",jbl_bitset_bits/4,(jbl_uint64)bitset[i]),++i);putchar('\n')
jbl_uint8	jbl_highbit				(jbl_uint64 a);
jbl_uint8	jbl_highbit0				(jbl_uint64 a);
jbl_uint8	jbl_highbit32			(jbl_uint32 a);
jbl_uint8	jbl_highbit320			(jbl_uint32 a);
void			jbl_bitset_init(jbl_bitset_type *bitset,jbl_uint32 len);
void			jbl_bitset_set(jbl_bitset_type *bitset,jbl_uint32 i,jbl_uint32 cnt);
void			jbl_bitset_reset(jbl_bitset_type *bitset,jbl_uint32 i,jbl_uint32 cnt);
jbl_uint32	jbl_bitset_find0(jbl_bitset_type *bitset,jbl_uint32 i,jbl_uint32 len);
jbl_uint32	jbl_bitset_find1(jbl_bitset_type *bitset,jbl_uint32 i,jbl_uint32 len);


#endif
#endif
