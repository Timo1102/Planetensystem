#ifndef _RK_DATATYPES_HPP_
#define _RK_DATATYPES_HPP_

#include "defines.hpp"

namespace RK
{
    typedef unsigned char       RKubyte;
	typedef unsigned char       RKuchar;
    typedef unsigned short      RKushort;
    typedef unsigned int        RKuint;
    typedef unsigned long long  RKuint64;
    typedef signed char         RKbyte;
	typedef char                RKchar;
    typedef signed short        RKshort;
    typedef signed int          RKint;
    typedef signed long long    RKint64;
    typedef float               RKfloat;
    typedef double              RKdouble;
    typedef long double         RKldouble;
    typedef void                RKvoid;
    typedef unsigned int        RKbitfield;
    typedef unsigned int        RKenum;
    typedef bool                RKboolean;
    typedef unsigned long       RKulong;
    typedef signed long         RKlong;
  #if defined(RK_CPU_X64)
    typedef unsigned long long  RKuintptr;
    typedef signed long long    RKintptr;
    typedef signed long long    RKsizei;
  #elif defined(RK_CPU_X86)
    typedef unsigned int        RKuintptr;
    typedef signed int          RKintptr;
    typedef signed int          RKsizei;
  #endif
}

#endif