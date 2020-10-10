#include "main.h"
#if JBL_PTHREAD_ENABLE==1
void * do_thread(void * a)
{
	for(int i=0;i<100;++i){louts();pchars("juruoyun\n");ulouts();}
	return NULL;
}
void * do_thread2(void * a)
{
	for(int i=0;i<100;++i){louts();pchar('1');pchar('\n');ulouts();}

	return NULL;
}
#define thread 100
#endif
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
//	jbl_string *s1=jbl_string_new();
//	jbl_string_view(s1);
//	s1=jbl_string_read(s1,UC"Input something:");
//	jbl_string_view(s1);
//	s1=jbl_string_read(s1,UC"Input something else:");
//	jbl_string_view(s1);
//	s1=jbl_string_read(s1,UC"Input something else:");
//	jbl_string_view(s1);
//	s1=jbl_string_free(s1);
	for(int i=0;i<10;++i)pchars("juruoyun\n");
#if JBL_PTHREAD_ENABLE==1
	pl();
	pthread_t t[thread];
	{
		int i=0;
		for(;i<thread/2;pthread_create(&t[i],NULL,do_thread,NULL),++i);
		for(;i<thread;pthread_create(&t[i],NULL,do_thread2,NULL),++i);
	}
	for(int i=0;i<thread;pthread_join(t[i],NULL),++i);	
	pl();
#endif


	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 	
}