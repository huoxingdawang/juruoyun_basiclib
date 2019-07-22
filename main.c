#include "main.h"

int main()
{
//jry_bl_string	
	printf("-------------------字符串部分-----------------------\n");
	jry_bl_string s1={0,0,0};
	jry_bl_string s2={0,0,0};
	jry_bl_string s3={0,0,0};
//三种初始化方式
	printf("-------------------三种初始化方式-------------------\n");
	printf("-------------------默认初始化-----------------------\n");
	jry_bl_string_init(&s1,JRY_BL_STRING_INIT_BY_NONE);
	jry_bl_string_view(stdout,&s1);
	printf("-------------------初始化大小-----------------------\n");
	jry_bl_string_init(&s2,JRY_BL_STRING_INIT_BY_LENGTH,512);
	jry_bl_string_view(stdout,&s2);	
	printf("-------------------由正产字符串初始化---------------\n");
	jry_bl_string_init(&s3,JRY_BL_STRING_INIT_BY_STRING,"juruoyun");
	jry_bl_string_view(stdout,&s3);	
	printf("\n\n\n");
//数字转字符串
	printf("-------------------数字转字符串----------------------\n");
	jry_bl_string_int_to_string(&s3,19260817);
	jry_bl_string_view(stdout,&s3);
	printf("\n\n\n");
//追加字符串
	printf("-------------------追加字符串------------------------\n");
	jry_bl_string_add(&s2,"追加s2");
	jry_bl_string_view(stdout,&s2);
	printf("\n\n\n");
//连接
	printf("-------------------连接字符串------------------------\n");
	jry_bl_string_link(&s3,&s2);
	jry_bl_string_view(stdout,&s2);
	jry_bl_string_view(stdout,&s3);
	printf("\n\n\n");
//转数字
	printf("-------------------字符串转数字----------------------\n");
	printf("从第0位开始:%lld\n",jry_bl_string_string_to_int(&s3,0));
	printf("从第10位%lld\n",jry_bl_string_string_to_int(&s3,10));
	printf("\n\n\n");
//回收
	jry_bl_string_deinit(&s1);
	jry_bl_string_deinit(&s2);
	jry_bl_string_deinit(&s3);
	
	
	return 0;
}