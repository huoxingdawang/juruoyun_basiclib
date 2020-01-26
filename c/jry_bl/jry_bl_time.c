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
jry_bl_int8		jry_bl_time_time_zone=JRY_BL_TIME_DEFAULT_TIME_ZONE;
inline void 	jry_bl_time_init	(jry_bl_time *this){*this=0;}
inline void 	jry_bl_time_free	(jry_bl_time *this){*this=0;}
inline void 	jry_bl_time_clear	(jry_bl_time *this){*this=0;}
inline void 	jry_bl_time_now		(jry_bl_time *this){struct timeb t;ftime(&t);(*this)=(((jry_bl_int64)t.time)*1000)+(t.millitm);}
jry_bl_uint8 jry_bl_time_if_leap_year		(jry_bl_uint32 year);
jry_bl_uint8 jry_bl_time_get_day_of_month	(jry_bl_uint8 month,jry_bl_uint32 year);
jry_bl_uint8 jry_bl_time_get_weekday		(jry_bl_uint8 day,jry_bl_uint8 month,jry_bl_uint32 year);
inline jry_bl_uint8 jry_bl_time_if_leap_year	(jry_bl_uint32 year){return (((year%400)==0)?1:(((year%100)==0)?0:(((year%4)==0)?1:0)));}
inline jry_bl_uint8 jry_bl_time_get_day_of_month(jry_bl_uint8 month,jry_bl_uint32 year){static const jry_bl_uint8 dpm[12]={31,28,31,30,31,30,31,31,30,31,30,31};return (month==2||(month==0)||(month>12))?(dpm[1]+jry_bl_time_if_leap_year(year)):(dpm[month-1]);}
inline jry_bl_uint8 jry_bl_time_get_weekday		(jry_bl_uint8 day,jry_bl_uint8 month,jry_bl_uint32 year){if((month==1)||(month==2))month+=12,year--;return (day+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7+1;}
jry_bl_uint8 		jry_bl_time_if_dst			(jry_bl_uint8 day,jry_bl_uint8 month,jry_bl_uint32 year)
{
	if(jry_bl_time_time_zone==JRY_BL_TIME_ZONE_ASIA_SHANGHAI)
	{
		
		
		
	}
	
}
void jry_bl_time_to_string(jry_bl_time *this,jry_bl_string *result)
{
	jry_bl_int64 ts=jry_bl_time_to_unix(this);
	int year=0,month=0,day=0,hour=0,minute=0,second=0,ms=0,days=0,dayTmp=0,secs=0;
	jry_bl_string_extend(result,21);
	if(jry_bl_time_time_zone==JRY_BL_TIME_ZONE_ASIA_SHANGHAI)
		ts+=8*3600000;
	if(ts>0)
	{
		ms=ts%1000,ts/=1000,days=ts/86400,secs=ts%86400;
		for(year=1970;days>0;++year)
			if(days>=(dayTmp=(365+jry_bl_time_if_leap_year(year))))
				days-=dayTmp;
			else
				break;
		for(month=1;month<12;++month)
			if(days>=(dayTmp=jry_bl_time_get_day_of_month(month,year)))
				days-=dayTmp;
			else
				break;
		month=month,day=days+1;
	}
	else
	{
		ms=(1000-(-ts)%1000),ts=((ts-(1000-ms))/1000),((ms==1000)?(ms=0):0),secs=-(ts%86400),secs=(secs==0)?0:(86400-secs),days=(ts-secs)/86400;
		for(year=1969;days<0;--year)
			if((-days)>=(dayTmp=(365+jry_bl_time_if_leap_year(year))))
				days+=dayTmp;
			else
				break;
		for(month=12;month>0;--month)
			if(days<(dayTmp=jry_bl_time_get_day_of_month(month,year)))
				days+=dayTmp;
			else
				break;
		if(days>jry_bl_time_get_day_of_month(month+1,year))
			++month,days-=jry_bl_time_get_day_of_month(month,year);
		month=month+1,day=days+1;
	}
	
	
	hour=secs/3600,secs%=3600,minute=secs/60,second=secs%60;
	jry_bl_string_add_uint64_length(result,year,4,'0');
	jry_bl_string_add_char1(result,'-');
	jry_bl_string_add_uint64_length(result,month,2,'0');
	jry_bl_string_add_char1(result,'-');
	jry_bl_string_add_uint64_length(result,day,2,'0');
	jry_bl_string_add_char1(result,' ');
	jry_bl_string_add_uint64_length(result,hour,2,'0');
	jry_bl_string_add_char1(result,':');
	jry_bl_string_add_uint64_length(result,minute,2,'0');
	jry_bl_string_add_char1(result,':');
	jry_bl_string_add_uint64_length(result,second,2,'0');
	jry_bl_string_add_char1(result,'.');
	jry_bl_string_add_uint64_length(result,ms,3,'0');
	jry_bl_string_add_char1(result,' ');
	
	jry_bl_string_add_uint64_length(result,jry_bl_time_get_weekday(day,month,year),1,'0');
}



#if JRY_BL_USE_STDARG==1
inline void	jry_bl_time_inits(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_time_init(va_arg(valist,jry_bl_time*));va_end(valist);}
inline void jry_bl_time_frees(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_time_free(va_arg(valist,jry_bl_time*));va_end(valist);}
inline void jry_bl_time_clears(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jry_bl_time_clear(va_arg(valist,jry_bl_time*));va_end(valist);}
#endif
#endif
