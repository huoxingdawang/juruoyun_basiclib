#include "main.h"
#include <time.h>
int main()
{
	jry_bl_string s1,s2,s3,s4,s5;jry_bl_string_inits(5,&s1,&s2,&s3,&s4,&s5);	

/*
	jry_bl_string_equal_char_pointer(&s1,"juruoyun");	jry_bl_string_view(&s1,stderr);
	jry_bl_md5(&s1,&s2);								jry_bl_string_view(&s2,stderr);
	jry_bl_string_clear(&s1);jry_bl_string_clear(&s2);jry_bl_string_clear(&s3);
*/
	FILE * fp;
	fp=fopen(filename,"rb");jry_bl_string_equal_file(&s1,fp);fclose(fp);
	clock_t __start=clock();	
	jry_bl_md5(&s1,&s2);
	fprintf(stderr,"\nMD5 used time:%fs\n",((double)(clock()-__start)/CLOCKS_PER_SEC));	
	__start=clock();	
	system("php testfiles/md5.php "filename);
	fprintf(stderr,"\nPHP MD5 used time:%fs\n",((double)(clock()-__start)/CLOCKS_PER_SEC));	
	fp=fopen("testfiles/md5_encode.out","wb");jry_bl_string_print(&s2,fp);fclose(fp);
	fp=fopen("testfiles/md5_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
	printf("With php encode:%s\n",((jry_bl_string_space_ship(&s2,&s4)==0)?"YES":"NO"));
	
	jry_bl_string_frees(5,&s1,&s2,&s3,&s4,&s5);
    return 0;
}