#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string s1;jry_bl_string_inits(1,&s1);
	static const jry_bl_string ping=jry_bl_string_const("ping 127.0.0.1",14);


	jry_bl_execute_cmd(&ping,&s1);


	jry_bl_string_view(&s1,stderr);

	jry_bl_string_frees(1,&s1);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size);	
}
