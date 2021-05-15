#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>

// --- ChunkedVector ---

const int CHUNK_SIZE = 10, CHUNK_COUNT = 1000;

template <typename T>
struct Chunk
{
	T data[CHUNK_SIZE + 1];
	Chunk<T>* next;
	int size;
	Chunk() : next( nullptr ), size( 0 ) { memset( data, 0, sizeof( data ) ); }
	~Chunk()
	{
		if ( next )
		{
			delete next;
		}
	}
	T operator[]( int idx ) { return data[idx]; }
	void insert( int idx, T& ele )
	{
		// std::cout << "chunk insert " << idx << " " << ele << std::endl;
		// Ignore invalid operation
		if ( idx != size )
		{
			memmove( &data[idx + 1], &data[idx], sizeof( T ) * ( size - idx ) );
		}
		data[idx] = ele;
		++size;
	}
	T remove( int idx )
	{
		T ele = data[idx];
		if ( idx < size - 1 )
		{
			memmove( &data[idx], &data[idx + 1], sizeof( T ) * ( size - idx - 1 ) );
		}
		--size;
		memset( &data[size], 0, sizeof( T ) );
		return ele;
	}
	void push_back( T& ele ) { insert( size, ele ); }
	void for_each( std::function<void( int, int )> op, int size_offset )
	{
		// std::cout << "Low foreach" << std::endl;
		for ( int i = 0; i < size; i++ )
		{
			op( data[i], size_offset + i );
		}
	}
};

template <typename T>
class ChunkedVector
{
public:
	ChunkedVector() : size( 0 ), chunk_count( 0 ), chunks( nullptr ) {}
	~ChunkedVector()
	{
		if ( chunks )
		{
			delete chunks;
		}
	}
	int getSize() { return size; }
	void partition()
	{
		static T buffer[CHUNK_COUNT * CHUNK_SIZE];
		Chunk<T>*c = chunks, *pc = nullptr;
		for ( int i = 0, idx = 0; i < chunk_count && idx < size; i++ )
		{
			memmove( buffer + idx, c->data, sizeof( T ) * c->size );
			idx += c->size;
			c = c->next;
		}
		int i = 0, idx = 0;
		c = chunks;
		while ( idx < size )
		{
			int s = std::min( size - idx, CHUNK_SIZE );
			memmove( c->data, buffer + idx, sizeof( T ) * s );
			c->size = s;
			idx += s;
			++i;
			pc = c;
			c = c->next;
			if ( c == nullptr )
			{
				pc->next = c = new Chunk<int>();
			}
		}
		chunk_count = i;
		while ( c )
		{
			c->size = 0;
			c = c->next;
		}
	}
	void insert( int idx, T& ele )
	{
		// std::cout << "insert " << idx << " " << ele << std::endl;
		if ( chunks == nullptr )
		{
			chunks = new Chunk<T>();
		}
		Chunk<T>*c = chunks, *c1 = chunks;
		int i = 0;
		for ( ; idx > c->size && i < chunk_count; i++ )
		{
			idx -= c->size;
			c1 = c;
			c = c->next;
		}
		if ( i == chunk_count )
		{
			++chunk_count;
		}
		if ( c == nullptr )
		{
			c1->next = c = new Chunk<T>();
		}
		c->insert( idx, ele );
		++size;
		if ( c->size > CHUNK_SIZE )
		{
			partition();
		}
	}
	void push_back( T& ele ) { insert( size, ele ); }
	T& operator[]( int idx )
	{
		Chunk<T>* c = chunks;
		while ( idx >= c->size )
		{
			idx -= c->size;
			c = c->next;
		}
		return c->data[idx];
	}
	T remove( int idx )
	{
		Chunk<T>* c = chunks;
		while ( idx >= c->size )
		{
			idx -= c->size;
			c = c->next;
		}
		T ele = c->remove( idx );
		--size;
		if ( c->size == 0 )
		{
			partition();
		}
		return ele;
	}
	void for_each( std::function<void( int, int )> op )
	{
		// std::cout << "Top foreach" << std::endl;
		int size_offset = 0, i = 0;
		Chunk<T>* c = chunks;
		while ( i < chunk_count )
		{
			c->for_each( op, size_offset );
			size_offset += c->size;
			c = c->next;
			++i;
		}
	}

private:
	int size, chunk_count;
	Chunk<T>* chunks;
};

// int main()
// {
// 	ChunkedVector<int> cv;
// 	for ( int i = 1; i <= 22; i++ )
// 		cv.insert( 0, i );
// 	cv.for_each( []( int a, int b ) { std::cout << a << ","; } );
// 	std::cout << std::endl;
// }

// --------------

const int NODE_COUNT = 1000006;
// MWT: Multi-Way Tree
struct MWTNode
{
	int parent, size;
	ChunkedVector<int> children;
} tree[NODE_COUNT];

// parentNode.children[childIndex] = node
void findNode( int& node, int& parentNode, int& childIndex )
{
	parentNode = node = 1;
	int l, k;
	bool good = true;
	std::cin >> l;
	while ( l-- )
	{
		std::cin >> k;
		if ( k >= tree[node].children.getSize() )
		{
			good = false;
		}
		if ( !good )
		{
			continue;
		}
		parentNode = node;
		node = tree[node].children[k];
		childIndex = k;
	}
}

void moveSubtree()
{
	// std::cout << "move subtree" << std::endl;

	int sourceNode, snParentNode, snChildIndex;
	int targetNode, tnParentNode, tnChildIndex;
	int deltaSize, node, rank;

	// Remove source node
	findNode( sourceNode, snParentNode, snChildIndex );
	tree[snParentNode].children.remove( snChildIndex );
	deltaSize = tree[sourceNode].size;
	while ( snParentNode )
	{
		tree[snParentNode].size -= deltaSize;
		snParentNode = tree[snParentNode].parent;
	}

	// Insert to target node
	findNode( targetNode, tnParentNode, tnChildIndex );
	std::cin >> rank;
	tree[targetNode].children.insert( rank, sourceNode );
	tree[sourceNode].parent = targetNode;
	while ( targetNode )
	{
		tree[targetNode].size += deltaSize;
		targetNode = tree[targetNode].parent;
	}
}

int queryHeight()
{
	int node, pn, ci, ans = 0;
	findNode( node, pn, ci );
	while ( node )
	{
		++ans;
		node = tree[node].parent;
	}
	return ans;
}

int querySize()
{
	int node, pn, ci;
	findNode( node, pn, ci );
	return tree[node].size;
}

int queryNode()
{
	int node, pn, ci;
	findNode( node, pn, ci );
	return node;
}

int initSize( int node )
{
	// std::cout << "initSize " << node << std::endl;
	int size = 1;
	tree[node].children.for_each( [&]( int n, int idx ) { size += initSize( n ); } );
	tree[node].size = size;
	// std::cout << "size " << node << " " << size << std::endl;
	return size;
}

void readTree( int n )
{
	for ( int i = 1; i <= n; i++ )
	{
		int k, l;
		std::cin >> k;
		for ( int j = 0; j < k; j++ )
		{
			std::cin >> l;
			tree[i].children.push_back( l );
			tree[l].parent = i;
		}
	}
	initSize( 1 );
}

void printTree( int node, int depth )
{
	for ( int i = 0; i < depth; i++ )
		std::cout << "  ";
	std::cout << "Node " << node << " Depth " << depth << " Size " << tree[node].size << std::endl;
	tree[node].children.for_each( [=]( int n, int i ) { printTree( n, depth + 1 ); } );
}

int main()
{
	int n, m, op;
	std::cin >> n >> m;
	readTree( n );
	while ( m-- )
	{
		std::cin >> op;
		switch ( op )
		{
		case 0:
			moveSubtree();
			break;
		case 1:
			std::cout << queryHeight() << std::endl;
			break;
		case 2:
			std::cout << querySize() << std::endl;
			break;
			// case 3:
			// 	std::cout << queryNode() << std::endl;
			// 	break;
			// case 4:
			// 	printTree( 1, 0 );
			// 	break;
		}
	}
}