#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/math_constants_availability.hpp>
//
// E.g. see the MSDN article on “math constants” at
// <url: https://msdn.microsoft.com/en-us/library/4hwaceh6.aspx>.
//
// STDLIB_NO_MATH_CONSTANTS suppresses the constant definitions.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef STDLIB_NO_MATH_CONSTANTS
#   undef   __STRICT_ANSI__             // For g++
#   undef   _USE_MATH_DEFINES           // Suppress sillywarning.
#   define  _USE_MATH_DEFINES           // M_PI etc.
#endif

// At least with MSVC this works for defining M_PI etc. even if <math.h> has
// been previously included - the definitions are outside the normal guard.
#include <math.h>
#include <cmath>

#ifndef STDLIB_NO_MATH_CONSTANTS
    #ifndef M_PI // TODO: also handle non-macro
        #define M_E         2.71828182845904523536          // e               
        #define M_LOG2E     1.44269504088896340736          // log2(e)         
        #define M_LOG10E    0.434294481903251827651         // log10(e)        
        #define M_LN2       0.693147180559945309417         // ln(2)           
        #define M_LN10      2.30258509299404568402          // ln(10)          
        #define M_PI        3.14159265358979323846          // pi              
        #define M_PI_2      1.57079632679489661923          // pi/2            
        #define M_PI_4      0.785398163397448309616         // pi/4            
        #define M_1_PI      0.318309886183790671538         // 1/pi            
        #define M_2_PI      0.636619772367581343076         // 2/pi            
        #define M_2_SQRTPI  1.12837916709551257390          // 2/sqrt(pi)      
        #define M_SQRT2     1.41421356237309504880          // sqrt(2)         
        #define M_SQRT1_2   0.707106781186547524401         // 1/sqrt(2)       
    #endif
#endif
