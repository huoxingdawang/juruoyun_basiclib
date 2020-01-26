#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	printf("jry_bl_file size:%lld\n",(long long)(sizeof (jry_bl_file)));	
	jry_bl_string	dir;jry_bl_string_init(&dir);
	jry_bl_file		test;jry_bl_file_init(&test);
	jry_bl_string_equal_char_pointer(&dir,"testfiles");
	
	
	jry_bl_file_open(&test,&dir,move);
	jry_bl_file_view(&test,stderr);
	
	
	
	jry_bl_file_free(&test);
	jry_bl_string_free(&dir);
	jry_bl_stop(); 
	
}
