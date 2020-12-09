#include "main.h"

int main()
{
#if JBL_ARRAY_ENABLE==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
#endif
}
