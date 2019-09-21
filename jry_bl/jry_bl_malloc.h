#ifndef __JRY_BL_MALLOC_H
#define __JRY_BL_MALLOC_H
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
void* jry_bl_malloc(size_t size);
void* jry_bl_realloc(void* ptr,size_t size);
void* jry_bl_free(void * p);
#endif
