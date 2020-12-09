#include "main.h"
#if JBL_SHA1_ENABLE ==1
#define thread_cnt 100
jbl_string *s1=NULL;
void *do_sha1(jbl_string * s2)
{
    for(int i=0;i<100;++i)
    {
        s2=jbl_sha1(s2,s1,false);
        s2=jbl_string_add_char(s2,'\n');
    }
    return NULL;
}
#endif
int main()
{
#if JBL_SHA1_ENABLE ==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	
    s1=jbl_string_add_chars(s1,UC"juruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyunjuruoyun");
    
    jbl_string *s2=jbl_string_new();
    jbl_string_free(jbl_refer(&s2));
    jbl_pthreads * threads=jbl_pthreads_new(thread_cnt);
	threads=jbl_pthreads_creat_thread(threads,do_sha1,thread_cnt,s2);
	threads=jbl_pthreads_wait(threads);
    threads=jbl_pthreads_free(threads);
    
	jbl_string_view(s1);
	jbl_string_view(s2);
//  pchars("ACC66DE3B01490CD99DFDA9D86FC513A\n");
	
	s1=jbl_string_free(s1);s2=jbl_string_free(s2);
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 
	return 0;
#endif
}