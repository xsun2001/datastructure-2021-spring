#include "avl.h"
#include <cstdio>

void AvlTree::rightRotate( Node*& n )
{
	auto m = n->left;
	n->left = m->right;
	m->right = n;
	updateHeight( n );
	updateHeight( m );
	n = m;
}

void AvlTree::leftRotate( Node*& n )
{
	auto m = n->right;
	n->right = m->left;
	m->left = n;
	updateHeight( n );
	updateHeight( m );
	n = m;
}

void AvlTree::rightLeftRotate( Node*& n )
{
	rightRotate( n->right );
	leftRotate( n );
}

void AvlTree::leftRightRotate( Node*& n )
{
	leftRotate( n->left );
	rightRotate( n );
}

int AvlTree::getHeight( Node* n ) { return n == nullptr ? -1 : n->height; }

void AvlTree::updateHeight( Node* n ) { n->height = 1 + max( getHeight( n->left ), getHeight( n->right ) ); }

void AvlTree::balance( Node*& n )
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
	updateHeight( n );
}

void AvlTree::insert( Node*& n, int element )
{
	if ( n == nullptr )
	{
		n = new Node();
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

void AvlTree::remove( Node*& n, int element )
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

AvlTree::Node* AvlTree::findMin( Node* n ) { return ( n == nullptr || n->left == nullptr ) ? n : findMin( n->left ); }

bool AvlTree::find( Node*& n, int element, int& found )
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

void AvlTree::print( AvlTree::Node* n, int depth )
{
	if ( n != nullptr )
	{
		print( n->left, depth + 1 );
		for ( int i = 0; i < depth; i++ )
			printf( "  " );
		printf( "%d\n", n->data );
		print( n->right, depth + 1 );
	}
}

void AvlTree::print() { print( root, 0 ); }
