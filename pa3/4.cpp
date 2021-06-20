#include <cstdio>
#include <functional>
#define MAXN 1000005

template <typename T>
void swap( T* a, T* b )
{
	T t = *a;
	*a = *b;
	*b = t;
}

// Union Find

class UnionFind
{
public:
	explicit UnionFind( int size ) : group( new int[size + 1] ), rank( new int[size + 1] )
	{
		for ( int i = 0; i <= size; i++ )
		{
			group[i] = i;
			rank[i] = 0;
		}
	}
	void Union( int a, int b )
	{
		if ( rank[a] < rank[b] )
		{
			group[a] = b;
		}
		else if ( rank[a] > rank[b] )
		{
			group[b] = a;
		}
		else
		{
			group[b] = a;
			rank[a]++;
		}
	}
	int Find( int a )
	{
		if ( group[a] != a )
		{
			group[a] = Find( group[a] );
		}
		return group[a];
	}

private:
	int *group, *rank;
};

// Left Heap

struct PQNode
{
	int data, npl, size;
	PQNode *left, *right, *parent;
	explicit PQNode( int data )
		: data( data ), npl( 1 ), size( 1 ), left( nullptr ), right( nullptr ), parent( nullptr )
	{
	}
};

int heapSize( PQNode* heap ) { return heap == nullptr ? 0 : heap->size; }

PQNode* merge( PQNode* a, PQNode* b )
{
	if ( a == nullptr )
		return b;
	if ( b == nullptr )
		return a;
	if ( a->data > b->data )
		swap( &a, &b );
	( a->right = merge( a->right, b ) )->parent = a;
	if ( !a->left || a->left->npl < a->right->npl )
		swap( &a->left, &a->right );
	a->npl = a->right ? 1 + a->right->npl : 1;
	a->size = 1 + heapSize( a->left ) + heapSize( a->right );
	return a;
}

int pop( PQNode*& head )
{
	int min = head->data;
	PQNode *left = head->left, *right = head->right;
	delete head;
	if ( left )
		left->parent = nullptr;
	if ( right )
		right->parent = nullptr;
	head = merge( left, right );
	return min;
}

void push( PQNode*& head, int data )
{
	auto* newNode = new PQNode( data );
	head = merge( head, newNode );
}

// Storage

int n, m, k, q, a, u, v, op;
PQNode* heaps[MAXN];

// Main

void connect( UnionFind& uf, int x, int y )
{
	int xGroup = uf.Find( x ), yGroup = uf.Find( y );
	if ( xGroup == yGroup )
		return;
	uf.Union( xGroup, yGroup );
	int newGroup = uf.Find( x );
	heaps[newGroup] = merge( heaps[xGroup], heaps[yGroup] );
	while ( heapSize( heaps[newGroup] ) > k )
	{
		pop( heaps[newGroup] );
	}
}

int main()
{
	scanf( "%d%d%d%d", &n, &m, &k, &q );
	UnionFind uf( n );
	for ( int i = 1; i <= n; i++ )
	{
		scanf( "%d", &a );
		heaps[i] = new PQNode( a );
	}
	for ( int i = 0; i < m; i++ )
	{
		scanf( "%d%d", &u, &v );
		connect( uf, u, v );
	}
	for ( int i = 0; i < q; i++ )
	{
		scanf( "%d", &op );
		if ( op == 1 )
		{
			scanf( "%d%d", &u, &v );
			connect( uf, u, v );
		}
		else if ( op == 2 )
		{
			scanf( "%d", &u );
			PQNode* heap = heaps[uf.Find( u )];
			printf( "%d\n", heapSize( heap ) == k ? heap->data : -1 );
		}
	}
}