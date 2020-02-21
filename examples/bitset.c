#include "main.h"

const jry_bl_uint8 len=(512>>jry_bl_bitset_2bits);
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_bitset_type bitset[len];
	jry_bl_bitset_init(bitset,len);
	jry_bl_bitset_view(bitset,len);
	jry_bl_bitset_set(bitset,0,2);
	jry_bl_bitset_view(bitset,len);
	printf("0:%d\n",jry_bl_bitset_find0(bitset,0,len));
	printf("1:%d\n",jry_bl_bitset_find1(bitset,385,len));
	jry_bl_bitset_reset(bitset,0,64);
//	jry_bl_bitset_set(bitset,510,2);
//	jry_bl_bitset_set(bitset,0,512);
	jry_bl_bitset_view(bitset,len);
	printf("0:%d\n",jry_bl_bitset_find0(bitset,0,len));
	printf("1:%d\n",jry_bl_bitset_find1(bitset,0,len));
	jry_bl_stop(); 	
}
