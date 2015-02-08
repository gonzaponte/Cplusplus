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

template< class T >
class Vector
{
private:
    T* _values;
    int _size;
    
    int TrueIndex( int index );
    
public:
    Vector();
    Vector( T& values, int size   );
    Vector( T* values, int size   );
    Vector( T  value , int length );
    Vector( Vector  V );
    Vector( Vector* V );
    ~Vector();
    int Size();
    T* Values();
    T* Slice( int n0, int n1 );
    Vector* Copy();
    
    
    inline int TrueIndex( int index ){ if (index < 0) return _size + index; else return index; }
    inline int Size(){return _size;}
    inline T* Values(){return _values;}
    inline T* Slice( int n0, int n1){ int n = abs(n1-n0);T* slice = new T[n];for (int i=n0; i!=n1; i++) slice[i-n0] = _values[i];return slice;}
};

std::ostream& operator <<( std::ostream&, const Vector& );
std::ostream& operator <<( std::ostream&,       Vector& );
std::ostream& operator <<( std::ostream&, const Vector* );
std::ostream& operator <<( std::ostream&,       Vector* );

