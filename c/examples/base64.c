#include "main.h"
int main()
{
	jry_bl_string s1,s2,s3,s4,s5;jry_bl_string_inits(5,&s1,&s2,&s3,&s4,&s5);	
//	jry_bl_string_equal_char_pointer(&s1,"juruoyun");		jry_bl_string_view(&s1,stderr);
//	jry_bl_base64_encode(&s1,&s2);							jry_bl_string_view(&s2,stderr);
//	jry_bl_base64_decode(&s2,&s3);							jry_bl_string_view(&s3,stderr);
//	jry_bl_string_clear(&s1);jry_bl_string_clear(&s2);jry_bl_string_clear(&s3);
	FILE * fp;
	fp=fopen("testfiles/test.jpg","rb");jry_bl_string_equal_file(&s1,fp);fclose(fp);
	jry_bl_base64_encode(&s1,&s2);
//	fp=fopen("testfiles/base64_encode.ans","rb");jry_bl_string_equal_file(&s2,fp);fclose(fp);
	jry_bl_base64_decode(&s2,&s3);
	fp=fopen("testfiles/base64_encode.out","wb");jry_bl_string_print(&s2,fp);fclose(fp);
	fp=fopen("testfiles/base64_decode.out","wb");jry_bl_string_print(&s3,fp);fclose(fp);
//	system("php testfiles/base64.php \"testfiles/test.jpg\"");
//	fp=fopen("testfiles/base64_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
//	fp=fopen("testfiles/base64_decode.ans","rb");jry_bl_string_equal_file(&s5,fp);fclose(fp);
	printf("With self:%s\n",((jry_bl_string_space_ship(&s1,&s3)==0)?"YES":"NO"));
//	printf("With php encode:%s\n",((jry_bl_string_space_ship(&s2,&s4)==0)?"YES":"NO"));
//	printf("With php decode:%s\n",((jry_bl_string_space_ship(&s3,&s5)==0)?"YES":"NO"));
	
	
	fp=fopen("testfiles/test.html","wb");fputs("<img style=\"max-height:100%;max-width:100%;\" src=\"data:image/jpg;base64,",fp);jry_bl_string_print(&s2,fp);fputs("\"/>",fp);fclose(fp);
	
	
	jry_bl_string_frees(5,&s1,&s2,&s3,&s4,&s5);
    return 0;
}