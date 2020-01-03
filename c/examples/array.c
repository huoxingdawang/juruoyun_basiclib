#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	
	
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size); 	
}
