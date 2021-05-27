#include "rbt.h"
#include <cstdio>
#include <limits>

RedBlackTree::RedBlackTree()
	: header( new Node ), nullNode( new Node ), current( nullptr ), p1( nullptr ), p2( nullptr ), p3( nullptr )
{
	header->data = std::numeric_limits<int>::min();
	nullNode->left = nullNode->right = header->left = header->right = nullNode;
	setBlack( { header, header->right, nullNode } );
}
bool RedBlackTree::isRed( RedBlackTree::Node* n ) { return ( n->data & 0x80000000 ) == 0; }
void RedBlackTree::setRed( std::initializer_list<RedBlackTree::Node*> ns )
{
	for ( auto n : ns )
	{
		n->data &= 0x7FFFFFFF;
	}
}
void RedBlackTree::setBlack( std::initializer_list<RedBlackTree::Node*> ns )
{
	for ( auto n : ns )
	{
		n->data |= 0x80000000;
	}
}
unsigned int RedBlackTree::getData( RedBlackTree::Node* n ) { return n->data & 0x7FFFFFFF; }
void RedBlackTree::setData( RedBlackTree::Node* n, unsigned int data ) { n->data = ( n->data & 0x80000000 ) | data; }
void RedBlackTree::handleReorient( int ele )
{
	setRed( { current } );
	setBlack( { current->left, current->right } );

	if ( isRed( p1 ) )
	{
		setRed( { p2 } );
		if ( ele < getData( p2 ) != ele < getData( p1 ) )
		{
			p1 = rotateUp( ele, p2 );
		}
		current = rotateUp( ele, p3 );
		setBlack( { current } );
	}

	setBlack( { header->right } );
}
RedBlackTree::Node* RedBlackTree::rotateUp( int ele, RedBlackTree::Node* parent )
{
	if ( ele < getData( parent ) )
	{
		ele < getData( parent->left ) ? rightRotate( parent->left ) : leftRotate( parent->left );
		return parent->left;
	}
	else
	{
		ele < getData( parent->right ) ? rightRotate( parent->right ) : leftRotate( parent->right );
		return parent->right;
	}
}
RedBlackTree::Node* RedBlackTree::rotateDown( int ele, RedBlackTree::Node* parent )
{
	if ( ele < getData( parent ) )
	{
		ele < getData( parent->left ) ? leftRotate( parent->left ) : rightRotate( parent->left );
		return parent->left;
	}
	else
	{
		ele < getData( parent->right ) ? leftRotate( parent->right ) : rightRotate( parent->right );
		return parent->right;
	}
}
void RedBlackTree::leftRotate( RedBlackTree::Node*& n )
{
	auto m = n->right;
	n->right = m->left;
	m->left = n;
	n = m;
}
void RedBlackTree::rightRotate( RedBlackTree::Node*& n )
{
	auto m = n->left;
	n->left = m->right;
	m->right = n;
	n = m;
}
bool RedBlackTree::find( int x, int& found, RedBlackTree::Node* c )
{
	if ( c == nullNode )
	{
		return false;
	}
	if ( getData( c ) == x )
	{
		found = x;
		return true;
	}
	if ( x < getData( c ) )
	{
		return find( x, found, c->left );
	}
	else
	{
		if ( !find( x, found, c->right ) )
		{
			found = getData( c );
		}
		return true;
	}
}
void RedBlackTree::insert( int x )
{
	current = p1 = p2 = header;
	setData( nullNode, x );

	while ( getData( current ) != x )
	{
		p3 = p2;
		p2 = p1;
		p1 = current;
		current = x < getData( current ) ? current->left : current->right;
		if ( isRed( current->left ) && isRed( current->right ) )
		{
			handleReorient( x );
		}
	}

	if ( current != nullNode )
	{
		return;
	}
	current = new Node;
	setData( current, x );
	current->left = current->right = nullNode;

	if ( x < getData( p1 ) )
	{
		p1->left = current;
	}
	else
	{
		p1->right = current;
	}
	handleReorient( x );
}

void RedBlackTree::remove( int x )
{
	setRed( { header->right } );
	// c: current, t: sibling, p: parent, g: grandparent
	Node *c = header, *t, *p, *g, *toDelete;
	t = p = g = toDelete = nullptr;

	while ( true )
	{
		// c is red
		if ( c->left == nullNode && c->right == nullNode )
		{
			break;
		}

		// push c down

		g = p;
		p = c;
		if ( x < getData( c ) )
		{
			t = c->right;
			c = c->left;
		}
		else
		{
			t = c->left;
			c = c->right;
		}
		if ( getData( c ) == x )
		{
			toDelete = c;
		}

		// balance

		if ( !isRed( c->left ) && !isRed( c->right ) )
		{
			if ( !isRed( t->left ) && !isRed( t->right ) )
			{
				// Case 1
				setRed( { c, t } );
				setBlack( { p, nullNode } );
			}
			else
			{

				if ( getData( c ) < getData( p ) )
				{
					if ( !isRed( t->right ) )
					{
						// Case 3
						rightRotate( p->right );
					}
				}
				else
				{
					if ( !isRed( t->left ) )
					{
						// Case 3
						leftRotate( p->left );
					}
				}
				// Case 2
				Node* subroot = rotateDown( x, g );
				setRed( { subroot, c } );
				setBlack( { subroot->left, subroot->right } );
			}
		}
		else
		{
			if ( ( isRed( c->left ) && isRed( c->right ) ) || ( ( x < getData( c ) ) == isRed( c->left ) ) )
			{
				// Case 4
				g = p;
				p = c;
				if ( x < getData( c ) )
				{
					t = c->right;
					c = c->left;
				}
				else
				{
					t = c->left;
					c = c->right;
				}
				if ( getData( c ) == x )
				{
					toDelete = c;
				}
			}
			else
			{
				// Case 5
				p = rotateDown( x, p );
				setBlack( { p } );
				setRed( { c } );
			}
		}

		// c is still red
	}

	if ( toDelete != nullptr )
	{
		setData( toDelete, getData( c ) );
		Node*& uplink = getData( c ) < getData( p ) ? p->left : p->right;
		if ( getData( c ) < getData( p ) )
		{
			p->left = nullNode;
		}
		else
		{
			p->right = nullNode;
		}
		delete c;
	}

	setBlack( { header->right, nullNode } );
}

bool RedBlackTree::find( int x, int& found ) { return find( x, found, header->right ); }
void RedBlackTree::print( RedBlackTree::Node* n, int depth )
{
	if ( n != nullNode )
	{
		print( n->left, depth + 1 );
		for ( int i = 0; i < depth; i++ )
			printf( "  " );
		printf( "%d %s\n", getData( n ), isRed( n ) ? "R" : "B" );
		print( n->right, depth + 1 );
	}
}
void RedBlackTree::print() { print( header->right, 0 ); }
