/*
 *    Vector library. Contains the definition of vector object based on
 *    std::vector. It basically adds functionalities such as inverse element
 *    access, concatenation, etc. See class structure for details.
 *
 *    @ Author: Gonzalo Martínez Lema
 *    @ Date: 22/07/2015
 *    @ version: 0.0
 *    @ Last update: 22/07/2015
 *
 */

#ifndef __GVECTOR__
#define __GVECTOR__

#include <iostream>
#include <stdexcept>
#include <vector>
// #include <algorithm>
#include <cmath>

//#include "Matrix.h"

namespace glib{

  template< class T >
  class Vector : public std::vector<T>
  {
  private:
      void _AssertRange( int index ) const;
      int  _TrueIndex( int index ) const;
      void _AssertDivision( const Vector<T>& V ) const;
      void _AssertDivision( T value ) const;

  public:
      using std::vector<T>::vector;
      Vector():std::vector<T>(){}
      Vector( T values[], int size );

      Vector<T> operator+( const Vector<T>& V ) const;
      Vector<T> operator+( T value ) const;
      Vector<T> operator-( const Vector<T>& V ) const;
      Vector<T> operator-( T value ) const;
      Vector<T> operator*( const Vector<T>& V ) const;
      Vector<T> operator*( T value ) const;
      Vector<T> operator/( const Vector<T>& V ) const;
      Vector<T> operator/( T value ) const;
      Vector<T>& operator+=( const Vector<T>& V );
      Vector<T>& operator+=( T value );
      Vector<T>& operator-=( const Vector<T>& V );
      Vector<T>& operator-=( T value );
      Vector<T>& operator*=( const Vector<T>& V );
      Vector<T>& operator*=( T value );
      Vector<T>& operator/=( const Vector<T>& V );
      Vector<T>& operator/=( T value );
      // Vector<T>& operator=( const Vector<T>& V );

      T operator[]( int index ) const;
      T& operator[]( int index );

      int Last() const;
      int Size() const;
      T* AsArray() const;
      Vector Copy() const;
      Vector Slice( int n0, int n1 ) const;
      Vector Slice( int n0, int n1, int n2 ) const;
      Vector<T> Concatenate( const Vector<T>& V ) const;
      void Append( T value );
      void Remove( T value );
      T Pop( int index = -1 );
      T Sum( void ) const;
      T Mod( void ) const;
      T Dot( const Vector<T>& V ) const;
      void Insert( int index, T value );
      void Erase( int index );
      void Swap( int index0, int index1 );
      //Vector<T> Dot( const Matrix<T>& M ) const;

  }; // class Vector

  template< class T > inline Vector<T>  Vector<T>::operator+( const Vector<T>& V ) const{ Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] += V[i]; return W; }
  template< class T > inline Vector<T>  Vector<T>::operator+( T value ) const{ Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] += value; return W; }
  template< class T > inline Vector<T>  Vector<T>::operator-( const Vector<T>& V ) const{ Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] -= V[i]; return W; }
  template< class T > inline Vector<T>  Vector<T>::operator-( T value ) const{ Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] -= value; return W; }
  template< class T > inline Vector<T>  Vector<T>::operator*( const Vector<T>& V ) const{ Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] *= V[i]; return W; }
  template< class T > inline Vector<T>  Vector<T>::operator*( T value ) const{ Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] *= value; return W; }
  template< class T > inline Vector<T>  Vector<T>::operator/( const Vector<T>& V ) const{ _AssertDivision(V); Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] /= V[i]; return W; }
  template< class T > inline Vector<T>  Vector<T>::operator/( T value ) const{ _AssertDivision(value); Vector<T> W(*this); for ( int i=0; i<this->Size(); i++ ) W[i] /= value; return W; }
  template< class T > inline Vector<T>&  Vector<T>::operator+=( const Vector<T>& V ){ for ( int i=0; i<this->Size(); i++ ) (*this)[i] += V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator+=( T value ){ for ( int i=0; i<this->Size(); i++ ) (*this)[i] += value; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator-=( const Vector<T>& V ){ for ( int i=0; i<this->Size(); i++ ) (*this)[i] -= V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator-=( T value ){ for ( int i=0; i<this->Size(); i++ ) (*this)[i] -= value; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator*=( const Vector<T>& V ){ for ( int i=0; i<this->Size(); i++ ) (*this)[i] *= V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator*=( T value ){ for ( int i=0; i<this->Size(); i++ ) (*this)[i] *= value; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator/=( const Vector<T>& V ){ _AssertDivision(V);for ( int i=0; i<this->Size(); i++ ) (*this)[i] /= V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator/=( T value ){ _AssertDivision(value); for ( int i=0; i<this->Size(); i++ ) (*this)[i] /= value; return *this; }

  template< class T > inline T Vector<T>::operator[]( int index ) const{ _AssertRange(index); return std::vector<T>::operator[]( _TrueIndex(index) );}
  template< class T > inline T& Vector<T>::operator[]( int index ){ _AssertRange(index); return std::vector<T>::operator[]( _TrueIndex(index) );}

  template< class T > inline void Vector<T>::_AssertRange( int index ) const{ int s = this->Size(); if ( ( index >= s ) || ( -index > s ) ) throw std::invalid_argument( "Error in Vector: index out of range" ); }
  template< class T > inline int Vector<T>::_TrueIndex( int index ) const{ return ( index < 0 ? this->Size() + index : index ); }
  template< class T > inline void Vector<T>::_AssertDivision( const Vector<T>& V ) const{ for (int i=0; i<V.Size(); i++ ) if (V[i] == 0) throw std::invalid_argument( "Error in Vector: division by zero" ); }
  template< class T > inline void Vector<T>::_AssertDivision( T value ) const { if (value == 0) throw std::invalid_argument( "Error in Vector: division by zero" ); }
  template< class T > inline int Vector<T>::Last() const{ return ( std::vector<T>::Size() ? std::vector<T>::Size() - 1 : 0 ); }
  template< class T > inline int Vector<T>::Size() const{ return (int)std::vector<T>::size(); }
  //template< class T > inline T*  Vector<T>::AsArray() const{ const int n = this->Size(); T v[n]; for (int i=0; i<n; i++) v[i] = (*this)[i]; return v;}
  template< class T > inline T*  Vector<T>::AsArray() const{ return this->data(); }
  template< class T > inline Vector<T> Vector<T>::Copy() const{ return Vector(*this); }
  template< class T > inline Vector<T> Vector<T>::Slice( int n0, int n1) const{ n0 = _TrueIndex(n0); n1 = _TrueIndex(n1); return Vector( this->begin() + n0, this->begin() + n1 ); }
  template< class T > inline Vector<T> Vector<T>::Slice( int n0, int n1, int n2) const{ n0 = _TrueIndex(n0); n1 = _TrueIndex(n1); Vector<T> W; for( int i = n0; i<n1; i+= n2 ) W.Append((*this)[i]); return W; }
  template< class T > inline T Vector<T>::Pop( int index ){ index  = _TrueIndex(index); T value((*this)[index]); this->erase( this->begin() + index ); return value; }
  template< class T > inline T Vector<T>::Sum( void ) const{ T sum = this->front(); for ( int i=1; i<this->Size(); i++ ) sum += (*this)[i]; return sum;}
  template< class T > inline T Vector<T>::Mod( void ) const{ return sqrt( this->Dot(*this) ); }
  template< class T > inline T Vector<T>::Dot( const Vector<T>& V ) const{ return ( (*this) * V ).Sum(); }
  template< class T > inline void Vector<T>::Append( T value ){ this->push_back( value ); }
  template< class T > inline void Vector<T>::Insert( int index, T value){ this->insert( this->begin() + _TrueIndex(index), value ); }
  template< class T > inline void Vector<T>::Erase( int index ){ this->erase( this->begin() + _TrueIndex(index) ); }
  template< class T > inline void Vector<T>::Swap( int index0, int index1 ){ index0  = _TrueIndex(index0); index1  = _TrueIndex(index1); int i0 = std::min(index0,index1); int i1 = std::max(index0,index1); this->Insert( i0, this->Pop(i1) ); this->Insert( i1, this->Pop(++i0) ); }
  //template< class T > inline Vector<T> Vector<T>::Dot( const Matrix<T>& M ) const{ Vector W; for ( int i=0; i<this->Size(); i++ ) W.Append( this->Dot( M.Column(i) ) ); return W;}

} // namespace glib

template< class T > std::ostream& operator <<( std::ostream& os, const glib::Vector<T>& V );
template< class T > std::ostream& operator <<( std::ostream& os, const glib::Vector<T>* V );

#endif // __GVECTOR__
