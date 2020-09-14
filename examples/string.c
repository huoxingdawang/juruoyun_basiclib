#include "main.h"
#include <time.h>

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_string *s1=jbl_string_new(),*s2=NULL,*s3=NULL,*s4=NULL;
//	jbl_string *s4=jbl_refer(&s1);
	s1=jbl_string_add_const(s1,UC"-123");
	jbl_string_view(s1);
//	jbl_string_view(s4);

	s2=jbl_string_copy(s1);
	jbl_string_view(s2);
	pchars("Space ship test:"),pint(jbl_string_space_ship(s1,s2)),pchar('\n');
	s1=jbl_string_add_chars(s1,UC"456");
	jbl_string_view(s1);
	pchars("Space ship test:"),pint(jbl_string_space_ship(s1,s2)),pchar('\n');

	s1=jbl_derefer(s1);

	s3=jbl_string_add_double(jbl_string_add_string(jbl_string_add_chars(jbl_string_copy(s1),UC" 0000"),s2),-89789.01234);
	s3=jbl_string_add_char(s3,'\n');
	s3=jbl_string_add_utf8_from_unicode(jbl_string_add_utf8_from_unicode(jbl_string_add_utf8_from_unicode(s3,0X849f),0X84BB),0X4E91);
	jbl_string_view(s3);
	s3=jbl_string_add_char(s3,'\n');
	s3=jbl_string_add_hex(s3,0XEFFFFF);
	s3=jbl_string_add_char(s3,'\n');
	s3=jbl_string_add_hex_8bits(s3,0XF);
//	jbl_gc_view(s1);
//	jbl_gc_view(s2);
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_string_view(s3);
	
	jbl_stream_push_uint(jbl_stream_stdout,jbl_string_get_uint(s3));jbl_stream_push_char(jbl_stream_stdout,'\n');
	jbl_stream_push_int(jbl_stream_stdout,jbl_string_get_int(s3));jbl_stream_push_char(jbl_stream_stdout,'\n');
	jbl_stream_push_double(jbl_stream_stdout,jbl_string_get_double(s3));jbl_stream_push_char(jbl_stream_stdout,'\n');
	jbl_stream_do(jbl_stream_stdout,jbl_stream_force);
	
	
	
	s1=jbl_string_read(s1,UC"input:");
	jbl_string_view(s1);
	s1=jbl_string_to_upper_case(s1);
	jbl_string_view(s1);
	s1=jbl_string_to_lower_case(s1);
	jbl_string_view(s1);
	
#if JBL_JSON_ENABLE==1
	s4=jbl_string_json_encode(s1,NULL,0,0);
	jbl_string_view(s4);
#endif
#if JBL_LL_ENABLE==1
	jbl_ll *l1=jbl_string_cut(s4,NULL,'3');
	jbl_ll_view(l1);
	l1=jbl_ll_free(l1);
#endif
//exit:	
	s1=jbl_string_free(s1);
	s2=jbl_string_free(s2);
	s3=jbl_string_free(s3);
	s4=jbl_string_free(s4);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}