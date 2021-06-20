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

// Quick Sort
using Comparor = std::function<int( int, int )>;

int partition( int* arr, int l, int r, const Comparor& comp )
{
	int p = arr[r];
	int i = l - 1;
	for ( int j = l; j < r; j++ )
	{
		if ( comp( arr[j], p ) == 1 )
		{
			++i;
			swap( arr + i, arr + j );
		}
	}
	swap( arr + ( i + 1 ), arr + r );
	return i + 1;
}

void sort( int* arr, int l, int r, const Comparor& comp )
{
	if ( l < r )
	{
		int p = partition( arr, l, r, comp );
		sort( arr, l, p - 1, comp );
		sort( arr, p + 1, r, comp );
	}
}

// Priority Queue
template <typename T>
class PriorityQueue
{
public:
	using Comp = std::function<bool( T&, T& )>;
	explicit PriorityQueue( Comp comp ) : comp( std::move( comp ) ), head( nullptr ) {}
	T pop()
	{
		T min = head->data;
		PQNode *left = head->left, *right = head->right;
		delete head;
		if ( left )
			left->parent = nullptr;
		if ( right )
			right->parent = nullptr;
		head = merge( left, right );
		return min;
	}
	void push( T data )
	{
		auto* newNode = new PQNode( data );
		head = merge( head, newNode );
	}

private:
	Comp comp;
	struct PQNode
	{
		T data;
		int npl;
		PQNode *left, *right, *parent;
		explicit PQNode( T data )
			: data( std::move( data ) ), npl( 1 ), left( nullptr ), right( nullptr ), parent( nullptr )
		{
		}
	} * head;
	PQNode* merge( PQNode* a, PQNode* b )
	{
		if ( a == nullptr )
			return b;
		if ( b == nullptr )
			return a;
		if ( comp( b->data, a->data ) )
			swap( &a, &b );
		( a->right = merge( a->right, b ) )->parent = a;
		if ( !a->left || a->left->npl < a->right->npl )
			swap( &a->left, &a->right );
		a->npl = a->right ? 1 + a->right->npl : 1;
		return a;
	}
};

// Hashmap

template <typename T>
class Hashmap
{
public:
	using HashFunction = std::function<int( T& )>;
	explicit Hashmap( HashFunction hash ) : hash( std::move( hash ) ) {}
	void insert( T data )
	{
		fraction = 1;
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
		fraction = 1;
		for ( int i = hash( data ) % capacity; filled[i]; nextIndex( i ) )
		{
			if ( data == buckets[i] )
			{
				return true;
			}
		}
		return false;
	}

private:
	static const int capacity = 8000003; // 2 * MAXK
	HashFunction hash;
	int fraction;
	T buckets[capacity];
	bool filled[capacity];
	void nextIndex( int& i )
	{
		i = ( i + 2 * fraction + 1 ) % capacity;
		++fraction;
	}
};

// Storage
int a[MAXN], b[MAXN], c[MAXN];
using Data = std::tuple<int, int, int>;
bool dataComp( Data& x, Data& y )
{
	return compare( a[std::get<0>( x )], b[std::get<1>( x )], c[std::get<2>( x )], a[std::get<0>( y )],
					b[std::get<1>( y )], c[std::get<2>( y )] ) == 1;
}
PriorityQueue<Data> pq( dataComp );
int dataHash( Data& x ) { return 43 * ( 43 * ( 43 * std::get<0>( x ) + std::get<1>( x ) ) + std::get<2>( x ) ); }
Hashmap<Data> hm( dataHash );

// get_kth
void get_kth( int n, int k, int* x, int* y, int* z )
{
	for ( int i = 1; i <= n; i++ )
	{
		a[i] = b[i] = c[i] = i;
	}
	sort( a, 1, n, []( int a, int b ) { return compare( a, 1, 1, b, 1, 1 ); } );
	sort( b, 1, n, []( int a, int b ) { return compare( 1, a, 1, 1, b, 1 ); } );
	sort( c, 1, n, []( int a, int b ) { return compare( 1, 1, a, 1, 1, b ); } );

	Data ans;
	pq.push( { 1, 1, 1 } );
	for ( int i = 0; i < k; i++ )
	{
		do
		{
			ans = pq.pop();
		} while ( hm.search( ans ) );
		hm.insert( ans );
		int u = std::get<0>( ans ), v = std::get<1>( ans ), w = std::get<2>( ans );
#define PUSH( X, Y, Z )               \
	if ( X <= n && Y <= n && Z <= n ) \
	{                                 \
		pq.push( { X, Y, Z } );       \
	}
		PUSH( u + 1, v, w );
		PUSH( u, v + 1, w );
		PUSH( u, v, w + 1 );
#undef PUSH
	}

	*x = a[std::get<0>( ans )], *y = b[std::get<1>( ans )], *z = c[std::get<2>( ans )];
}