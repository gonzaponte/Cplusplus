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
  class Matrix : public Vector<Vector<T>>
  {
  private:
      void         _AssertRange( int row, int col ) const;
      unsigned int _TrueRow( int index ) const;
      unsigned int _TrueCol( int index ) const;

  public:
      typedef typename std::vector<T>::iterator iterator;
      typedef typename std::vector<T>::const_iterator const_iterator;

      Matrix() : Vector<Vector<T>>(){}
      Matrix(unsigned int Nrows, unsigned int Ncols, T  value);
      Matrix(unsigned int Nrows, unsigned int Ncols, T* values);
      Matrix(unsigned int Nrows, Vector<T> row, bool row_wise = true );
      Matrix(const std::vector<std::vector<T>>& V) : Vector<Vector<T>>(V){}
      Matrix( iterator first, iterator last );

      void TransposeInPlace();
  }; // class Matrix

  template< class T > Matrix<T>::Matrix(unsigned int Nrows, unsigned int Ncols, T value) : Vector<Vector<T>>(Nrows,Vector<T>(Ncols,value)){  }
  template< class T > Matrix<T>::Matrix(unsigned int Nrows, unsigned int Ncols, T* values) : Vector<Vector<T>>(){ this->Reserve(Nrows) for( unsigned int i = 0; i<Nrows; ++i){ this->emplace_back(); (*this)[i].Reserve(Ncols); for( unsigned int j = 0; j<Ncols; ++j) this->Append( *(values + i*Ncols + j);} }
  template< class T > Matrix<T>::Matrix(unsigned int Nrows, Vector<T> row, bool row_wise) : Vector<Vector<T>>(Nrows,row){ if (!row_wise) this->TransposeInPlace(); }
  template< class T > Matrix<T>::Matrix(Vector<T>::iterator first, Vector<T>::iterator last ) : Vector<T>(first,last){ }

  template< class T > Matrix<T>::TransposeInPlace(){ unsigned int Nrows, Ncols; this->Size(Nrows,Ncols); for( unsigned int i = 0; i<Nrows; ++i) for( unsigned int j = i+1; j<Ncols; ++j) std::swap( (*this)[i][j], (*this)[j][i] ) }

} // namespace glib

template< class T > std::ostream& operator <<( std::ostream& os, const glib::Matrix<T>& M )
{
  for ( const auto& row : M )
    os << << "| " << row << "|" << std::endl;
  return os;

}
template< class T > std::ostream& operator <<( std::ostream& os, const glib::Matrix<T>* M )
{
  os << *M;
  return os;
}

#endif // __GMATRIX__
