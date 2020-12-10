#include "main.h"
int main(int argc,char** argv)
{
#if JBL_JSON_ENABLE ==1
	jbl_start();
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
/*
	jbl_stream* fs1=jbl_file_stream_new(jbl_file_open_chars(NULL,UC((argc>1)?argv[1]:"testfiles/test.json"),JBL_FILE_READ));
	jbl_stream * jdes=jbl_json_decode_stream_new();
	jbl_stream_connect(fs1,jdes);
	jbl_stream_do(fs1,true);
	void * v1=jbl_json_decode_stream_var(jdes);
	jbl_var_view(v1);
	v1=jbl_var_free(v1);
		
	jdes=jbl_stream_free(jdes);
	fs1=jbl_stream_free(fs1);
*/
	pchars("--------------------------------" __FILE__ "--------------------------------\n");
	jbl_stop();	
#endif
}