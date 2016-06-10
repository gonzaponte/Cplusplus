/*
 *    GLIB: Gonzalo's library. Contains the definition of useful objects for
 *    a wide range of applications, but they are mainly maths-oriented.
 *
 *    @ Author: Gonzalo Martínez Lema
 *    @ Date: 10/07/2016
 *    @ version: 0.0
 *    @ Last update: 10/07/2016
 *
 */

#ifndef __GLIB_DECLARATIONS__
#define __GLIB_DECLARATIONS__

#if __cplusplus < 201103L
#error "This code must be compiled with -std=c++0x or above"
#endif

namespace glib{
  template<class T> class Vector;
  template<class T> class Matrix;
}
#endif // __GLIB_DECLARATIONS__
