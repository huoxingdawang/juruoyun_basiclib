#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();	
	jbl_rand_srand(0);
	jbl_time t1,t2;jbl_time_inits(2,&t1,&t2);
	
	int slot,base;
	printf("Input slot and base\n");
	scanf("%d %d",&slot,&base);
	char **a=jbl_malloc(slot*sizeof(char*));
	for(int i=0;i<slot;a[i]=NULL,++i);
	jbl_time_now(&t1);
	for(jbl_uint64 i=0,n=(1LL<<base);i<n;++i)
	{
		register jbl_uint32 size;
		register jbl_uint32 pos=jbl_rand()%slot;
		if(a[pos]==NULL)
		{
			switch(jbl_rand()%7)
			{
				case 0:case 1:case 2:case 3:case 4:
					size=(jbl_rand()%3072)+1;break;
				case 5:case 6:case 7:
					size=((jbl_rand())%2093056)+1;break;
				case 8:case 9:
					size=2093056+((jbl_rand())%2093056);break;
			}
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
	fprintf(stderr,"\nmalloc used time:%lldms\n",jbl_time_minus((jbl_time_now(&t2),&t2),&t1));	
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
	jbl_time_frees(2,&t1,&t2);	
	jbl_stop();
	return 0;
}