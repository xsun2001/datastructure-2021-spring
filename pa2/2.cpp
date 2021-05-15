#include <cmath>
#include <cstdio>
#include <cstdlib>
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
	void unset( int idx ) { data[idx >> 6] &= ~( 1ULL << ( idx & 0x3F ) ); }
	void load()
	{
		char c;
		for ( ;; )
		{
			c = getchar();
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
	void print()
	{
		printf( "Length: %d %d %d\n", len, len1, len2 );
		for ( int i = 0; i <= len1 - 1; i++ )
		{
			printf( "%d: ", i );
			for ( int j = 63; j >= 0; j-- )
			{
				putchar( ( data[i] & ( 1ULL < j ) ) ? '1' : '0' );
			}
			putchar( '\n' );
		}
	}
} input, contains;

int digitalCount( unsigned int x ) { return x == 0 ? 1 : 1 + floor( log2( x ) ); }

void binaryPrint( unsigned int x, unsigned int len )
{
	for ( int i = len - 1; i >= 0; i-- )
	{
		putchar( ( x & ( 1 << i ) ) == 0 ? '0' : '1' );
	}
}

static const unsigned int WINDOW[] = {
	0x0,	0x1,	0x3,	0x7,	0xF,	 0x1F,	  0x3F,	   0x7F,	0xFF,	  0x1FF,	0x3FF,	  0x7FF,   0xFFF,
	0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF, 0x1FFFF, 0x3FFFF, 0x7FFFF, 0xFFFFF, 0x1FFFFF, 0x3FFFFF, 0x7FFFFF, 0xFFFFFF };

inline unsigned int reverseBits( unsigned int num )
{
	unsigned int count = sizeof( num ) * 8 - 1;
	unsigned int reverse_num = num;

	num >>= 1;
	while ( num )
	{
		reverse_num <<= 1;
		reverse_num |= num & 1;
		num >>= 1;
		count--;
	}
	reverse_num <<= count;
	return reverse_num;
}

int main()
{
	input.load();
	// printf( "%d\n", input.length() );
	// for ( int i = 0; i < input.length(); i++ )
	// {
	// 	printf( "%d", input[i] );
	// }
	// printf( "\n" );
	// printf( "Loaded\n" );
	for ( unsigned int len = 1; len <= 24; len++ )
	{
		unsigned int x = 0, i = 0, remaining = 1 << len;
		contains.clear();
		unsigned int idx1 = 0, idx2 = 0, buf;
		
		

		for ( ; i < len - 1; i++ )
		{
			x = ( ( x << 1 ) | input[i] );
		}
		for ( ; i < input.length() && remaining; i++ )
		{
			x = ( ( ( x << 1 ) | input[i] ) & ( ~( 1 << len ) ) );
			if ( contains[x] == 0 )
			{
				// binaryPrint( x, len );
				// putchar( '\n' );
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
				putchar( '\n' );
				return 0;
			}
			// binaryPrint( i, len );
			// printf( ": %s\n", contains[i] ? "true" : "false" );
		}
	}
}