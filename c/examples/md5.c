#include "main.h"
int main()
{
	jry_bl_string s1,s2,s3,s4,s5;jry_bl_string_inits(5,&s1,&s2,&s3,&s4,&s5);	

/*
	jry_bl_string_equal_char_pointer(&s1,"juruoyun");	jry_bl_string_view(&s1,stderr);
	jry_bl_md5(&s1,&s2);								jry_bl_string_view(&s2,stderr);
	jry_bl_string_clear(&s1);jry_bl_string_clear(&s2);jry_bl_string_clear(&s3);
*/
	FILE * fp;
	fp=fopen("testfiles/test.txt","rb");jry_bl_string_equal_file(&s1,fp);fclose(fp);	
	jry_bl_md5(&s1,&s2);
	system("php testfiles/md5.php \"testfiles/test.txt\"");
	fp=fopen("testfiles/md5_encode.out","wb");jry_bl_string_print(&s2,fp);fclose(fp);
	fp=fopen("testfiles/md5_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
	printf("With php encode:%s\n",((jry_bl_string_space_ship(&s2,&s4)==0)?"YES":"NO"));
	
	jry_bl_string_frees(5,&s1,&s2,&s3,&s4,&s5);
    return 0;
}