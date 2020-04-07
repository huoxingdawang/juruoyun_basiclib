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
	s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);s4=jry_bl_string_free(s4);
	
	
	
	
	s2=jry_bl_aes_128_cbc_encode(key,"0CoJUm6Qyw8W8jud",s1,NULL);
	s4=jry_bl_base64_encode(s2,NULL);	
	s3=jry_bl_aes_128_cbc_decode(key,"0CoJUm6Qyw8W8jud",s2,NULL);
	jry_bl_string_view(s4);
	jry_bl_string_view(s3);	
	s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);s4=jry_bl_string_free(s4);
	
	s1=jry_bl_string_free(s1);
	
	key=jry_bl_aes_128_free_key(key);
	jry_bl_stop();	
}
