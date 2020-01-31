#include "main.h"
#include <time.h>
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	srand(time(0));
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
	jry_bl_string s1,s2,cmd;jry_bl_string_inits(3,&s1,&s2,&cmd);
	jry_bl_string_clear(&s1);jry_bl_time_to_string((jry_bl_time_from_unix(&t1,-1000),&t1),&s1);jry_bl_string_view(&s1);
	jry_bl_string_clear(&s1);jry_bl_time_to_string((jry_bl_time_from_unix(&t1,1578396070453),&t1),&s1);jry_bl_string_view(&s1);
	jry_bl_string_clear(&s1);jry_bl_time_to_string((jry_bl_time_from_unix(&t1,-3116553732000),&t1),&s1);jry_bl_string_view(&s1);
	jry_bl_string_clear(&s1);jry_bl_time_to_string((jry_bl_time_from_unix(&t1,-1368813421877),&t1),&s1);jry_bl_string_view(&s1);
	
	jry_bl_time_now(&t1);
	jry_bl_string_clear(&s1);jry_bl_time_to_string(&t1,&s1);jry_bl_string_view(&s1);
	putchar('\n');putchar('\n');putchar('\n');
	for(int i=0;i<10;i++)
	{
		jry_bl_int64 t=((jry_bl_uint64)rand()*(jry_bl_uint64)rand()*/*(jry_bl_uint64)rand()*(rand()%2==0?1:-1)**/1000);
		jry_bl_string_clears(2,&s1,&s2);jry_bl_time_to_string((jry_bl_time_from_unix(&t2,t),&t2),&s1);
		jry_bl_string_equal_chars(&cmd,"php testfiles/time.php ");jry_bl_string_add_int64(&cmd,t);jry_bl_string_set0(&cmd);
		jry_bl_execute_cmd(&cmd,&s2);
		printf("%lld:\n",t);putchar('\t');jry_bl_string_print(&s1,stderr);putchar('\n');putchar('\t');jry_bl_string_print(&s2,stderr);putchar('\n');
		if(!jry_bl_string_if_equal(&s1,&s2)){printf("Fail!\n");jry_bl_string_print(&cmd,stderr);putchar('\n');break;}
	}
	printf("%lld\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));
	
	
	jry_bl_time_frees(2,&t1,&t2);
	jry_bl_string_frees(3,&s1,&s2,&cmd);
	jry_bl_stop(); 	
}
