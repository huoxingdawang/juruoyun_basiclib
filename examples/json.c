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
	
	jry_bl_string_view(&s1);
	jry_bl_var_from_json(&v1,&s1);
	//jry_bl_var_put(&v1,&jry_bl_stream_stdout,view,(jry_bl_view_default_tabs_num<<16)|(__LINE__<<1)|1,__FILE__);jry_bl_stream_do(&jry_bl_stream_stdout,1);
	jry_bl_var_view(&v1);
/*	
	fp=fopen("testfiles/json.out","w");
	jry_bl_var_view(&v1,fp);
	fclose(fp);
	jry_bl_var_view(&v1;
	
	jry_bl_var_to_json(&v1,&s2);
	jry_bl_string_view(&s2);
	jry_bl_var_from_json(&v2,&s2);
	printf("\nspace ship:%d\n",jry_bl_var_space_ship(&v1,&v2));
*/	
	
	printf("%d\n",__LINE__);
	jry_bl_var_frees(3,&v1,&v2,&v3);
	printf("%d\n",__LINE__);
	jry_bl_string_frees(2,&s1,&s2);
	printf("%d\n",__LINE__);
	jry_bl_stop();	
}