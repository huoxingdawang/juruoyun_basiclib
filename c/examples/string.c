#include "main.h"

int main()
{
	jry_bl_string s1,s2,s3;jry_bl_string_inits(3,&s1,&s2,&s3);
/*
	jry_bl_string_views(stderr,2,&s1,&s2);
	jry_bl_string_equal_char_pointer(&s1,"juruoyun");		jry_bl_string_view(&s1,stderr);
	jry_bl_string_equal_char_pointer(&s2,"12345678");		jry_bl_string_view(&s2,stderr);
	jry_bl_string_equal_char_pointer_length(&s2,"12345",2);	jry_bl_string_view(&s2,stderr);
	jry_bl_string_add_string(&s1,&s2);						jry_bl_string_view(&s1,stderr);jry_bl_string_clears(2,&s1,&s2);
	jry_bl_string_add_char(&s1,'a');						jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
*/
/*	
	jry_bl_string_add_unsigned_long_long(&s1,12356);		jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
	jry_bl_string_add_long_long(&s1,-12356);				jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
	jry_bl_string_add_double(&s1,1.123);				jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
	jry_bl_string_equal_double_length(&s1,1.12346786789898,100);	jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
	jry_bl_string_equal_double_length(&s1,1.123,3);	jry_bl_string_view(&s1,stderr);jry_bl_string_clear(&s1);
	jry_bl_string_equal_double_length(&s2,1.123,4);	jry_bl_string_view(&s2,stderr);jry_bl_string_clear(&s2);
*/
/*
	jry_bl_string_equal_char_pointer(&s1,"juruoyun");		jry_bl_string_view(&s1,stderr);
	jry_bl_string_equal_char_pointer(&s2,"12312312");		jry_bl_string_view(&s2,stderr);
	printf("Space ship test:%d\n",jry_bl_string_space_ship(&s1,&s2));
*/
/*
//	´óÎÄ¼þ¶ÁÐ´²âÊÔ
	FILE * fp;
	jry_bl_string_equal_char_pointer(&s1,"juruoyun");
	for(int i=0;i<2;i++)
		jry_bl_string_add_string(&s1,&s1);
	printf("Copy finish\n");
	fp=fopen ("testfiles/test2.txt","w");
	jry_bl_string_print(&s1,fp);
	fclose(fp);
	printf("Write %lld Byte data\n",s1.len);

	fp=fopen ("testfiles/test2.txt","r");
	jry_bl_string_equal_file(&s1,fp);
	fclose(fp);
	printf("Read %lld Byte data\n",s1.len);
*/
/*
	jry_bl_string_equal_char_pointer(&s1,"12345678");		jry_bl_string_view(&s1,stderr);printf("%lld\n",jry_bl_string_get_long_long(&s1));
	jry_bl_string_equal_char_pointer(&s1,"-12345678");		jry_bl_string_view(&s1,stderr);printf("%lld\n",jry_bl_string_get_long_long(&s1));
	jry_bl_string_equal_char_pointer(&s1,"-12345678");		jry_bl_string_view(&s1,stderr);printf("%lld\n",jry_bl_string_get_unsigned_long_long(&s1));
	jry_bl_string_equal_char_pointer(&s1,"-123.4567");		jry_bl_string_view(&s1,stderr);printf("%lld\n",jry_bl_string_get_long_long(&s1));
	jry_bl_string_equal_char_pointer(&s1,"123.4567");		jry_bl_string_view(&s1,stderr);printf("%f\n",(double)jry_bl_string_get_double(&s1));
	jry_bl_string_equal_char_pointer(&s1,"123");			jry_bl_string_view(&s1,stderr);printf("%f\n",(double)jry_bl_string_get_double(&s1));
	jry_bl_string_equal_char_pointer(&s1,"1.1123");			jry_bl_string_equal_double(&s2,jry_bl_string_get_double(&s1));jry_bl_string_view(&s2,stderr);
*/
/*
	jry_bl_string_equal_char_pointer(&s1,"juruoyun");		jry_bl_string_view(&s1,stderr);
	jry_bl_string_equal_string_light(&s2,&s1);				jry_bl_string_views(stderr,2,&s1,&s2);
	jry_bl_string_equal_string_light_move(&s2,&s1);			jry_bl_string_views(stderr,2,&s1,&s2);
*/
/*
	jry_bl_string_equal_char_pointer(&s1,"ju\"ruoyun");
	jry_bl_string_to_json(&s1,&s2);
	jry_bl_string_view(&s2,stderr);
	jry_bl_string_from_json(&s3,&s2);
	jry_bl_string_view(&s3,stderr);
*/
/*
	jry_bl_string_equal_char_pointer(&s1,"juruoyunjuruoyun");
	printf("%lld\n",jry_bl_string_find_char(&s1,'u'));
	printf("%lld\n",jry_bl_string_find_char_start(&s1,'u',2));
*/


	
	jry_bl_string_frees(3,&s1,&s2,&s3);	
	return 0;
}