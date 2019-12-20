#include "main.h"
#include <time.h>
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();	
	
	jry_bl_string s1,s2,s3,s4,s5;jry_bl_string_inits(5,&s1,&s2,&s3,&s4,&s5);	
	FILE * fp;
	fp=fopen(filename,"rb");jry_bl_string_equal_file(&s1,fp);fclose(fp);
	clock_t __start=clock();	
	jry_bl_sha1(&s1,&s2);
	fprintf(stderr,"SHA1 used time:%fs\n",((double)(clock()-__start)/CLOCKS_PER_SEC));	
	system("php testfiles/sha1.php "filename);
	fp=fopen("testfiles/sha1_encode.out","wb");jry_bl_string_print(&s2,fp);fclose(fp);
	fp=fopen("testfiles/sha1_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
	printf("With php encode:%s\n",((jry_bl_string_space_ship(&s2,&s4)==0)?"YES":"NO"));
	
	jry_bl_string_frees(5,&s1,&s2,&s3,&s4,&s5);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size); 
	return 0;
}