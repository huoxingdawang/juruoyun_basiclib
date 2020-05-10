#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_time t1,t2;jbl_time_inits(2,&t1,&t2);
	jbl_time_now(&t1);	
	
	fprintf(stderr,"\nused time:%lldms\n",jbl_time_minus((jbl_time_now(&t2),&t2),&t1));	
	jbl_time_frees(2,&t1,&t2);		
	jbl_stop();	
}
//‭00010000‬
//11110000‬