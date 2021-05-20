#include "framework/hashtable.h"

struct overflow_region : public collision_strategy
{
	void init() override;
	int operator()( hash_entry* Table, int table_size, int last_choice ) override;
	bool is_overflow() override;
};