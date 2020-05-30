#include "main.h"
#include <time.h>

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_string *s1=jbl_string_new(),*s2=NULL,*s3=NULL;
//	jbl_string *s4=jbl_refer(&s1);
	s1=jbl_string_add_chars(s1,UC"-123");
	jbl_string_view(s1);
//	jbl_string_view(s4);

	s2=jbl_string_copy(s1);
	jbl_string_view(s2);
	pchars("Space ship test:"),pint(jbl_string_space_ship(s1,s2)),pchar('\n');
	s1=jbl_string_add_chars(s1,UC"456");
	pchars("Space ship test:"),pint(jbl_string_space_ship(s1,s2)),pchar('\n');

	s1=jbl_derefer(s1);

	s3=jbl_string_add_double(jbl_string_add_string(jbl_string_add_chars(jbl_string_copy(s1),UC" 0000"),s2),-89789.01234);
	s3=jbl_string_add_char(s3,'\n');
	s3=jbl_string_add_unicode_as_utf8(jbl_string_add_unicode_as_utf8(jbl_string_add_unicode_as_utf8(s3,0X849f),0X84BB),0X4E91);
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
	
	jbl_stream_push_uint64(sout,jbl_string_get_uint64(s3));jbl_stream_push_char(sout,'\n');
	jbl_stream_push_int64(sout,jbl_string_get_int64(s3));jbl_stream_push_char(sout,'\n');
	jbl_stream_push_double(sout,jbl_string_get_double(s3));jbl_stream_push_char(sout,'\n');
	jbl_stream_do(sout,jbl_stream_force);
	
	jbl_stream *ss1=jbl_string_stream_new(jbl_refer(&s1));
	pchars("input something\n");
	jbl_stream_connect(jbl_stream_stdin,ss1);
	jbl_stream_do(jbl_stream_stdin,jbl_stream_force);
	jbl_string_view(s1);
	ss1=jbl_stream_free(ss1);
	
	jbl_string *s4=jbl_string_json_encode(s1,NULL,0,0);
	jbl_string_view(s4);
#if JBL_LL_ENABLE==1
	jbl_ll *l1=jbl_string_cut(s4,NULL,'3');
	jbl_ll_view(l1);
	l1=jbl_ll_free(l1);
#endif
	
//exit:	
	s1=jbl_string_free(s1);s2=jbl_string_free(s2);s3=jbl_string_free(s3);
	s4=jbl_string_free(s4);
	jbl_stop();
	return 0;
}