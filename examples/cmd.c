#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string *cmd=jry_bl_string_add_chars(NULL,"php testfiles/cmd.php 123456781234567812345678");
	jry_bl_string *s1=jry_bl_execute_cmd(cmd,NULL);
	jry_bl_string_view(s1);
	
	s1=jry_bl_string_free(s1);cmd=jry_bl_string_free(cmd);
	jry_bl_stop(); 	
}
