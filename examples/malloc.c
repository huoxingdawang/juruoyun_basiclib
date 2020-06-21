#include "main.h"
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_rand_srand(0);
	jbl_time *t1=NULL,*t2=NULL;
	
	int slot=1024,base=16;
	int small=90;
	int large=9;
	int huge=1;
//	pchars("Input slot and base\n");pf();
//	scanf("%d %d",&slot,&base);
	pchars("Slot:");pint(slot);pt();pchars("Base:");pint(base);pn();pf();
	pchars("Small:");pdouble(small*100.0/(small+large+huge));pchar('%');pt();pchars("Large:");pdouble(large*100.0/(small+large+huge));pchar('%');pt();pchars("Huge:");pdouble(huge*100.0/(small+large+huge));pchar('%');pn();pf();
	char **a=jbl_malloc(slot*sizeof(char*));
	for(int i=0;i<slot;a[i]=NULL,++i);
	t1=jbl_time_now(t1);
	for(jbl_uint64 i=0,n=(1LL<<base);i<n;++i)
	{
		register jbl_uint32 size;
		register jbl_uint32 pos=jbl_rand()%slot;
		if(a[pos]==NULL)
		{
			jbl_uint32 r=jbl_rand_between(0,small+large+huge);
			if(r<=small)			size=(jbl_rand()%3072)+1;
			else if(r<=small+large)	size=((jbl_rand())%2093056)+1;
			else					size=2093056+((jbl_rand())%2093056);
			//printf("M %d\t%s %d\n",pos,(size)<=3072?"small":(size<=2093056?"large":"huge "),size);
			a[pos]=jbl_malloc(size);
			while(size--)a[pos][size]='c';
		}
		else
		{
			//printf("F %d\n",pos);
			jbl_free(a[pos]),a[pos]=NULL;	
		}			
	}
	pchars("\nmalloc used time:");puint(jbl_time_minus((t2=jbl_time_now(t2)),t1));pchars("ms\n");
	for(int i=0;i<slot;++i)if(a[i]!=NULL)jbl_free(a[i]);
	jbl_free(a);a=NULL;
	
	t1=jbl_time_free(t1);t2=jbl_time_free(t2);	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();
	return 0;
}