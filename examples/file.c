#include "main.h"

int main()
{
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_file * f1=jbl_file_new();
	f1=jbl_file_open_chars(f1,UC"testfiles//test.txt",JBL_FILE_CLOSE);
	jbl_file_view(f1);

	f1=jbl_file_free(f1);
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop(); 
	
}
