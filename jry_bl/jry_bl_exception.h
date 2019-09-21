#ifndef __JRY_BL_EXCEPTION_H
#define __JRY_BL_EXCEPTION_H
#define jry_bl_exception(x) _jry_bl_exception(__FILE__,__LINE__,x)
void _jry_bl_exception(const char * file,int line,const char* x);
#endif
