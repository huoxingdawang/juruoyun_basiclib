#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_rand_srand(1);
	for(jbl_uint8 i=0;i<100;i++)
		jbl_stream_push_uint(jbl_stream_stdout,jbl_rand()),jbl_stream_push_char(jbl_stream_stdout,'\n');
	for(jbl_uint8 i=0;i<100;i++)
		jbl_stream_push_uint(jbl_stream_stdout,jbl_rand_between (0,200)),jbl_stream_push_char(jbl_stream_stdout,'\n');
	
#if JBL_STRING_ENABLE==1
	jbl_string *s1=NULL;
	for(jbl_uint8 i=0;i<100;i++)
	{
		s1=jbl_rand_string(NULL,40,UC jbl_rand_dict_small);
		jbl_string_view(s1);s1=jbl_string_free(s1);
	}
	for(jbl_uint8 i=0;i<100;i++)
	{
		s1=jbl_rand_string(NULL,40,UC jbl_rand_dict_big);
		jbl_string_view(s1);s1=jbl_string_free(s1);
	}
	for(jbl_uint8 i=0;i<100;i++)
	{
		s1=jbl_rand_string(NULL,40,UC jbl_rand_dict_number);
		jbl_string_view(s1);s1=jbl_string_free(s1);
	}
	for(jbl_uint8 i=0;i<100;i++)
	{
		s1=jbl_rand_string(NULL,40,UC jbl_rand_dict_symbol);
		jbl_string_view(s1);s1=jbl_string_free(s1);
	}
	for(jbl_uint8 i=0;i<100;i++)
	{
		s1=jbl_rand_string(NULL,40,UC jbl_rand_dict_small jbl_rand_dict_big  jbl_rand_dict_number jbl_rand_dict_symbol);
		jbl_string_view(s1);s1=jbl_string_free(s1);
	}
#endif 	
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
