#include "main.h"
#include <time.h>
jbl_uint32 slot=2048,base=19;
jbl_uint32 small=90;
jbl_uint32 large=5;
jbl_uint32 huge=5;
#define thread_cnt 8
typedef struct
{
    jbl_uint32 slot;jbl_uint64 n;
    jbl_uint32 small,large,huge;
}do_malloc_data;
jbl_uint32 get_size(do_malloc_data *data)
{
	register jbl_uint32 size;
	jbl_uint32 r=jbl_rand_between(0,data->small+data->large+data->huge-2);
	if(r<data->small)			        size=(jbl_rand()%3072)+1;
	else if(r<data->small+data->large)	size=((jbl_rand())%(2093056-3073))+3073;
	else					            size=2093057+((jbl_rand())%2093056);
	return size;
}
void * do_malloc(do_malloc_data *data)
{
    puint(jbl_pthread_get_id());pn();pf();
	char **a=jbl_malloc(data->slot*sizeof(char*));
	for(jbl_uint32 i=0;i<data->slot;a[i]=NULL,++i);
	for(jbl_uint64 i=0;i<data->n;++i)
	{
		register jbl_uint32 pos=jbl_rand()%data->slot;
		if(a[pos])
			if(jbl_rand()&1)
				jbl_free(a[pos]),a[pos]=NULL;				
			else
			{
				jbl_uint32 size=get_size(data);
				a[pos]=jbl_realloc(a[pos],size);
				for(jbl_uint32 i=0;i<size;a[pos][i]=(char)(i&0XFF),i+=0XF);
			}				
		else
		{
				jbl_uint32 size=get_size(data);
			a[pos]=jbl_malloc(size);
			for(jbl_uint32 i=0;i<size;a[pos][i]=(char)(i&0XFF),i+=0XF);
		}
        jbl_pthread_check_exit();
	}
	for(jbl_uint32 i=0;i<data->slot;++i)if(a[i]!=NULL)jbl_free(a[i]);
	jbl_free(a);a=NULL;
    return NULL;
}
jbl_pthreads * threads;

int main()
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
    do_malloc_data data={slot,(1ULL<<base)/thread_cnt,small,large,huge};
    threads=jbl_pthreads_new(thread_cnt);
	threads=jbl_pthreads_creat_thread(threads,do_malloc,thread_cnt,&data);
	threads=jbl_pthreads_wait(threads);
    threads=jbl_pthreads_free(threads);

#if JBL_TIME_ENABLE ==1
	pchars("\nmalloc used time:");puint(jbl_time_minus((t2=jbl_time_now(t2)),t1));pchars("ms\n");
	t1=jbl_time_free(t1);t2=jbl_time_free(t2);	
#endif
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}