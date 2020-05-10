#include "main.h"
#include <time.h>

int main()
{
	printf("\n--------------------------------" __FILE__ "--------------------------------\n");
	printf("jbl_string size:%lld\n",(long long)(sizeof (jbl_string)));	
	jbl_start();
	jbl_string s1,s2,s3;jbl_string_inits(3,&s1,&s2,&s3);
	jbl_time t1,t2;jbl_time_inits(2,&t1,&t2);	
	jbl_string_equal_chars_light(&s1,"juruoyun");					jbl_string_view(&s1);
	jbl_string_parse(&s1);										jbl_string_view(&s1);
	printf("Hash:%lld\n",jbl_string_hash(&s1));
	jbl_string_add_string(&s1,&s1);								jbl_string_view(&s1);
	printf("Hash:%lld\n",jbl_string_hash(&s1));
		
	jbl_string_equal_chars(&s2,"12345678");				jbl_string_view(&s2);
	jbl_string_equal_chars_length(&s2,"12345",2);			jbl_string_view(&s2);
	jbl_string_add_string(&s1,&s2);								jbl_string_view(&s1);jbl_string_clears(2,&s1,&s2);
	jbl_string_add_char(&s1,'a');								jbl_string_view(&s1);jbl_string_clear(&s1);

	jbl_string_add_uint64(&s1,12356);							jbl_string_view(&s1);jbl_string_clear(&s1);
	jbl_string_add_int64(&s1,-12356);							jbl_string_view(&s1);jbl_string_clear(&s1);
	jbl_string_add_double(&s1,1.123);							jbl_string_view(&s1);jbl_string_clear(&s1);
	jbl_string_equal_double_length(&s1,1.12346786789898,100);	jbl_string_view(&s1);jbl_string_clear(&s1);
	jbl_string_equal_double_length(&s1,1.123,3);					jbl_string_view(&s1);jbl_string_clear(&s1);
	jbl_string_equal_double_length(&s2,1.123,4);					jbl_string_view(&s2);jbl_string_clear(&s2);
	jbl_string_equal_hex(&s2,(jbl_uint64)0XF);			jbl_string_view(&s2);jbl_string_clear(&s2);


	jbl_string_equal_chars(&s1,"juruoyun");		jbl_string_view(&s1);
	jbl_string_equal_chars(&s2,"12312312");		jbl_string_view(&s2);
	printf("Space ship test:%d\n",jbl_string_space_ship(&s1,&s2));


//	大文件读写测试
	FILE * fp;
	jbl_string_equal_chars(&s1,"j");
	jbl_string_frees(2,&s2,&s3);	
//	jbl_string_extend_to(&s1,2LL*1024*1024*1024);
	for(int i=0;i<0;i++)
		jbl_string_add_string(&s1,&s1);
	printf("Copy finish\n");
	jbl_time_now(&t1);	
	fp=fopen ("testfiles/bigstring.out","w");
	jbl_string_print(&s1,fp);
	fclose(fp);
	fprintf(stderr,"Write %lld Byte data used time:%lldms\n",s1.len,jbl_time_minus((jbl_time_now(&t2),&t2),&t1));	

	jbl_time_now(&t1);	
	fp=fopen ("testfiles/bigstring.out","r");
	jbl_string_equal_file(&s1,fp);
	fclose(fp);
	fprintf(stderr,"Read %lld Byte data used time:%lldms\n",s1.len,jbl_time_minus((jbl_time_now(&t2),&t2),&t1));	
	jbl_string_free(&s1);	


	jbl_string_equal_chars(&s1,"12345678");		jbl_string_view(&s1);printf("%lld\n",jbl_string_get_int64(&s1));
	jbl_string_equal_chars(&s1,"-12345678");		jbl_string_view(&s1);printf("%lld\n",jbl_string_get_int64(&s1));
	jbl_string_equal_chars(&s1,"-12345678");		jbl_string_view(&s1);printf("%lld\n",jbl_string_get_uint64(&s1));
	jbl_string_equal_chars(&s1,"-123.4567");		jbl_string_view(&s1);printf("%lld\n",jbl_string_get_int64(&s1));
	jbl_string_equal_chars(&s1,"123.4567");		jbl_string_view(&s1);printf("%f\n",(double)jbl_string_get_double(&s1));
	jbl_string_equal_chars(&s1,"123");			jbl_string_view(&s1);printf("%f\n",(double)jbl_string_get_double(&s1));
	jbl_string_equal_chars(&s1,"1.1123");			jbl_string_equal_double(&s2,jbl_string_get_double(&s1));jbl_string_view(&s2);
	jbl_string_equal_chars(&s1,"FF");				jbl_string_view(&s1);printf("%lld\n",jbl_string_get_hex(&s1));


	jbl_string_equal_chars(&s1,"juruoyun");		jbl_string_view(&s1);
	jbl_string_equal_string_light(&s2,&s1);				jbl_string_views(2,&s1,&s2);
	jbl_string_equal_string_light_copy(&s2,&s1);			jbl_string_views(2,&s1,&s2);


	jbl_string_equal_chars(&s1,"ju\"ruoyun");
	jbl_string_to_json(&s1,&s2);
	jbl_string_view(&s2);
	jbl_string_from_json(&s3,&s2);
	jbl_string_view(&s3);


	jbl_string_equal_chars(&s1,"juruoyunjuruoyun");
	printf("%lld\n",jbl_string_find_char(&s1,'u'));
	printf("%lld\n",jbl_string_find_char_start(&s1,'u',2));


exit:	
	jbl_string_frees(3,&s1,&s2,&s3);	
	jbl_time_frees(2,&t1,&t2);	
	jbl_stop();
	return 0;
}