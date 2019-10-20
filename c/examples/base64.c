#include "main.h"
int main()
{
	jry_bl_string s1,s2,s3;jry_bl_string_inits(3,&s1,&s2,&s3);	
	jry_bl_string_equal_char_pointer(&s1,"juruoyun");		jry_bl_string_view(&s1,stderr);
	jry_bl_base64_encode(&s1,&s2);							jry_bl_string_view(&s2,stderr);
	jry_bl_base64_decode(&s2,&s3);							jry_bl_string_view(&s3,stderr);
	jry_bl_string_frees(3,&s1,&s2,&s3);
	jry_bl_string_clear(&s1);jry_bl_string_clear(&s2);jry_bl_string_clear(&s3);
	FILE * fp;
	fp=fopen("testfiles/test.txt","r");
	jry_bl_string_equal_file(&s1,fp);
	fclose(fp);
	jry_bl_base64_encode(&s1,&s2);
	fp=fopen("testfiles/base64_encode.out","w");jry_bl_string_print(&s2,fp);fclose(fp);
	jry_bl_base64_decode(&s2,&s3);
	fp=fopen("testfiles/base64_decode.out","w");jry_bl_string_print(&s3,fp);fclose(fp);
	
    return 0;
}