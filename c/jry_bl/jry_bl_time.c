/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jry_bl_time.h"
#if JRY_BL_TIME_ENABLE==1
inline void jry_bl_time_init	(jry_bl_time *this){this->s=0;this->ms=0;}
inline void jry_bl_time_free	(jry_bl_time *this){this->s=0;this->ms=0;}
inline void jry_bl_time_clear	(jry_bl_time *this){this->s=0;this->ms=0;}
inline void jry_bl_time_now		(jry_bl_time *this){struct timeb t;ftime(&t);this->s=t.time;this->ms=t.millitm;}


#if JRY_BL_USE_STDARG==1
inline void	jry_bl_time_inits(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_time_init(va_arg(valist,jry_bl_time*));va_end(valist);}
inline void jry_bl_time_frees(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_time_free(va_arg(valist,jry_bl_time*));va_end(valist);}
inline void jry_bl_time_clears(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_time_clear(va_arg(valist,jry_bl_time*));va_end(valist);}
#endif
#endif
