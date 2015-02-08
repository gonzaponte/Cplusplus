/*
 *
 *    Array module. Contains definitions of array-like objects such as vectors
 *    and matrices.
 *
 *
 *    @ Author: Gonzalo Martínez Lema
 *    @ Date: 31/01/2015
 *
 *
 *
 */
#include "Array.h"

Vector::Vector()
{
    _values = 0;
    _size = 0;
}

Vector::Vector( T* values, int size )
{
    _values = new T[size];
    for (int i=0; i<size; i++) _values[i] = T(values[i]);
    _size = size;
}

Vector::Vector( T value, int size )
{
    _values = new int[size];
    _size = size;
}

Vector::Vector( Vector V )
{
    this = V.Copy()
}

Vector::Vector( Vector* V )
{
    this = V->Copy()
}

Vector::~Vector()
{
    delete _values;
    delete &_size;
}

T* GetValues();
T* GetSlice();
Vector* Copy();
};


template <class A_Type> A_Type calc<A_Type>::multiply(A_Type x,A_Type y)
{
    return x*y;
}