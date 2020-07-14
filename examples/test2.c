#include <signal.h>
#include <stdio.h>
int on=0;
void jbl_signal_callback(int sign)
{
	on=1;
	for(int i=0;i<1000;++i)
		printf("2\n");
	exit(0);
}
void main()
{
	signal(SIGINT,jbl_signal_callback);	
	signal(SIGTERM,jbl_signal_callback);	
	while(1)
		if(!on)
			printf("1\n");
}