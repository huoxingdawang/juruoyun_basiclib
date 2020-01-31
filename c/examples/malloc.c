#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();	
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
	jry_bl_time_now(&t1);
	for(int i=0;i<(1<<24);++i)
		jry_bl_free(jry_bl_malloc(16));
	
	
	
	
	fprintf(stderr,"malloc used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));	
	jry_bl_time_frees(2,&t1,&t2);	
	jry_bl_stop();
	return 0;
}