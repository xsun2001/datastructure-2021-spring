#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using entry = std::tuple<std::string, int, bool>;
std::ifstream dataset;
std::ofstream input, output;
int insertion_count, query_count, distribution = 1;
double inserted_ratio = 0.8;
std::vector<entry> data;
std::vector<entry> selected;

static const std::string helpString[] = {
	"Usage: data-generator <dataset-path> <input-path> <output-path> <insertion-count> "
	"<query-count> [distribution] [inserted-ratio]\n"
	"[distribution]: 1 --> insert first (default)\n"
	"                2 --> uniform distribute\n"
	"[inserted-ratio]: inserted key ratio in queries. default is 0.8",
	"Error: dataset is not exist", "Error: input is not valid number" };
template <typename NumberType>
bool parseNumber( char* str, NumberType& res )
{
	static std::stringstream ss;
	ss.clear();
	ss << str;
	ss >> res;
	return !ss.fail();
}

int parseCommandLine( int argc, char** argv )
{
	if ( argc < 6 || argc > 8 )
	{
		return 1;
	}
	dataset = std::ifstream( argv[1] );
	input = std::ofstream( argv[2] );
	output = std::ofstream( argv[3] );
	if ( !( parseNumber( argv[4], insertion_count ) && parseNumber( argv[5], query_count ) ) )
	{
		return 3;
	}
	if ( argc >= 7 && !( parseNumber( argv[6], distribution ) && ( distribution == 1 || distribution == 2 ) ) )
	{
		return 3;
	}
	if ( argc >= 8 && !( parseNumber( argv[7], inserted_ratio ) && inserted_ratio >= 0 && inserted_ratio <= 1 ) )
	{
		return 3;
	}
	return 0;
}

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
using RandomReal = RangedRandom<double, std::uniform_real_distribution<>>;

entry& getUnselected()
{
	static RandomInt r( 0, data.size() - 1 );
	int idx = r();
	while ( std::get<2>( data[idx] ) )
	{
		idx = r();
	}
	return data[idx];
}

entry& getSelected()
{
	static RandomInt r( 0, data.size() - 1 );
	return selected[r() % selected.size()];
}

void newInsertion()
{
	auto& record = getUnselected();
	input << "0 " << std::get<0>( record ) << " " << std::get<1>( record ) << std::endl;
	selected.push_back( record );
	std::get<2>( record ) = true;
}

void newInsertedQuery()
{
	auto& record = getSelected();
	input << "1 " << std::get<0>( record ) << std::endl;
	output << std::get<1>( record ) << std::endl;
}

void newUninsertedQuery()
{
	auto& record = getUnselected();
	input << "1 " << std::get<0>( record ) << std::endl;
	output << "-1" << std::endl;
}

void newQuery()
{
	static RandomReal r( 0, 1 );
	if ( r() <= inserted_ratio )
	{
		newInsertedQuery();
	}
	else
	{
		newUninsertedQuery();
	}
}

int main( int argc, char** argv )
{
	int error = parseCommandLine( argc, argv );
	if ( error != 0 )
	{
		std::cout << helpString[error - 1] << std::endl;
		return -1;
	}
	int i1, i2, i3;
	std::string name;
	while ( dataset >> i1 >> name >> i2 >> i3 )
	{
		data.emplace_back( name, i2, false );
	}
	std::cout << "Read " << data.size() << " records in database";
	if ( distribution == 1 )
	{
		for ( int i = 0; i < insertion_count; i++ )
		{
			newInsertion();
		}
		for ( int i = 0; i < query_count; i++ )
		{
			newQuery();
		}
	}
	else
	{
		RandomReal r( 0, 1 );
		double limit = (double) insertion_count / ( insertion_count + query_count );
		newInsertion();
		--insertion_count;
		while ( insertion_count > 0 || query_count > 0 )
		{
			if ( query_count == 0 || r() <= limit )
			{
				newInsertion();
				--insertion_count;
			}
			else
			{
				newQuery();
				--query_count;
			}
		}
	}
	input << "2" << std::endl;
}