#include "main.h"

const jbl_uint8 len=(512>>jbl_bitset_2bits);
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_bitset_type bitset[len];
	jbl_bitset_init(bitset,len);
	jbl_bitset_view(bitset,len);
	jbl_bitset_set(bitset,0,2);
	jbl_bitset_view(bitset,len);
	printf("0:%d\n",jbl_bitset_find0(bitset,0,len));
	printf("1:%d\n",jbl_bitset_find1(bitset,385,len));
	jbl_bitset_reset(bitset,0,64);
//	jbl_bitset_set(bitset,510,2);
//	jbl_bitset_set(bitset,0,512);
	jbl_bitset_view(bitset,len);
	printf("0:%d\n",jbl_bitset_find0(bitset,0,len));
	printf("1:%d\n",jbl_bitset_find1(bitset,0,len));
	jbl_stop(); 	
}
