#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_rand_srand(1);
	for(jbl_uint8 i=0;i<100;i++)
		jbl_stream_push_uint64(sout,jbl_rand()),jbl_stream_push_char(sout,'\n');
	for(jbl_uint8 i=0;i<100;i++)
		jbl_stream_push_uint64(sout,jbl_rand_between (0,200)),jbl_stream_push_char(sout,'\n');
	
#if JBL_STRING_ENABLE==1
	for(jbl_uint8 i=0;i<100;i++)
	{
		jbl_string *s1=jbl_rand_string(NULL,40,"abcdefghijklmnopqrstuvwxyz");
		jbl_string_view(s1);
		s1=jbl_string_free(s1);
	}
#endif 	
	
	jbl_stop(); 	
}
