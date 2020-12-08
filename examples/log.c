#include "main.h"
#define thread_cnt 100
void * do_log(void * a)
{
	for(int i=0;i<100;++i){jbl_log(UC "%d",i);}
	return NULL;
}
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();
	jbl_log(UC "%d",1);
	jbl_log(UC "test %d%d%d %s %X %c juruoyun",1,123,456,"123123123121",0XFE,'a');
	jbl_log(UC "%errstr",1);
#if JBL_STRING_ENABLE ==1
	jbl_string * s1=jbl_string_add_const(NULL,UC "jbl_string test");
	jbl_log(UC "%j",s1);
	s1=jbl_string_free(s1);
#endif	
#if JBL_PTHREAD_ENABLE==1
	pl();
    jbl_pthreads * threads=jbl_pthreads_new(thread_cnt);
	threads=jbl_pthreads_creat_thread(threads,do_log,thread_cnt,NULL);
	threads=jbl_pthreads_wait(threads);
    threads=jbl_pthreads_free(threads);
#endif	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
