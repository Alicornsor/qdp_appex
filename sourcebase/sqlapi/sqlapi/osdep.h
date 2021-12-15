// osdep.h



#if !defined(OSDEP_H__B087DD27_981D_4084_991C_5328FC455942__INCLUDED_)

#define OSDEP_H__B087DD27_981D_4084_991C_5328FC455942__INCLUDED_



#if defined(_WINDOWS) || defined(WIN32)

	#include <windows.h>

#endif


#ifndef va_copy 
# ifdef __va_copy 
# define va_copy(DEST,SRC) __va_copy((DEST),(SRC)) 
# else 
# define va_copy(DEST, SRC) memcpy((&DEST), (&SRC), sizeof(va_list)) 
# endif 
#endif 


#endif // !defined(OSDEP_H__B087DD27_981D_4084_991C_5328FC455942__INCLUDED_)

