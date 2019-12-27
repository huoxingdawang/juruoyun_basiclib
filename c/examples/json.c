#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string s1,s2;jry_bl_string_inits(2,&s1,&s2);
	jry_bl_var v1,v2,v3;jry_bl_var_inits(3,&v1,&v2,&v3);	
	FILE * fp;
	fp=fopen ("testfiles/test.json","r");
	jry_bl_string_equal_file(&s1,fp);
	fclose(fp);
	
	jry_bl_string_view(&s1,stderr);
	jry_bl_var_from_json(&v1,&s1);
	jry_bl_var_view(&v1,stderr);
	
	jry_bl_var_to_json(&v1,&s2);
	jry_bl_string_view(&s2,stderr);
	jry_bl_var_from_json(&v2,&s2);
	printf("\nspace ship:%d\n",jry_bl_var_space_ship(&v1,&v2));
	
	
	
	jry_bl_string_frees(2,&s1,&s2);
	jry_bl_var_frees(3,&v1,&v2,&v3);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size);	
}