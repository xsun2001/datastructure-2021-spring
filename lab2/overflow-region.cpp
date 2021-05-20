#include "overflow-region.h"

void overflow_region::init() {}

int overflow_region::operator()( hash_entry* Table, int table_size, int last_choice )
{
	if ( last_choice < table_size )
	{
		return table_size;
	}
	else
	{
		return last_choice + 1;
	}
}

bool overflow_region::is_overflow() { return true; }
