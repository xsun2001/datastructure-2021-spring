#include <functional>
#include <iostream>

// template <typename T>
// struct ListNode
// {
// 	T data {};
// 	ListNode<T>*next = nullptr, *prev = nullptr;
// };

// template <typename T>
// class List
// {
// private:
// 	int size = 0;
// 	ListNode<T>* head = nullptr;
// 	void connect( ListNode<T>* n1, ListNode<T>* n2 )
// 	{
// 		n1->next = n2;
// 		n2->prev = n1;
// 	}

// public:
// 	~List()
// 	{
// 		ListNode<T>* nxt;
// 		while ( size-- )
// 		{
// 			nxt = head->next;
// 			delete head;
// 			head = nxt;
// 		}
// 	}
// 	void insert( int idx, T ele )
// 	{
// 		ListNode<T>* node = head;
// 		for ( int i = 0; i < idx; i++ )
// 		{
// 			node = node->next;
// 		}
// 		ListNode<T>* newNode = new ListNode<T>();
// 		newNode->data = ele;
// 		if ( size == 0 )
// 		{
// 			connect( newNode, newNode );
// 			head = newNode;
// 		}else{
// 			if(node == nullptr)
// 		}
// 		if ( node == nullptr )
// 		{
// 			connect( newNode, newNode );
// 		}
// 		else
// 		{
// 			connect( node->prev, newNode );
// 			connect( newNode, node );
// 		}
// 		if ( idx == 0 )
// 		{
// 			head = newNode;
// 		}
// 		++size;
// 	}
// 	void remove( int idx )
// 	{
// 		ListNode<T>* node = head;
// 		for ( int i = 0; i < idx; i++ )
// 		{
// 			node = node->next;
// 		}
// 		connect( node->prev, node->next );
// 		delete node;
// 		--size;
// 	}
// 	void push_back( T& ele )
// 	{
// 		ListNode<T>* newNode = new ListNode<T>();
// 		newNode->data = ele;
// 		if ( size == 0 )
// 		{
// 			connect( newNode, newNode );
// 			head = newNode;
// 		}
// 		else
// 		{
// 			connect( head->prev, newNode );
// 			connect( newNode, head );
// 		}
// 		++size;
// 	}
// 	void for_each( std::function<void( int, int )> op )
// 	{
// 		if ( size == 0 )
// 			return;
// 		int idx = 0;
// 		ListNode<T>* node = head;
// 		do
// 		{
// 			op( node->data, idx++ );
// 			node = node->next;
// 		} while ( node != head );
// 	}
// 	int getSize() { return size; }
// 	T operator[]( int idx )
// 	{
// 		ListNode<T>* node = head;
// 		for ( int i = 0; i < idx; i++ )
// 		{
// 			node = node->next;
// 		}
// 		return node->data;
// 	}
// };

template <typename T>
struct ListNode
{
	T data;
	ListNode* nxt;
};

template <typename T>
class List
{
private:
	ListNode<T>*head, *tail;
	int size;

public:
	int getSize() { return size; }
	void push_back( T data )
	{
		auto node = new ListNode<T>();
		node->data = data;
		if ( tail == nullptr )
		{
			head = tail = node;
		}
		else
		{
			tail->nxt = node;
			tail = node;
		}
		++size;
	}
	void remove( int idx )
	{
		if ( idx == 0 )
		{
			auto node = head;
			head = head->nxt;
			delete node;
			if ( size == 1 )
			{
				tail = nullptr;
			}
		}
		else
		{
			auto node = head;
			for ( int i = 0; i < idx - 1; i++ )
			{
				node = node->nxt;
			}
			auto toRemove = node->nxt;
			node->nxt = toRemove->nxt;
			if ( toRemove == tail )
			{
				tail = node;
			}
			delete toRemove;
		}
		--size;
	}
	void insert( int idx, T data )
	{
		if ( idx == 0 )
		{
			auto node = new ListNode<T>();
			node->data = data;
			node->nxt = head;
			head = node;
			if ( size == 0 )
			{
				tail = head;
			}
		}
		else if ( size == idx )
		{
			push_back( data );
		}
		else
		{
			auto node = head, newNode = new ListNode<T>();
			newNode->data = data;
			for ( int i = 0; i < idx - 1; i++ )
			{
				node = node->nxt;
			}
			newNode->nxt = node->nxt;
			node->nxt = newNode;
		}
		++size;
	}
	T get( int idx )
	{
		ListNode<T>* node = head;
		for ( int i = 0; i < idx; i++ )
		{
			node = node->nxt;
		}
		return node->data;
	}
	T operator[]( int idx ) { return get( idx ); }
	void for_each( std::function<void( int, int )> op )
	{
		if ( size == 0 )
			return;
		int idx = 0;
		ListNode<T>* node = head;
		do
		{
			op( node->data, idx++ );
			node = node->nxt;
		} while ( node );
	}
};

const int NODE_COUNT = 1000006;
// MWT: Multi-Way Tree
struct MWTNode
{
	int parent, size;
	List<int> children;
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
	int deltaSize, rank;

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

int initTree( int node )
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
		case 3:
			std::cout << queryNode() << std::endl;
			break;
		case 4:
			printTree( 1, 0 );
			break;
		}
	}
}