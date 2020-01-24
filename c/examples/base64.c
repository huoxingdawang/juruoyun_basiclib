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
	jry_bl_base64_encode(&s1,&s2);
	fprintf(stderr,"BASE64 encode used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));		
	jry_bl_time_now(&t1);	
	jry_bl_base64_decode(&s2,&s3);
	fprintf(stderr,"BASE64 decode used time:%lldms\n",jry_bl_time_minus((jry_bl_time_now(&t2),&t2),&t1));		
	fp=fopen("testfiles/base64_encode.out","wb");jry_bl_string_print(&s2,fp);fclose(fp);
	fp=fopen("testfiles/base64_decode.out","wb");jry_bl_string_print(&s3,fp);fclose(fp);
	system("php testfiles/base64.php "filename);
	fp=fopen("testfiles/base64_encode.ans","rb");jry_bl_string_equal_file(&s4,fp);fclose(fp);
	fp=fopen("testfiles/base64_decode.ans","rb");jry_bl_string_equal_file(&s5,fp);fclose(fp);
	printf("With self:%s\n",((jry_bl_string_space_ship(&s1,&s3)==0)?"YES":"NO"));
	printf("With php encode:%s\n",((jry_bl_string_space_ship(&s2,&s4)==0)?"YES":"NO"));
	printf("With php decode:%s\n",((jry_bl_string_space_ship(&s3,&s5)==0)?"YES":"NO"));
	
	
	fp=fopen("testfiles/test.html","wb");fputs("<img style=\"max-height:100%;max-width:100%;\" src=\"data:image/jpg;base64,",fp);jry_bl_string_print(&s2,fp);fputs("\"/>",fp);fclose(fp);


//	fp=fopen(filename".ljt.out","wb");fputs("PICTURE="filename",THUMBNAIL=",fp);jry_bl_string_print(&s2,fp);fputs(";",fp);fclose(fp);
//	fp=fopen("base64.query.out","a");
//	fputs("fetch(\"http://zhjy.lelearning.com/ajax/WisdomEducation.AjaxData,WisdomEducation.ashx?_method=AddNote&_session=rw\", {\"credentials\":\"include\",\"headers\":{\"accept\":\"*/*\",\"accept-language\":\"zh-CN,zh;q=0.9\",\"content-type\":\"text/plain;charset=UTF-8\"},\"referrer\":\"http://zhjy.lelearning.com/html/studentmanage/microclasssubjectinfo.html?xk=wky&id=jselw\",\"referrerPolicy\":\"no-referrer-when-downgrade\",\"body\":\"pobId=@wky@jselw\\r\\ntTitle=祭十二郎文\\r\\ntNote=<p>",fp);
//	fputs("PICTURE="filename",THUMBNAIL=",fp);jry_bl_string_print(&s2,fp);fputs(";",fp);
//	fputs("</p>\",\"method\":\"POST\",\"mode\":\"cors\"});\n",fp);
//	fclose(fp);
	
	jry_bl_string_frees(5,&s1,&s2,&s3,&s4,&s5);
	jry_bl_time_frees(2,&t1,&t2);
	jry_bl_stop();
	return 0;
}