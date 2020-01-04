#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();	
	
	jry_bl_string s1,s2,s3,s4,s5;jry_bl_string_inits(5,&s1,&s2,&s3,&s4,&s5);	
	FILE * fp;
	fp=fopen(filename,"rb");jry_bl_string_equal_file(&s1,fp);fclose(fp);
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
	jry_bl_time_now(&t1);
	jry_bl_md5(&s1,&s2);
	fprintf(stderr,"MD5 used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));	
	system("php testfiles/md5.php "filename);
	fp=fopen("testfiles/md5_encode.out","wb");jry_bl_string_print(&s2,fp);fclose(fp);
	fp=fopen("testfiles/md5_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
	printf("With php encode:%s\n",((jry_bl_string_space_ship(&s2,&s4)==0)?"YES":"NO"));
	
	jry_bl_string_frees(5,&s1,&s2,&s3,&s4,&s5);
	jry_bl_time_frees(2,&t1,&t2);	
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size); 
	return 0;
}