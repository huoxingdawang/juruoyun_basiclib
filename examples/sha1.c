#include "main.h"
int main()
{
#if JBL_SHA1_ENABLE ==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_string *s1=jbl_string_add_chars(NULL,UC"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	jbl_string *s2=jbl_sha1(s1,NULL,false);
	
	
	jbl_string_view(s1);
	jbl_string_view(s2);
	
	s1=jbl_string_free(s1);s2=jbl_string_free(s2);
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 
	return 0;
#endif
}