#include "main.h"
int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_rand_srand(0);
	jbl_time *t1=NULL,*t2=NULL;
	
	int slot,base;
	int small=70;
	int large=20;
	int huge=10;
	printf("Input slot and base\n");
	scanf("%d %d",&slot,&base);
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
	fprintf(stderr,"\nmalloc used time:%I64dms\n",jbl_time_minus((t2=jbl_time_now(t2)),t1));	
	for(int i=0;i<slot;++i)if(a[i]!=NULL)jbl_free(a[i]);
	jbl_free(a);a=NULL;

/*
jbl_malloc_fmap_type	fmap[(512/jbl_malloc_fmap_bits)];
for(int i=0,n=(512/jbl_malloc_fmap_bits);i<n;fmap[i]=0,++i);
__jbl_malloc_set_fmap(fmap,0,1);		__jbl_malloc_view_fmap(fmap);
//__jbl_malloc_set_fmap(fmap,132,128);		for(int i=0,n=(512/jbl_malloc_fmap_bits);i<n;printf("%0 16llX ",fmap[i]),++i);putchar('\n');
//__jbl_malloc_reset_fmap(fmap,2,128);		for(int i=0,n=(512/jbl_malloc_fmap_bits);i<n;printf("%0 16llX ",fmap[i]),++i);putchar('\n');
//__jbl_malloc_reset_fmap(fmap,132,128);	for(int i=0,n=(512/jbl_malloc_fmap_bits);i<n;printf("%0 16llX ",fmap[i]),++i);putchar('\n');

for(jbl_uint16 i=0,cnt0=0,j=0;i<512;++i)
{
	j=__jbl_malloc_fmap_find0(fmap,i);
	i=__jbl_malloc_fmap_find1(fmap,j);
	cnt0=i-j;
	printf("%d %d %d\n",j,i,cnt0);
}
*/
/*
	char *ptr0,*ptr1,*ptr2;
	ptr0=jbl_malloc(8);
	ptr1=jbl_malloc(1048576);
	ptr2=jbl_malloc(2093057);
	ptr0[0]='c';
	printf("%lld\n",jbl_malloc_size(ptr0));
	printf("%lld\n",jbl_malloc_size(ptr1));
	printf("%lld\n",jbl_malloc_size(ptr2));

	printf("\nBefore realloc:0X%X %lld\n",ptr1,jbl_malloc_size(ptr1));
	ptr1=jbl_realloc(ptr1,2076672);
	printf("After realloc :0X%X %lld\n",ptr1,jbl_malloc_size(ptr1));
	
	jbl_free(ptr0);
	jbl_free(ptr1);
	jbl_free(ptr2);
//	jbl_free(jbl_malloc(3584));
*/	
	t1=jbl_time_free(t1);	
	t2=jbl_time_free(t2);	
	jbl_stop();
	return 0;
}