#include <cstdint>
#include <cstdio>
#define MAXN 500005

// Prefix Tree (Trie)

class Trie
{
public:
	void insert( uint64_t x, int xk )
	{
		int node = 0;
		for ( int digit = 63; digit >= 0; digit-- )
		{
			int k = ( x & ( 1ULL << digit ) ) == 0 ? 0 : 1;
			if ( nxt[node][k] == 0 )
				nxt[node][k] = ++size;
			node = nxt[node][k];
		}
		insert_key( node, xk );
	}
	int query( uint64_t x )
	{
		int node = 0;
		for ( int digit = 63; digit >= 0; digit-- )
		{
			int k = ( x & ( 1ULL << digit ) ) == 0 ? 1 : 0;
			if ( nxt[node][k] == 0 )
				k = k == 0 ? 1 : 0;
			node = nxt[node][k];
		}
		return front_key( node );
	}
	void remove( uint64_t x, int node = 0, int digit = 63 )
	{
		if ( digit >= 0 )
		{
			int k = ( x & ( 1ULL << digit ) ) == 0 ? 0 : 1;
			int nl = nxt[node][k];
			remove( x, nl, digit - 1 );
			if ( nxt[nl][0] == 0 && nxt[nl][1] == 0 )
				nxt[node][k] = 0;
		}
		else
		{
			pop_key( node );
		}
	}

private:
	int nxt[MAXN * 50][2], size;
	int key_head[MAXN * 50], key_tail[MAXN * 50], keys[MAXN], key_next[MAXN], list_cnt;
	void insert_key( int node, int key )
	{
		if ( key_tail[node] == 0 )
		{
			key_head[node] = key_tail[node] = ++list_cnt;
		}
		else
		{
			key_tail[node] = key_next[key_tail[node]] = ++list_cnt;
		}
		keys[list_cnt] = key;
	}
	int front_key( int node ) { return keys[key_head[node]]; }
	void pop_key( int node ) { key_head[node] = key_next[key_head[node]]; }
};

Trie trie;
int n, k, p, q;
uint64_t a[MAXN];

uint64_t readUint64()
{
	int c = getchar();
	while ( c != '0' && c != '1' )
		c = getchar();
	uint64_t ans = 0ULL;
	for ( int i = 0; i < 64; i++ )
		ans = ( ans << 1 ) | ( c - '0' ), c = getchar();
	return ans;
}

int main()
{
	scanf( "%d%d", &n, &k );
	for ( int i = 0; i < n; i++ )
		a[i] = readUint64();
	for ( int i = 0; i < n; i++ )
	{
		while ( q - i <= k + 1 && q < n )
		{
			trie.insert( a[q], q );
			++q;
		}
		while ( i - p > k + 1 )
		{
			trie.remove( a[p] );
			++p;
		}
		printf( "%d\n", trie.query( a[i] ) );
	}
}