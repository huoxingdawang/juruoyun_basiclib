#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_string s1,s2;jbl_string_inits(2,&s1,&s2);
	jbl_var v1,v2,v3;jbl_var_inits(3,&v1,&v2,&v3);	
	FILE * fp;
	fp=fopen ("testfiles/test.json","r");
	jbl_string_equal_file(&s1,fp);
	fclose(fp);
	
	jbl_string_view(&s1);
	jbl_var_from_json(&v1,&s1);
	//jbl_var_put(&v1,&jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|(__LINE__<<1)|1,__FILE__);jbl_stream_do(&jbl_stream_stdout,1);
	jbl_var_view(&v1);
/*	
	fp=fopen("testfiles/json.out","w");
	jbl_var_view(&v1,fp);
	fclose(fp);
	jbl_var_view(&v1;
	
	jbl_var_to_json(&v1,&s2);
	jbl_string_view(&s2);
	jbl_var_from_json(&v2,&s2);
	printf("\nspace ship:%d\n",jbl_var_space_ship(&v1,&v2));
*/	
	
	printf("%d\n",__LINE__);
	jbl_var_frees(3,&v1,&v2,&v3);
	printf("%d\n",__LINE__);
	jbl_string_frees(2,&s1,&s2);
	printf("%d\n",__LINE__);
	jbl_stop();	
}