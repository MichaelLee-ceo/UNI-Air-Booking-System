#ifndef VEC_ITERATOR_H
#define VEC_ITERATOR_H

using namespace std;

// VecIterator class template definition
template< typename T >
class VecIterator
{
   template< typename T > friend class vector;
public:
   VecIterator( T *p = nullptr ) // default constructor
      : ptr( p )
   {
   }

   VecIterator( const VecIterator &iteratorToCopy ) // copy constructor
      : ptr( iteratorToCopy.ptr )
   {
   }

   ~VecIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const VecIterator& operator=( const VecIterator &right )
   {
      if( &right != this ) // avoid self-assignment
         ptr = right.ptr;
      return *this; // enables x = y = z, for example
   }

   bool operator==( const VecIterator &right ) const // equal to
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VecIterator &right ) const // not equal to
   {
      return ptr != right.ptr;
   }

   T& operator*() const // dereferencing operator
   {
      return *ptr;
   }

   T* operator->() const
   {
      return ptr;
   }

   VecIterator& operator++() // prefix increment operator
   {
      ++ptr;
      return *this;
   }

   VecIterator& operator--() // predecrement an iterator
   {
      --ptr;
      return *this;
   }

private:
   T *ptr; // keep a pointer to vector
}; // end class template VecIterator

#endif


#ifndef VECTOR_H
#define VECTOR_H

// vector class template definition
template< typename T >
class vector
{
public:
   using iterator = VecIterator< T >;

   vector( unsigned int n = 0 ); // Constructor; Constructs a zero vector with size n

   // Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
   vector( const vector &x );

   ~vector(); // Destroys the vector.

   const vector& operator=( const vector &x ); // assignment operator

   // Returns a pointer pointing to the first element in the vector.
   // If the vector is empty, the returned pointer shall not be dereferenced.
   iterator begin() const;

   // Returns an pointer pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end() const;

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   unsigned int size() const;

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   unsigned int capacity() const;

   // Resizes the vector so that it contains n elements.
   // If n is smaller than the current vector size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current vector size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current vector capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( unsigned int n );

   // subscript operator for non-const objects returns modifiable lvalue
   T &operator[]( unsigned int );

   // subscript operator for const objects returns rvalue
   T operator[]( unsigned int ) const;

   // Adds a new element at the end of the vector,
   // after its current last element.
   // The content of val is copied to the new element.
   // This effectively increases the vector size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const T val );

   // Removes from the vector a single element.   
   // This effectively reduces the container size by one.   
   // Relocates all the elements after the element erased to their new positions.
   iterator erase( iterator position );

private:
   T *myFirst;
   T *myLast;
   T *myEnd;
}; // end class template vector


// constructor; constructs a zero vector with size n
template< typename T >
vector< T >::vector( unsigned int n )
   : myFirst( n == 0 ? nullptr : new T[ n ]() ),
      myLast( n == 0 ? nullptr : myFirst + n ),
       myEnd( n == 0 ? nullptr : myLast )
{
} // end vector default constructor

// copy constructor; constructs a vector with a copy of each of the elements in vectorToCopy
template< typename T >
vector< T >::vector( const vector< T > &x )
{
	myFirst = new T[x.capacity()]();
	for (int i = 0; i < x.size(); i++)
		myFirst[i] = x.myFirst[i];

	myLast = myFirst + x.size();
	myEnd = myFirst + x.capacity();
} // end vector copy constructor

// destructor; destroys the vector
template< typename T >
vector< T >::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
} // end destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const vector< T >& vector< T >::operator=( const vector< T > &x )
{
   if( &x != this ) // avoid self-assignment
   {
	   if (myFirst != nullptr)
		   delete[] myFirst;

	   myFirst = new T[x.capacity()]();
	   for (int i = 0; i < x.size(); i++)
		   myFirst[i] = x.myFirst[i];

	   myLast = myFirst + x.size();
	   myEnd = myFirst + x.capacity();
   } // end outer if

   return *this; // enables x = y = z, for example
} // end function operator=

template< typename T >
typename vector< T >::iterator vector< T >::begin() const
{
   return iterator( myFirst );
}

template< typename T >
typename vector< T >::iterator vector< T >::end() const
{
   return iterator( myLast );
}

template< typename T >
unsigned int vector< T >::size() const
{
   return ( myLast - myFirst );
}

template< typename T >
unsigned int vector< T >::capacity() const
{
   return ( myEnd - myFirst );
}

// Resizes the vector container so that it contains n elements.
template< typename T >
void vector< T >::resize( unsigned int n )
{
	int newCap;
	if (n > capacity())
	{
		if (capacity() < 2)
			newCap = capacity() + 1;
		else
			newCap = capacity() * 1.5;
	}
	else
		newCap = capacity();

	T *buffer = new T[newCap]();
	for (int i = 0; i < size(); i++)
		buffer[i] = myFirst[i];

	if (myFirst != nullptr)
		delete[] myFirst;

	myFirst = buffer;
	myLast = myFirst + n;
	myEnd = myFirst + newCap;
}

// overloaded subscript operator for non-const Arrays;
// reference return creates a modifiable lvalue
template< typename T >
T &vector< T >::operator[]( unsigned int subscript )
{
	return myFirst[subscript];
} // end function operator[]

// overloaded subscript operator for const Arrays
// const reference return creates an rvalue
template< typename T >
T vector< T >::operator[]( unsigned int subscript ) const
{
	return myFirst[subscript];
} // end function operator[]

template< typename T >
void vector< T >::push_back( const T val )
{
	int newSize = size() + 1;
	int newCap;
	if (size() == capacity())
	{
		if (capacity() < 2)
			newCap = capacity() + 1;
		else
			newCap = capacity() * 1.5;
	}
	else
		newCap = capacity();

	T *buffer = new T[newCap]();

	for (int i = 0; i < size(); i++)
		buffer[i] = myFirst[i];

	buffer[size()] = val;

	if (myFirst != nullptr)
		delete[] myFirst;

	myFirst = buffer;
	myLast = myFirst + newSize;
	myEnd = myFirst + newCap;
}

template< typename T >
typename vector< T >::iterator vector< T >::erase( iterator position )
{
	iterator f = position;
	for (++f; f != end(); ++f, ++position)
		*position = *f;

	--myLast;
	return begin();
}

#endif