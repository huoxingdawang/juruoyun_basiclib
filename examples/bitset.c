#include "main.h"

int main()
{
#if JBL_BITSET_ENABLE==1
const jbl_uint8 len=(512>>jbl_bitset_2bits);
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	pf();
	jbl_bitset_type bitset[len];
	jbl_bitset_init(bitset,len);
	jbl_bitset_view(bitset,len);
	jbl_bitset_set(bitset,5,295);
//	jbl_bitset_set(bitset,510,2);
//	jbl_bitset_set(bitset,0,512);
	jbl_bitset_view(bitset,len);
	printf("0:%d\n",jbl_bitset_find0(bitset,0,len));
	printf("1:%d\n",jbl_bitset_find1(bitset,0,len));
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
#endif
}
