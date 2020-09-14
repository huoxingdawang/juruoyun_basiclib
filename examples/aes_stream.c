#include "main.h"
//TODO
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_aes_128_key *key=jbl_aes_128_key_set(NULL,UC"0CoJUm6Qyw8W8jud");
	jbl_file *f1=jbl_file_open_chars(NULL,UC"tmp/bigfile.tmp",JBL_FILE_READ);
	jbl_stream* fs1=jbl_file_stream_new(jbl_refer(&f1));
	
	
	
	jbl_string *s4=jbl_string_extend(NULL,jbl_file_get_size(f1)/3*4+4);
	jbl_stream* ss4=jbl_string_stream_new(jbl_refer(&s4));
	jbl_stream* b64en=jbl_stream_base64_encode_new();
	jbl_stream *cbcen=jbl_stream_aes_128_cbc_encode_new(key,UC"0CoJUm6Qyw8W8jud");

	jbl_stream_connect(fs1,cbcen);
	jbl_stream_connect(cbcen,b64en);
	jbl_stream_connect(b64en,ss4);
	
	
	
	jbl_time * t1=jbl_time_now(NULL);
	jbl_stream_do(fs1,jbl_stream_force);
	jbl_time * t2=jbl_time_now(NULL);
	pchars(UC "C   AES 128 CBC encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);
	f1=jbl_file_free(f1);	
	fs1=jbl_stream_free(fs1);	
	ss4=jbl_stream_free(ss4);	
	b64en=jbl_stream_free(b64en);	
	cbcen=jbl_stream_free(cbcen);	
	
	f1=jbl_file_open_chars(NULL,UC"testfiles/aes_128_cbc_encode.out",JBL_FILE_WRITE);
	f1=jbl_file_write(f1,s4);
	f1=jbl_file_free(f1);	
	jbl_string *sr=jbl_execute_cmd_chars(UC "php testfiles/aes128cbc.php  tmp/bigfile.tmp",NULL);

	f1=jbl_file_open_chars(NULL,UC"testfiles/aes_128_cbc_encode.ans",JBL_FILE_READ);
	jbl_string *s1=jbl_file_read(f1,NULL,0,-1);
	f1=jbl_file_free(f1);	
	puint(jbl_string_if_equal(s1,s4));pchars("\n");pf();
	s1=jbl_string_free(s1);

	jbl_string *s2=jbl_string_extend(NULL,jbl_string_get_length(s4));
	jbl_stream* ss2=jbl_string_stream_new(jbl_refer(&s2));
	jbl_stream* b64de=jbl_stream_base64_decode_new();
	jbl_stream *cbcde=jbl_stream_aes_128_cbc_decode_new(key,UC"0CoJUm6Qyw8W8jud");
	jbl_stream_connect(b64de,cbcde);
	jbl_stream_connect(cbcde,ss2);
	t1=jbl_time_now(NULL);
	jbl_stream_push_string(b64de,s4);
	jbl_stream_do(b64de,jbl_stream_force);
	t2=jbl_time_now(NULL);
	pchars(UC "C   AES 128 CBC decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);

	ss2=jbl_stream_free(ss2);	
	b64de=jbl_stream_free(b64de);	
	cbcde=jbl_stream_free(cbcde);


	f1=jbl_file_open_chars(NULL,UC"tmp/bigfile.tmp",JBL_FILE_READ);
	s1=jbl_file_read(f1,NULL,0,-1);
	f1=jbl_file_free(f1);	
	puint(jbl_string_if_equal(s1,s2));pchars("\n");pf();	
	s1=jbl_string_free(s1);
	s2=jbl_string_free(s2);
	s4=jbl_string_free(s4);
	jbl_stream_push_string(jbl_stream_stdout,sr);
	sr=jbl_string_free(sr);	










	f1=jbl_file_open_chars(NULL,UC"tmp/bigfile.tmp",JBL_FILE_READ);
	fs1=jbl_file_stream_new(jbl_refer(&f1));
	
	s4=jbl_string_extend(NULL,jbl_file_get_size(f1)/3*4+4);
	ss4=jbl_string_stream_new(jbl_refer(&s4));
	b64en=jbl_stream_base64_encode_new();
	jbl_stream *ecben=jbl_stream_aes_128_ecb_encode_new(key);

	jbl_stream_connect(fs1,ecben);
	jbl_stream_connect(ecben,b64en);
	jbl_stream_connect(b64en,ss4);
	
	t1=jbl_time_now(NULL);
	jbl_stream_do(fs1,jbl_stream_force);
	t2=jbl_time_now(NULL);
	pchars(UC "C   AES 128 ECB encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);
	f1=jbl_file_free(f1);	
	fs1=jbl_stream_free(fs1);	
	ss4=jbl_stream_free(ss4);	
	b64en=jbl_stream_free(b64en);	
	ecben=jbl_stream_free(ecben);	
	
	f1=jbl_file_open_chars(NULL,UC"testfiles/aes_128_ecb_encode.out",JBL_FILE_WRITE);
	f1=jbl_file_write(f1,s4);
	f1=jbl_file_free(f1);	
	sr=jbl_execute_cmd_chars(UC "php testfiles/aes128ecb.php  tmp/bigfile.tmp",NULL);

	f1=jbl_file_open_chars(NULL,UC"testfiles/aes_128_ecb_encode.ans",JBL_FILE_READ);
	s1=jbl_file_read(f1,NULL,0,-1);
	f1=jbl_file_free(f1);	
	puint(jbl_string_if_equal(s1,s4));pchars("\n");pf();
	s1=jbl_string_free(s1);

	s2=jbl_string_extend(NULL,jbl_string_get_length(s4));
	ss2=jbl_string_stream_new(jbl_refer(&s2));
	b64de=jbl_stream_base64_decode_new();
	jbl_stream *ecbde=jbl_stream_aes_128_ecb_decode_new(key);
	jbl_stream_connect(b64de,ecbde);
	jbl_stream_connect(ecbde,ss2);
	t1=jbl_time_now(NULL);
	jbl_stream_push_string(b64de,s4);
	jbl_stream_do(b64de,jbl_stream_force);
	t2=jbl_time_now(NULL);
	pchars(UC "C   AES 128 ECB decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);

	ss2=jbl_stream_free(ss2);	
	b64de=jbl_stream_free(b64de);	
	ecbde=jbl_stream_free(ecbde);

	f1=jbl_file_open_chars(NULL,UC"tmp/bigfile.tmp",JBL_FILE_READ);
	s1=jbl_file_read(f1,NULL,0,-1);
	f1=jbl_file_free(f1);	
	puint(jbl_string_if_equal(s1,s2));pchars("\n");pf();	
	s1=jbl_string_free(s1);
	s2=jbl_string_free(s2);
	s4=jbl_string_free(s4);
	jbl_stream_push_string(jbl_stream_stdout,sr);
	sr=jbl_string_free(sr);	








	
	key=jbl_aes_128_key_free(key);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
}
