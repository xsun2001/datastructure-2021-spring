#include "rbt.h"
#include <cstdio>
#include <limits>
RedBlackTree::RedBlackTree()
	: header( new Node ), nullNode( new Node ), current( nullptr ), p1( nullptr ), p2( nullptr ), p3( nullptr )
{
	header->data = std::numeric_limits<int>::min();
	nullNode->left = nullNode->right = header->left = header->right = nullNode;
}
void RedBlackTree::handleReorient( int ele )
{
	current->color = RED;
	current->left->color = current->right->color = BLACK;

	if ( p1->color == RED )
	{
		p2->color = RED;
		if ( ele < p2->data != ele < p1->data )
		{
			p1 = rotateUp( ele, p2 );
		}
		current = rotateUp( ele, p3 );
		current->color = BLACK;
	}

	header->right->color = BLACK;
}
RedBlackTree::Node* RedBlackTree::rotateUp( int ele, RedBlackTree::Node* parent )
{
	if ( ele < parent->data )
	{
		ele < parent->left->data ? rightRotate( parent->left ) : leftRotate( parent->left );
		return parent->left;
	}
	else
	{
		ele < parent->right->data ? rightRotate( parent->right ) : leftRotate( parent->right );
		return parent->right;
	}
}
RedBlackTree::Node* RedBlackTree::rotateDown( int ele, RedBlackTree::Node* parent )
{
	if ( ele < parent->data )
	{
		ele < parent->left->data ? leftRotate( parent->left ) : rightRotate( parent->left );
		return parent->left;
	}
	else
	{
		ele < parent->right->data ? leftRotate( parent->right ) : rightRotate( parent->right );
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
	if ( c->data == x )
	{
		found = x;
		return true;
	}
	if ( x < c->data )
	{
		return find( x, found, c->left );
	}
	else
	{
		if ( !find( x, found, c->right ) )
		{
			found = c->data;
		}
		return true;
	}
}
void RedBlackTree::insert( int x )
{
	current = p1 = p2 = header;
	nullNode->data = x;

	while ( current->data != x )
	{
		p3 = p2;
		p2 = p1;
		p1 = current;
		current = x < current->data ? current->left : current->right;
		if ( current->left->color == RED && current->right->color == RED )
		{
			handleReorient( x );
		}
	}

	if ( current != nullNode )
	{
		return;
	}
	current = new Node;
	current->data = x;
	current->left = current->right = nullNode;

	if ( x < p1->data )
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
	header->right->color = RED;
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
		if ( x < c->data )
		{
			t = c->right;
			c = c->left;
		}
		else
		{
			t = c->left;
			c = c->right;
		}
		if ( c->data == x )
		{
			toDelete = c;
		}

		// balance

		if ( c->left->color == BLACK && c->right->color == BLACK )
		{
			if ( t->left->color == BLACK && t->right->color == BLACK )
			{
				// Case 1
				c->color = t->color = RED;
				p->color = nullNode->color = BLACK;
			}
			else
			{

				if ( c->data < p->data )
				{
					if ( t->right->color == BLACK )
					{
						// Case 3
						rightRotate( p->right );
					}
				}
				else
				{
					if ( t->left->color == BLACK )
					{
						// Case 3
						leftRotate( p->left );
					}
				}
				// Case 2
				Node* subroot = rotateDown( x, g );
				subroot->color = c->color = RED;
				subroot->left->color = subroot->right->color = BLACK;
			}
		}
		else
		{
			if ( ( c->left->color == RED && c->right->color == RED ) || ( x < c->data ) == ( c->left->color == RED ) )
			{
				// Case 4
				g = p;
				p = c;
				if ( x < c->data )
				{
					t = c->right;
					c = c->left;
				}
				else
				{
					t = c->left;
					c = c->right;
				}
				if ( c->data == x )
				{
					toDelete = c;
				}
			}
			else
			{
				// Case 5
				p = rotateDown( x, p );
				p->color = BLACK;
				c->color = RED;
			}
		}

		// c is still red
	}

	if ( toDelete != nullptr )
	{
		toDelete->data = c->data;
		Node*& uplink = c->data < p->data ? p->left : p->right;
		if ( c->data < p->data )
		{
			p->left = nullNode;
		}
		else
		{
			p->right = nullNode;
		}
		delete c;
	}

	nullNode->color = header->right->color = BLACK;

	if ( nullNode->left != nullNode || nullNode->right != nullNode || nullNode->color == RED ||
		 check( header->right ) == -1 )
	{
		printf( "WARNING: %d\n", x );
	}
}

bool RedBlackTree::find( int x, int& found ) { return find( x, found, header->right ); }
void RedBlackTree::print( RedBlackTree::Node* n, int depth )
{
	if ( n != nullNode )
	{
		print( n->left, depth + 1 );
		for ( int i = 0; i < depth; i++ )
			printf( "  " );
		printf( "%d %s\n", n->data, n->color == BLACK ? "B" : "R" );
		print( n->right, depth + 1 );
	}
}
void RedBlackTree::print() { print( header->right, 0 ); }
int RedBlackTree::check( RedBlackTree::Node* n )
{
	if ( n == nullNode )
	{
		return 0;
	}
	int lb = check( n->left ), rb = check( n->right );
	if ( lb == -1 || rb == -1 || lb != rb )
	{
		return -1;
	}
	return lb + ( n->color == BLACK ? 1 : 0 );
}
