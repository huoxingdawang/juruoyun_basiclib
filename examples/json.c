#include "main.h"
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	FILE *fp;
	jbl_string *s1=jbl_string_add_file(NULL,fp=fopen("testfiles/test2.json","rb"));fclose(fp);
//	jbl_string_view(s1);
	
	jbl_string_size_type i=0;
	jbl_var *v1=jbl_var_json_decode(NULL,s1,&i);

	jbl_string *s2=jbl_var_json_encode(v1,NULL,1,0);
	jbl_string_print(s2,fp=fopen("tmp/json.out","w"));fclose(fp);
	s2=jbl_string_free(s2);

	jbl_var_view(v1);
	jbl_var_json_put(v1,jbl_stream_stdout,1,1);
	pn();
	jbl_var_json_put(v1,jbl_stream_stdout,0,0);



	
	s1=jbl_string_free(s1);
	v1=jbl_var_free(v1);
	jbl_stop();	
}