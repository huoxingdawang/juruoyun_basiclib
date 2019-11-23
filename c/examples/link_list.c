#include "main.h"

int main()
{
	printf("--------------------------------" __FILE__ "--------------------------------\n");
	jry_bl_malloc_init();	
	jry_bl_link_list l1,l2;jry_bl_link_list_inits(2,&l1,&l2);
	jry_bl_var v1;jry_bl_var_init(&v1);
	jry_bl_string s1,s2;jry_bl_string_inits(2,&s1,&s2);
/*	
	for(int i=0;i<5;i++)
	{
		jry_bl_string_equal_long_long(&s1,i);
		jry_bl_var_equal_string(&v1,&s1);	
		jry_bl_link_list_add_var_light_move(&l1,&v1);
		jry_bl_var_free(&v1);
	}
	jry_bl_string_clear(&s1);
	jry_bl_link_list_view(&l1,stderr);
	jry_bl_link_list_delete_head(&l1);
	jry_bl_link_list_delete_tail(&l1);
	jry_bl_link_list_view(&l1,stderr);
	jry_bl_link_list_swap_node(&l1,l1.head->nxt,l1.tail);
	jry_bl_link_list_view(&l1,stderr);
	jry_bl_link_list_frees(2,&l1,&l2);
*/	
/*	
	jry_bl_string_equal_char_pointer(&s1,"12312312\n1231231");
	jry_bl_string_cut(&s1,&l1,'\n');
	jry_bl_link_list_view(&l1,stderr);
	jry_bl_string_equal_char_pointer(&s1,"125675675675763\n1231231");
	jry_bl_string_cut(&s1,&l2,'\n');
	jry_bl_link_list_view(&l2,stderr);
	printf("space ship:%d",jry_bl_link_list_space_ship(&l1,&l2));
	jry_bl_link_list_frees(2,&l1,&l2);
*/	
/*
	jry_bl_string_equal_char_pointer(&s1,"12312312\n1231231");
	jry_bl_string_cut(&s1,&l1,'\n');
	jry_bl_link_list_equal_light_move(&l2,&l1);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size);	
	jry_bl_link_list_frees(1,&l1);
	jry_bl_link_list_view(&l2,stderr);
*/
	jry_bl_string_equal_char_pointer(&s1,"12312312\n1231231");
	jry_bl_string_cut(&s1,&l1,'\n');
	jry_bl_link_list_to_json(&l1,&s2);
	jry_bl_string_view(&s2,stderr);
	jry_bl_link_list_from_json(&l2,&s2);
	jry_bl_link_list_view(&l2,stderr);
	
	
	jry_bl_string_frees(2,&s1,&s2);
	jry_bl_link_list_frees(2,&l1,&l2);
	printf("\nMEMEORY:%lld\n",jry_bl_malloced_size);	
}
