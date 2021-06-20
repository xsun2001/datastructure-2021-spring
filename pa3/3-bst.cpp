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

template <typename T>
T max( T a, T b )
{
	return a >= b ? a : b;
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

// BST (AVL Tree)

template <typename T>
class AvlTree
{
public:
	using Comp = std::function<bool( T&, T& )>;
	explicit AvlTree( Comp comp ) : comp( std::move( comp ) ) {}
	void insert( T element ) { insert( root, element ); }
	T popMin() { return popMin( root ); }

private:
	Comp comp;
	struct Node
	{
		T data;
		int height;
		Node *left, *right;
		explicit Node( T data ) : data( std::move( data ) ), left( nullptr ), right( nullptr ), height( 0 ) {}
	};
	Node* root = nullptr;
	// Single Rotation
	void rightRotate( Node*& n )
	{
		auto m = n->left;
		n->left = m->right;
		m->right = n;
		updateHeight( n );
		updateHeight( m );
		n = m;
	}
	void leftRotate( Node*& n )
	{
		auto m = n->right;
		n->right = m->left;
		m->left = n;
		updateHeight( n );
		updateHeight( m );
		n = m;
	}

	// Double Rotation
	void rightLeftRotate( Node*& n )
	{
		rightRotate( n->right );
		leftRotate( n );
	}
	void leftRightRotate( Node*& n )
	{
		leftRotate( n->left );
		rightRotate( n );
	}
	// Height Helper Functions
	int getHeight( Node* n ) { return n == nullptr ? -1 : n->height; }
	void updateHeight( Node* n ) { n->height = 1 + max( getHeight( n->left ), getHeight( n->right ) ); }
	// Balance
	void balance( Node*& n )
	{
		if ( n == nullptr )
		{
			return;
		}
		int heightDiff = getHeight( n->left ) - getHeight( n->right );
		if ( heightDiff > 1 )
		{
			if ( getHeight( n->left->left ) >= getHeight( n->left->right ) )
			{
				rightRotate( n );
			}
			else
			{
				leftRightRotate( n );
			}
		}
		else if ( heightDiff < -1 )
		{
			if ( getHeight( n->right->right ) >= getHeight( n->right->left ) )
			{
				leftRotate( n );
			}
			else
			{
				rightLeftRotate( n );
			}
		}
		updateHeight( n );
	}
	// Internal Functions
	void insert( Node*& n, T element )
	{
		if ( n == nullptr )
		{
			n = new Node( element );
			return;
		}
		else if ( n->data == element )
		{
			return;
		}
		else if ( comp( element, n->data ) )
		{
			insert( n->left, element );
		}
		else
		{
			insert( n->right, element );
		}
		balance( n );
	}
	T popMin( Node*& n )
	{
		if ( n->left == nullptr )
		{
			T data = n->data;
			Node* m = n;
			n = n->right;
			delete m;
			return data;
		}
		T data = popMin( n->left );
		balance( n );
		return data;
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
AvlTree<Data> pq( dataComp );

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
	pq.insert( { 1, 1, 1 } );
	for ( int i = 0; i < k; i++ )
	{
		ans = pq.popMin();
		int u = std::get<0>( ans ), v = std::get<1>( ans ), w = std::get<2>( ans );
#define PUSH( X, Y, Z )               \
	if ( X <= n && Y <= n && Z <= n ) \
	{                                 \
		pq.insert( { X, Y, Z } );     \
	}
		PUSH( u + 1, v, w );
		PUSH( u, v + 1, w );
		PUSH( u, v, w + 1 );
#undef PUSH
	}

	*x = a[std::get<0>( ans )], *y = b[std::get<1>( ans )], *z = c[std::get<2>( ans )];
}