#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	
	jry_bl_string *s1=jry_bl_string_new(),*s2=NULL,*s3=NULL;
	jry_bl_string *s4=jry_bl_refer(&s1);
	s1=jry_bl_string_add_chars(s1,"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	s2=jry_bl_base64_encode(s1,NULL);
	s3=jry_bl_base64_decode(s2,NULL);
	
	jry_bl_string_view(s1);
	jry_bl_string_view(s2);
	jry_bl_string_view(s3);
	
	s1=jry_bl_string_free(s1);s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);

	jry_bl_stop();
	return 0;
}