#include "main.h"
#include <time.h>
jbl_uint32 get_size(jbl_uint32 small,jbl_uint32 large,jbl_uint32 huge)
{
	register jbl_uint32 size;
	jbl_uint32 r=jbl_rand_between(0,small+large+huge-2);
	if(r<small)			    size=(jbl_rand()%3072)+1;
	else if(r<small+large)	size=((jbl_rand())%(2093056-3073))+3073;
	else					size=2093057+((jbl_rand())%2093056);
	return size;
}
jbl_uint32 slot=2048,base=19;
jbl_uint32 small=90;
jbl_uint32 large=5;
jbl_uint32 huge=5;
#define thread_cnt 4
void do_malloc(jbl_uint32 slot,jbl_uint64 n,jbl_uint32 small,jbl_uint32 large,jbl_uint32 huge)
{
	char **a=jbl_malloc(slot*sizeof(char*));
	for(jbl_uint32 i=0;i<slot;a[i]=NULL,++i);
	for(jbl_uint64 i=0;i<n;++i)
	{
		register jbl_uint32 pos=jbl_rand()%slot;
		if(a[pos])
			if(jbl_rand()&1)
				jbl_free(a[pos]),a[pos]=NULL;				
			else
			{
				jbl_uint32 size=get_size(small,large,huge);
				a[pos]=jbl_realloc(a[pos],size);
				for(jbl_uint32 i=0;i<size;a[pos][i]=(char)(i&0XFF),i+=0XF);
			}				
		else
		{
			jbl_uint32 size=get_size(small,large,huge);
			a[pos]=jbl_malloc(size);
			for(jbl_uint32 i=0;i<size;a[pos][i]=(char)(i&0XFF),i+=0XF);
		}
	}
	for(jbl_uint32 i=0;i<slot;++i)if(a[i]!=NULL)jbl_free(a[i]);
	jbl_free(a);a=NULL;
}
void * do_thread(void * a)
{
	do_malloc(slot/thread_cnt,((jbl_uint32)(1<<base))/thread_cnt,small,large,huge);
	a++;
    return NULL;
}
pthread_t threads[thread_cnt];
int mainn()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_uint32 seed=((jbl_uint32)time(0));
    jbl_rand_srand(seed);
	printf("seed=%d\n",seed);
	pchars("Input slot and base\n");pf();
	pchars("Slot:");pint(slot);pt();pchars("Base:");pint(base);pn();pf();
	pchars("Small:");pdouble(small*100.0/(small+large+huge));pchar('%');pt();pchars("Large:");pdouble(large*100.0/(small+large+huge));pchar('%');pt();pchars("Huge:");pdouble(huge*100.0/(small+large+huge));pchar('%');pn();pf();
#if JBL_TIME_ENABLE ==1
	jbl_time *t1=NULL,*t2=NULL;
	t1=jbl_time_now(t1);
#endif
//	pl();
#if JBL_PTHREAD_ENABLE==1
	for(jbl_uint32 i=0;i<thread_cnt;pthread_create(&threads[i],NULL,do_thread,NULL),++i);
	for(jbl_uint32 i=0;i<thread_cnt;pthread_join(threads[i],NULL),++i);
#else
	do_malloc(slot,(1ULL<<base),small,large,huge);	
#endif
	
    
#if JBL_TIME_ENABLE ==1
	pchars("\nmalloc used time:");puint(jbl_time_minus((t2=jbl_time_now(t2)),t1));pchars("ms\n");
	t1=jbl_time_free(t1);t2=jbl_time_free(t2);	
#endif
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}
int main()
{
    for(int i=1;i<=1000;++i)
        printf("%d\n",i),mainn();
}