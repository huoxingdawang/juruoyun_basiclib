#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_string *cmd=jbl_string_add_chars(NULL,UC"php testfiles/cmd.php 123456781234567812345678");
	jbl_string *s1=jbl_execute_cmd(cmd,NULL);
	jbl_string_view(s1);
	
	s1=jbl_string_free(s1);cmd=jbl_string_free(cmd);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
