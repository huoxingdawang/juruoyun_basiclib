#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	printf("jbl_file size:%lld\n",(long long)(sizeof (jbl_file)));	
	jbl_string	dir;jbl_string_init(&dir);
	jbl_file		test;jbl_file_init(&test);
	jbl_string_equal_chars(&dir,"testfiles");
	
	
	jbl_file_open(&test,&dir,move);
	jbl_file_view(&test,stderr);
	
	
	
	jbl_file_free(&test);
	jbl_string_free(&dir);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 
	
}
