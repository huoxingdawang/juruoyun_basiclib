#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string s1,cmd;jry_bl_string_inits(2,&s1,&cmd);
	jry_bl_string_add_char_pointer(&cmd,"php testfiles/cmd.php 123456781234567812345678");
	jry_bl_execute_cmd(&cmd,&s1);
	jry_bl_string_view(&s1);
	
	jry_bl_string_frees(2,&s1,&cmd);
	jry_bl_stop(); 	
}
