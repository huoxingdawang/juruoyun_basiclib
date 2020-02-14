#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();	
	jry_bl_rand_srand(0);
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
	
	int slot,base;
	printf("Input slot and base\n");
	scanf("%d %d",&slot,&base);
	char **a=jry_bl_malloc(slot*sizeof(char*));
	for(int i=0;i<slot;a[i]=NULL,++i);
	jry_bl_time_now(&t1);
	for(jry_bl_uint64 i=0,n=(1LL<<base);i<n;++i)
	{
		register jry_bl_uint32 size;
		register jry_bl_uint32 pos=jry_bl_rand()%slot;
		if(a[pos]==NULL)
		{
			switch(jry_bl_rand()%7)
			{
				case 0:case 1:case 2:case 3:case 4:
					size=(jry_bl_rand()%3072)+1;break;
				case 5:case 6:case 7:
					size=((jry_bl_rand())%2093056)+1;break;
				case 8:case 9:
					size=2093056+((jry_bl_rand())%2093056);break;
			}
			//printf("M %d\t%s %d\n",pos,(size)<=3072?"small":(size<=2093056?"large":"huge "),size);
			a[pos]=jry_bl_malloc(size);
			while(size--)a[pos][size]='c';
		}
		else
		{
			//printf("F %d\n",pos);
			jry_bl_free(a[pos]),a[pos]=NULL;	
		}			
	}
	fprintf(stderr,"\nmalloc used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));	
	for(int i=0;i<slot;++i)if(a[i]!=NULL)jry_bl_free(a[i]);
	jry_bl_free(a);a=NULL;

/*
jry_bl_malloc_fmap_type	fmap[(512/jry_bl_malloc_fmap_bits)];
for(int i=0,n=(512/jry_bl_malloc_fmap_bits);i<n;fmap[i]=0,++i);
__jry_bl_malloc_set_fmap(fmap,0,1);		__jry_bl_malloc_view_fmap(fmap);
//__jry_bl_malloc_set_fmap(fmap,132,128);		for(int i=0,n=(512/jry_bl_malloc_fmap_bits);i<n;printf("%0 16llX ",fmap[i]),++i);putchar('\n');
//__jry_bl_malloc_reset_fmap(fmap,2,128);		for(int i=0,n=(512/jry_bl_malloc_fmap_bits);i<n;printf("%0 16llX ",fmap[i]),++i);putchar('\n');
//__jry_bl_malloc_reset_fmap(fmap,132,128);	for(int i=0,n=(512/jry_bl_malloc_fmap_bits);i<n;printf("%0 16llX ",fmap[i]),++i);putchar('\n');

for(jry_bl_uint16 i=0,cnt0=0,j=0;i<512;++i)
{
	j=__jry_bl_malloc_fmap_find0(fmap,i);
	i=__jry_bl_malloc_fmap_find1(fmap,j);
	cnt0=i-j;
	printf("%d %d %d\n",j,i,cnt0);
}
*/
/*
	char *ptr0,*ptr1,*ptr2;
	ptr0=jry_bl_malloc(8);
	ptr1=jry_bl_malloc(1048576);
	ptr2=jry_bl_malloc(2093057);
	ptr0[0]='c';
	printf("%lld\n",jry_bl_malloc_size(ptr0));
	printf("%lld\n",jry_bl_malloc_size(ptr1));
	printf("%lld\n",jry_bl_malloc_size(ptr2));

	printf("\nBefore realloc:0X%X %lld\n",ptr1,jry_bl_malloc_size(ptr1));
	ptr1=jry_bl_realloc(ptr1,2076672);
	printf("After realloc :0X%X %lld\n",ptr1,jry_bl_malloc_size(ptr1));
	
	jry_bl_free(ptr0);
	jry_bl_free(ptr1);
	jry_bl_free(ptr2);
//	jry_bl_free(jry_bl_malloc(3584));
*/	
	jry_bl_time_frees(2,&t1,&t2);	
	jry_bl_stop();
	return 0;
}