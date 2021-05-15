#include <cstdio>
#include <functional>

struct HuffmanTreeNode
{
	char key;
	int size;
	HuffmanTreeNode *left, *right;
};

// Just a simple degenerated priority queue
template <typename T>
struct PQLinkNode
{
	T data;
	PQLinkNode* nxt;
};

// min heap
template <typename T>
class PriorityQueue
{
private:
	PQLinkNode<T>* head;
	int size;
	std::function<int( T&, T& )> comparator;

public:
	PriorityQueue( std::function<int( T&, T& )> comparator ) : head( nullptr ), size( 0 ), comparator( comparator ) {}
	~PriorityQueue()
	{
		while ( head )
		{
			auto nxt = head->nxt;
			delete head;
			head = nxt;
		}
	}
	void push( T& t )
	{
		auto newNode = new PQLinkNode<T>();
		newNode->data = t;
		if ( size == 0 )
		{
			head = newNode;
			size = 1;
			return;
		}
		PQLinkNode<T>*node = head, *prev = nullptr;
		while ( node != nullptr && comparator( newNode->data, node->data ) >= 0 ) // newNode >= node
		{
			prev = node;
			node = node->nxt;
		}
		if ( prev == nullptr )
		{
			newNode->nxt = head;
			head = newNode;
		}
		else
		{
			prev->nxt = newNode;
			newNode->nxt = node;
		}
		++size;
	}
	T pop()
	{
		// ignore size == 0
		T t = head->data;
		auto nxt = head->nxt;
		delete head;
		head = nxt;
		--size;
		return t;
	}
	int getSize() { return size; }
};

int htnComparator( HuffmanTreeNode* n1, HuffmanTreeNode* n2 ) { return n1->size - n2->size; }
PriorityQueue<HuffmanTreeNode*> nodes( htnComparator );

int charCount[30];

int calculateLength( HuffmanTreeNode* node, int depth )
{
	if ( node == nullptr )
	{
		return 0;
	}
	if ( node->key )
	{
		return node->size * ( depth == 0 ? 1 : depth );
	}
	else
	{
		return calculateLength( node->left, depth + 1 ) + calculateLength( node->right, depth + 1 );
	}
}

char encode[100];
int encodeLength = -1;
void printEncodingScheme( HuffmanTreeNode* node )
{
	if ( node == nullptr )
	{
		return;
	}
	if ( node->key )
	{
		if ( encodeLength == -1 )
		{
			printf( "%c 0\n", node->key );
		}
		else
		{
			printf( "%c %s\n", node->key, encode );
		}
	}
	else
	{
		++encodeLength;
		encode[encodeLength] = '0';
		printEncodingScheme( node->left );
		encode[encodeLength] = '1';
		printEncodingScheme( node->right );
		encode[encodeLength] = '\0';
		--encodeLength;
	}
}

int main()
{
	char c;
	for ( ;; )
	{
		c = getchar();
		if ( c < 'a' || c > 'z' )
		{
			break;
		}
		charCount[c - 'a']++;
	}
	for ( int i = 0; i <= 'z' - 'a'; i++ )
	{
		if ( charCount[i] > 0 )
		{
			auto node = new HuffmanTreeNode();
			node->key = i + 'a';
			node->size = charCount[i];
			node->left = node->right = nullptr;
			nodes.push( node );
		}
	}
	while ( nodes.getSize() > 1 )
	{
		auto n1 = nodes.pop(), n2 = nodes.pop();
		auto node = new HuffmanTreeNode();
		node->key = 0;
		node->size = n1->size + n2->size;
		node->left = n1;
		node->right = n2;
		nodes.push( node );
	}
	auto treeRoot = nodes.pop();
	printf( "%d\n", calculateLength( treeRoot, 0 ) );

	printEncodingScheme( treeRoot );
}