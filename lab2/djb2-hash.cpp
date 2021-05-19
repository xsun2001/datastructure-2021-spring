#include "framework/hashtable.h"

struct String
{
	explicit String( char* str ) : data( nullptr ), current_index( 0 )
	{
		int len = strlen( str );
		data = new char[len];
		strcpy( data, str );
	}
	~String() { delete[] data; }
	virtual int next() = 0;

protected:
	int current_index;
	char* data;
};

struct AsciiString : public String
{
	explicit AsciiString( char* str ) : String( str ) {}
	int next() override
	{
		int c = data[current_index];
		++current_index;
		return c;
	}
};

struct Utf8String : public String
{
	explicit Utf8String( char* str ) : String( str ) {}
	int next() override
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
};

unsigned long djb2_hash( String& str )
{
	unsigned long hash = 5381;
	int c;

	while ( ( c = str.next() ) )
		hash = ( ( hash << 5 ) + hash ) + c; /* hash * 33 + c */

	return hash;
}

struct djb2_ascii_hashing_strategy : public hashing_strategy
{
	int operator()( char* str, int N ) override
	{
		AsciiString string( str );
		return (int) ( djb2_hash( string ) % (unsigned long) N );
	}
};

struct djb2_utf8_hashing_strategy : public hashing_strategy
{
	int operator()( char* str, int N ) override
	{
		Utf8String string( str );
		return (int) ( djb2_hash( string ) % (unsigned long) N );
	}
};