#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_string* s1=jbl_string_add_chars(NULL,UC"juruoyun");
	s1=jbl_string_delete(s1,2,4);
	jbl_string_view(s1);
	s1=jbl_string_free(s1);
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
