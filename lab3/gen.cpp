#include <random>
#include <set>
#include <string>

template <typename RandomType, typename RandomDist>
class RangedRandom
{
private:
	std::random_device rd;
	std::mt19937 gen;
	RandomDist dist;

public:
	RangedRandom( int a, int b ) : rd(), gen( rd() ), dist( a, b ) {}
	RandomType operator()() { return dist( gen ); }
};

using RandomInt = RangedRandom<int, std::uniform_int_distribution<>>;

std::set<int, std::greater<>> s;
FILE *input, *output;

bool newInsertion( int x )
{
	if ( s.find( x ) != s.end() )
	{
		return false;
	}
	s.insert( x );
	fprintf( input, "A %d\n", x );
	return true;
}

bool newRemove( int x )
{
	if ( s.find( x ) == s.end() )
	{
		return false;
	}
	s.erase( x );
	fprintf( input, "B %d\n", x );
	return true;
}

bool newQuery( int x )
{
	auto it = s.lower_bound( x );
	fprintf( input, "C %d\n", x );
	fprintf( output, "%d\n", it == s.end() ? -1 : *it );
	return true;
}

int toInt( const char* str )
{
	int x;
	sscanf( str, "%d", &x );
	return x;
}

int main( int argc, char** argv )
{
	int n = toInt( argv[1] ), mode = toInt( argv[2] ), maxInt = toInt( argv[3] );
	input = fopen( "input.txt", "w" );
	output = fopen( "output.txt", "w" );
	fprintf( input, "%d\n", n );
	RandomInt r( 0, maxInt ), rop( 0, 2 );
	if ( mode == 0 )
	{
		while ( n )
		{
			int op = rop(), x = r();
			bool ok = true;
			if ( op == 0 )
			{
				ok = newInsertion( x );
			}
			else if ( op == 1 )
			{
				ok = newRemove( x );
			}
			else
			{
				ok = newQuery( x );
			}
			if ( ok )
			{
				--n;
			}
		}
	}
	else if ( mode == 1 )
	{
		while ( n )
		{
			int x = r();
			if ( newInsertion( x ) )
			{
				--n;
			}
		}
	}
	else
	{
		int m = n / 10;
		n = n - m;
		while ( m )
		{
			int x = r();
			if ( newInsertion( x ) )
			{
				--m;
			}
		}
		while ( n )
		{
			int x = r();
			if ( newQuery( x ) )
			{
				--n;
			}
		}
	}
	fclose( input );
	fclose( output );
}
