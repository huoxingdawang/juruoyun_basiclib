#include "main.h"
int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();
	FILE * fp;
	unsigned char key[]="0CoJUm6Qyw8W8jud";
	jry_bl_string s1,s2,s3,s4,s5,s6,s7;jry_bl_string_inits(7,&s1,&s2,&s3,&s4,&s5,&s6,&s7);	
	jry_bl_aes_128_extened_key keyy;
	jry_bl_aes_128_extend_key(key,keyy);
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);
//AES 128 ECB
	jry_bl_string_clears(7,&s1,&s2,&s3,&s4,&s5,&s6,&s7);
	fp=fopen(filename,"rb");jry_bl_string_equal_file(&s1,fp);fclose(fp);
	jry_bl_time_now(&t1);
	jry_bl_aes_128_ecb_encode(keyy,&s1,&s2);
	fprintf(stderr,"AES 128 ECB encode used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));
	jry_bl_base64_encode(&s2,&s6);
	jry_bl_time_now(&t1);
	jry_bl_aes_128_ecb_decode(keyy,&s2,&s3);
	fprintf(stderr,"AES 128 ECB decode used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));
	fp=fopen("testfiles/aes_128_ecb_encode.out","wb");jry_bl_string_print(&s6,fp);fclose(fp);
	fp=fopen("testfiles/aes_128_ecb_decode.out","wb");jry_bl_string_print(&s3,fp);fclose(fp);
	system("php testfiles/aes128ecb.php "filename);
	fp=fopen("testfiles/aes_128_ecb_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
	fp=fopen("testfiles/aes_128_ecb_decode.ans","rb");jry_bl_string_equal_file(&s5,fp);fclose(fp);
	printf("AES 128 ECB with self:%s\n",((jry_bl_string_space_ship(&s1,&s3)==0)?"YES":"NO"));
	printf("AES 128 ECB with php encode:%s\n",((jry_bl_string_space_ship(&s6,&s4)==0)?"YES":"NO"));
	printf("AES 128 ECB with php decode:%s\n",((jry_bl_string_space_ship(&s3,&s5)==0)?"YES":"NO"));
//AES 128 CBC
	jry_bl_string_clears(7,&s1,&s2,&s3,&s4,&s5,&s6,&s7);
	fp=fopen(filename,"rb");jry_bl_string_equal_file(&s1,fp);fclose(fp);
	jry_bl_time_now(&t1);
	jry_bl_aes_128_cbc_encode(keyy,"0CoJUm6Qyw8W8jud",&s1,&s2);
	fprintf(stderr,"AES 128 CBC encode used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));
	jry_bl_base64_encode(&s2,&s6);
	jry_bl_time_now(&t1);
	jry_bl_aes_128_cbc_decode(keyy,"0CoJUm6Qyw8W8jud",&s2,&s3);
	fprintf(stderr,"AES 128 CBC decode used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));
	fp=fopen("testfiles/aes_128_cbc_encode.out","wb");jry_bl_string_print(&s6,fp);fclose(fp);
	fp=fopen("testfiles/aes_128_cbc_decode.out","wb");jry_bl_string_print(&s3,fp);fclose(fp);
	system("php testfiles/aes128cbc.php "filename);
	fp=fopen("testfiles/aes_128_cbc_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
	fp=fopen("testfiles/aes_128_cbc_decode.ans","rb");jry_bl_string_equal_file(&s5,fp);fclose(fp);
	printf("AES 128 CBC with self:%s\n",((jry_bl_string_space_ship(&s1,&s3)==0)?"YES":"NO"));
	printf("AES 128 CBC with php encode:%s\n",((jry_bl_string_space_ship(&s6,&s4)==0)?"YES":"NO"));
	printf("AES 128 CBC with php decode:%s\n",((jry_bl_string_space_ship(&s3,&s5)==0)?"YES":"NO"));
	jry_bl_string_frees(7,&s1,&s2,&s3,&s4,&s5,&s6,&s7);
	jry_bl_time_frees(2,&t1,&t2);	
	jry_bl_stop();	
}
