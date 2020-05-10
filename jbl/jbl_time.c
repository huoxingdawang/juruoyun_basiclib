/* Copyright (c) [2019] juruoyun developer team
   Juruoyun basic lib is licensed under the Mulan PSL v1.
   You can use this software according to the terms and conditions of the Mulan PSL v1.
   You may obtain a copy of Mulan PSL v1 at:
      http://license.coscl.org.cn/MulanPSL
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
   PURPOSE.
   See the Mulan PSL v1 for more details.*/
#include "jbl_time.h"
#if JBL_TIME_ENABLE==1
jbl_int8		jbl_time_time_zone=JBL_TIME_DEFAULT_TIME_ZONE;
inline void 	jbl_time_init	(jbl_time *this){*this=0;}
inline void 	jbl_time_free	(jbl_time *this){*this=0;}
inline void 	jbl_time_clear	(jbl_time *this){*this=0;}
inline void 	jbl_time_now		(jbl_time *this){struct timeb t;ftime(&t);(*this)=(((jbl_int64)t.time)*1000)+(t.millitm);}
jbl_uint8 jbl_time_if_leap_year		(jbl_uint32 year);
jbl_uint8 jbl_time_get_day_of_month	(jbl_uint8 month,jbl_uint32 year);
jbl_uint8 jbl_time_get_weekday		(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year);
inline jbl_uint8 jbl_time_if_leap_year	(jbl_uint32 year){return (((year%400)==0)?1:(((year%100)==0)?0:(((year%4)==0)?1:0)));}
inline jbl_uint8 jbl_time_get_day_of_month(jbl_uint8 month,jbl_uint32 year){static const jbl_uint8 dpm[12]={31,28,31,30,31,30,31,31,30,31,30,31};return (month==2||(month==0)||(month>12))?(dpm[1]+jbl_time_if_leap_year(year)):(dpm[month-1]);}
inline jbl_uint8 jbl_time_get_weekday		(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year){if((month==1)||(month==2))month+=12,year--;return (day+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7+1;}
jbl_uint8 		jbl_time_if_dst			(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year)
{
	if(jbl_time_time_zone==JBL_TIME_ZONE_ASIA_SHANGHAI)
	{
		
		
		
	}
	
}
#if JBL_STRING_ENABLE==1
void jbl_time_to_string(jbl_time *this,jbl_string *result)
{
	jbl_int64 ts=jbl_time_to_unix(this);
	int year=0,month=0,day=0,hour=0,minute=0,second=0,ms=0,days=0,dayTmp=0,secs=0;
	jbl_string_extend(result,21);
	if(jbl_time_time_zone==JBL_TIME_ZONE_ASIA_SHANGHAI)
		ts+=8*3600000;
	if(ts>0)
	{
		ms=ts%1000,ts/=1000,days=ts/86400,secs=ts%86400;
		for(year=1970;days>0;++year)
			if(days>=(dayTmp=(365+jbl_time_if_leap_year(year))))
				days-=dayTmp;
			else
				break;
		for(month=1;month<12;++month)
			if(days>=(dayTmp=jbl_time_get_day_of_month(month,year)))
				days-=dayTmp;
			else
				break;
		month=month,day=days+1;
	}
	else
	{
		ms=(1000-(-ts)%1000),ts=((ts-(1000-ms))/1000),((ms==1000)?(ms=0):0),secs=-(ts%86400),secs=(secs==0)?0:(86400-secs),days=(ts-secs)/86400;
		for(year=1969;days<0;--year)
			if((-days)>=(dayTmp=(365+jbl_time_if_leap_year(year))))
				days+=dayTmp;
			else
				break;
		for(month=12;month>0;--month)
			if(days<(dayTmp=jbl_time_get_day_of_month(month,year)))
				days+=dayTmp;
			else
				break;
		if(days>jbl_time_get_day_of_month(month+1,year))
			++month,days-=jbl_time_get_day_of_month(month,year);
		month=month+1,day=days+1;
	}
	
	
	hour=secs/3600,secs%=3600,minute=secs/60,second=secs%60;
	jbl_string_add_uint64_length(result,year,4,'0');
	jbl_string_add_char1(result,'-');
	jbl_string_add_uint64_length(result,month,2,'0');
	jbl_string_add_char1(result,'-');
	jbl_string_add_uint64_length(result,day,2,'0');
	jbl_string_add_char1(result,' ');
	jbl_string_add_uint64_length(result,hour,2,'0');
	jbl_string_add_char1(result,':');
	jbl_string_add_uint64_length(result,minute,2,'0');
	jbl_string_add_char1(result,':');
	jbl_string_add_uint64_length(result,second,2,'0');
	jbl_string_add_char1(result,'.');
	jbl_string_add_uint64_length(result,ms,3,'0');
	jbl_string_add_char1(result,' ');
	
	jbl_string_add_uint64_length(result,jbl_time_get_weekday(day,month,year),1,'0');
}
#endif



#if JBL_USE_STDARG==1
inline void	jbl_time_inits(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_time_init(va_arg(valist,jbl_time*));va_end(valist);}
inline void jbl_time_frees(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_time_free(va_arg(valist,jbl_time*));va_end(valist);}
inline void jbl_time_clears(int n,...)	{va_list valist;va_start(valist,n);for(int i=0;i<n;i++)jbl_time_clear(va_arg(valist,jbl_time*));va_end(valist);}
#endif
#endif
