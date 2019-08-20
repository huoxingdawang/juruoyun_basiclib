#include "jry_bl_string.h"
int jry_bl_string_init(jry_bl_string *s)
{
	if(s->len!=0||s->size!=0||s->size!=0)
		return 0;
	s->len=0;
	s->size=JRY_BL_STRING_BASIC_LENGTH;
	s->s=(char *)malloc(s->size);
	if(s->s==NULL)
		return 0;	
	return 1;
}
int jry_bl_string_init_by_length(jry_bl_string *s,JRY_BL_STRING_SIZE_TYPE size)
{
	if(s->len!=0||s->size!=0||s->size!=0)
		return 0;
	s->len=0;
	s->size=size;
	s->s=(char *)malloc(s->size);
	if(s->s==NULL)
		return 0;		
	return 1;
}
int jry_bl_string_init_by_string(jry_bl_string *s,char *in)
{
	if(s->len!=0||s->size!=0||s->size!=0)
		return 0;
	s->len=strlen(in);
	s->size=(ceil((long double)s->len/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
	s->s=(char *)malloc(s->size);
	stpcpy(s->s,in);
	return 1;
}
int jry_bl_string_deinit(jry_bl_string *s)
{
	free(s->s);
	s->s=NULL;
	s->size=0;
	s->len=0;
}
int jry_bl_string_view(jry_bl_string *s,FILE * file)
{
	fprintf(file,"len:\t%lld\nsize:\t%lld\ns:\t%s\n",(long long)s->len,(long long)s->size,s->s);
}
int jry_bl_string_link(jry_bl_string *s,jry_bl_string *s2)
{
	if((s->len+s2->len)>s->size)
	{
		s->size=(ceil((double)(s->len+s2->len)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		char * sb=realloc(s->s,s->size);
		if(sb==NULL)
			return 0;
		s->s=sb;
	}
	for(int i=0;i<s2->len;i++)
		s->s[s->len+i]=s2->s[i];
	s->len=(s->len+s2->len);
	s->s[s->len]=0;
	return 1;
}
int jry_bl_string_add(jry_bl_string *s,char * s2)
{
	int s2_len=strlen(s2);
	if((s->len+s2_len)>s->size)
	{
		s->size=(ceil((double)(s->len+s2_len)/JRY_BL_STRING_BASIC_LENGTH))*JRY_BL_STRING_BASIC_LENGTH;
		char * sb=realloc(s->s,s->size);
		if(sb==NULL)
			return 0;
		s->s=sb;
	}
	for(int i=0;i<s2_len;i++)
		s->s[s->len+i]=s2[i];	
	s->len=(s->len+s2_len);
	s->s[s->len]=0;
	return 1;
}
long long jry_bl_string_string_to_int(jry_bl_string *s,int start)
{
	register int f,i;register char c;register long long x=0;
	for (f=0,i=start;(c=s->s[i])<'0'||c>'9'&&i<s->len;f=c=='-',++i);
	for (x=c-'0',++i; (c=s->s[i])>='0'&&c<='9'&&i<s->len; x=(x<<3)+(x<<1)+c-'0',++i);
	return f?-x:x;
}
int jry_bl_string_int_to_string(jry_bl_string *s,long long in)
{
	register int f=(in<0),cnt=20;
	char b[21];
	if(f)
		in=-in;
	b[cnt--]=0;
	while(in)
	{
		b[cnt--]=in%10+'0';
		in/=10;
	}
	if(f)
		b[cnt--]='-';
	jry_bl_string_add(s,b+cnt+1);
	return 1;
}

