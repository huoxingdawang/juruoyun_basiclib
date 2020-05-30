#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_string *s1=jbl_string_new();
	jbl_string_view(s1);	
	jbl_stream *ss1=jbl_string_stream_new(jbl_refer(&s1));
	jbl_stream_connect_ref(jbl_stream_stdin,ss1);
	jbl_stream_do(jbl_stream_stdin,jbl_stream_force);
	jbl_string_view(s1);pf();
	


	ss1=jbl_stream_free(ss1);
	s1=jbl_string_free(s1);
	jbl_stop(); 	
}

/*
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_string *s1=jbl_string_new(),*s2=NULL,*s3=NULL;
	s1=jbl_string_add_chars(s1,"-123");
	jbl_string_view(s1);	
	jbl_stream *ss1=jbl_string_stream_new(jbl_refer(&s1));
	jbl_stream *ss2=jbl_stream_copy(ss1);
	jbl_stream *ss3=jbl_refer(&ss1);
//	puts("input something");
	jbl_stream_connect(jbl_stream_stdin,ss1);
	jbl_stream_do(jbl_stream_stdin,jbl_stream_force);
	jbl_string_view(s1);pf();
	
//	puts("input something");
	jbl_stream_connect(jbl_stream_stdin,ss2);
	jbl_stream_do(jbl_stream_stdin,jbl_stream_force);
	jbl_string_view(s1);	
	jbl_string_view((jbl_string*)ss2->data);	

//	puts("input something");
	jbl_stream_connect(jbl_stream_stdin,ss3);
	jbl_stream_do(jbl_stream_stdin,jbl_stream_force);
	jbl_string_view(s1);
	
	ss1=jbl_stream_free(ss1);
	ss2=jbl_stream_free(ss2);
	ss3=jbl_stream_free(ss3);
	s1=jbl_string_free(s1);
	jbl_stop(); 	
}
*/