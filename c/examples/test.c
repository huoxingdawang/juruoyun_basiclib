#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string s1;jry_bl_string_inits(1,&s1);
//	unsigned char s[]={0X5f,0X90,0};
//	unsigned char s[100]="徐";
	jry_bl_string_add_unicode_as_utf8(&s1,0X5F90);
	jry_bl_string_add_unicode_as_utf8(&s1,0X548C);




	jry_bl_string_view(&s1,stderr);

	jry_bl_string_frees(1,&s1);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size);	
}
