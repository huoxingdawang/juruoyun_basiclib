#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_log(UC "test %d%d%d %s %X %c juruoyun",1,123,456,"123123123121",0XFE,'a');
	
	
	jbl_log_save();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
