#include "bst.h"
#include <initializer_list>

class RedBlackTree : public BinarySearchTree
{
private:
	struct Node
	{
		unsigned int data;
		Node *left, *right;
	};
	Node *header, *nullNode, *current, *p1, *p2, *p3;
	static bool isRed( Node* n );
	static void setRed( std::initializer_list<Node*> ns );
	static void setBlack( std::initializer_list<Node*> ns );
	static unsigned int getData( Node* n );
	static void setData( Node* n, unsigned int data );
	static Node* rotateUp( int ele, Node* parent );
	static Node* rotateDown( int ele, Node* parent );
	static void leftRotate( Node*& n );
	static void rightRotate( Node*& n );
	void handleReorient( int ele );
	bool find( int x, int& found, Node* c );
	void print( Node* n, int depth );

public:
	RedBlackTree();
	void insert( int x ) override;
	void remove( int x ) override;
	bool find( int x, int& found ) override;
	void print() override;
};