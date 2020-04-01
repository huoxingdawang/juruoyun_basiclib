#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_rand_srand(1);
	for(jry_bl_uint8 i=0;i<100;i++)
		jry_bl_stream_push_uint64(sout,jry_bl_rand()),jry_bl_stream_push_char(sout,'\n');
	
	jry_bl_stop(); 	
}
