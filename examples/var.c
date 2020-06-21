#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_var *v1=jbl_Vuint_set(NULL,100);
	jbl_var *v2=jbl_Vint_set(NULL,-1024);
	jbl_var *v3=jbl_Vdouble_set(NULL,1926.0817);
	jbl_var *v4=jbl_Vnull_new();
	jbl_var *v5=jbl_Vtrue_new();
	jbl_var *v6=jbl_Vfalse_new();
	
	jbl_var_view(v1);
	jbl_var_view(v2);
	jbl_var_view(v3);
	jbl_var_view(v4);
	jbl_var_view(v5);
	jbl_var_view(v6);

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