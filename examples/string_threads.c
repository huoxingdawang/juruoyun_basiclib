#include "main.h"


       
#define thread_cnt 10
void do_string(jbl_string * s1)
{
printf("0X%llX\n",pthread_self());
    for(int i=0;i<100;++i)
    {
        s1=jbl_string_add_chars(s1,UC"juruoyun\n");
        s1=jbl_string_add_char(s1,'c');
    }
}
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
#if JBL_PTHREAD_ENABLE==1
    jbl_string *s1=jbl_string_new();
    jbl_pthreads * threads=jbl_pthreads_new(thread_cnt);
	threads=jbl_pthreads_creat_thread(threads,do_string,thread_cnt,s1);
	threads=jbl_pthreads_wait(threads);
    threads=jbl_pthreads_free(threads);
//    printf("%s",s1->s);
//    printf("%lld",s1->len);
//    jbl_string_view(s1);
    s1=jbl_string_free(s1);
#endif
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}