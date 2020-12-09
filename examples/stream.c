#include "main.h"
#if JBL_STREAM_ENABLE ==1
#define thread_cnt 100
void *do_stream(void * p)
{
    for(int i=0;i<100;++i)
    {
lo();
        puint(jbl_pthread_get_id());    pt();
        pchars((char *)p);              pt();
        phex(i);                        pt();
        pint(i);                        pt();
        pint(-i);                       pt();
        pchars((char *)p);              pn();
ulo(); 
    }
    return NULL;
}
#endif
int main()
{
#if JBL_STREAM_ENABLE ==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
    jbl_pthreads * threads=jbl_pthreads_new(thread_cnt);
	threads=jbl_pthreads_creat_thread(threads,do_stream,thread_cnt,"juruoyun蒟蒻云");
	threads=jbl_pthreads_wait(threads);
    threads=jbl_pthreads_free(threads);
	jbl_string *s1=jbl_string_new();
	jbl_string_view(s1);
	s1=jbl_string_read(s1,UC"Input something:");
	jbl_string_view(s1);
	s1=jbl_string_read(s1,UC"Input something else:");
	jbl_string_view(s1);
	s1=jbl_string_read(s1,UC"Input something else:");
	jbl_string_view(s1);
	s1=jbl_string_free(s1);

	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
#endif
}