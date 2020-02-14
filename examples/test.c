#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
	jry_bl_time_now(&t1);	
	
	fprintf(stderr,"\nused time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));	
	jry_bl_time_frees(2,&t1,&t2);		
	jry_bl_stop();	
}
//‭00010000‬
//11110000‬