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
#include <sys/timeb.h>
#if JBL_VAR_ENABLE==1
#include "jbl_var.h"
#endif
#if JBL_STRING_ENABLE==1
#include "jbl_string.h"
#endif
jbl_int8		jbl_time_time_zone=JBL_TIME_DEFAULT_TIME_ZONE;
inline jbl_time * jbl_time_new()
{
	return jbl_time_init(jbl_malloc(sizeof(jbl_time)));
}
inline jbl_time * jbl_time_init(jbl_time *this)
{
	jbl_gc_init(this);
	jbl_gc_plus(this);
	this->t=0;
	return this;
}
inline jbl_time * jbl_time_free(jbl_time *this)
{
	if(this==NULL)return NULL;
	jbl_gc_minus(this);
	if(!jbl_gc_reference_cnt(this))
	{
		((jbl_gc_is_ref(this))?jbl_time_free((jbl_time *)jbl_refer_pull(this)):0);
#if JBL_VAR_ENABLE==1
		if(jbl_gc_is_var(this))
			jbl_free((char*)this-sizeof(jbl_var));
		else
#endif
			jbl_free(this);
	}
	return NULL;
}
inline jbl_time * jbl_time_set(jbl_time * this,jbl_uint64 time)
{
	if(!this)this=jbl_time_new();
	((jbl_time *)(jbl_refer_pull(this)))->t=time;
	return this;
}
inline jbl_time * jbl_time_copy(jbl_time * that)
{
	return jbl_time_set(NULL,((jbl_time*)jbl_refer_pull(that))->t);
}
inline jbl_time * jbl_time_now(jbl_time *this)
{
	struct timeb t;
	ftime(&t);
	return jbl_time_set(this,(((jbl_int64)t.time)*1000)+(t.millitm));
	return this;
}
inline char jbl_time_space_ship(jbl_time *this,jbl_time *that)
{
	jbl_uint64 t=jbl_time_minus(this,that);
	return (t>0)?1:((t<0)?(-1):0);
}
inline jbl_uint8	jbl_time_if_leap_year		(jbl_uint32 year){return (((year%400)==0)?1:(((year%100)==0)?0:(((year%4)==0)?1:0)));}
inline jbl_uint8	jbl_time_get_day_of_month	(jbl_uint8 month,jbl_uint32 year){static const jbl_uint8 dpm[12]={31,28,31,30,31,30,31,31,30,31,30,31};return (month==2||(month==0)||(month>12))?(dpm[1]+jbl_time_if_leap_year(year)):(dpm[month-1]);}
inline jbl_uint8	jbl_time_get_weekday		(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year){if((month==1)||(month==2))month+=12,year--;return (day+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7+1;}
jbl_uint8 jbl_time_if_dst(jbl_uint8 day,jbl_uint8 month,jbl_uint32 year)
{
	if(jbl_time_time_zone==JBL_TIME_ZONE_ASIA_SHANGHAI)
	{
		
		
		
	}
	
}

#if JBL_STRING_ENABLE==1
jbl_string * jbl_time_to_string(const jbl_time *this,jbl_string *result)
{
	jbl_int64 ts=jbl_time_to_unix(this);
	int year=0,month=0,day=0,hour=0,minute=0,second=0,ms=0,days=0,dayTmp=0,secs=0;
	result=jbl_string_extend(result,64);
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
	result=jbl_string_add_uint64_length(result,year,4,'0');
	result=jbl_string_add_char(result,'-');
	result=jbl_string_add_uint64_length(result,month,2,'0');
	result=jbl_string_add_char(result,'-');
	result=jbl_string_add_uint64_length(result,day,2,'0');
	result=jbl_string_add_char(result,' ');
	result=jbl_string_add_uint64_length(result,hour,2,'0');
	result=jbl_string_add_char(result,':');
	result=jbl_string_add_uint64_length(result,minute,2,'0');
	result=jbl_string_add_char(result,':');
	result=jbl_string_add_uint64_length(result,second,2,'0');
	result=jbl_string_add_char(result,'.');
	result=jbl_string_add_uint64_length(result,ms,3,'0');
	result=jbl_string_add_char(result,' ');
	
	result=jbl_string_add_uint64_length(result,jbl_time_get_weekday(day,month,year),1,'0');
	return result;
}
inline jbl_string* jbl_time_json_encode(const jbl_time* this,jbl_string *out,char format,jbl_int32 tabs)
{
	jbl_string *s1=jbl_time_to_string(this,NULL);
	out=jbl_string_json_encode(s1,out,format,tabs);
	jbl_string_free(s1);
	return out;
}
#endif


#if JBL_VAR_ENABLE==1
const jbl_var_operators jbl_time_operators={
	(void* (*)(void *))jbl_time_free,
	(void* (*)(void *))jbl_time_copy,
	(char  (*)(const void*,const void*))jbl_time_space_ship,
	(jbl_string*(*)(const void*,jbl_string *,char,jbl_int32))jbl_time_json_encode,
#if JBL_STREAM_ENABLE==1
	/*(void(*)(const void*,jbl_stream *,jbl_int32,char*,jbl_int32))jbl_time_view_put*/NULL,
	/*(void(*)(const void*,jbl_stream *,char,jbl_int32))jbl_time_json_put*/NULL,
#endif
};
jbl_var * jbl_Vtime_new()
{
	jbl_var *this=(jbl_var*)((char*)(jbl_malloc((sizeof(jbl_time))+(sizeof(jbl_var)))+(sizeof(jbl_var))));
	jbl_time_init($jbl_time(this));
	jbl_gc_set_var($jbl_time(this));
	jbl_var_set_operators(this,&jbl_time_operators);
	return this;
}
#endif
#endif
