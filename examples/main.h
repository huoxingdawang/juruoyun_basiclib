#ifndef __MAIN_H
#define __MAIN_H
#include "include.h"
#include <stdlib.h>
#ifdef __linux__
#define filename "testfiles/test.txt"
#else
#define filename "testfiles\\test.txt"
#endif
#endif
