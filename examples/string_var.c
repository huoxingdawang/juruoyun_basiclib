#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_string *	s1=jbl_string_add_chars(NULL,UC"j");
	jbl_var    *	v1=jbl_string_copy_as_var(s1);
	jbl_string *	s2=jbl_refer(&s1);
	jbl_var    *	v2=jbl_string_copy_as_var(s2);
	jbl_var    *	v3=jbl_var_copy(v1);
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
pl();
	s1=jbl_string_add_chars(s1,UC"u");
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
pl();
	s2=jbl_string_add_chars(s2,UC"r");
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
pl();
	v1=jbl_V(jbl_string_add_chars(jbl_Vstring(v1),UC"o"));	
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
pl();
	v2=jbl_V(jbl_string_add_chars(jbl_Vstring(v2),UC"y"));	
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
pl();
	v3=jbl_V(jbl_string_add_chars(jbl_Vstring(v3),UC"n"));	
	jbl_string_view(s1);
	jbl_string_view(s2);
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	
	s1=jbl_string_free(s1);
	s2=jbl_string_free(s2);
	v1=jbl_var_free(v1);
	v2=jbl_var_free(v2);
	v3=jbl_var_free(v3);
	
	
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}