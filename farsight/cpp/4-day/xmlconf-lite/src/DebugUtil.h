#ifndef XSE_DEBUG_UTIL_H
#define XSE_DEBUG_UTIL_H

#ifdef _DEBUG
#	include <assert.h>
#	include <stdio.h>

#	define PRINTF1(s) printf(s);
#	define PRINTF2(s1, s2) printf(s1, s2);
#	define PRINTF3(s1, s2, s3) printf(s1, s2, s3);
#	define PRINTF4(s1, s2, s3, s4) printf(s1, s2, s3, s4)
#	define PRINTF5(s1, s2, s3, s4, s5) printf(s1, s2, s3, s4, s5)
#	undef  ASSERT
#	define ASSERT(s) assert(s);
#else//_DEBUG
#	define PRINTF1(s) (void)0;
#	define PRINTF2(s1, s2) (void)0;
#	define PRINTF3(s1, s2, s3) (void)0;
#	define PRINTF4(s1, s2, s3, s4) (void)0;
#	define PRINTF5(s1, s2, s3, s4, s5) (void)0;
#	define ASSERT(s) (void)0;
#endif//_DEBUG

#endif//XSE_DEBUG_UTIL_H
