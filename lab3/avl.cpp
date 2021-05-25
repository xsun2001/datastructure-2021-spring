#include "avl.h"

void AvlTree::rightRotate( AvlNode*& n )
{
	auto m = n->left;
	n->left = m->right;
	m->right = n;
	updateHeightAndSize( n );
	updateHeightAndSize( m );
	n = m;
}

void AvlTree::leftRotate( AvlNode*& n )
{
	auto m = n->right;
	n->right = m->left;
	m->left = n;
	updateHeightAndSize( n );
	updateHeightAndSize( m );
	n = m;
}

void AvlTree::rightLeftRotate( AvlNode*& n )
{
	rightRotate( n->right );
	leftRotate( n );
}

void AvlTree::leftRightRotate( AvlNode*& n )
{
	leftRotate( n->left );
	rightRotate( n );
}

int AvlTree::getSize( AvlNode* n ) { return n == nullptr ? 0 : n->size; }

int AvlTree::getHeight( AvlNode* n ) { return n == nullptr ? -1 : n->height; }

void AvlTree::updateHeightAndSize( AvlNode* n )
{
	n->height = 1 + max( getHeight( n->left ), getHeight( n->right ) );
	n->size = 1 + max( getSize( n->left ), getSize( n->right ) );
}

void AvlTree::balance( AvlNode*& n )
{
	if ( n == nullptr )
	{
		return;
	}
	int heightDiff = getHeight( n->left ) - getHeight( n->right );
	if ( heightDiff > 1 )
	{
		if ( getHeight( n->left->left ) >= getHeight( n->left->right ) )
		{
			rightRotate( n );
		}
		else
		{
			leftRightRotate( n );
		}
	}
	else if ( heightDiff < -1 )
	{
		if ( getHeight( n->right->right ) >= getHeight( n->right->left ) )
		{
			leftRotate( n );
		}
		else
		{
			rightLeftRotate( n );
		}
	}
	updateHeightAndSize( n );
}

void AvlTree::insert( AvlNode*& n, int element )
{
	if ( n == nullptr )
	{
		n = new AvlNode();
		n->data = element;
		return;
	}
	else if ( n->data > element )
	{
		insert( n->left, element );
	}
	else if ( n->data < element )
	{
		insert( n->right, element );
	}
	balance( n );
}

void AvlTree::remove( AvlNode*& n, int element )
{
	if ( n == nullptr )
	{
		return;
	}
	if ( n->data > element )
	{
		remove( n->left, element );
	}
	else if ( n->data < element )
	{
		remove( n->right, element );
	}
	else if ( n->left != nullptr && n->right != nullptr )
	{
		n->data = findMin( n->right )->data;
		remove( n->right, n->data );
	}
	else
	{
		auto m = n;
		n = ( n->left == nullptr ) ? n->right : n->left;
		delete m;
	}
	balance( n );
}

AvlNode* AvlTree::findMin( AvlNode* n ) { return ( n == nullptr || n->left == nullptr ) ? n : findMin( n->left ); }

bool AvlTree::find( AvlNode*& n, int element, int& found )
{
	if ( n == nullptr )
	{
		return false;
	}
	else if ( n->data > element )
	{
		return find( n->left, element, found );
	}
	else if ( n->data < element )
	{
		if ( find( n->right, element, found ) )
		{
			return true;
		}
	}
	found = n->data;
	return true;
}

void AvlTree::insert( int element ) { insert( root, element ); }

void AvlTree::remove( int element ) { remove( root, element ); }

bool AvlTree::find( int element, int& found ) { return find( root, element, found ); }
