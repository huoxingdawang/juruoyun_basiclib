#include "main.h"
#include <time.h>

int main()
{
	printf("\n--------------------------------" __FILE__ "--------------------------------\n");
	printf("jry_bl_string size:%lld\n",(long long)(sizeof (jry_bl_string)));	
	jry_bl_start();

	jry_bl_string *s1=jry_bl_string_new(),*s2=NULL,*s3=NULL;
//	jry_bl_string *s4=jry_bl_refer(&s1);
	s1=jry_bl_string_add_chars(s1,"-123");
	jry_bl_string_view(s1);
//	jry_bl_string_view(s4);

	s2=jry_bl_string_copy(s1);
	jry_bl_string_view(s2);
	printf("Space ship test:%d\n",jry_bl_string_space_ship(s1,s2));
	s1=jry_bl_string_add_chars(s1,"456");
	printf("Space ship test:%d\n",jry_bl_string_space_ship(s1,s2));

	s1=jry_bl_derefer(s1);

	s3=jry_bl_string_add_double(jry_bl_string_add_string(jry_bl_string_add_chars(jry_bl_string_copy(s1)," 0000 "),s2),-89789.1234);
	s3=jry_bl_string_add_char(s3,'\n');
	s3=jry_bl_string_add_unicode_as_utf8(jry_bl_string_add_unicode_as_utf8(jry_bl_string_add_unicode_as_utf8(s3,0X849f),0X84BB),0X4E91);
	jry_bl_string_view(s3);
	s3=jry_bl_string_add_char(s3,'\n');
	s3=jry_bl_string_add_hex(s3,0XEFFFFF);
	s3=jry_bl_string_add_char(s3,'\n');
	s3=jry_bl_string_add_hex_8bits(s3,0XF);
	
//	jry_bl_gc_view(s1);
//	jry_bl_gc_view(s2);
	jry_bl_string_view(s1);
	jry_bl_string_view(s2);
	jry_bl_string_view(s3);
	
	jry_bl_stream_push_uint64(sout,jry_bl_string_get_uint64(s3));jry_bl_stream_push_char(sout,'\n');
	jry_bl_stream_push_int64(sout,jry_bl_string_get_int64(s3));jry_bl_stream_push_char(sout,'\n');
	jry_bl_stream_push_double(sout,jry_bl_string_get_double(s3));jry_bl_stream_push_char(sout,'\n');
	jry_bl_stream_do(sout,jry_bl_stream_force);
	
#if JRY_BL_STREAM_ENABLE==1
	jry_bl_stream *ss1=jry_bl_string_stream_new(jry_bl_refer(&s1));
	puts("input something");
	jry_bl_stream_connect(jry_bl_stream_stdin,ss1);
	jry_bl_stream_do(jry_bl_stream_stdin,jry_bl_stream_force);
	jry_bl_string_view(s1);
	ss1=jry_bl_stream_free(ss1);
	
#endif
	
	
exit:	
	s1=jry_bl_string_free(s1);s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);
//	s4=jry_bl_string_free(s4);

	jry_bl_stop();
	return 0;
}