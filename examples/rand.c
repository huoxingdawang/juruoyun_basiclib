#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_rand_srand(1);
	for(jbl_uint8 i=0;i<100;i++)
		jbl_stream_push_uint64(sout,jbl_rand()),jbl_stream_push_char(sout,'\n');
	
	jbl_stop(); 	
}
