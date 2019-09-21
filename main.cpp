#include "main.h"

int main()
{
//jry_bl_string	
	printf("-------------------字符串部分-----------------------\n");
//三种初始化方式
	printf("-------------------三种初始化方式-------------------\n");
	printf("-------------------默认初始化-----------------------\n");
	jry_bl_string s1;
	s1.view(stdout);
	printf("-------------------初始化大小-----------------------\n");
	jry_bl_string s2(2048);
	s2.view(stdout);
	printf("-------------------由正产字符串初始化---------------\n");
	jry_bl_string s3("juruoyun");
	s3.view(stdout);
	printf("\n\n\n");
//输出
	printf("-------------------输出---------------\n");
	printf("-------------------逐个输出---------------\n");
	std::cout<<s3[1];
	std::cout<<s3[2];
	std::cout<<s3[3]<<std::endl;
	printf("-------------------一起输出---------------\n");
	std::cout<<s3<<std::endl;
	s2=s3;
	s1=(s3+=s3);
	printf("-------------------动态扩容---------------\n");
	s2.view(stdout);
	for(int i=0;i<10;i++,(s2+=s2));
	s2.view(stdout);
	s3.view(stdout);
	for(int i=0;i<1000;i++,(s3+="kuorong"));
	s3.view(stdout);
	s1.view(stdout);
	s1+=1234123;
	s1.view(stdout);
	std::cout<<s1.getint()<<std::endl;
	std::cout<<s1.getint(20)<<std::endl;
	s1.free();s2.free();s3.free();
	s1.view(stdout);s2.view(stdout);s3.view(stdout);
//数字转字符串
/*	printf("-------------------数字转字符串----------------------\n");
	jry_bl_string_add(&s3,19260817);
	jry_bl_string_view(&s3,stdout);
	printf("\n\n\n");
//追加字符串
	printf("-------------------追加字符串------------------------\n");
	jry_bl_string_add(&s2,"追加s2");
	jry_bl_string_view(&s2,stdout);
	printf("\n\n\n");
//连接
	printf("-------------------连接字符串------------------------\n");
	jry_bl_string_add(&s3,&s2);
	jry_bl_string_view(&s2,stdout);
	jry_bl_string_view(&s3,stdout);
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
*/	
	
	return 0;
}