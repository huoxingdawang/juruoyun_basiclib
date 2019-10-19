/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#ifndef __JRY_BL_ARRAY_H
#define __JRY_BL_ARRAY_H
#include "jry_bl_array_config.h"
#ifndef NULL
	#define NULL 0
#endif
#if JRY_BL_ARRAY_USE_IOSTREAM==1
#include <iostream>
#endif
template <typename jry_bl_array_load>
class jry_bl_array
{
	public:
		struct element
		{
			element *nxt,*pre;
			jry_bl_array_load load;			
		};	
	private:
		element *start,*end;
	public:
		jry_bl_array								();
		~jry_bl_array								();
	
#if JRY_BL_ARRAY_USE_IOSTREAM==1
		void 			view					(std::ostream& out=std::cout);
#endif

};
#endif
