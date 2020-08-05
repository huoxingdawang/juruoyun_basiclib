#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
#if JBL_VAR_ENABLE==1
	jbl_time *	t1=jbl_time_now(NULL);
	jbl_var  *	v1=jbl_time_copy_as_var(t1);
	jbl_time *	t2=jbl_refer(&t1);
	jbl_var  *	v2=jbl_time_copy_as_var(t2);
	
	jbl_time_view(t1);
	jbl_time_view(t2);
	jbl_var_view(v1);
	jbl_var_view(v2);
pl();
	t1=jbl_time_set(t1,1593009049993);
	jbl_time_view(t1);
	jbl_time_view(t2);
	jbl_var_view(v1);
	jbl_var_view(v2);
pl();	
	t2=jbl_time_set(t2,-1368835200000);
	jbl_time_view(t1);
	jbl_time_view(t2);
	jbl_var_view(v1);
	jbl_var_view(v2);
pl();
	v1=jbl_V(jbl_time_set(jbl_Vtime(v1),946684800000));	
	jbl_time_view(t1);
	jbl_time_view(t2);
	jbl_var_view(v1);
	jbl_var_view(v2);
pl();
	v2=jbl_V(jbl_time_set(jbl_Vtime(v2),1577836800000));	
	jbl_time_view(t1);
	jbl_time_view(t2);
	jbl_var_view(v1);
	jbl_var_view(v2);
	
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);
	v1=jbl_var_free(v1);
	v2=jbl_var_free(v2);
#endif	
	
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}