#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_string *cmd=jbl_string_add_chars(NULL,"php testfiles/cmd.php 123456781234567812345678");
	jbl_string *s1=jbl_execute_cmd(cmd,NULL);
	jbl_string_view(s1);
	
	s1=jbl_string_free(s1);cmd=jbl_string_free(cmd);
	jbl_stop(); 	
}
