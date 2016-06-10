/*
 *    Vector library. Contains the definition of vector object based on
 *    std::vector. It basically adds functionalities such as inverse element
 *    access, concatenation, etc. See class structure for details.
 *
 *    @ Author: Gonzalo Martínez Lema
 *    @ Date: 22/07/2015
 *    @ version: 0.1
 *    @ Last update: 10/07/2016
 *
 */

#ifndef __GVECTOR__
#define __GVECTOR__

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>

#include "GLIB.h"

namespace glib{

  template< class T >
  class Vector : public std::vector<T>
  {
  private:
      void         _AssertStep( int step ) const;
      void         _AssertRange( int index ) const;
      unsigned int _TrueIndex( int index ) const;
      void         _AssertDivision( const Vector<T>& V ) const;
      void         _AssertDivision( T value ) const;

  public:
      typedef typename std::vector<T>::iterator iterator;
      typedef typename std::vector<T>::const_iterator const_iterator;
      // typedef typename std::vector<T>::iterator Iter;
      static bool StepAssertion;
      static bool RangeAssertion;
      static bool DivisionAssertion;

      Vector() : std::vector<T>(){}
      Vector(unsigned int Nvalues, T value);
      Vector(unsigned int Nvalues, T* values);
      Vector( T* first, T* last );
      Vector(const std::vector<T>& V) : std::vector<T>(V){ std::cout << "OKKKK" << std::endl;}
      Vector( iterator first, iterator last );

      Vector<T>  operator+ ( const Vector<T>& V ) const;
      Vector<T>  operator+ ( T value ) const;
      Vector<T>  operator- ( const Vector<T>& V ) const;
      Vector<T>  operator- ( T value ) const;
      Vector<T>  operator* ( const Vector<T>& V ) const;
      Vector<T>  operator* ( T value ) const;
      Vector<T>  operator/ ( const Vector<T>& V ) const;
      Vector<T>  operator/ ( T value ) const;

      Vector<T>& operator+=( const Vector<T>& V );
      Vector<T>& operator+=( T value );
      Vector<T>& operator-=( const Vector<T>& V );
      Vector<T>& operator-=( T value );
      Vector<T>& operator*=( const Vector<T>& V );
      Vector<T>& operator*=( T value );
      Vector<T>& operator/=( const Vector<T>& V );
      Vector<T>& operator/=( T value );
      Vector<T>& operator= ( const std::vector<T>& V );

      T  operator[]( int index ) const;
      T& operator[]( int index );

      unsigned int Last() const;
      unsigned int Size() const;
      T* AsArray() const;
      Vector Copy() const;
      // Vector Slice( int n0, int n1 ) const;
      Vector Reverse() const;
      void   ReverseInPlace();
      Vector Slice( int n0, int n1, int step = 1 ) const;
      Vector ForwardSlice( int n0, int n1, int step = 1 ) const;
      Vector ReverseSlice( int n0, int n1, int step = 1 ) const;
      Vector<T> Concatenate( const Vector<T>& V ) const;
      T Sum() const;
      double Mod() const;
      double Mod2() const;
      T Dot( const Vector<T>& V ) const;
      T Pop( int index = -1 );
      void Reserve( unsigned int N );
      void Append( T value );
      void Remove( T value );
      void Insert( int index, T value );
      void Erase( int index );
      void Swap( int index0, int index1 );
      //Vector<T> Dot( const Matrix<T>& M ) const;

  }; // class Vector
  template< class T > Vector<T>::Vector(unsigned int Nvalues, T value) : std::vector<T>(Nvalues,value){  }
  template< class T > Vector<T>::Vector(unsigned int Nvalues, T* values) : std::vector<T>(values, values + Nvalues){  }
  template< class T > Vector<T>::Vector(T* first, T* last) : std::vector<T>(first,last){  }
  template< class T > Vector<T>::Vector(Vector<T>::iterator first, Vector<T>::iterator last ) : std::vector<T>(first,last){ }

  template< class T > inline Vector<T>   Vector<T>::operator+ ( const Vector<T>& V ) const{ Vector<T> W(*this); W += V; return W; }
  template< class T > inline Vector<T>   Vector<T>::operator+ ( T value ) const{ Vector<T> W(*this); W += value; return W; }
  template< class T > inline Vector<T>   Vector<T>::operator- ( const Vector<T>& V ) const{ Vector<T> W(*this); W -= V; return W; }
  template< class T > inline Vector<T>   Vector<T>::operator- ( T value ) const{ Vector<T> W(*this); W -= value; return W; }
  template< class T > inline Vector<T>   Vector<T>::operator* ( const Vector<T>& V ) const{ Vector<T> W(*this); W *= V; return W; }
  template< class T > inline Vector<T>   Vector<T>::operator* ( T value ) const{ Vector<T> W(*this); W *= value; return W; }
  template< class T > inline Vector<T>   Vector<T>::operator/ ( const Vector<T>& V ) const{ Vector<T> W(*this); W /= V; return W; }
  template< class T > inline Vector<T>   Vector<T>::operator/ ( T value ) const{ Vector<T> W(*this); W /= value; return W; }

  template< class T > inline Vector<T>&  Vector<T>::operator+=( const Vector<T>& V ){ for ( unsigned int i=0; i<this->Size(); ++i ) (*this)[i] += V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator+=( T value ){ for ( T& vi : *this ) vi += value; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator-=( const Vector<T>& V ){ for ( unsigned int i=0; i<this->Size(); ++i ) (*this)[i] -= V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator-=( T value ){ for ( T& vi : *this ) vi -= value; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator*=( const Vector<T>& V ){ for ( unsigned int i=0; i<this->Size(); ++i ) (*this)[i] *= V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator*=( T value ){ for ( T& vi : *this ) vi *= value; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator/=( const Vector<T>& V ){ _AssertDivision(V); for ( unsigned int i=0; i<this->Size(); ++i ) (*this)[i] /= V[i]; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator/=( T value ){ _AssertDivision(value); for ( T& vi : *this ) vi /= value; return *this; }
  template< class T > inline Vector<T>&  Vector<T>::operator= ( const std::vector<T>& V ){ *this = V; }

  template< class T > inline T  Vector<T>::operator[]( int index ) const{ _AssertRange(index); return std::vector<T>::operator[]( _TrueIndex(index) );}
  template< class T > inline T& Vector<T>::operator[]( int index )      { _AssertRange(index); return std::vector<T>::operator[]( _TrueIndex(index) );}

  template< class T > inline void Vector<T>::_AssertStep( int step ) const{ if ( StepAssertion && !step ) throw std::invalid_argument( "Error in Vector: not valid step for slicing" ); }
  template< class T > inline void Vector<T>::_AssertRange( int index ) const{ if ( RangeAssertion && ( index < 0 ? -index > this->Size() : index >= this->Size() ) ) throw std::invalid_argument( "Error in Vector: index out of range" ); }
  template< class T > inline void Vector<T>::_AssertDivision( const Vector<T>& V ) const{ if ( DivisionAssertion && std::find( V.begin(), V.end(), (T) 0 ) != V.end() ) throw std::invalid_argument( "Error in Vector: division by zero" ); }
  template< class T > inline void Vector<T>::_AssertDivision( T value ) const { if (!value) throw std::invalid_argument( "Error in Vector: division by zero" ); }
  template< class T > inline unsigned int Vector<T>::_TrueIndex( int index ) const{ return (unsigned int) ( index < 0 ? (int)this->Size() + index : index ); }
  template< class T > inline unsigned int Vector<T>::Last() const{ return std::max( this->Size() - 1, 0 ); }
  template< class T > inline unsigned int Vector<T>::Size() const{ return this->size(); }

  //template< class T > inline T*  Vector<T>::AsArray() const{ const int n = this->Size(); T v[n]; for (int i=0; i<n; i++) v[i] = (*this)[i]; return v;}
  template< class T > inline T* Vector<T>::AsArray() const{ return this->data(); }
  template< class T > inline Vector<T> Vector<T>::Copy() const{ return Vector<T>(*this); }
  // template< class T > inline Vector<T> Vector<T>::Slice( int n0, int n1) const{ return Vector<T>( this->begin() + _TrueIndex(n0), this->begin() + _TrueIndex(n1) ); }
  // template< class T > inline Vector<T> Vector<T>::Slice( int n0, int n1) const{ return Vector<T>(); }
  template< class T > inline Vector<T> Vector<T>::Reverse() const{ Vector<T> W(*this); W.ReverseInPlace(); return W;}
  template< class T > inline void      Vector<T>::ReverseInPlace(){ for ( unsigned int i=0; i<this->Size()/2; ++i ) this->Swap(i,-i-1); }
  template< class T > inline Vector<T> Vector<T>::Slice( int n0, int n1, int step) const{ _AssertStep(step); return step>0? this->ForwardSlice(_TrueIndex(n0),_TrueIndex(n1),step) : this->ReverseSlice(_TrueIndex(n0),_TrueIndex(n1),-step); }
  template< class T > inline Vector<T> Vector<T>::ForwardSlice( int n0, int n1, int step) const{ Vector<T> W; for( int i = n0; i<n1; i+= step ) W.Append((*this)[i]); return W; }
  template< class T > inline Vector<T> Vector<T>::ReverseSlice( int n0, int n1, int step) const{ Vector<T> W; for( int i = n1; i>n0; i-= step ) W.Append((*this)[i]); return W; }
  template< class T > inline Vector<T> Vector<T>::Concatenate( const Vector<T>& V ) const{ Vector<T> W(*this); W.Reserve( this->size() + V.size() ); for ( T vi : V) W.emplace_back( vi ); return W; }
  template< class T > inline T Vector<T>::Pop( int index ){ T out = (*this)[index]; this->Erase( index ); return out; }
  template< class T > inline T Vector<T>::Sum( void ) const{ return std::accumulate( this->begin(), this->end(), (T) 0 ); }
  template< class T > inline double Vector<T>::Mod( void ) const{ return std::sqrt( this->Mod2() ); }
  template< class T > inline double Vector<T>::Mod2( void ) const{ return this->Dot(*this); }
  template< class T > inline T Vector<T>::Dot( const Vector<T>& V ) const{ return ( (*this) * V ).Sum(); }
  template< class T > inline void Vector<T>::Reserve( unsigned int N ){ this->reserve(N); }
  template< class T > inline void Vector<T>::Append( T value ){ this->push_back( value ); }
  template< class T > inline void Vector<T>::Insert( int index, T value ){ this->insert( this->begin() + _TrueIndex(index), value ); }
  template< class T > inline void Vector<T>::Erase( int index ){ this->erase( this->begin() + _TrueIndex(index) ); }
  template< class T > inline void Vector<T>::Swap( int index0, int index1 ){ std::swap( (*this)[index0], (*this)[index1] ); }
  //template< class T > inline Vector<T> Vector<T>::Dot( const Matrix<T>& M ) const{ Vector W; for ( int i=0; i<this->Size(); i++ ) W.Append( this->Dot( M.Column(i) ) ); return W;}
  template< class T > void Vector<T>::Remove( T value ) { auto it = std::find( this->begin(), this->end(), value );if ( it != this->end() ){this->erase( it - this->begin() );return;} std::cerr << "Warning (glib::Vector<T>::Remove): value " << value << " has not been found. Removal not performed." << std::endl;}

  template<class T> bool glib::Vector<T>::StepAssertion    = true;
  template<class T> bool glib::Vector<T>::RangeAssertion    = true;
  template<class T> bool glib::Vector<T>::DivisionAssertion = true;

} // namespace glib

template< class T > std::ostream& operator <<( std::ostream& os, const glib::Vector<T>& V )
{
  for ( const T& v : V )
    os << v << " ";
  return os;
}
template< class T > std::ostream& operator <<( std::ostream& os, const glib::Vector<T>* V )
{
  os << *V;
  return os;
}


#endif // __GVECTOR__
