#pragma once

class BinarySearchTree
{
public:
	virtual void insert( int element ) = 0;
	virtual void remove( int element ) = 0;
	virtual bool find( int element, int& found ) = 0;
	virtual void print() = 0;
};

template <typename T>
T max( T t1, T t2 )
{
	return t1 > t2 ? t1 : t2;
}