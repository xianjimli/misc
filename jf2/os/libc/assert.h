#ifndef ASSERT_H
#define ASSERT_H
#ifdef PC
#include <assert.h>
#else
#define assert(p) if(!(p)) {jtrace(__func__, __LINE__, #p);}
#endif

#endif/*ASSERT_H*/
