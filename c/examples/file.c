#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string dir;jry_bl_string_init(&dir);
	jry_bl_string_equal_char_pointer(&dir,"testfiles");
	jry_bl_file test;jry_bl_file_init(&test);
	
	
	jry_bl_file_open(&test,&dir,JRY_BL_COPY_LIGHT_MOVE);
	jry_bl_file_view(&test,stderr);
	
	
	
	jry_bl_file_free(&test);
	jry_bl_string_free(&dir);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size); 
	
}
