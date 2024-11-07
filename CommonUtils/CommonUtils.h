#pragma once

#include <windows.h>
#include <stdarg.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

/* Define the LIBSPEC modifier for function names and other imported/exported
 * symblols. This is only required when building for Win32; you wouldn't
 * need this under, for example, UNIX/Linux. The following #ifdef is
 * redundant (we're only building for Win32), but it's a good habit in case
 * you need to build portable code in the future
 */
#ifdef WIN32
 /* When building a static library, the only modifier needed is
	extern "C" when calling from a C++ program */
#ifdef _LIB
#if defined (__cplusplus)
#define LIBSPEC extern "C"
#else
#define LIBSPEC
#endif	/* __cplusplus */
#endif	/* _STATICLIB */

#ifdef _WINDLL
#define LIBSPEC __declspec (dllexport)
#elif defined(__cplusplus)
#define LIBSPEC extern "C" __declspec (dllimport)
#else 
#define LIBSPEC __declspec (dllimport)
#endif

#endif	/* end of #ifdef WIN32 */

#define EMPTY _T ("")
#define YES _T ("y")
#define NO _T("n")
#define CR 0x0D
#define LF 0x0A
#define TSIZE sizeof (TCHAR)

/* Limits and constants. */
#define TYPE_FILE 1		/* Used in ls, rm, and lsFP */
#define TYPE_DIR 2
#define TYPE_DOT 3

#define MAX_OPTIONS 20	/* Max # command line options */
#define MAX_ARG 1000	/* Max # of command line arguments */
#define MAX_COMMAND_LINE MAX_PATH+50 /* Max size of a command line */
#define MAX_PATH_LONG 32767  /* Very long path names with \\?\ prefix. */
#define MAX_NAME 256    /* Name length - users and groups */

LIBSPEC DWORD Options(int, LPCTSTR*, LPCTSTR, ...);
LIBSPEC VOID ReportError(LPCTSTR, DWORD, BOOL);
LIBSPEC VOID ReportException(LPCTSTR, DWORD);

/* Constants needed by the security functions. */
#define LUSIZE 1024
#define ACCT_NAME_SIZE LUSIZE

#ifdef _UNICODE /* This declaration had to be added. */
#define _tstrrchr wcsrchr
#else
#define _tstrrchr strrchr
#endif

#ifdef _UNICODE /* This declaration had to be added. */
#define _tstrstr wcsstr
#else
#define _tstrstr strstr
#endif

#ifdef _UNICODE /* This declaration had to be added. */
#define _memtchr wmemchr
#else
#define _memtchr memchr
#endif
