/*
 *
 *    Array module. Contains definitions of array-like objects such as vectors
 *    and matrices.
 *
 *
 *    @ Author: Gonzalo Martínez Lema
 *    @ Date: 22/07/2015
 *
 *
 *
 */

#include "Vector.h"

template< class T >
glib::Vector<T>::Vector( T values[], int size ) : std::vector<T>( values, values + size )
{}

template< class T >
glib::Vector<T> glib::Vector<T>::Concatenate( const glib::Vector<T>& V ) const
{
  glib::Vector<T> W(*this);
  for (int i=0; i<V.size(); i++) W.push_back( V[i] );
  return W;
}

template< class T >
void glib::Vector<T>::Remove( T value )
{
  for( int i = this->Last(); i>=0; i-- )
    if ( (*this)[i] == value )
      this->erase(i);
}

template< class T >
std::ostream& operator <<( std::ostream& os, const glib::Vector<T>& V )
{
  for ( int i=0; i<V.size(); i++ )
    os << i << " -> " << V[i] << std::endl;
  return os;
}

template< class T >
std::ostream& operator <<( std::ostream& os, const glib::Vector<T>* V )
{
  return os << (*V);
}
