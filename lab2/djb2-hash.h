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
	int next() override;
};

struct Utf8String : public String
{
	explicit Utf8String( char* str ) : String( str ) {}
	int next() override;
};

struct djb2_ascii_hashing_strategy : public hashing_strategy
{
	int operator()( char* str, int N ) override;
};

struct djb2_utf8_hashing_strategy : public hashing_strategy
{
	int operator()( char* str, int N ) override;
};