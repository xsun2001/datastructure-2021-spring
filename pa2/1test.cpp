#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <functional>

template <typename T>
struct LLNode
{
	T data;
	LLNode* nxt;
	explicit LLNode( T data ) : data( data ), nxt( nullptr ) {}
};

template <typename T>
class LinkedList
{
private:
	LLNode<T>* head;
	int size;

public:
	LinkedList() : head( nullptr ), size( 0 ) {}
	//	~LinkedList()
	//	{
	//		while ( head )
	//		{
	//			auto nxt = head->nxt;
	//			delete head;
	//			head = nxt;
	//		}
	//	}
	void push_back( T t )
	{
		auto newNode = new LLNode<T>( t );
		if ( size == 0 )
		{
			head = newNode;
		}
		else
		{
			auto node = head;
			while ( node->nxt != nullptr )
			{
				node = node->nxt;
			}
			node->nxt = newNode;
		}
		++size;
	}
	void insert( int idx, T t )
	{
		auto newNode = new LLNode<T>( t );
		if ( idx == 0 )
		{
			newNode->nxt = head;
			head = newNode;
		}
		else
		{
			auto node = head;
			for ( int i = 1; i < idx; i++ )
			{
				node = node->nxt;
			}
			newNode->nxt = node->nxt;
			node->nxt = newNode;
		}
		++size;
	}
	void remove( int idx )
	{
		if ( idx == 0 )
		{
			auto toRemove = head;
			head = head->nxt;
			delete toRemove;
		}
		else
		{
			auto node = head;
			for ( int i = 1; i < idx; i++ )
			{
				node = node->nxt;
			}
			auto toRemove = node->nxt;
			node->nxt = node->nxt->nxt;
			delete toRemove;
		}
		--size;
	}
	void for_each( std::function<void( T, int )> op )
	{
		auto node = head;
		for ( int i = 0; i < size; i++ )
		{
			op( node->data, i );
			node = node->nxt;
		}
	}
	int getSize() { return size; }
	T operator[]( int idx )
	{
		auto node = head;
		for ( int i = 0; i < idx; i++ )
		{
			node = node->nxt;
		}
		return node->data;
	}
};

int randint( int m ) { return rand() % m; }

int main()
{
	srand( time( nullptr ) );
	LinkedList<int> ll;
	for ( int i = 0; i < 10000; i++ )
	{
		ll.push_back( i );
	}
	printf( "%d\n", ll.getSize() );
	for ( int i = 0; i < 10000; i++ )
	{
		int idx = randint( ll.getSize() );
		ll.remove( idx );
		printf( "%d %d\n", idx, ll.getSize() );
	}
}