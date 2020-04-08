#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_start();	
	jry_bl_link_list l1,l2;jry_bl_link_list_inits(2,&l1,&l2);
	jry_bl_var v1;jry_bl_var_init(&v1);
	jry_bl_string s1,s2;jry_bl_string_inits(2,&s1,&s2);
/*	
	for(int i=0;i<5;i++)
	{
		jry_bl_string_equal_int64(&s1,i);
		jry_bl_var_equal_string(&v1,&s1,move);	
		jry_bl_link_list_add_var_move(&l1,&v1);
		jry_bl_var_free(&v1);
	}
	jry_bl_string_clear(&s1);
	jry_bl_link_list_view(&l1);
	jry_bl_link_list_delete_head(&l1);
	jry_bl_link_list_delete_tail(&l1);
	jry_bl_link_list_view(&l1);
	jry_bl_link_list_swap_node(&l1,l1.head->nxt,l1.tail);
	jry_bl_link_list_view(&l1);
	jry_bl_link_list_frees(2,&l1,&l2);
*/	
/*	
	jry_bl_string_equal_chars(&s1,"12312312\n1231231");
	jry_bl_string_cut(&s1,&l1,'\n');
	jry_bl_link_list_view(&l1);
	jry_bl_string_equal_chars(&s1,"125675675675763\n1231231");
	jry_bl_string_cut(&s1,&l2,'\n');
	jry_bl_link_list_view(&l2);
	printf("space ship:%d",jry_bl_link_list_space_ship(&l1,&l2));
	jry_bl_link_list_frees(2,&l1,&l2);
*/	
/*
	jry_bl_string_equal_chars(&s1,"12312312\n1231231");
	jry_bl_string_cut(&s1,&l1,'\n');
	jry_bl_link_list_equal_move(&l2,&l1);
	jry_bl_stop();	
	jry_bl_link_list_frees(1,&l1);
	jry_bl_link_list_view(&l2);
*/
	jry_bl_string_equal_chars(&s1,"12312312\n1231231");
	jry_bl_string_cut(&s1,&l1,'\n');
	jry_bl_link_list_put(&l1,&jry_bl_stream_stdout,view,(jry_bl_view_default_tabs_num<<16)|(__LINE__<<1)|1,__FILE__);jry_bl_stream_do(&jry_bl_stream_stdout,1);
	
	jry_bl_link_list_to_json(&l1,&s2);
	jry_bl_string_view(&s2);
	jry_bl_link_list_from_json(&l2,&s2);
	jry_bl_link_list_view(&l2);
	
	
	jry_bl_string_frees(2,&s1,&s2);
	jry_bl_link_list_frees(2,&l1,&l2);
	jry_bl_stop();	
}