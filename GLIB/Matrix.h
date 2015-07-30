/*
 *    Matrix library. Contains the definition of matrix object based on
 *    std::vector< std::vector >. It basically adds the matrix-related
 *    functionalities to Vector
 *
 *    @ Author: Gonzalo Martínez Lema
 *    @ Date: 22/07/2015
 *    @ version: 0.0
 *    @ Last update: 22/07/2015
 *
 */

#ifndef __GMATRIX__
#define __GMATRIX__

#include "Vector.h"

namespace glib{

  template< class T >
  class Matrix : public Vector<T>
  {
  public:
      using Vector<T>::Vector;
      Matrix( T values[], int size );

  }; // class Vector

} // namespace glib

template< class T > std::ostream& operator <<( std::ostream& os, const glib::Vector<T>& V );
template< class T > std::ostream& operator <<( std::ostream& os, const glib::Vector<T>* V );

#endif // __GMATRIX__
