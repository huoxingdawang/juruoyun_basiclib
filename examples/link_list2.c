#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_start();	
	jbl_link_list l1,l2;jbl_link_list_inits(2,&l1,&l2);
	jbl_var v1;jbl_var_init(&v1);
	jbl_string s1,s2;jbl_string_inits(2,&s1,&s2);
/*	
	for(int i=0;i<5;i++)
	{
		jbl_string_equal_int64(&s1,i);
		jbl_var_equal_string(&v1,&s1,move);	
		jbl_link_list_add_var_move(&l1,&v1);
		jbl_var_free(&v1);
	}
	jbl_string_clear(&s1);
	jbl_link_list_view(&l1);
	jbl_link_list_delete_head(&l1);
	jbl_link_list_delete_tail(&l1);
	jbl_link_list_view(&l1);
	jbl_link_list_swap_node(&l1,l1.head->nxt,l1.tail);
	jbl_link_list_view(&l1);
	jbl_link_list_frees(2,&l1,&l2);
*/	
/*	
	jbl_string_equal_chars(&s1,"12312312\n1231231");
	jbl_string_cut(&s1,&l1,'\n');
	jbl_link_list_view(&l1);
	jbl_string_equal_chars(&s1,"125675675675763\n1231231");
	jbl_string_cut(&s1,&l2,'\n');
	jbl_link_list_view(&l2);
	printf("space ship:%d",jbl_link_list_space_ship(&l1,&l2));
	jbl_link_list_frees(2,&l1,&l2);
*/	
/*
	jbl_string_equal_chars(&s1,"12312312\n1231231");
	jbl_string_cut(&s1,&l1,'\n');
	jbl_link_list_equal_move(&l2,&l1);
	jbl_stop();	
	jbl_link_list_frees(1,&l1);
	jbl_link_list_view(&l2);
*/
	jbl_string_equal_chars(&s1,"12312312\n1231231");
	jbl_string_cut(&s1,&l1,'\n');
	jbl_link_list_put(&l1,&jbl_stream_stdout,view,(jbl_view_default_tabs_num<<16)|(__LINE__<<1)|1,__FILE__);jbl_stream_do(&jbl_stream_stdout,1);
	
	jbl_link_list_to_json(&l1,&s2);
	jbl_string_view(&s2);
	jbl_link_list_from_json(&l2,&s2);
	jbl_link_list_view(&l2);
	
	
	jbl_string_frees(2,&s1,&s2);
	jbl_link_list_frees(2,&l1,&l2);
	jbl_stop();	
}
