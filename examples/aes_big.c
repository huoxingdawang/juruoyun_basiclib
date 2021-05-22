#include "main.h"
//TODO
int main()
{
#if JBL_AES_128_ENABLE==1 && JBL_FILE_ENABLE ==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_aes_128_key *key=jbl_aes_128_key_set(NULL,UC"0CoJUm6Qyw8W8jud");
	jbl_file   *f1=jbl_file_open_chars(NULL,UC"tmp/bigfile.tmp",JBL_FILE_READ);
	jbl_string *source=jbl_file_read(f1,NULL,0,-1ULL);
	f1=jbl_file_free(f1);
    {
        //CBC加解密
        {
            jbl_time *t1=NULL,*t2=NULL;
            
            t1=jbl_time_now(t1);
            jbl_string *s2=jbl_aes_128_cbc_encode(key,UC"0CoJUm6Qyw8W8jud",source,NULL);
            jbl_string *s3=jbl_base64_encode(s2,NULL);
            t2=jbl_time_now(t2);
            pchars(UC "C   AES 128 CBC encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();

            f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_encode.out",JBL_FILE_WRITE);
            f1=jbl_file_write(f1,s3);
            f1=jbl_file_free(f1);

            t1=jbl_time_now(t1);
            jbl_string *s4=jbl_base64_decode(s3,NULL);
            jbl_string *s5=jbl_aes_128_cbc_decode(key,UC"0CoJUm6Qyw8W8jud",s4,NULL);
            t2=jbl_time_now(t2);
            pchars(UC "C   AES 128 CBC decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
            
            f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_decode.out",JBL_FILE_WRITE);
            f1=jbl_file_write(f1,s5);
            f1=jbl_file_free(f1);

            t1=jbl_time_free(t1);
            t2=jbl_time_free(t2);
            s2=jbl_string_free(s2);
            s3=jbl_string_free(s3);
            s4=jbl_string_free(s4);
            s5=jbl_string_free(s5);
            
        }
        //PHP CBC加解密
        {
            jbl_string *sr=jbl_execute_cmd_chars(UC "php testfiles/aes128cbc.php  tmp/bigfile.tmp",NULL);
            jbl_stream_push_string(jbl_stream_stdout,sr);
            sr=jbl_string_free(sr);	
        }
        //比较加密结果
        {
            jbl_file   *f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_encode.out",JBL_FILE_READ);
            jbl_file   *f2=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_encode.ans",JBL_FILE_READ);
            jbl_string *s1=jbl_file_read(f1,NULL,0,-1ULL);
            jbl_string *s2=jbl_file_read(f2,NULL,0,-1ULL);
            f1=jbl_file_free(f1);
            pchars("AES CBC encode ");pchars(jbl_string_if_equal(s1,s2)?"equal":"error");pchars("\n");pf();
            s1      =jbl_string_free(s1);
            s2      =jbl_string_free(s2);
            f1      =jbl_file_free  (f1);
            f2      =jbl_file_free  (f2);
        }
        //比较解密结果
        {
            jbl_file   *f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_decode.out",JBL_FILE_READ);
            jbl_file   *f2=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_decode.ans",JBL_FILE_READ);
            jbl_string *s1=jbl_file_read(f1,NULL,0,-1ULL);
            jbl_string *s2=jbl_file_read(f2,NULL,0,-1ULL);
            f1=jbl_file_free(f1);
            pchars("AES CBC decode ");pchars(jbl_string_if_equal(s1,s2)?"equal":"error");pchars("\n");pf();
            s1      =jbl_string_free(s1);
            s2      =jbl_string_free(s2);
            f1      =jbl_file_free  (f1);
            f2      =jbl_file_free  (f2);
        }    
    }
    {
        //ECB加解密
        {
            jbl_time *t1=NULL,*t2=NULL;
            
            t1=jbl_time_now(t1);
            jbl_string *s2=jbl_aes_128_ecb_encode(key,source,NULL);
            jbl_string *s3=jbl_base64_encode(s2,NULL);
            t2=jbl_time_now(t2);
            pchars(UC "C   AES 128 ECB encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();

            f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_encode.out",JBL_FILE_WRITE);
            f1=jbl_file_write(f1,s3);
            f1=jbl_file_free(f1);

            t1=jbl_time_now(t1);
            jbl_string *s4=jbl_base64_decode(s3,NULL);
            jbl_string *s5=jbl_aes_128_ecb_decode(key,s4,NULL);
            t2=jbl_time_now(t2);
            pchars(UC "C   AES 128 ECB decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
            
            f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_decode.out",JBL_FILE_WRITE);
            f1=jbl_file_write(f1,s5);
            f1=jbl_file_free(f1);

            t1=jbl_time_free(t1);
            t2=jbl_time_free(t2);
            s2=jbl_string_free(s2);
            s3=jbl_string_free(s3);
            s4=jbl_string_free(s4);
            s5=jbl_string_free(s5);
            
        }        
        //PHP ECB加解密
        {
            jbl_string *sr=jbl_execute_cmd_chars(UC "php testfiles/aes128ecb.php  tmp/bigfile.tmp",NULL);
            jbl_stream_push_string(jbl_stream_stdout,sr);
            sr=jbl_string_free(sr);	
        }
        //比较加密结果
        {
            jbl_file   *f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_encode.out",JBL_FILE_READ);
            jbl_file   *f2=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_encode.ans",JBL_FILE_READ);
            jbl_string *s1=jbl_file_read(f1,NULL,0,-1ULL);
            jbl_string *s2=jbl_file_read(f2,NULL,0,-1ULL);
            f1=jbl_file_free(f1);
            pchars("AES ECB encode ");pchars(jbl_string_if_equal(s1,s2)?"equal":"error");pchars("\n");pf();
            s1      =jbl_string_free(s1);
            s2      =jbl_string_free(s2);
            f1      =jbl_file_free  (f1);
            f2      =jbl_file_free  (f2);
        }
        //比较解密结果
        {
            jbl_file   *f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_decode.out",JBL_FILE_READ);
            jbl_file   *f2=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_decode.ans",JBL_FILE_READ);
            jbl_string *s1=jbl_file_read(f1,NULL,0,-1ULL);
            jbl_string *s2=jbl_file_read(f2,NULL,0,-1ULL);
            f1=jbl_file_free(f1);
            pchars("AES ECB decode ");pchars(jbl_string_if_equal(s1,s2)?"equal":"error");pchars("\n");pf();
            s1      =jbl_string_free(s1);
            s2      =jbl_string_free(s2);
            f1      =jbl_file_free  (f1);
            f2      =jbl_file_free  (f2);
        }
    }

    
    
    
    
    
	source=jbl_string_free     (source);
	key   =jbl_aes_128_key_free(key);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    
    
    
    
    
    
	jbl_string *s1=jbl_string_copy(s0);
	
	
	s2=jbl_string_free(s2);
	pchars(UC "C   AES 128 CBC encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);
	
	f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_encode.out",JBL_FILE_WRITE);
	f1=jbl_file_write(f1,s3);
	f1=jbl_file_free(f1);	
	
	jbl_string *sr=jbl_execute_cmd_chars(UC "php testfiles/aes128cbc.php  tmp/bigfile.tmp",NULL);
		
	f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_encode.ans",JBL_FILE_READ);
	s1=jbl_file_read(f1,NULL,0,-1ULL);
	f1=jbl_file_free(f1);	
	puint(jbl_string_if_equal(s1,s3));pchars("\n");pf();
	s1=jbl_string_free(s1);
	
	
	
	
	t1=jbl_time_now(NULL);
	s2=jbl_base64_decode(s3,NULL);
	s3=jbl_string_free(s3);
	s1=jbl_aes_128_cbc_decode(key,UC"0CoJUm6Qyw8W8jud",s2,NULL);
	s2=jbl_string_free(s2);
	t2=jbl_time_now(NULL);
	pchars(UC "C   AES 128 CBC decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);	
	puint(jbl_string_if_equal(s1,s0));pchars("\n");pf();
	s1=jbl_string_free(s1);
	
	
	jbl_stream_push_string(jbl_stream_stdout,sr);
	sr=jbl_string_free(sr);
	
	
	
	s1=jbl_string_copy(s0);
	t1=jbl_time_now(NULL);
	s2=jbl_aes_128_ecb_encode(key,s1,NULL);
	s1=jbl_string_free(s1);
	s3=jbl_base64_encode(s2,NULL);
	s2=jbl_string_free(s2);
	t2=jbl_time_now(NULL);
	pchars(UC "C   AES 128 ECB encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);
	
	f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_encode.out",JBL_FILE_WRITE);
	f1=jbl_file_write(f1,s3);
	f1=jbl_file_free(f1);	
	
	sr=jbl_execute_cmd_chars(UC "php testfiles/aes128ecb.php  tmp/bigfile.tmp",NULL);
		
	f1=jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_encode.ans",JBL_FILE_READ);
	s1=jbl_file_read(f1,NULL,0,-1ULL);
	f1=jbl_file_free(f1);	
	puint(jbl_string_if_equal(s1,s3));pchars("\n");pf();
	s1=jbl_string_free(s1);
	
	
	
	
	t1=jbl_time_now(NULL);
	s2=jbl_base64_decode(s3,NULL);
	s3=jbl_string_free(s3);
	s1=jbl_aes_128_ecb_decode(key,s2,NULL);
	s2=jbl_string_free(s2);
	t2=jbl_time_now(NULL);
	pchars(UC "C   AES 128 ECB decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
	t1=jbl_time_free(t1);
	t2=jbl_time_free(t2);	
	puint(jbl_string_if_equal(s1,s0));pchars("\n");pf();
	s1=jbl_string_free(s1);
	
	
	jbl_stream_push_string(jbl_stream_stdout,sr);
	sr=jbl_string_free(sr);
		
	*/
	
	
	
	
	
	
	
	
	
	
	
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
#endif
}
