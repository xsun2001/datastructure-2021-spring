#include <cstdio>
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
	~LinkedList()
	{
		while ( head )
		{
			auto nxt = head->nxt;
			delete head;
			head = nxt;
		}
	}
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

const int NODE_COUNT = 1000006;
// MWT: Multi-Way Tree
struct MWTNode
{
	int parent, size, highestChild, height;
	LinkedList<int> children;
} tree[NODE_COUNT];

// parentNode.children[childIndex] = node
void findNode( int& node, int& parentNode, int& childIndex )
{
	parentNode = node = 1;
	int l, k;
	bool good = true;
	scanf( "%d", &l );
	if ( l <= 0 )
	{
		return;
	}
	while ( l-- )
	{
		scanf( "%d", &k );
		if ( !good )
		{
			continue;
		}
		if ( k < 0 || k >= tree[node].children.getSize() )
		{
			good = false;
			continue;
		}
		parentNode = node;
		node = tree[node].children[k];
		childIndex = k;
	}
}

void updateSize( int node, int deltaSize )
{
	while ( node )
	{
		tree[node].size += deltaSize;
		node = tree[node].parent;
	}
}

void updateHeight( int node )
{
	while ( node )
	{
		int lastHeight = tree[node].height;
		tree[node].height = tree[node].highestChild = 0;
		if ( tree[node].children.getSize() > 0 )
		{
			tree[node].children.for_each(
				[=]( int n, int idx )
				{
					if ( tree[n].height > tree[node].height )
					{
						tree[node].height = tree[n].height;
						tree[node].highestChild = n;
					}
				} );
			++tree[node].height;
		}
		int parent = tree[node].parent;
		if ( parent == 0 || tree[parent].highestChild != node || lastHeight == tree[node].height )
		{
			return;
		}
		node = parent;
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
	updateSize( snParentNode, -deltaSize );
	if ( sourceNode == tree[snParentNode].highestChild )
	{
		updateHeight( snParentNode );
	}

	// Insert to target node
	findNode( targetNode, tnParentNode, tnChildIndex );
	scanf( "%d", &rank );
	tree[targetNode].children.insert( rank, sourceNode );
	tree[sourceNode].parent = targetNode;
	updateSize( targetNode, deltaSize );
	if ( tree[sourceNode].height + 1 > tree[targetNode].height )
	{
		tree[targetNode].highestChild = sourceNode;
		tree[targetNode].height = tree[sourceNode].height + 1;
		updateHeight( tree[targetNode].parent );
	}
}

int queryHeight()
{
	int node, pn, ci;
	findNode( node, pn, ci );
	return tree[node].height;
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

void initTree( int node )
{
	if ( tree[node].children.getSize() == 0 )
	{
		tree[node].size = 1;
		tree[node].height = 0;
		return;
	}
	// std::cout << "initTree " << node << std::endl;
	tree[node].children.for_each(
		[=]( int n, int idx )
		{
			initTree( n );
			tree[node].size += tree[n].size;
			if ( tree[n].height > tree[node].height )
			{
				tree[node].highestChild = n;
				tree[node].height = tree[n].height;
			}
		} );
	++tree[node].size;
	++tree[node].height;
	// std::cout << "size " << node << " " << size << std::endl;
}

void readTree( int n )
{
	for ( int i = 1; i <= n; i++ )
	{
		int k, l;
		scanf( "%d", &k );
		for ( int j = 0; j < k; j++ )
		{
			scanf( "%d", &l );
			tree[i].children.push_back( l );
			tree[l].parent = i;
		}
	}
	initTree( 1 );
}

void printTree( int node, int depth )
{
	for ( int i = 0; i < depth; i++ )
		printf( "  " );
	printf( "[%d, %d, %d, %d, %d]\n", node, depth, tree[node].size, tree[node].height, tree[node].highestChild );
	tree[node].children.for_each( [=]( int n, int i ) { printTree( n, depth + 1 ); } );
}

int main()
{
	int n, m, op;
	scanf( "%d%d", &n, &m );
	readTree( n );
	while ( m-- )
	{
		scanf( "%d", &op );
		switch ( op )
		{
		case 0:
			moveSubtree();
			break;
		case 1:
			printf( "%d\n", queryHeight() );
			break;
		case 2:
			printf( "%d\n", querySize() );
			break;
		case 3:
			printf( "%d\n", queryNode() );
			break;
		case 4:
			printTree( 1, 0 );
			break;
		}
	}
}