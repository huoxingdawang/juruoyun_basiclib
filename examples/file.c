#include "main.h"

int main()
{
#if JBL_FILE_ENABLE==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_file * f1=jbl_file_new();
	f1=jbl_file_open_chars(f1,UC"testfiles/test.txt",JBL_FILE_RW);
	jbl_file_view(f1);
	
	
	jbl_string *s1=jbl_file_read(f1,NULL,2,16);
	jbl_string_view(s1);
	s1=jbl_string_free(s1);
	

	jbl_stream* ss1=jbl_file_stream_new(f1);
	jbl_file_stream_set_offset(ss1,2);
	jbl_file_stream_set_end(ss1,12);
	jbl_stream_connect(ss1,jbl_stream_stdout);
	jbl_stream_do(ss1,true);pn();	

	pchars("input\n");pf();
	jbl_stream_connect(jbl_stream_stdin,ss1);
	jbl_stream_do(jbl_stream_stdin,false);
	jbl_stream_do(ss1,true);
	
	
	ss1=jbl_stream_free(ss1);

	f1=jbl_file_free(f1);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
#endif
}
