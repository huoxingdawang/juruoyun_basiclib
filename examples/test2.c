#include "main.h"
jbl_uint32 __jbl_string_u8tu(const unsigned char *s,jbl_uint8 *start,jbl_uint8 len);
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	for(int i=0;i<1024;++i)
		jbl_log("1231231231233123");
	jbl_log("1231231231233123");
	jbl_logstr(jbl_string_add_chars(NULL,UC "7678678678"));
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
}