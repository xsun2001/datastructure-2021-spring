#pragma once
#include "bst.h"

class AvlTree : public BinarySearchTree
{
private:
	struct Node
	{
		int data, height, size;
		Node *left, *right;
		Node() : data( 0 ), left( nullptr ), right( nullptr ), height( 0 ), size( 1 ) {}
	};
	Node* root = nullptr;
	// Single Rotation
	void rightRotate( Node*& n );
	void leftRotate( Node*& n );
	// Double Rotation
	void rightLeftRotate( Node*& n );
	void leftRightRotate( Node*& n );
	// Size & Height Helper Functions
	int getSize( Node* n );
	int getHeight( Node* n );
	void updateHeightAndSize( Node* n );
	// Balance
	void balance( Node*& n );
	// Internal Functions
	void insert( Node*& n, int element );
	void remove( Node*& n, int element );
	Node* findMin( Node* n );
	bool find( Node*& n, int element, int& found );

public:
	void insert( int element ) override;
	void remove( int element ) override;
	bool find( int element, int& found ) override;
};