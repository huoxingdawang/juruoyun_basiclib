#include "main.h"
//TODO
#include <time.h>
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");


	for(int i=0;i<10;i++)
	{
		jbl_int64 t=jbl_rand()/1000*1000;
		jbl_time * t1=jbl_time_set(NULL,t);
		jbl_string *s1=jbl_time_to_string(t1,NULL);
		jbl_string *cmd=jbl_string_add_uint(jbl_string_add_chars(NULL,UC "php testfiles/time.php "),t);
		jbl_string *s2=jbl_execute_cmd(cmd,NULL);
		jbl_string_view(s1);
		jbl_string_view(s2);
		t1=jbl_time_free(t1);
		s1=jbl_string_free(s1);
		cmd=jbl_string_free(cmd);
		s2=jbl_string_free(s2);
	}

	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
