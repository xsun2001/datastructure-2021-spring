#pragma once
#include "bst.h"

class AvlTree : public BinarySearchTree
{
private:
	struct Node
	{
		int data, height;
		Node *left, *right;
		Node() : data( 0 ), left( nullptr ), right( nullptr ), height( 0 ) {}
	};
	Node* root = nullptr;
	// Single Rotation
	void rightRotate( Node*& n );
	void leftRotate( Node*& n );
	// Double Rotation
	void rightLeftRotate( Node*& n );
	void leftRightRotate( Node*& n );
	// Height Helper Functions
	int getHeight( Node* n );
	void updateHeight( Node* n );
	// Balance
	void balance( Node*& n );
	// Internal Functions
	void insert( Node*& n, int element );
	void remove( Node*& n, int element );
	Node* findMin( Node* n );
	bool find( Node*& n, int element, int& found );
	void print( Node* n, int depth );

public:
	void insert( int element ) override;
	void remove( int element ) override;
	bool find( int element, int& found ) override;
	void print() override;
};