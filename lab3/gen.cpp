#include <random>
#include <set>

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

int main()
{
	int n = 1000000;
	RandomInt r( 0, 3000 ), rop( 0, 2 );
	std::set<int, std::greater<>> s;
	FILE *input = fopen( "input.txt", "w" ), *output = fopen( "output.txt", "w" );
	fprintf( input, "%d\n", n );
	while ( n-- )
	{
		int op = rop(), x = r();
		switch ( op )
		{
		case 0:
			if ( s.find( x ) != s.end() )
			{
				n++;
				continue;
			}
			else
			{
				s.insert( x );
			}
			break;
		case 1:
			if ( s.find( x ) == s.end() )
			{
				n++;
				continue;
			}
			else
			{
				s.erase( x );
			}
			break;
		case 2:
			auto it = s.lower_bound( x );
			fprintf( output, "%d\n", it == s.end() ? -1 : *it );
		}
		fprintf( input, "%c %d\n", 'A' + op, x );
	}
	fclose( input );
	fclose( output );
}
