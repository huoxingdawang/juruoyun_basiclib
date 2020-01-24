#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	FILE * in,*out;
	jry_bl_stream ins,outs,b64en,aes128cbcen;	
	unsigned char key[]="0CoJUm6Qyw8W8jud";
	jry_bl_aes_128_extened_key keyy;
	jry_bl_aes_128_extend_key(key,keyy);
	jry_bl_aes_128_ecb_encode_stream_init(&aes128cbcen,keyy);
	in=fopen(filename,"rb");
	out=fopen("testfiles/stream.out","wb");
	jry_bl_stream_init(&ins,jry_bl_stream_file_operator,in,NULL,0);
	jry_bl_stream_init(&outs,jry_bl_stream_file_operator,out,jry_bl_malloc(JRY_BL_STREAM_EXCEED_LENGTH),JRY_BL_STREAM_EXCEED_LENGTH);
	
	jry_bl_base64_encode_stream_init(&b64en);
	jry_bl_stream_connect(&ins,&aes128cbcen);
	jry_bl_stream_connect(&aes128cbcen,&b64en);
	jry_bl_stream_connect(&b64en,&outs);
	jry_bl_stream_do(&ins,jry_bl_stream_force);	
	
	
	jry_bl_free(outs.buf),jry_bl_stream_free(&outs);
	jry_bl_stream_free(&ins);	
	jry_bl_base64_encode_stream_free(&b64en);
	jry_bl_aes_128_ecb_encode_stream_free(&aes128cbcen);
	
	jry_bl_stop();	
}
