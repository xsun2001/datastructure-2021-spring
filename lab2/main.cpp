#include "djb2-hash.h"
#include "overflow-region.h"
#include "quadratic-probing.h"

#include <cstdio>
#include <sstream>

template <typename NumberType>
bool parseNumber( char* str, NumberType& res )
{
	static std::stringstream ss;
	ss.clear();
	ss << str;
	ss >> res;
	return !ss.fail();
}

int main( int argc, char** argv )
{
	int type, data, hash_type, collision_type;
	char buffer[1000];
	if ( argc < 3 )
	{
		hash_type = collision_type = 0;
	}
	else
	{
		parseNumber( argv[1], hash_type );
		parseNumber( argv[2], collision_type );
	}

	hashing_strategy* hash;
	collision_strategy* collision;
	if ( hash_type == 1 )
	{
		hash = new djb2_ascii_hashing_strategy();
	}
	else if ( hash_type == 2 )
	{
		hash = new djb2_utf8_hashing_strategy();
	}
	else
	{
		hash = new naive_hashing();
	}
	if ( collision_type == 1 )
	{
		collision = new quadratic_probing();
	}
	else if ( collision_type == 2 )
	{
		collision = new overflow_region();
	}
	else
	{
		collision = new linear_probe();
	}

	hashtable table( 2000, hash, collision );
	while ( true )
	{
		scanf( "%d", &type );
		if ( type == 0 )
		{
			scanf( "%s", buffer );
			scanf( "%d", &data );
			table.insert( hash_entry( buffer, data ) );
		}
		else if ( type == 1 )
		{
			scanf( "%s", buffer );
			printf( "%d\n", table.query( buffer ) );
		}
		else
			break;
	}
	return 0;
}