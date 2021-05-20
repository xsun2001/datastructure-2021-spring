#include "djb2-hash.h"

int AsciiString::next()
{
	int c = data[current_index];
	++current_index;
	return c;
}

int Utf8String::next()
{
	int c1 = data[current_index];
	if ( ( c1 & 0b10000000 ) == 0 )
	{
		current_index += 1;
		return c1;
	}
	else
	{
		int c2 = data[current_index + 1];
		if ( ( c1 >> 5 ) == 0b110 && ( c2 >> 6 ) == 0b10 )
		{
			current_index += 2;
			return ( ( c1 & 0b11111 ) << 6 ) | ( c2 & 0b111111 );
		}
		else
		{
			int c3 = data[current_index + 1];
			if ( ( c1 >> 4 ) == 0b1110 && ( c2 >> 6 ) == 0b10 && ( c3 >> 6 ) == 0b10 )
			{
				current_index += 3;
				return ( ( ( ( c1 & 0b1111 ) << 6 ) | ( c2 & 0b111111 ) ) << 6 ) | ( c3 & 0b111111 );
			}
		}
	}
	return 0;
}

unsigned long djb2_hash( String& str )
{
	unsigned long hash = 5381;
	int c;

	while ( ( c = str.next() ) )
		hash = ( ( hash << 5 ) + hash ) + c; /* hash * 33 + c */

	return hash;
}

int djb2_ascii_hashing_strategy::operator()( char* str, int N )
{
	AsciiString string( str );
	return (int) ( djb2_hash( string ) % (unsigned long) N );
}

int djb2_utf8_hashing_strategy::operator()( char* str, int N )
{
	Utf8String string( str );
	return (int) ( djb2_hash( string ) % (unsigned long) N );
}
