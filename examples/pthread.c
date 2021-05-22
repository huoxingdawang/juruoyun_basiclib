#include "main.h"
#if JBL_LOG_ENABLE ==1
#define thread_cnt 100
void * test(jbl_string * a)
{
    a=jbl_string_copy(a);
    a=jbl_string_add_double(a,123.456);
    jbl_string_view(a);
    a=jbl_string_free(a);
	return NULL;
}
#endif
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
#if JBL_PTHREAD_ENABLE==1
    jbl_string * s1=jbl_string_new();
    jbl_pthreads * threads=jbl_pthreads_new(2);
	threads=jbl_pthreads_creat_thread(threads,test,1,s1);
	threads=jbl_pthreads_wait(threads);
    threads=jbl_pthreads_free(threads);
    jbl_string_free(s1);
    
#endif	    
    

	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}
