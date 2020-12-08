#include "main.h"


       
#define thread_cnt 10
void *do_string(jbl_string * s1)
{
    for(int i=0;i<100;++i)
    {
//      jbl_refer_pull_wrlock(s1);
        s1=jbl_string_add_const(s1,UC"juruoyun");
//      s1=jbl_string_add_chars(s1,UC"juruoyun\n");
//      s1=jbl_string_add_double(s1,-1123.456);
//      pdouble(jbl_string_get_double(s1));pn();
//      s1=jbl_string_add_double(s1,-789.0);
//      s1=jbl_string_add_hex(s1,0X123Aa);
//      phex(jbl_string_get_hex(s1));pn();
//      phex(jbl_string_get_hex_start_len(s1,0,2));pn();
//      s1=jbl_string_add_hex_8bits(s1,0X88);
//      s1=jbl_string_add_char(s1,'\n');
//      jbl_refer_pull_unwrlock(s1);
        if(jbl_string_get_length(s1)>64)
            s1=jbl_string_clear(s1);
        jbl_string_view(s1);
    }
    return NULL;
}
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
    jbl_string *s1=jbl_string_new();
    jbl_pthreads * threads=jbl_pthreads_new(thread_cnt);
	threads=jbl_pthreads_creat_thread(threads,do_string,thread_cnt,s1);
	threads=jbl_pthreads_wait(threads);
    threads=jbl_pthreads_free(threads);
    s1=jbl_string_free(s1);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}
