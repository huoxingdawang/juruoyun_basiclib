#include "main.h"
//TODO
int main()
{
#if JBL_AES_128_ENABLE==1 && JBL_FILE_ENABLE ==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_aes_128_key *key=jbl_aes_128_key_set(NULL,UC"0CoJUm6Qyw8W8jud");
    {
        {
            jbl_file   *f1          =jbl_file_open_chars(NULL,UC"tmp/bigfile.tmp",JBL_FILE_READ);
            jbl_file   *f2          =jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_encode.out",JBL_FILE_WRITE);
            jbl_file_free  (jbl_refer(&f1));
            jbl_file_free  (jbl_refer(&f2));
            jbl_stream * s_f1       =jbl_file_stream_new(f1);
            jbl_stream * s_f2       =jbl_file_stream_new(f2);
            jbl_stream * b64en      =jbl_stream_base64_encode_new();
            jbl_stream * cbcen      =jbl_stream_aes_128_cbc_encode_new(key,UC"0CoJUm6Qyw8W8jud");
            
            jbl_stream_connect(s_f1 ,cbcen);
            jbl_stream_connect(cbcen,b64en);
            jbl_stream_connect(b64en,s_f2);
            
            jbl_time * t1=jbl_time_now(NULL);
            jbl_stream_do(s_f1,true);
            jbl_time * t2=jbl_time_now(NULL);
            pchars(UC "C   AES 128 CBC encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
            t1=jbl_time_free(t1);
            t2=jbl_time_free(t2);
            
            
            f1      =jbl_file_free  (f1);	
            f2      =jbl_file_free  (f2);	
            s_f1    =jbl_stream_free(s_f1);
            s_f2    =jbl_stream_free(s_f2);
            b64en   =jbl_stream_free(b64en);
            cbcen   =jbl_stream_free(cbcen);
            
        }
        {
            jbl_file   *f1    =jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_encode.out",JBL_FILE_READ);
            jbl_file   *f2    =jbl_file_open_chars(NULL,UC"tmp/aes_128_cbc_decode.out",JBL_FILE_WRITE);
            jbl_file_free  (jbl_refer(&f1));
            jbl_file_free  (jbl_refer(&f2));
            jbl_stream * s_f1       =jbl_file_stream_new(f1);
            jbl_stream * s_f2       =jbl_file_stream_new(f2);
            jbl_stream * b64de      =jbl_stream_base64_decode_new();
            jbl_stream * cbcde      =jbl_stream_aes_128_cbc_decode_new(key,UC"0CoJUm6Qyw8W8jud");
            
            jbl_stream_connect(s_f1 ,b64de);
            jbl_stream_connect(b64de,cbcde);
            jbl_stream_connect(cbcde,s_f2);
            
            jbl_time * t1=jbl_time_now(NULL);
            jbl_stream_do(s_f1,true);
            jbl_time * t2=jbl_time_now(NULL);
            pchars(UC "C   AES 128 CBC decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
            t1=jbl_time_free(t1);
            t2=jbl_time_free(t2);
            
            
            f1      =jbl_file_free  (f1);	
            f2      =jbl_file_free  (f2);	
            s_f1    =jbl_stream_free(s_f1);
            s_f2    =jbl_stream_free(s_f2);
            b64de   =jbl_stream_free(b64de);
            cbcde   =jbl_stream_free(cbcde);
            
        }
        {
            jbl_string *sr=jbl_execute_cmd_chars(UC "php testfiles/aes128cbc.php  tmp/bigfile.tmp",NULL);
            jbl_stream_push_string(jbl_stream_stdout,sr);
            sr=jbl_string_free(sr);	
        }
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
        {
            jbl_file   *f1          =jbl_file_open_chars(NULL,UC"tmp/bigfile.tmp",JBL_FILE_READ);
            jbl_file   *f2          =jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_encode.out",JBL_FILE_WRITE);
            jbl_file_free  (jbl_refer(&f1));
            jbl_file_free  (jbl_refer(&f2));
            jbl_stream * s_f1       =jbl_file_stream_new(f1);
            jbl_stream * s_f2       =jbl_file_stream_new(f2);
            jbl_stream * b64en      =jbl_stream_base64_encode_new();
            jbl_stream * ecben      =jbl_stream_aes_128_ecb_encode_new(key);
            
            jbl_stream_connect(s_f1 ,ecben);
            jbl_stream_connect(ecben,b64en);
            jbl_stream_connect(b64en,s_f2);
            
            jbl_time * t1=jbl_time_now(NULL);
            jbl_stream_do(s_f1,true);
            jbl_time * t2=jbl_time_now(NULL);
            pchars(UC "C   AES 128 ECB encode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
            t1=jbl_time_free(t1);
            t2=jbl_time_free(t2);
            
            
            f1      =jbl_file_free  (f1);	
            f2      =jbl_file_free  (f2);	
            s_f1    =jbl_stream_free(s_f1);
            s_f2    =jbl_stream_free(s_f2);
            b64en   =jbl_stream_free(b64en);
            ecben   =jbl_stream_free(ecben);
            
        }
        {
            jbl_file   *f1    =jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_encode.out",JBL_FILE_READ);
            jbl_file   *f2    =jbl_file_open_chars(NULL,UC"tmp/aes_128_ecb_decode.out",JBL_FILE_WRITE);
            jbl_file_free  (jbl_refer(&f1));
            jbl_file_free  (jbl_refer(&f2));
            jbl_stream * s_f1       =jbl_file_stream_new(f1);
            jbl_stream * s_f2       =jbl_file_stream_new(f2);
            jbl_stream * b64de      =jbl_stream_base64_decode_new();
            jbl_stream * cbcde      =jbl_stream_aes_128_ecb_decode_new(key);
            
            jbl_stream_connect(s_f1 ,b64de);
            jbl_stream_connect(b64de,cbcde);
            jbl_stream_connect(cbcde,s_f2);
            
            jbl_time * t1=jbl_time_now(NULL);
            jbl_stream_do(s_f1,true);
            jbl_time * t2=jbl_time_now(NULL);
            pchars(UC "C   AES 128 ECB decode used time:");puint(jbl_time_minus(t2,t1));pchars("ms\n");pf();
            t1=jbl_time_free(t1);
            t2=jbl_time_free(t2);
            
            
            f1      =jbl_file_free  (f1);	
            f2      =jbl_file_free  (f2);	
            s_f1    =jbl_stream_free(s_f1);
            s_f2    =jbl_stream_free(s_f2);
            b64de   =jbl_stream_free(b64de);
            cbcde   =jbl_stream_free(cbcde);
            
        }
        {
            jbl_string *sr=jbl_execute_cmd_chars(UC "php testfiles/aes128ecb.php  tmp/bigfile.tmp",NULL);
            jbl_stream_push_string(jbl_stream_stdout,sr);
            sr=jbl_string_free(sr);	
        }
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




	
	key=jbl_aes_128_key_free(key);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
#endif	
}
