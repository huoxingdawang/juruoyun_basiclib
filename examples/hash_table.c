#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();	
	jbl_hash_table	ht1,ht2	;jbl_hash_table_inits(2,&ht1,&ht2);
	jbl_string		s1,s2	;jbl_string_inits(2,&s1,&s2);
	jbl_var		 	v1,v2	;jbl_var_inits(2,&v1,&v2);
	jbl_hash_table_insert_str(&ht1,"test","value",&s1,&s2,&v1);
	jbl_hash_table_insert_str(&ht1,"aaa","bbb",&s1,&s2,&v1);
	jbl_hash_table_insert_str(&ht1,"ccc","123",&s1,&s2,&v1);
	jbl_hash_table_insert_str(&ht1,"ffff","123123",&s1,&s2,&v1);
	jbl_hash_table_insert_str(&ht1,"123123","ttt",&s1,&s2,&v1);
	jbl_hash_table_insert_str_int64(&ht1,"tttt",-123,&s1,&v1);
	jbl_hash_table_insert_str_uint64(&ht1,"ttt1",123,&s1,&v1);
	jbl_hash_table_insert_str_double(&ht1,"tt2t",123.456,&s1,&v1);
	jbl_hash_table_insert_str_true(&ht1,"tt3t",&s1,&v1);
	jbl_hash_table_insert_str_false(&ht1,"tt4t",&s1,&v1);
	jbl_hash_table_view(&ht1);

	
	jbl_hash_table_insert_str(&ht1,"123123","ddd",&s1,&s2,&v1);
	jbl_hash_table_view(&ht1);
	jbl_string_equal_chars_light(&s1,"ffff");jbl_hash_table_unset(&ht1,&s1);
	jbl_hash_table_view(&ht1);	
	jbl_hash_table_rehash(&ht1);
	jbl_hash_table_view(&ht1);	
	jbl_string_equal_chars_light(&s1,"test");jbl_hash_table_unset(&ht1,&s1);
	jbl_hash_table_view(&ht1);	
	jbl_string_equal_chars_light(&s1,"123123");jbl_hash_table_unset(&ht1,&s1);
	jbl_string_equal_chars_light(&s1,"ccc");jbl_hash_table_unset(&ht1,&s1);
	jbl_string_equal_chars_light(&s1,"aaa");jbl_hash_table_unset(&ht1,&s1);
	jbl_hash_table_view(&ht1);

	
	jbl_hash_table_insert_str(&ht1,"kkkk","ddd",&s1,&s2,&v1);
	jbl_hash_table_insert_str(&ht2,"kkkk","ddd",&s1,&s2,&v1);
	jbl_hash_table_insert_str(&ht2,"k123","d2d",&s1,&s2,&v1);
	printf("Space ship:%d\n",jbl_hash_table_space_ship(&ht1,&ht2));
	jbl_hash_table_clears(2,&ht1,&ht2);
	
	
	jbl_hash_table_insert_str(&ht2,"kkkk","ddd",&s1,&s2,&v1);
	jbl_hash_table_insert_str(&ht2,"k123","d2d",&s1,&s2,&v1);
	jbl_hash_table_copy(&ht1,&ht2,move);
	jbl_hash_table_view(&ht1);
	jbl_hash_table_insert_str(&ht2,"kkk","ddd",&s1,&s2,&v1);
	jbl_hash_table_view(&ht2);
	
	jbl_hash_table_clear(&ht1);
	jbl_string_clear(&s1);
	jbl_hash_table_to_json(&ht2,&s1);
	jbl_string_view(&s1);
	jbl_hash_table_view(&ht1);
	
	jbl_hash_table_from_json(&ht1,&s1);
	jbl_hash_table_view(&ht1);
	
	
	
	
	
	
exit:	
	jbl_hash_table_frees(2,&ht1,&ht2);
	jbl_string_frees(2,&s1,&s2);
	jbl_var_frees(2,&v1,&v2);
	jbl_stop();	
}
