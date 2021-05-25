#pragma once
#include "bst.h"

struct AvlNode
{
	int data, height, size;
	AvlNode *left, *right;
	AvlNode() : data( 0 ), left( nullptr ), right( nullptr ), height( 0 ), size( 1 ) {}
};

class AvlTree : public BinarySearchTree
{
private:
	AvlNode* root = nullptr;
	// Single Rotation
	void rightRotate( AvlNode*& n );
	void leftRotate( AvlNode*& n );
	// Double Rotation
	void rightLeftRotate( AvlNode*& n );
	void leftRightRotate( AvlNode*& n );
	// Size & Height Helper Functions
	int getSize( AvlNode* n );
	int getHeight( AvlNode* n );
	void updateHeightAndSize( AvlNode* n );
	// Balance
	void balance( AvlNode*& n );
	// Internal Functions
	void insert( AvlNode*& n, int element );
	void remove( AvlNode*& n, int element );
	AvlNode* findMin( AvlNode* n );
	bool find( AvlNode*& n, int element, int& found );

public:
	void insert( int element ) override;
	void remove( int element ) override;
	bool find( int element, int& found ) override;
};