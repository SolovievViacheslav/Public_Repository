#ifndef __TCHAR_VAR_H__
#define __TCHAR_VAR_H__

#ifdef WIN32
#include "tchar.h"
#else

#endif

#endif

#if defined(_UNICODE) || defined(UNICODE)

#define TCHAR   wchar_t
#define LPCTSTR const wchar_t*
#define LPWSTR  wchar_t*

#ifndef _T
#define _T(x) L##x
#endif

#else //defined(_UNICODE) || defined(UNICODE)
#define TCHAR char_t
#define LPCTSTR const char*

#define _T(x) x
#endif

#ifndef _MAX_PATH
#define _MAX_PATH 260
#define MAX_PATH 260
#endif
