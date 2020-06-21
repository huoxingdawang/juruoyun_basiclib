#include "main.h"
//测试refer
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");	
	jbl_var    *v1=jbl_V(jbl_string_add_chars(jbl_Vstring(jbl_Vstring_new()),UC"j"));	
	jbl_var    *v2=NULL,*v3=NULL,*v4=NULL,*v5=NULL,*v6=NULL;
	v5=jbl_var_copy(v1);
	v2=jbl_refer(&v1);
	v3=jbl_refer(&v2);
	v4=jbl_var_copy(v3);
	v6=jbl_var_copy(v1);
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	jbl_var_view(v4);
	jbl_var_view(v5);
	jbl_var_view(v6);
	v1=jbl_V(jbl_string_add_chars(jbl_Vstring(v1),UC"u"));	
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);	
	jbl_var_view(v4);
	jbl_var_view(v5);
	jbl_var_view(v6);
	v3=jbl_V(jbl_string_add_chars(jbl_Vstring(v3),UC"r"));	
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	jbl_var_view(v4);
	jbl_var_view(v5);
	jbl_var_view(v6);

	v4=jbl_V(jbl_string_add_chars(jbl_Vstring(v4),UC"o"));	
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	jbl_var_view(v4);
	jbl_var_view(v5);
	jbl_var_view(v6);
	v5=jbl_V(jbl_string_add_chars(jbl_Vstring(v5),UC"y"));	
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	jbl_var_view(v4);
	jbl_var_view(v5);
	jbl_var_view(v6);
	v6=jbl_V(jbl_string_add_chars(jbl_Vstring(v6),UC"a"));	
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	jbl_var_view(v4);
	jbl_var_view(v5);
	jbl_var_view(v6);
//v1,v6z ^ same
//       |-------
//v2,v3,v4 same |
//phex(v1);pn();
//phex(v2);pn();
//phex(v3);pn();
//phex(v6);pn();

	v1=jbl_var_free(v1);
	v2=jbl_var_free(v2);
	v3=jbl_var_free(v3);
	v4=jbl_var_free(v4);
	v5=jbl_var_free(v5);
	v6=jbl_var_free(v6);
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}