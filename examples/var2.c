#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	printf("Pointer size:%lld\n",(long long)(sizeof (char *)));
	printf("jbl_var_fs size:%lld\n",(long long)(sizeof (jbl_var_fs)));
	printf("jbl_var_functions size:%lld\n",(long long)(sizeof (jbl_var_functions)));
	printf("jbl_var_tmp_functions size:%lld\n",(long long)(sizeof (jbl_var_tmp_functions)));
	printf("jbl_var_functions_struct size:%lld\n",(long long)(sizeof (jbl_var_functions_struct)));
//	jbl_var_tmp_register(0,10,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
		
	jbl_var va,vb,vc;jbl_var_inits(3,&va,&vb,&vc);
	jbl_string sa,sb,sc,sd;jbl_string_inits(4,&sa,&sb,&sc,&sd);
	int a=0;

	jbl_string_equal_chars(&sa,"juruoyun");
	jbl_var_equal_string(&va,&sa,copy);
	jbl_var_equal_string(&vb,&sa,light);
	jbl_var_equal_string(&vc,&sa,move);
		
	jbl_string_view(jbl_var_get_string(&va));
	jbl_string_view(jbl_var_get_string(&vb));
	jbl_string_view(jbl_var_get_string(&vc));
	jbl_var_views(3,&va,&vb,&vc);
	jbl_var_equal_int64(&va,1234234);
	jbl_var_equal_double(&vb,2.2222);
	jbl_var_equal_pointer(&vc,&a);
	jbl_var_views(3,&va,&vb,&vc);

	jbl_var_equal_double(&va,1234234.123);
	jbl_string_clear(&sa);
	jbl_var_to_json(&va,&sa);
	jbl_string_view(&sa);
	
	jbl_var_from_json(&va,&sa);
	jbl_var_view(&va);
	
	jbl_var_frees(3,&va,&vb,&vc);
	jbl_string_frees(4,&sa,&sb,&sc,&sd);

	jbl_var_equal_double(&va,234234.123);
	jbl_var_equal_double(&vb,4234.123);
	printf("Space ship test:%d\n",jbl_var_space_ship(&va,&vb));	
	
/*
*/	
exit:
	jbl_string_frees(4,&sa,&sb,&sc,&sd);
	jbl_var_frees(3,&va,&vb,&vc);
	jbl_stop();
	return 0;
}