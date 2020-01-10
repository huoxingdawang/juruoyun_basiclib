#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	printf("Pointer size:%lld\n",(long long)(sizeof (char *)));
	printf("jry_bl_var_fs size:%lld\n",(long long)(sizeof (jry_bl_var_fs)));
	printf("jry_bl_var_functions size:%lld\n",(long long)(sizeof (jry_bl_var_functions)));
	printf("jry_bl_var_tmp_functions size:%lld\n",(long long)(sizeof (jry_bl_var_tmp_functions)));
//	jry_bl_var_tmp_register(0,10,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
		
	jry_bl_var va,vb,vc;jry_bl_var_inits(3,&va,&vb,&vc);
	jry_bl_string sa,sb,sc,sd;jry_bl_string_inits(4,&sa,&sb,&sc,&sd);
	int a=0;

	jry_bl_string_equal_char_pointer(&sa,"juruoyun");
	jry_bl_var_equal_string(&va,&sa,JRY_BL_COPY);
	jry_bl_var_equal_string(&vb,&sa,JRY_BL_COPY_LIGHT);
	jry_bl_var_equal_string(&vc,&sa,JRY_BL_COPY_LIGHT_MOVE);
	

	jry_bl_string_view(jry_bl_var_get_string(&va),stderr);
	jry_bl_string_view(jry_bl_var_get_string(&vb),stderr);
	jry_bl_string_view(jry_bl_var_get_string(&vc),stderr);
	jry_bl_var_views(stderr,3,&va,&vb,&vc);
	jry_bl_var_equal_int64(&va,1234234);
	jry_bl_var_equal_double(&vb,2.2222);
	jry_bl_var_equal_pointer(&vc,&a);
	jry_bl_var_views(stderr,3,&va,&vb,&vc);

	jry_bl_var_equal_double(&va,1234234.123);
	jry_bl_string_clear(&sa);
	jry_bl_var_to_json(&va,&sa);
	jry_bl_string_view(&sa,stderr);
	
	jry_bl_var_from_json(&va,&sa);
	jry_bl_var_view(&va,stderr);
	
	jry_bl_var_frees(3,&va,&vb,&vc);
	jry_bl_string_frees(4,&sa,&sb,&sc,&sd);

	jry_bl_var_equal_double(&va,234234.123);
	jry_bl_var_equal_double(&vb,4234.123);
	printf("Space ship test:%d\n",jry_bl_var_space_ship(&va,&vb));	
	
/*
*/	
	jry_bl_string_frees(4,&sa,&sb,&sc,&sd);
	jry_bl_var_frees(3,&va,&vb,&vc);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size);
	return 0;
}