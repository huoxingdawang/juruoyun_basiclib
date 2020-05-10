#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();	
	
	jbl_string *s1=jbl_string_add_chars(NULL,"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	jbl_string *s2=jbl_md5(s1,NULL);
	
	
	jbl_string_view(s1);
	jbl_string_view(s2);
	
	s1=jbl_string_free(s1);s2=jbl_string_free(s2);
	
	jbl_stop(); 
	return 0;
}