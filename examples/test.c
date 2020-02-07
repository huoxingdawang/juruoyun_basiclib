#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	for(int i=0;i<0XFF;i++)
		printf("%d\t%d\n",i,1<<(jry_bl_highbit(i-1)+1));
	jry_bl_stop();	
}
