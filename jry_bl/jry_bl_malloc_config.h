/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_MALLOC_CONFIG_H
#define __JRY_BL_MALLOC_CONFIG_H
#include "jry_bl_config.h"
#if JRY_BL_MALLOC_ENABLE==1
#include "jry_bl_ying.h"
#define JRY_BL_MALLOC_FAST			1

typedef jry_bl_uint64 jry_bl_malloc_size_type;

#define jry_bl_malloc_fmap_2bits	6
#define jry_bl_malloc_fmap_bits		64	//(1<<jry_bl_malloc_fmap_2bits)
#define jry_bl_malloc_fmap_len		8	//(512/jry_bl_malloc_fmap_bits)
typedef jry_bl_uint64 jry_bl_malloc_fmap_type;


#endif
#endif