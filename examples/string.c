#include "main.h"
#include <time.h>

int main()
{
	printf("\n--------------------------------" __FILE__ "--------------------------------\n");
	printf("jry_bl_string size:%lld\n",(long long)(sizeof (jry_bl_string)));	
	jry_bl_start();
	jry_bl_string s1,s2,s3;jry_bl_string_inits(3,&s1,&s2,&s3);
	jry_bl_time t1,t2;jry_bl_time_inits(2,&t1,&t2);	
	jry_bl_string_equal_chars_light(&s1,"juruoyun");					jry_bl_string_view(&s1);
	jry_bl_string_parse(&s1);										jry_bl_string_view(&s1);
	printf("Hash:%lld\n",jry_bl_string_hash(&s1));
	jry_bl_string_add_string(&s1,&s1);								jry_bl_string_view(&s1);
	printf("Hash:%lld\n",jry_bl_string_hash(&s1));
		
	jry_bl_string_equal_chars(&s2,"12345678");				jry_bl_string_view(&s2);
	jry_bl_string_equal_chars_length(&s2,"12345",2);			jry_bl_string_view(&s2);
	jry_bl_string_add_string(&s1,&s2);								jry_bl_string_view(&s1);jry_bl_string_clears(2,&s1,&s2);
	jry_bl_string_add_char(&s1,'a');								jry_bl_string_view(&s1);jry_bl_string_clear(&s1);

	jry_bl_string_add_uint64(&s1,12356);							jry_bl_string_view(&s1);jry_bl_string_clear(&s1);
	jry_bl_string_add_int64(&s1,-12356);							jry_bl_string_view(&s1);jry_bl_string_clear(&s1);
	jry_bl_string_add_double(&s1,1.123);							jry_bl_string_view(&s1);jry_bl_string_clear(&s1);
	jry_bl_string_equal_double_length(&s1,1.12346786789898,100);	jry_bl_string_view(&s1);jry_bl_string_clear(&s1);
	jry_bl_string_equal_double_length(&s1,1.123,3);					jry_bl_string_view(&s1);jry_bl_string_clear(&s1);
	jry_bl_string_equal_double_length(&s2,1.123,4);					jry_bl_string_view(&s2);jry_bl_string_clear(&s2);
	jry_bl_string_equal_hex(&s2,(jry_bl_uint64)0XF);			jry_bl_string_view(&s2);jry_bl_string_clear(&s2);


	jry_bl_string_equal_chars(&s1,"juruoyun");		jry_bl_string_view(&s1);
	jry_bl_string_equal_chars(&s2,"12312312");		jry_bl_string_view(&s2);
	printf("Space ship test:%d\n",jry_bl_string_space_ship(&s1,&s2));


//	���ļ���д����
	FILE * fp;
	jry_bl_string_equal_chars(&s1,"j");
	jry_bl_string_frees(2,&s2,&s3);	
//	jry_bl_string_extend_to(&s1,2LL*1024*1024*1024);
	for(int i=0;i<30;i++)
		jry_bl_string_add_string(&s1,&s1);
	printf("Copy finish\n");
	jry_bl_time_now(&t1);	
	fp=fopen ("testfiles/bigstring.out","w");
	jry_bl_string_print(&s1,fp);
	fclose(fp);
	fprintf(stderr,"Write %lld Byte data used time:%lldms\n",s1.len,jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));	

	jry_bl_time_now(&t1);	
	fp=fopen ("testfiles/bigstring.out","r");
	jry_bl_string_equal_file(&s1,fp);
	fclose(fp);
	fprintf(stderr,"Read %lld Byte data used time:%lldms\n",s1.len,jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));	
	jry_bl_string_free(&s1);	


	jry_bl_string_equal_chars(&s1,"12345678");		jry_bl_string_view(&s1);printf("%lld\n",jry_bl_string_get_int64(&s1));
	jry_bl_string_equal_chars(&s1,"-12345678");		jry_bl_string_view(&s1);printf("%lld\n",jry_bl_string_get_int64(&s1));
	jry_bl_string_equal_chars(&s1,"-12345678");		jry_bl_string_view(&s1);printf("%lld\n",jry_bl_string_get_uint64(&s1));
	jry_bl_string_equal_chars(&s1,"-123.4567");		jry_bl_string_view(&s1);printf("%lld\n",jry_bl_string_get_int64(&s1));
	jry_bl_string_equal_chars(&s1,"123.4567");		jry_bl_string_view(&s1);printf("%f\n",(double)jry_bl_string_get_double(&s1));
	jry_bl_string_equal_chars(&s1,"123");			jry_bl_string_view(&s1);printf("%f\n",(double)jry_bl_string_get_double(&s1));
	jry_bl_string_equal_chars(&s1,"1.1123");			jry_bl_string_equal_double(&s2,jry_bl_string_get_double(&s1));jry_bl_string_view(&s2);
	jry_bl_string_equal_chars(&s1,"FF");				jry_bl_string_view(&s1);printf("%lld\n",jry_bl_string_get_hex(&s1));


	jry_bl_string_equal_chars(&s1,"juruoyun");		jry_bl_string_view(&s1);
	jry_bl_string_equal_string_light(&s2,&s1);				jry_bl_string_views(2,&s1,&s2);
	jry_bl_string_equal_string_light_copy(&s2,&s1);			jry_bl_string_views(2,&s1,&s2);


	jry_bl_string_equal_chars(&s1,"ju\"ruoyun");
	jry_bl_string_to_json(&s1,&s2);
	jry_bl_string_view(&s2);
	jry_bl_string_from_json(&s3,&s2);
	jry_bl_string_view(&s3);


	jry_bl_string_equal_chars(&s1,"juruoyunjuruoyun");
	printf("%lld\n",jry_bl_string_find_char(&s1,'u'));
	printf("%lld\n",jry_bl_string_find_char_start(&s1,'u',2));


exit:	
	jry_bl_string_frees(3,&s1,&s2,&s3);	
	jry_bl_time_frees(2,&t1,&t2);	
	jry_bl_stop();
	return 0;
}