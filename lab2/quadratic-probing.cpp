#include "quadratic-probing.h"

void quadratic_probing::init()
{
	last_addition = 0;
	last_direction = -1;
}

int quadratic_probing::operator()( hash_entry* Table, int table_size, int last_choice )
{
	last_choice -= last_direction * last_addition * last_addition;
	if ( last_direction == -1 )
	{
		last_direction = 1;
		last_addition += 1;
	}
	else
	{
		last_direction = -1;
	}
	last_choice += last_direction * last_addition * last_addition;
	last_index = ( last_choice % table_size + table_size ) % table_size;
	return last_index;
}