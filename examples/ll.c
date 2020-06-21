#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_ll * l1=jbl_ll_new();
	jbl_ll * l2=NULL;
	jbl_ll * l3=NULL;
	jbl_var * vl1=NULL;
	jbl_var * vl2=NULL;	
	jbl_var * v1=jbl_V(jbl_string_add_chars(jbl_Vstring(jbl_Vstring_new()),UC"juruoyun"));
	jbl_var * v2=jbl_V(jbl_string_add_chars(jbl_Vstring(jbl_Vstring_new()),UC"12345678"));
	jbl_var * v3=jbl_Vuint_set(NULL,19260817);
	jbl_var * v4=NULL;
	jbl_string *s1=NULL;
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("插入\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	l1=jbl_ll_add(l1,v1);
	l1=jbl_ll_add(l1,v2);
	jbl_ll_view(l1);
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("交换\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	l1=jbl_ll_swap_node(l1,l1->head,l1->tail);
	jbl_ll_view(l1);
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("复制\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	l2=jbl_ll_copy(l1);
	v4=jbl_ll_copy_as_var(l1);
	jbl_ll_view(l1);
	jbl_ll_view(l2);
	jbl_var_view(v4);
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("太空船操作符\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	jbl_ll_view(l1);
	jbl_ll_view(l2);
	pchars("Space ship test:"),pint(jbl_ll_space_ship(l1,l2)),pn();
	l2=jbl_ll_swap_node(l2,l2->head,l2->tail);
	jbl_ll_view(l1);
	jbl_ll_view(l2);
	pchars("Space ship test:"),pint(jbl_ll_space_ship(l1,l2)),pn();	
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("写时分离\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	l2=jbl_ll_add(l2,v3);
	v4=jbl_V(jbl_ll_add(jbl_Vll(v4),v1));
	jbl_ll_view(l1);
	jbl_ll_view(l2);
	jbl_var_view(v4);
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("合并\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	l1=jbl_ll_merge(l1,l2);
	jbl_ll_view(l1);
	jbl_ll_view(l2);	
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("JSON\n");
pchars("/////////////////////////////////////////////////////////////////////\n");	
	jbl_ll_json_put(l1,jbl_stream_stdout,1,1);
	pn();
	s1=jbl_ll_json_encode(l1,NULL,1,1);
	jbl_string_view(s1);
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("Var & refer\n");
pchars("/////////////////////////////////////////////////////////////////////\n");		
	
	vl1=jbl_Vll_new();
	vl1=jbl_V(jbl_ll_merge(jbl_Vll(vl1),l2));
	jbl_var_view(vl1);
	l3=jbl_refer(&l2);
	jbl_ll_view(l3);
	vl2=jbl_refer(&vl1);
	jbl_var_view(vl2);
	vl2=jbl_V(jbl_ll_add(jbl_Vll(vl2),v3));
	jbl_var_view(vl2);
	l3=jbl_ll_delete_head(l3);
	l3=jbl_ll_delete_tail(l3);
	jbl_ll_view(l3);
#if JBL_HT_ENABLE==1
pchars("/////////////////////////////////////////////////////////////////////\n");
pchars("ht合并\n");
pchars("/////////////////////////////////////////////////////////////////////\n");
	jbl_ht * h1=jbl_ht_merge_ll(NULL,l2);
	jbl_ll_view(l2);
	jbl_ht_view(h1);
	h1=jbl_ht_free(h1);
#endif	
//exit:;
	l1=jbl_ll_free(l1);
	l2=jbl_ll_free(l2);
	l3=jbl_ll_free(l3);
	v1=jbl_var_free(v1);
	v2=jbl_var_free(v2);
	v3=jbl_var_free(v3);
	v4=jbl_var_free(v4);
	s1=jbl_string_free(s1);
	vl1=jbl_var_free(vl1);
	vl2=jbl_var_free(vl2);
/*
	jbl_ll l1,l2;jbl_ll_inits(2,&l1,&l2);
	jbl_var v1;jbl_var_init(&v1);
	jbl_string s1,s2;jbl_string_inits(2,&s1,&s2);
	for(int i=0;i<5;i++)
	{
		jbl_string_equal_int64(&s1,i);
		jbl_var_equal_string(&v1,&s1,move);	
		jbl_ll_add_var_move(&l1,&v1);
		jbl_var_free(&v1);
	}
	jbl_string_clear(&s1);
	jbl_ll_view(&l1);
	jbl_ll_delete_head(&l1);
	jbl_ll_delete_tail(&l1);
	jbl_ll_view(&l1);
	jbl_ll_swap_node(&l1,l1.head->nxt,l1.tail);
	jbl_ll_view(&l1);
	jbl_ll_frees(2,&l1,&l2);
*/	
/*	
	jbl_string_equal_chars(&s1,UC"12312312\n1231231");
	jbl_string_cut(&s1,&l1,'\n');
	jbl_ll_view(&l1);
	jbl_string_equal_chars(&s1,UC"125675675675763\n1231231");
	jbl_string_cut(&s1,&l2,'\n');
	jbl_ll_view(&l2);
	printf("space ship:%d",jbl_ll_space_ship(&l1,&l2));
	jbl_ll_frees(2,&l1,&l2);
	jbl_string_equal_chars(&s1,UC"12312312\n1231231");
	jbl_string_cut(&s1,&l1,'\n');
	jbl_ll_equal_move(&l2,&l1);
	jbl_stop();	
	jbl_ll_frees(1,&l1);
	jbl_ll_view(&l2);
	jbl_string_equal_chars(&s1,UC"12312312\n1231231");
	jbl_string_cut(&s1,&l1,'\n');
	jbl_ll_put(&l1,&jbl_stream_stdout,view,(JBL_VIEW_DEFAULT_TABS<<16)|(__LINE__<<1)|1,__FILE__);jbl_stream_do(&jbl_stream_stdout,1);
	
	jbl_ll_to_json(&l1,&s2);
	jbl_string_view(&s2);
	jbl_ll_from_json(&l2,&s2);
	jbl_ll_view(&l2);
	
	
	jbl_string_frees(2,&s1,&s2);
	jbl_ll_frees(2,&l1,&l2);

*/
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
}
