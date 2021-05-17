#include <cstdio>
#include <functional>
#define L( X ) ( ( X ) << 1 )
#define R( X ) ( ( ( X ) << 1 ) | 1 )
#define P( X ) ( ( X ) >> 1 )
#define MAXN 100005
#define MAXM 100005

#ifdef DEBUG
#define TRACE( ... ) printf( __VA_ARGS__ )
#else
#define TRACE( ... )
#endif

template <typename T>
struct LLNode
{
	T data;
	LLNode* nxt;
	explicit LLNode( T data ) : data( data ), nxt( nullptr ) {}
};

template <typename T>
class LinkedList
{
private:
	LLNode<T>* head;
	int size;

public:
	LinkedList() : head( nullptr ), size( 0 ) {}
	void insert( LLNode<T>* node )
	{
		if ( size == 0 )
		{
			head = node;
		}
		else if ( head->data > node->data )
		{
			node->nxt = head;
			head = node;
		}
		else
		{
			auto n = head;
			while ( n->nxt != nullptr && n->nxt->data < node->data )
			{
				n = n->nxt;
			}
			node->nxt = n->nxt;
			n->nxt = node;
		}
		++size;
	};
	void insert( T t ) { insert( new LLNode<T>( t ) ); }
	void insert( LinkedList& list )
	{
		if ( &list == this )
		{
			return;
		}
		auto node = list.head;
		while ( node )
		{
			auto nxt = node->nxt;
			insert( nxt );
			node = nxt;
		}
	}
	void for_each( std::function<void( T, int )> op )
	{
		auto node = head;
		for ( int i = 0; i < size; i++ )
		{
			op( node->data, i );
			node = node->nxt;
		}
	}
	int getSize() { return size; }
};

using ull = unsigned long long;
ull value[MAXN], length[MAXN], mask[MAXN];
LinkedList<int> ops[MAXN];
int points[2 * MAXM], ql[MAXM], qr[MAXM];
char qop[MAXM][6];
int n, m, plength;

template <typename T>
void swap( T* a, T* b )
{
	T t = *a;
	*a = *b;
	*b = t;
}

void unique()
{
	plength = 0;
	for ( int i = 0; i < 2 * m; i++ )
	{
		if ( points[i] != points[plength] )
		{
			++plength;
			points[plength] = points[i];
		}
	}
}

// Quick Sort: https://www.geeksforgeeks.org/quick-sort/
int partition( int l, int r )
{
	int p = points[r];
	int i = l - 1;
	for ( int j = l; j < r; j++ )
	{
		if ( points[j] < p )
		{
			++i;
			swap( points + i, points + j );
		}
	}
	swap( points + ( i + 1 ), points + r );
	return i + 1;
}

void sort( int l, int r )
{
	if ( l < r )
	{
		int p = partition( l, r );
		sort( l, p - 1 );
		sort( p + 1, r );
	}
}

void sort() { sort( 0, 2 * n - 1 ); }

// Binary Search: https://www.geeksforgeeks.org/binary-search/
int find( int x, int l, int r )
{
	if ( l <= r )
	{
		int mid = l + ( ( r - l ) >> 1 );
		if ( points[mid] > x )
		{
			return find( x, l, mid - 1 );
		}
		else if ( points[mid] < x )
		{
			return find( x, mid + 1, r );
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int find( int x ) { return find( x, 0, plength ); }

// Segment Tree: https://oi-wiki.org/ds/seg/
void build( int l, int r, int idx )
{
	TRACE( "build(%d, %d, %d)\n", l, r, idx );
	if ( l == r )
	{
		length[idx] = l == plength ? 0 : points[l + 1] - points[l];
	}
	else
	{
		int mid = l + ( ( r - l ) >> 1 );
		build( l, mid, L( idx ) );
		build( mid + 1, r, R( idx ) );
		length[idx] = length[L( idx )] + length[R( idx )];
	}
	TRACE( "build => #%d (%d, %d) = %llu\n", idx, l, r, length[idx] );
}

void pushDown( int i )
{
	if ( mask[i] == 0 )
	{
		return;
	}

	int l = L( i );
	mask[l] += mask[i];
	value[l] += length[l] * mask[i];

	int r = R( i );
	mask[r] += mask[i];
	value[r] += length[r] * mask[i];

	mask[i] = 0ULL;
}

// left, right, range left, range right, index
ull query( int l, int r, int rl, int rr, int i )
{
	ull ans = 0ULL;
	if ( l <= rl && r >= rr )
	{
		ans = value[i];
	}
	else
	{
		int mid = rl + ( ( rr - rl ) >> 1 );
		if ( rl != rr )
		{
			pushDown( i );
		}
		if ( l <= mid )
		{
			ans += query( l, r, rl, mid, L( i ) );
		}
		if ( r > mid )
		{
			ans += query( l, r, mid + 1, rr, R( i ) );
		}
	}
	TRACE( "query(%d, %d, %d, %d, %d) = %llu\n", l, r, rl, rr, i, ans );
	return ans;
}

void flip( int l, int r, int rl, int rr, int i, int opidx )
{
	TRACE( "flip(%d, %d, %d, %d, %d)\n", l, r, rl, rr, i );
	if ( l <= rl && rr <= r )
	{
		++mask[i];
		value[i] += length[i];
	}
	else
	{
		int mid = rl + ( ( rr - rl ) >> 1 );
		if ( rl != rr )
		{
			pushDown( i );
		}
		if ( l <= mid )
		{
			flip( l, r, rl, mid, L( i ), opidx );
		}
		if ( r > mid )
		{
			flip( l, r, mid + 1, rr, R( i ), opidx );
		}
		value[i] = value[L( i )] + value[R( i )];
	}
}

int main()
{
	scanf( "%d%d", &n, &m );
	for ( int i = 0; i < n; i++ )
	{
		scanf( "%d%d", &ql[i], &qr[i] );
		points[i << 1] = ql[i];
		++qr[i];
		points[( i << 1 ) + 1] = qr[i];
	}
	sort();
	unique();
	build( 0, plength, 1 );
	for ( int i = 0; i < n; i++ )
	{
		int l = find( ql[i] ), r = find( qr[i] );
		flip( l, r - 1, 0, plength, 1, i + 1 );
	}
	for ( int i = 0; i < m; i++ )
	{
		int k;
		scanf( "%d", &k );
		printf( "%llu\n", query( l, r - 1, 0, plength, 1 ) );
	}
}