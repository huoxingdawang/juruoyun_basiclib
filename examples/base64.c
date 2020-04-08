#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	
	jry_bl_string *s1=jry_bl_string_new(),*s2=NULL,*s3=NULL;
	s1=jry_bl_string_add_chars(s1,"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
	s2=jry_bl_base64_encode(s1,NULL);
	s3=jry_bl_base64_decode(s2,NULL);
	
	jry_bl_string_view(s1);
	jry_bl_string_view(s2);
	jry_bl_string_view(s3);
	
#if JRY_BL_STREAM_ENABLE==1
	jry_bl_stream *ss1=jry_bl_string_stream_new(jry_bl_refer(&s1));
	jry_bl_stream *ss2=jry_bl_string_stream_new(jry_bl_refer(&s2));
	jry_bl_stream *b64en=jry_bl_base64_encode_stream_init();
	jry_bl_stream *b64de=jry_bl_base64_decode_stream_init();
	
	jry_bl_stream_connect(ss1,b64en);
	jry_bl_stream_connect(b64en,sout);
	jry_bl_stream_do(ss1,jry_bl_stream_force);
	putchar('\n');
	jry_bl_stream_connect(ss2,b64de);
	jry_bl_stream_connect(b64de,sout);
	jry_bl_stream_do(ss2,jry_bl_stream_force);
	putchar('\n');

	ss1=jry_bl_stream_free(ss1);	
	ss2=jry_bl_stream_free(ss2);	
	b64en=jry_bl_stream_free(b64en);	
	b64de=jry_bl_stream_free(b64de);	
#endif	
	
	s1=jry_bl_string_free(s1);s2=jry_bl_string_free(s2);s3=jry_bl_string_free(s3);

	jry_bl_stop();
	return 0;
}