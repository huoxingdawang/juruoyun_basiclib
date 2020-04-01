#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();	
	jry_bl_string *s1=jry_bl_string_add_chars(NULL,"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	jry_bl_string *s2=jry_bl_sha1(s1,NULL);
	
	
	jry_bl_string_view(s1);
	jry_bl_string_view(s2);
	
	s1=jry_bl_string_free(s1);s2=jry_bl_string_free(s2);
	
	jry_bl_stop(); 
	return 0;
}