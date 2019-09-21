#ifndef __JRY_BL_STRING_H
#define __JRY_BL_STRING_H

#include "jry_bl_exception.h"
#include "jry_bl_string_config.h"
#include "jry_bl_malloc.h"
#if JRY_BL_STRING_IOSTREAM_USE==1
#include <iostream>
#endif

#include <stdio.h>
#include <cmath>

class jry_bl_string
{
	private:
		JRY_BL_STRING_SIZE_TYPE	len;
		JRY_BL_STRING_SIZE_TYPE	size;
		char *					s;
	public:
		jry_bl_string();
		jry_bl_string(JRY_BL_STRING_SIZE_TYPE sizee);
		jry_bl_string(const char *in);
		char & 					operator []		(JRY_BL_STRING_SIZE_TYPE i);
		const char & 			operator []		(JRY_BL_STRING_SIZE_TYPE i) const;
		jry_bl_string 			operator +=		(const jry_bl_string& b);
		jry_bl_string 			operator +=		(const char * s2);
		jry_bl_string 			operator +=		(long long in);
		jry_bl_string 			operator =		(const jry_bl_string& b);
#if JRY_BL_STRING_IOSTREAM_USE==1
		friend std::ostream &	operator<<	(std::ostream& out, const jry_bl_string& that);
#endif	
		void 		view				(FILE * file);
		void 		free				();
		long long 	getint				();
		long long	getint				(JRY_BL_STRING_SIZE_TYPE start);
};






#endif
