#include "main.h"
#include <time.h>
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_time * t1=jbl_time_now(NULL);
	jbl_var  * v1=jbl_Vtime_now(jbl_Vtime_new());
	jbl_string *s1=jbl_time_to_string(t1,NULL);
	jbl_string_view(s1);
	s1=jbl_string_free(s1);
	s1=jbl_var_json_encode(v1,s1,1,1);
	jbl_string_view(s1);
	s1=jbl_string_free(s1);
		
	
	t1=jbl_time_free(t1);
	v1=jbl_var_free(v1);
/*	
	srand(time(0));
	jbl_time t1,t2;jbl_time_inits(2,&t1,&t2);
	jbl_string s1,s2,cmd;jbl_string_inits(3,&s1,&s2,&cmd);
	jbl_string_clear(&s1);jbl_time_to_string((jbl_time_from_unix(&t1,-1000),&t1),&s1);jbl_string_view(&s1);
	jbl_string_clear(&s1);jbl_time_to_string((jbl_time_from_unix(&t1,1578396070453),&t1),&s1);jbl_string_view(&s1);
	jbl_string_clear(&s1);jbl_time_to_string((jbl_time_from_unix(&t1,-3116553732000),&t1),&s1);jbl_string_view(&s1);
	jbl_string_clear(&s1);jbl_time_to_string((jbl_time_from_unix(&t1,-1368813421877),&t1),&s1);jbl_string_view(&s1);
	
	jbl_time_now(&t1);
	jbl_string_clear(&s1);jbl_time_to_string(&t1,&s1);jbl_string_view(&s1);
	putchar('\n');putchar('\n');putchar('\n');
	for(int i=0;i<10;i++)
	{
		jbl_int64 t=((jbl_uint64)rand()*(jbl_uint64)rand()(jbl_uint64)rand()*(rand()%2==0?1:-1)1000);
		jbl_string_clears(2,&s1,&s2);jbl_time_to_string((jbl_time_from_unix(&t2,t),&t2),&s1);
		jbl_string_equal_chars(&cmd,"php testfiles/time.php ");jbl_string_add_int64(&cmd,t);jbl_string_set0(&cmd);
		jbl_execute_cmd(&cmd,&s2);
		printf("%lld:\n",t);putchar('\t');jbl_string_print(&s1,stderr);putchar('\n');putchar('\t');jbl_string_print(&s2,stderr);putchar('\n');
		if(!jbl_string_if_equal(&s1,&s2)){printf("Fail!\n");jbl_string_print(&cmd,stderr);putchar('\n');break;}
	}
	printf("%lld\n",jbl_time_minus((jbl_time_now(&t2),&t2),&t1));
	jbl_time_frees(2,&t1,&t2);
	jbl_string_frees(3,&s1,&s2,&cmd);
*/	
	
	jbl_stop(); 	
}
