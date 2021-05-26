#include "bst.h"

class RedBlackTree : public BinarySearchTree
{
private:
	enum Color : bool
	{
		RED = true,
		BLACK = false
	};
	struct Node
	{
		int data;
		Node *left, *right;
		Color color;
	};
	Node *header, *nullNode, *current, *p1, *p2, *p3;
	void handleReorient( int ele );
	Node* rotate( int ele, Node* parent );
	void leftRotate( Node*& n );
	void rightRotate( Node*& n );
	bool find( int x, int& found, Node* c );

public:
	RedBlackTree();
	void insert( int x ) override;
	void remove( int x ) override;
	bool find( int x, int& found ) override;
};