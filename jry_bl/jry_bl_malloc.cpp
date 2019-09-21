#include "jry_bl_malloc.h"
void* jry_bl_malloc(size_t size)
{
	return malloc(size);
}
void* jry_bl_realloc(void* ptr,size_t size)
{
#ifdef linux	
	return realloc(ptr,size);
#else
	void * p=malloc(size);
	if(p==NULL)
		return NULL;
	size_t s=_msize(ptr);
	memcpy(p,ptr,s);
	free(ptr);
	return p;
#endif
}
void* jry_bl_free(void * p)
{
	free(p);
}