#include "main.h"

int main()
{
#if JBL_LL_ENABLE ==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_ll * l1=jbl_ll_new();
	jbl_ll * l2=NULL;
	jbl_ll * l3=NULL;
	jbl_string * v1=jbl_string_add_chars(NULL,UC"juruoyun");
	jbl_string * v2=jbl_string_add_chars(NULL,UC"12345678");
	jbl_var_data * v3=jbl_Vuint_set(NULL,19260817);
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
	jbl_ll_view(l1);
	jbl_var_view(l2);
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
	jbl_ll_view(l1);
	jbl_ll_view(l2);
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
	s1=jbl_string_free(s1);
	
	
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
#endif
}
