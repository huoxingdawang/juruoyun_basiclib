#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string *s1=jry_bl_string_new(),*s2=NULL,*s3=NULL;
	s1=jry_bl_string_add_chars(s1,"-123");
	jry_bl_string_view(s1);	
	jry_bl_stream *ss1=jry_bl_string_stream_new(jry_bl_refer(&s1));
	jry_bl_stream *ss2=jry_bl_stream_copy(ss1);
	jry_bl_stream *ss3=jry_bl_refer(&ss1);
	puts("input something");
	jry_bl_stream_connect(jry_bl_stream_stdin,ss1);
	jry_bl_stream_do(jry_bl_stream_stdin,jry_bl_stream_force);
	jry_bl_string_view(s1);
	
	puts("input something");
	jry_bl_stream_connect(jry_bl_stream_stdin,ss2);
	jry_bl_stream_do(jry_bl_stream_stdin,jry_bl_stream_force);
	jry_bl_string_view(s1);	
	jry_bl_string_view((jry_bl_string*)ss2->data);	

	puts("input something");
	jry_bl_stream_connect(jry_bl_stream_stdin,ss3);
	jry_bl_stream_do(jry_bl_stream_stdin,jry_bl_stream_force);
	jry_bl_string_view(s1);
	
	ss1=jry_bl_stream_free(ss1);
	ss2=jry_bl_stream_free(ss2);
	ss3=jry_bl_stream_free(ss3);
	s1=jry_bl_string_free(s1);
	jry_bl_stop(); 	
}
