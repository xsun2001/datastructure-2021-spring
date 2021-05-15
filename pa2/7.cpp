#include <cstdio>
#include <cstdlib>
#include <cstring>

// 拉链法实现简单Hashmap
// https://zh.wikipedia.org/wiki/%E5%93%88%E5%B8%8C%E8%A1%A8 除留余数法
struct HashMapEntry
{
	int realKey, value;
	HashMapEntry* nxt;
};

const int MAX_BUCKET = 2000003;
class HashMap
{
private:
	HashMapEntry* buckets[MAX_BUCKET];

public:
	HashMap() { memset( buckets, 0, sizeof( buckets ) ); }
	~HashMap()
	{
		for ( auto entry : buckets )
		{
			while ( entry )
			{
				auto nxt = entry->nxt;
				delete entry;
				entry = nxt;
			}
		}
	}
	int get( int key ) // return -1 for non-exist key
	{
		HashMapEntry* entry = buckets[key % MAX_BUCKET];
		while ( entry != nullptr && entry->realKey != key )
		{
			entry = entry->nxt;
		}
		return entry == nullptr ? -1 : entry->value;
	}
	void set( int key, int value )
	{
		HashMapEntry* entry = buckets[key % MAX_BUCKET];
		while ( entry != nullptr && entry->realKey != key )
		{
			entry = entry->nxt;
		}
		if ( entry == nullptr )
		{
			HashMapEntry* newEntry = new HashMapEntry();
			newEntry->realKey = key;
			newEntry->value = value;
			newEntry->nxt = buckets[key % MAX_BUCKET];
			buckets[key % MAX_BUCKET] = newEntry;
		}
		else
		{
			entry->value = value;
		}
	}
} hashmap;

int main()
{
	int ans = 0, n, k;
	scanf( "%d", &n );
	for ( int i = 1; i <= n; i++ )
	{
		scanf( "%d", &k );
		k ^= ans;
		ans = hashmap.get( k );
		if ( ans == -1 )
		{
			ans = i;
		}
		hashmap.set( k, i );
		printf( "%d\n", ans );
	}
}