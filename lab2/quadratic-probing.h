#include "framework/hashtable.h"

struct quadratic_probing : public collision_strategy
{
	void init() override;
	int operator()( hash_entry* Table, int table_size, int last_choice ) override;

private:
	int last_index = 0, last_addition = 0, last_direction = 1;
};