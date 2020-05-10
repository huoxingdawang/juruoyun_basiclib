#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	
	jbl_string *s1=jbl_string_add_chars(NULL,"juruoyunwansui"),*s2,*s3;
	jbl_var *v1=jbl_var_copy_from_string(s1),*v2,*v3,*v4,*v5;
	jbl_var_view(v1);
	v2=jbl_var_copy(v1);
	v3=jbl_refer(&v1);
	v4=jbl_var_copy(v3);
	v1=jbl_vstring_add_chars(v1,"45564556");
	v2=jbl_vstring_add_chars(v2,"7788");
	v3=jbl_vstring_add_chars(v3,"9999");
	v4=jbl_vstring_add_chars(v4,"123");
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	jbl_var_view(v4);
	
	printf("0X%X\n",jbl_vstring_hash(v1));
	v2=jbl_vstring_add_vstring(v2,v1);	jbl_var_view(v2);
	v2=jbl_vstring_add_string(v2,s1);	jbl_var_view(v2);
	s1=jbl_string_add_vstring(s1,v1);	jbl_string_view(s1);
	s2=jbl_string_copy_from_var(v1);		jbl_string_view(s2);
	s2=jbl_string_add_chars(s2,"67687");	jbl_string_view(s2);

	v5=jbl_refer_as_var(&s2,&jbl_string_operators);
	jbl_var_view(v5);
	s2=jbl_string_add_chars(s2,"67687");	jbl_string_view(s2);
	jbl_var_view(v5);
	
exit:

	v1=jbl_var_free(v1);
	v2=jbl_var_free(v2);
	v3=jbl_var_free(v3);
	v4=jbl_var_free(v4);
	v5=jbl_var_free(v5);
	s1=jbl_string_free(s1);
	s2=jbl_string_free(s2);
	s3=jbl_string_free(s3);

	jbl_stop();
	return 0;
}