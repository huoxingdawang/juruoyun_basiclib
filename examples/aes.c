#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	FILE * fp;
	jry_bl_aes_128_key *key=jry_bl_aes_128_extend_key("0CoJUm6Qyw8W8jud");

	jry_bl_string *s1=jry_bl_string_new(),*s2=NULL,*s3=NULL,*s4=NULL,*s5=NULL;
	s1=jry_bl_string_add_chars(s1,"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	s2=jry_bl_aes_128_ecb_encode(key,s1,NULL);
	s4=jry_bl_base64_encode(s2,NULL);	
	s3=jry_bl_aes_128_ecb_decode(key,s2,NULL);
	jry_bl_string_view(s4);
	jry_bl_string_view(s3);
#if JRY_BL_STREAM_ENABLE==1
	jry_bl_stream *ss1=jry_bl_string_stream_new(jry_bl_refer(&s1));
	jry_bl_stream *ss4=jry_bl_string_stream_new(jry_bl_refer(&s4));
	jry_bl_stream *b64en=jry_bl_stream_base64_encode_new();
	jry_bl_stream *b64de=jry_bl_stream_base64_decode_new();
	jry_bl_stream *ecben=jry_bl_stream_aes_128_ecb_encode_new(key);
	jry_bl_stream *ecbde=jry_bl_stream_aes_128_ecb_decode_new(key);
	
	jry_bl_stream_connect(ss1,ecben);
	jry_bl_stream_connect(ecben,b64en);
	jry_bl_stream_connect(b64en,sout);
	jry_bl_stream_do(ss1,jry_bl_stream_force);
	putchar('\n');
	jry_bl_stream_connect(ss4,b64de);
	jry_bl_stream_connect(b64de,ecbde);
	jry_bl_stream_connect(ecbde,sout);
	jry_bl_stream_do(ss4,jry_bl_stream_force);
	putchar('\n');

	ss1=jry_bl_stream_free(ss1);	
	ss4=jry_bl_stream_free(ss4);	
	b64en=jry_bl_stream_free(b64en);	
	b64de=jry_bl_stream_free(b64de);	
	ecben=jry_bl_stream_free(ecben);	
	ecbde=jry_bl_stream_free(ecbde);	
#endif	
	s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);s4=jry_bl_string_free(s4);
	
	
	
	
	s2=jry_bl_aes_128_cbc_encode(key,"0CoJUm6Qyw8W8jud",s1,NULL);
	s4=jry_bl_base64_encode(s2,NULL);	
	s3=jry_bl_aes_128_cbc_decode(key,"0CoJUm6Qyw8W8jud",s2,NULL);
	jry_bl_string_view(s4);
	jry_bl_string_view(s3);	
#if JRY_BL_STREAM_ENABLE==1
	ss1=jry_bl_string_stream_new(jry_bl_refer(&s1));
	ss4=jry_bl_string_stream_new(jry_bl_refer(&s4));
	b64en=jry_bl_stream_base64_encode_new();
	b64de=jry_bl_stream_base64_decode_new();
	jry_bl_stream *cbcen=jry_bl_stream_aes_128_cbc_encode_new(key,"0CoJUm6Qyw8W8jud");
	jry_bl_stream *cbcde=jry_bl_stream_aes_128_cbc_decode_new(key,"0CoJUm6Qyw8W8jud");
	
	jry_bl_stream_connect(ss1,cbcen);
	jry_bl_stream_connect(cbcen,b64en);
	jry_bl_stream_connect(b64en,sout);
	jry_bl_stream_do(ss1,jry_bl_stream_force);
	putchar('\n');
	jry_bl_stream_connect(ss4,b64de);
	jry_bl_stream_connect(b64de,cbcde);
	jry_bl_stream_connect(cbcde,sout);
	jry_bl_stream_do(ss4,jry_bl_stream_force);
	putchar('\n');

	ss1=jry_bl_stream_free(ss1);	
	ss4=jry_bl_stream_free(ss4);	
	b64en=jry_bl_stream_free(b64en);	
	b64de=jry_bl_stream_free(b64de);	
	cbcen=jry_bl_stream_free(cbcen);	
	cbcde=jry_bl_stream_free(cbcde);	
#endif	
	s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);s4=jry_bl_string_free(s4);



	
	
	s1=jry_bl_string_free(s1);
	key=jry_bl_aes_128_free_key(key);
	jry_bl_stop();	
}
