#include "jry_bl_exception.h"
#include <iostream>
void _jry_bl_exception(const char * file,int line,const char* x)
{
	std::cout<<"\nAt "<<file<<" line "<<line<<'\n'<<x<<"\n";
	exit(0);
}