#include "main.h"
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	FILE *fp;
	jbl_string *s1=jbl_string_add_file(NULL,fp=fopen("tmp/bigfile.tmp","rb"));fclose(fp);
	pint(jbl_string_get_length(s1));pn();
	jbl_string_print(s1,fp=fopen("C:\\tmp\\bigfile_out.tmp","w"));fclose(fp);
	s1=jbl_string_free(s1);
	jbl_stop();	
}
//?00010000?
//11110000?