#include "main.h"
int main(int argc,char** argv)
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_file * f1=jbl_file_open_chars(NULL,UC((argc>1)?argv[1]:"testfiles/test.json"),JBL_FILE_READ);
	jbl_string *s1=jbl_file_read(f1,NULL,0,-1);
	jbl_file_free(f1);
//	jbl_string_view(s1);
	
	jbl_string_size_type i=0;

	jbl_var *v1=jbl_var_json_decode(NULL,s1,&i);

	jbl_string *s2=jbl_var_json_encode(v1,NULL,1,0);
	jbl_file_free(jbl_file_write(jbl_file_open_chars(NULL,UC"tmp/json.out",JBL_FILE_WRITE),s2));
	s2=jbl_string_free(s2);
	

	jbl_var_view(v1);
pf();
	jbl_var_json_put(v1,jbl_stream_stdout,1,1);
	pn();
	jbl_var_json_put(v1,jbl_stream_stdout,0,0);

	jbl_log(UC "test %d%d%d %s %X %c juruoyun %v",1,123,456,"123123123121",0XFE,'a',v1);
	
/*
*/


	
	s1=jbl_string_free(s1);
	v1=jbl_var_free(v1);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
}