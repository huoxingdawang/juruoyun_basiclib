#include "main.h"
jbl_uint32 get_size(int small,int large,int huge)
{
	register jbl_uint32 size;
	jbl_uint32 r=jbl_rand_between(0,small+large+huge);
	if(r<small)			    size=(jbl_rand()%3072)+1;
	else if(r<small+large)	size=((jbl_rand())%2093056)+3073;
	else					size=2093057+((jbl_rand())%2093056);
	return size;
}
int slot=2048,base=17;
int small=90;
int large=5;
int huge=5;
int thread=4;
void do_malloc(jbl_uint64 slot,jbl_uint64 n,jbl_uint64 small,jbl_uint64 large,jbl_uint64 huge)
{
	char **a=jbl_malloc(slot*sizeof(char*));
	for(int i=0;i<slot;a[i]=NULL,++i);
	for(jbl_uint64 i=0;i<n;++i)
	{
		register jbl_uint32 pos=jbl_rand()%slot;
		if(a[pos])
			if(jbl_rand())
				jbl_free(a[pos]),a[pos]=NULL;				
			else
			{
				jbl_uint32 size=get_size(small,large,huge);
				a[pos]=jbl_realloc(a[pos],size);
				for(jbl_uint32 i=0;i<size;a[pos][i]=i&0XFF,i+=0XF);
			}				
		else
		{
			jbl_uint32 size=get_size(small,large,huge);
			a[pos]=jbl_malloc(size);
            size=jbl_malloc_size(a[pos]);
			for(jbl_uint32 i=0;i<size;a[pos][i]=i&0XFF,i+=0XF);
		}
	}
	for(int i=0;i<slot;++i)if(a[i]!=NULL)jbl_free(a[i]);
	jbl_free(a);a=NULL;
}
void * do_thread(void * a)
{
	do_malloc(slot/thread,(1<<base)/thread,small,large,huge);
	return NULL;
}
int main()
{
	jbl_start();
//	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_rand_srand(0);
	
//	pchars("Input slot and base\n");pf();
//	scanf("%d %d",&slot,&base);
//	pchars("Slot:");pint(slot);pt();pchars("Base:");pint(base);pn();pf();
//	pchars("Small:");pdouble(small*100.0/(small+large+huge));pchar('%');pt();pchars("Large:");pdouble(large*100.0/(small+large+huge));pchar('%');pt();pchars("Huge:");pdouble(huge*100.0/(small+large+huge));pchar('%');pn();pf();
#if JBL_TIME_ENABLE ==1
	jbl_time *t1=NULL,*t2=NULL;
	t1=jbl_time_now(t1);
#endif
//	pl();
#if JBL_PTHREAD_ENABLE==1
	pthread_t t[thread];
	for(int i=0;i<thread;pthread_create(&t[i],NULL,do_thread,NULL),++i);
	for(int i=0;i<thread;pthread_join(t[i],NULL),++i);
#else
	do_malloc(slot,(1<<base),small,large,huge);	
#endif
	
    
#if JBL_TIME_ENABLE ==1
	pchars("\nmalloc used time:");puint(jbl_time_minus((t2=jbl_time_now(t2)),t1));pchars("ms\n");
	t1=jbl_time_free(t1);t2=jbl_time_free(t2);	
#endif
//	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}