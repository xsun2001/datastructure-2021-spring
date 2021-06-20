#include "kth.h"
#include <cstdio>
#include <functional>
#include <utility>
#define MAXN 500005

template <typename T>
void swap( T* a, T* b )
{
	T t = *a;
	*a = *b;
	*b = t;
}

// Storage
int a[MAXN], b[MAXN], c[MAXN];
struct Data
{
	int ai, bi, ci, av, bv, cv;
};
bool operator==( Data& x, Data& y ) { return x.ai == y.ai && x.bi == y.bi && x.ci == y.ci; }

// Quick Sort

int partition( int* arr, int l, int r, bool ( *lt )( int, int ) )
{
	int p = arr[r];
	int i = l - 1;
	for ( int j = l; j < r; j++ )
	{
		if ( lt( arr[j], p ) == 1 )
		{
			++i;
			swap( arr + i, arr + j );
		}
	}
	swap( arr + ( i + 1 ), arr + r );
	return i + 1;
}

void sort( int* arr, int l, int r, bool ( *lt )( int, int ) )
{
	if ( l < r )
	{
		int p = partition( arr, l, r, lt );
		sort( arr, l, p - 1, lt );
		sort( arr, p + 1, r, lt );
	}
}

// Priority Queue
template <typename T>
class PriorityQueue
{
public:
	explicit PriorityQueue( bool ( *comp )( T&, T& ) ) : comp( std::move( comp ) ), size( 0 ) {}
	T pop()
	{
		T min = heap[1];
		swap( &heap[1], &heap[size] );
		--size;
		percolateDown( 1 );
		return min;
	}
	void push( T data )
	{
		heap[++size] = data;
		percolateUp( size );
	}

private:
	bool ( *comp )( T&, T& );
	T heap[4000003];
	int size;
	void percolateUp( int idx )
	{
		for ( int p = idx >> 1; p > 0 && comp( heap[idx], heap[p] ); idx = p, p >>= 1 )
		{
			swap( &heap[idx], &heap[p] );
		}
	}
	int properParent( int i )
	{
		int j = i << 1, k = j | 1;
		if ( j > size )
			return i;
		int r = k > size || comp( heap[j], heap[k] ) ? j : k;
		r = r > size || comp( heap[i], heap[r] ) ? i : r;
		return r;
	}
	void percolateDown( int idx )
	{
		for ( int p = properParent( idx ); p != idx; idx = p, p = properParent( p ) )
		{
			swap( &heap[idx], &heap[p] );
		}
	}
};

// Hashmap
template <typename T>
class Hashmap
{
public:
	explicit Hashmap( unsigned long ( *hash )( T& ) ) : hash( hash ) {}
	void insert( T data )
	{
		fraction = 0;
		for ( int i = hash( data ) % capacity;; nextIndex( i ) )
		{
			if ( !filled[i] )
			{
				buckets[i] = data;
				filled[i] = true;
				return;
			}
		}
	}
	bool search( T data )
	{
		fraction = 0;
		for ( int i = hash( data ) % capacity; filled[i]; nextIndex( i ) )
			if ( data == buckets[i] )
				return true;
		return false;
	}

private:
	static const int capacity = 5000003; // 2 * MAXK
	unsigned long ( *hash )( T& );
	int fraction;
	T buckets[capacity];
	bool filled[capacity];
	void nextIndex( int& i )
	{
		i = ( i + 2 * fraction + 1 ) % capacity;
		++fraction;
	}
};

bool compA( int x, int y ) { return compare( x, 1, 1, y, 1, 1 ) == 1; }
bool compB( int x, int y ) { return compare( 1, x, 1, 1, y, 1 ) == 1; }
bool compC( int x, int y ) { return compare( 1, 1, x, 1, 1, y ) == 1; }
bool dataComp( Data& x, Data& y ) { return compare( x.av, x.bv, x.cv, y.av, y.bv, y.cv ) == 1; }
PriorityQueue<Data> pq( dataComp );
unsigned long dataHash( Data& x ) { return 43 * ( 43 * ( 43 * x.ai + x.bi ) + x.ci ); }
Hashmap<Data> hm( dataHash );

// get_kth
void get_kth( int n, int k, int* x, int* y, int* z )
{
	for ( int i = 1; i <= n; i++ )
	{
		a[i] = b[i] = c[i] = i;
	}
	sort( a, 1, n, compA );
	sort( b, 1, n, compB );
	sort( c, 1, n, compC );

	Data ans = { 1, 1, 1, a[1], b[1], c[1] }, temp;
	pq.push( ans );
	for ( int i = 0; i < k; i++ )
	{
		do
		{
			ans = pq.pop();
		} while ( hm.search( ans ) );
		hm.insert( ans );
		int u = ans.ai, v = ans.bi, w = ans.ci;
#define PUSH( X, Y, Z )                           \
	if ( X <= n && Y <= n && Z <= n )             \
	{                                             \
		pq.push( { X, Y, Z, a[X], b[Y], c[Z] } ); \
	}
		PUSH( u + 1, v, w );
		PUSH( u, v + 1, w );
		PUSH( u, v, w + 1 );
#undef PUSH
	}

	*x = a[ans.ai], *y = b[ans.bi], *z = c[ans.ci];
}