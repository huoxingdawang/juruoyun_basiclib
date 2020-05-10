#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	FILE * fp;
	jbl_aes_128_key *key=jbl_aes_128_extend_key("0CoJUm6Qyw8W8jud");

	jbl_string *s1=jbl_string_new(),*s2=NULL,*s3=NULL,*s4=NULL,*s5=NULL;
	s1=jbl_string_add_chars(s1,"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	s2=jbl_aes_128_ecb_encode(key,s1,NULL);
	s4=jbl_base64_encode(s2,NULL);	
	s3=jbl_aes_128_ecb_decode(key,s2,NULL);
	jbl_string_view(s4);
	jbl_string_view(s3);
#if JBL_STREAM_ENABLE==1
	jbl_stream *ss1=jbl_string_stream_new(jbl_refer(&s1));
	jbl_stream *ss4=jbl_string_stream_new(jbl_refer(&s4));
	jbl_stream *b64en=jbl_stream_base64_encode_new();
	jbl_stream *b64de=jbl_stream_base64_decode_new();
	jbl_stream *ecben=jbl_stream_aes_128_ecb_encode_new(key);
	jbl_stream *ecbde=jbl_stream_aes_128_ecb_decode_new(key);
	
	jbl_stream_connect(ss1,ecben);
	jbl_stream_connect(ecben,b64en);
	jbl_stream_connect(b64en,sout);
	jbl_stream_do(ss1,jbl_stream_force);
	putchar('\n');
	jbl_stream_connect(ss4,b64de);
	jbl_stream_connect(b64de,ecbde);
	jbl_stream_connect(ecbde,sout);
	jbl_stream_do(ss4,jbl_stream_force);
	putchar('\n');

	ss1=jbl_stream_free(ss1);	
	ss4=jbl_stream_free(ss4);	
	b64en=jbl_stream_free(b64en);	
	b64de=jbl_stream_free(b64de);	
	ecben=jbl_stream_free(ecben);	
	ecbde=jbl_stream_free(ecbde);	
#endif	
	s2=jbl_string_free(s2);s3=jbl_string_free(s3);s4=jbl_string_free(s4);
	
	
	
	
	s2=jbl_aes_128_cbc_encode(key,"0CoJUm6Qyw8W8jud",s1,NULL);
	s4=jbl_base64_encode(s2,NULL);	
	s3=jbl_aes_128_cbc_decode(key,"0CoJUm6Qyw8W8jud",s2,NULL);
	jbl_string_view(s4);
	jbl_string_view(s3);	
#if JBL_STREAM_ENABLE==1
	ss1=jbl_string_stream_new(jbl_refer(&s1));
	ss4=jbl_string_stream_new(jbl_refer(&s4));
	b64en=jbl_stream_base64_encode_new();
	b64de=jbl_stream_base64_decode_new();
	jbl_stream *cbcen=jbl_stream_aes_128_cbc_encode_new(key,"0CoJUm6Qyw8W8jud");
	jbl_stream *cbcde=jbl_stream_aes_128_cbc_decode_new(key,"0CoJUm6Qyw8W8jud");
	
	jbl_stream_connect(ss1,cbcen);
	jbl_stream_connect(cbcen,b64en);
	jbl_stream_connect(b64en,sout);
	jbl_stream_do(ss1,jbl_stream_force);
	putchar('\n');
	jbl_stream_connect(ss4,b64de);
	jbl_stream_connect(b64de,cbcde);
	jbl_stream_connect(cbcde,sout);
	jbl_stream_do(ss4,jbl_stream_force);
	putchar('\n');

	ss1=jbl_stream_free(ss1);	
	ss4=jbl_stream_free(ss4);	
	b64en=jbl_stream_free(b64en);	
	b64de=jbl_stream_free(b64de);	
	cbcen=jbl_stream_free(cbcen);	
	cbcde=jbl_stream_free(cbcde);	
#endif	
	s2=jbl_string_free(s2);s3=jbl_string_free(s3);s4=jbl_string_free(s4);



	
	
	s1=jbl_string_free(s1);
	key=jbl_aes_128_free_key(key);
	jbl_stop();	
}
