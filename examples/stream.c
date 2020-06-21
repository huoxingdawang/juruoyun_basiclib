#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_string *s1=jbl_string_new();
	jbl_string_view(s1);
	s1=jbl_string_read(s1,UC"Input something:");
	jbl_string_view(s1);
	s1=jbl_string_read(s1,UC"Input something else:");
	jbl_string_view(s1);
	s1=jbl_string_read(s1,UC"Input something else:");
	jbl_string_view(s1);
	


	s1=jbl_string_free(s1);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}