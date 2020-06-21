#include "main.h"
//TODO
#include <time.h>
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_time * t1=jbl_time_now(NULL);
	jbl_var  * v1=jbl_V(jbl_time_now(jbl_Vtime(jbl_Vtime_new())));
	
	jbl_time_view(t1);
	jbl_var_view(v1);
	
	jbl_time_json_put(t1,jbl_stream_stdout,1,1);pn();
		
	
	t1=jbl_time_free(t1);
	v1=jbl_var_free(v1);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
