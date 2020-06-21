#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_ht *  ht1 =jbl_ht_new();
	jbl_ht *  ht2 =NULL;
	jbl_var * Vht3=jbl_Vht_new();
	jbl_ht *ht4=NULL;
	jbl_var *Vht5=NULL;
	jbl_string * s1=jbl_string_add_chars(NULL,UC"juruoyun");
	jbl_string * s2=jbl_string_add_chars(NULL,UC"juruo");
	jbl_string * s3=NULL;
	jbl_var * v1=jbl_V(jbl_string_add_chars(jbl_Vstring(jbl_Vstring_new()),UC"juruoyun"));
	jbl_var * v2=jbl_Vuint_set(NULL,19260817);
	jbl_var * v3=jbl_V(jbl_string_add_chars(jbl_Vstring(jbl_Vstring_new()),UC"juruoyunjuruoyunjuruoyunjuruoyun"));
	jbl_var * v4=NULL;
	jbl_var * v5=NULL;
	ht1=jbl_ht_insert(ht1,s1,v1);
	jbl_ht_view(ht1);
	ht1=jbl_ht_insert(ht1,s2,v2);
	jbl_ht_view(ht1);
	ht1=jbl_ht_insert(ht1,s1,v3);
	jbl_ht_view(ht1);
	ht1=jbl_ht_insert(ht1,s1,NULL);
	jbl_ht_view(ht1);
	ht1=jbl_ht_unset(ht1,s1);
	jbl_ht_view(ht1);
	ht1=jbl_ht_rehash(ht1);
	jbl_ht_view(ht1);

pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("写时分离\n");
pchars("/////////////////////////////////////////////////////////////////////\n");			
	ht2=jbl_ht_copy(ht1);
	v5=jbl_ht_copy_as_var(ht1);
	ht1=jbl_ht_insert_chars(ht1,UC"0",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"1",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"2",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"3",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"4",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"5",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"6",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"7",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"8",v1);
	ht1=jbl_ht_insert_chars(ht1,UC"9",v1);
	ht1=jbl_ht_insert_int(ht1,0,v2);
	ht1=jbl_ht_insert_int(ht1,1,v3);
	v5=jbl_V(jbl_ht_insert_chars(jbl_Vht(v5),UC"9",v1));
	jbl_ht_view(ht1);
	jbl_ht_view(ht2);
	jbl_var_view(v5);
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("获取操作\n");
pchars("/////////////////////////////////////////////////////////////////////\n");		
	v4=jbl_ht_get(ht1,s2);
	jbl_var_view(v4);
	v4=jbl_var_free(v4);
	v4=jbl_ht_get_chars(ht1,UC"2");
	jbl_var_view(v4);
	v4=jbl_var_free(v4);
	v4=jbl_ht_get_int(ht1,0);
	jbl_var_view(v4);
	v4=jbl_var_free(v4);

pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("删除操作\n");
pchars("删除前\n");
pchars("/////////////////////////////////////////////////////////////////////\n");		
	jbl_ht_view(ht1);	
	ht1=jbl_ht_unset(ht1,s2);
	ht1=jbl_ht_unset_chars(ht1,UC"7");
	ht1=jbl_ht_unset_int(ht1,1);
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("删除后(删除 \"juruo\" \"7\" 1)\n");
pchars("/////////////////////////////////////////////////////////////////////\n");		
	jbl_ht_view(ht1);	

pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("太空船操作符\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	ht2=jbl_ht_free(ht2);
	ht2=jbl_ht_copy(ht1);
	jbl_ht_view(ht1);
	jbl_ht_view(ht2);
	pchars("Space ship test:"),pint(jbl_ht_space_ship(ht1,ht2)),pn();
	ht2=jbl_ht_insert_int(ht2,0,v3);
	jbl_ht_view(ht2);
	pchars("Space ship test:"),pint(jbl_ht_space_ship(ht1,ht2)),pn();
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("Notice : 合并操作后面的会覆盖前面的\n");
pchars("/////////////////////////////////////////////////////////////////////\n");
	ht1=jbl_ht_insert_int(ht1,10,v3);
	ht2=jbl_ht_insert_int(ht2,11,v2);
	jbl_ht_view(ht1);
	jbl_ht_view(ht2);
	ht1=jbl_ht_merge(ht1,ht2);
	jbl_ht_view(ht1);
	
	Vht3=jbl_V(jbl_ht_merge(jbl_Vht(Vht3),ht2));
	jbl_var_view(Vht3);
	
	
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("引用下的修改操作\n");
pchars("/////////////////////////////////////////////////////////////////////\n");
	ht4=jbl_refer(&ht1);
	ht4=jbl_ht_insert_int(ht4,1000,Vht3);
	jbl_ht_view(ht1);
	jbl_ht_view(ht4);

	Vht5=jbl_refer(&Vht3);	
	Vht5=jbl_V(jbl_ht_insert_int(jbl_Vht(Vht5),1000,v1));
	jbl_var_view(Vht3);
	jbl_var_view(Vht5);
#if JBL_JSON_ENABLE==1
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("Notice : JSON格式化不会输出int key类型的数据\n");
pchars("/////////////////////////////////////////////////////////////////////\n");
	s3=jbl_ht_json_encode(ht1,NULL,1,1);
	jbl_string_view(s3);

pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("Notice : 注意观察使用jbl_ht_merge_int合并int key前后的JSON结果\n");
pchars("合并前\n");
pchars("/////////////////////////////////////////////////////////////////////\n");
	jbl_ht_view(ht1);
	jbl_ht_json_put(ht1,jbl_stream_stdout,1,1);
	jbl_stream_push_char(jbl_stream_stdout,'\n');
	
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("合并后\n");
pchars("/////////////////////////////////////////////////////////////////////\n");
	ht1=jbl_ht_merge_int(ht1);
	jbl_ht_view(ht1);
	jbl_ht_json_put(ht1,jbl_stream_stdout,1,1);
	jbl_stream_push_char(jbl_stream_stdout,'\n');
#endif
#if JBL_LL_ENABLE==1
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("ll合并\n");
pchars("/////////////////////////////////////////////////////////////////////\n");
	jbl_ll * l1=jbl_ll_merge_ht(NULL,ht1);
	jbl_ll_view(l1);
	l1=jbl_ll_free(l1);
#endif
goto exit;	
exit:;
	ht1=jbl_ht_free(ht1);
	ht2=jbl_ht_free(ht2);
	Vht3=jbl_var_free(Vht3);
	ht4=jbl_ht_free(ht4);
	Vht5=jbl_var_free(Vht5);
	s1=jbl_string_free(s1);
	s2=jbl_string_free(s2);
	s3=jbl_string_free(s3);
	v1=jbl_var_free(v1);
	v2=jbl_var_free(v2);
	v3=jbl_var_free(v3);
	v4=jbl_var_free(v4);
	v5=jbl_var_free(v5);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
}
