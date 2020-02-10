#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();	
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
	jry_bl_time_now(&t1);
	for(int i=0;i<(1<<24);++i)jry_bl_free(jry_bl_malloc(16));
//	for(int i=0;i<1;++i)jry_bl_free(jry_bl_malloc(16));
/*
	char *ptr0,*ptr1,*ptr2;
	ptr0=jry_bl_malloc(8);
	ptr1=jry_bl_malloc(2093057);
	ptr2=jry_bl_malloc(2093057);
	ptr0[0]='c';
	printf("%lld\n",jry_bl_malloc_size(ptr0));
	printf("%lld\n",jry_bl_malloc_size(ptr1));
	printf("%lld\n",jry_bl_malloc_size(ptr2));
	
	jry_bl_free(ptr0);
	jry_bl_free(ptr1);
	jry_bl_free(ptr2);
*/	
	fprintf(stderr,"malloc used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));	
	jry_bl_time_frees(2,&t1,&t2);	
	jry_bl_stop();
	return 0;
}