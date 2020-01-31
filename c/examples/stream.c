#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	jry_bl_string s1,s2,s3,s4;jry_bl_string_inits(4,&s1,&s2,&s3,&s4);
	jry_bl_stream ss1,ss2,ss3,ss4,b64en,b64de,aes128ecben,aes128ecbde,aes128cbcen,aes128cbcde;
	jry_bl_string_stream_init(&ss1,&s1);
	jry_bl_string_stream_init(&ss2,&s2);
	jry_bl_string_stream_init(&ss3,&s3);
	jry_bl_string_stream_init(&ss4,&s4);
	jry_bl_base64_encode_stream_init(&b64en);
	jry_bl_base64_decode_stream_init(&b64de);
	unsigned char key[]="0CoJUm6Qyw8W8jud";
	jry_bl_aes_128_extened_key keyy;
	jry_bl_aes_128_extend_key(key,keyy);
	jry_bl_aes_128_ecb_encode_stream_init(&aes128ecben,keyy);
	jry_bl_aes_128_ecb_decode_stream_init(&aes128ecbde,keyy);
	jry_bl_aes_128_cbc_encode_stream_init(&aes128cbcen,keyy,"0CoJUm6Qyw8W8jud");
	jry_bl_aes_128_cbc_decode_stream_init(&aes128cbcde,keyy,"0CoJUm6Qyw8W8jud");
	jry_bl_string_equal_chars(&s1,"12345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678123456781234567812345678");
	
//字符串输出	
/*	
	jry_bl_string_view(&s1;
	jry_bl_stream_connect(&ss1,&jry_bl_stream_stdout);
	jry_bl_stream_do(&ss1,jry_bl_stream_force);
	putchar('\n');
*/
//字符串输入	
/*
	puts("input something");
	jry_bl_stream_connect(&jry_bl_stream_stdin,&ss2);
	jry_bl_stream_connect(&ss2,&b64en);
	jry_bl_stream_connect(&b64en,&ss3);
	jry_bl_stream_connect(&ss3,&b64de);
	jry_bl_stream_connect(&b64de,&ss4);
	jry_bl_stream_connect(&ss4,&jry_bl_stream_stdout);
	jry_bl_stream_do(&jry_bl_stream_stdin,jry_bl_stream_force);
	jry_bl_string_view(&s2;
	jry_bl_string_view(&s3;
	jry_bl_string_view(&s4;
*/
//输入直接输出	
/*
	puts("input something");
	jry_bl_stream_connect(&jry_bl_stream_stdin,&b64en);
	jry_bl_stream_connect(&b64en,&jry_bl_stream_stdout);
	jry_bl_stream_do(&jry_bl_stream_stdin,jry_bl_stream_force);
*/		
//字符串对拷
/*
	jry_bl_stream_connect(&ss1,&ss2);
	jry_bl_stream_do(&ss1,jry_bl_stream_force);
	jry_bl_string_stream_reset(&ss1);
	jry_bl_stream_do(&ss1,jry_bl_stream_force);
	jry_bl_string_view(&s2;
*/
//base64 encode
/*
	jry_bl_string_clear(&s2);jry_bl_string_clear(&s3);
	jry_bl_string_stream_reset(&ss1);jry_bl_string_stream_reset(&ss3);
	jry_bl_base64_encode(&s1,&s2);
	jry_bl_stream_connect(&ss1,&b64en);
	jry_bl_stream_connect(&b64en,&ss3);
	jry_bl_stream_do(&ss1,jry_bl_stream_force);
	jry_bl_string_view(&s2;
	jry_bl_string_view(&s3;
*/
//base64 decode
/*
	jry_bl_string_equal_chars(&s1,"YWhmamdhaGZnYWhqc2Znamhhc2dmaGphc2dmaGp");
	jry_bl_string_equal_chars(&s2,"hc2dmamhhc2dmamhhc2ZqaGFnc2pobW5iek5NamhlZnM=");
	jry_bl_string_clear(&s3);
	jry_bl_string_stream_reset(&ss1);jry_bl_string_stream_reset(&ss2);jry_bl_string_stream_reset(&ss3);
	jry_bl_stream_connect(&b64de,&ss3);
	jry_bl_stream_connect(&ss1,&b64de);
	jry_bl_stream_do(&ss1,0);
	jry_bl_stream_connect(&ss2,&b64de);
	jry_bl_stream_do(&ss2,jry_bl_stream_force);
	
	jry_bl_string_view(&s1;
	jry_bl_string_view(&s2;
	jry_bl_string_view(&s3;
*/
//aes128ecb
/*
	jry_bl_string_clear(&s2);jry_bl_string_clear(&s3);jry_bl_string_clear(&s4);
	jry_bl_aes_128_ecb_encode(keyy,&s1,&s3);jry_bl_base64_encode(&s3,&s2);jry_bl_string_clear(&s3);
	jry_bl_string_stream_reset(&ss1);jry_bl_string_stream_reset(&ss3);jry_bl_string_stream_reset(&ss4);jry_bl_stream_reset(&b64en);jry_bl_stream_reset(&b64de);
	jry_bl_stream_connect(&ss1,&aes128ecben);
	jry_bl_stream_connect(&aes128ecben,&b64en);
	jry_bl_stream_connect(&b64en,&ss3);
	jry_bl_stream_connect(&ss3,&b64de);
	jry_bl_stream_connect(&b64de,&aes128ecbde);
	jry_bl_stream_connect(&aes128ecbde,&ss4);
	jry_bl_stream_do(&ss1,jry_bl_stream_force);
	jry_bl_string_view(&s2;
	jry_bl_string_view(&s3;	
	jry_bl_string_view(&s4;	
	printf("AES 128 ECB encode %s\n",((jry_bl_string_space_ship(&s2,&s3)==0)?"YES":"NO"));
	printf("AES 128 ECB decode %s\n",((jry_bl_string_space_ship(&s4,&s1)==0)?"YES":"NO"));
*/
//aes128cbc
/*
	jry_bl_string_clear(&s2);jry_bl_string_clear(&s3);jry_bl_string_clear(&s4);
	jry_bl_aes_128_cbc_encode(keyy,"0CoJUm6Qyw8W8jud",&s1,&s3);jry_bl_base64_encode(&s3,&s2);jry_bl_string_clear(&s3);
	jry_bl_string_stream_reset(&ss1);jry_bl_string_stream_reset(&ss3);jry_bl_string_stream_reset(&ss4);jry_bl_stream_reset(&b64en);jry_bl_stream_reset(&b64de);
	jry_bl_stream_connect(&ss1,&aes128cbcen);
	jry_bl_stream_connect(&aes128cbcen,&b64en);
	jry_bl_stream_connect(&b64en,&ss3);
	jry_bl_stream_connect(&ss3,&b64de);
	jry_bl_stream_connect(&b64de,&aes128cbcde);
	jry_bl_stream_connect(&aes128cbcde,&ss4);
	jry_bl_stream_do(&ss1,jry_bl_stream_force);
	jry_bl_string_view(&s2;
	jry_bl_string_view(&s3;	
	jry_bl_string_view(&s4;	
	printf("AES 128 CBC encode %s\n",((jry_bl_string_space_ship(&s2,&s3)==0)?"YES":"NO"));
	printf("AES 128 CBC decode %s\n",((jry_bl_string_space_ship(&s4,&s1)==0)?"YES":"NO"));
*/



	jry_bl_string_stream_free(&ss1);
	jry_bl_string_stream_free(&ss2);
	jry_bl_string_stream_free(&ss3);		
	jry_bl_string_stream_free(&ss4);		
	jry_bl_base64_encode_stream_free(&b64en);		
	jry_bl_base64_decode_stream_free(&b64de);		
	jry_bl_aes_128_ecb_encode_stream_free(&aes128ecben);
	jry_bl_aes_128_ecb_decode_stream_free(&aes128ecbde);
	jry_bl_aes_128_cbc_encode_stream_free(&aes128cbcen);
	jry_bl_aes_128_cbc_decode_stream_free(&aes128cbcde);
	jry_bl_string_frees(4,&s1,&s2,&s3,&s4);	
	jry_bl_stop(); 	
}
