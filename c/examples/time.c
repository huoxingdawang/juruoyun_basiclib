#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
	jry_bl_time_now(&t1);
	for(int i=0;i<100000000;i++);
	printf("%lld\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));
	
	jry_bl_time_frees(2,&t1,&t2);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size); 	
}
