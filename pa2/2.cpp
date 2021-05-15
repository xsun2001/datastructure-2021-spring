#include <cstdio>
#include <cstring>

const int BITMAP_COUNT = 300000;
struct BitMap
{
	unsigned long long data[BITMAP_COUNT];
	unsigned int len1 = 0, len2 = 0, len = 0;
	BitMap() { memset( data, 0, sizeof( data ) ); }
	void clear() { memset( data, 0, sizeof( data ) ); }
	int length() { return len; }
	int operator[]( int idx ) { return ( data[idx >> 6] & ( 1ULL << ( idx & 0x3F ) ) ) ? 1 : 0; }
	void set( int idx ) { data[idx >> 6] |= ( 1ULL << ( idx & 0x3F ) ); }
	void load()
	{
		char c;
		for ( ;; )
		{
			c = getchar_unlocked();
			if ( c != '0' && c != '1' )
			{
				return;
			}
			if ( len2 == 64 )
			{
				++len1;
				len2 = 0;
			}
			if ( c == '1' )
			{
				data[len1] |= ( 1ULL << len2 );
			}
			++len2;
			++len;
		}
	}
} input, contains;

void binaryPrint( unsigned int x, unsigned int len )
{
	for ( int i = len - 1; i >= 0; i-- )
	{
		putchar_unlocked( ( x & ( 1 << i ) ) == 0 ? '0' : '1' );
	}
}

int main()
{
	input.load();
	for ( unsigned int len = 1; len <= 24; len++ )
	{
		unsigned int x = 0, i = 0, remaining = 1 << len;
		contains.clear();

		for ( ; i < len - 1; i++ )
		{
			x = ( ( x << 1 ) | input[i] );
		}
		for ( ; i < input.length() && remaining; i++ )
		{
			x = ( ( ( x << 1 ) | input[i] ) & ( ~( 1 << len ) ) );
			if ( contains[x] == 0 )
			{
				contains.set( x );
				--remaining;
			}
		}
		if ( remaining == 0 )
		{
			continue;
		}
		for ( i = 0; i < ( 1 << len ); i++ )
		{
			if ( contains[i] == 0 )
			{
				binaryPrint( i, len );
				putchar_unlocked( '\n' );
				return 0;
			}
		}
	}
}