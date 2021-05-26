#include "rbt.h"
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
			p1 = rotate( ele, p2 );
		}
		current = rotate( ele, p3 );
		current->color = BLACK;
	}

	header->right->color = BLACK;
}
RedBlackTree::Node* RedBlackTree::rotate( int ele, RedBlackTree::Node* parent )
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
	Node *c = header->right, *t = header->left, *p = header, *g = header, *toDelete = c->data == x ? c : nullptr;
	while ( true )
	{
		if ( c->left == nullNode && c->right == nullNode )
		{
			if ( toDelete != nullptr )
			{
				toDelete->data = c->data;
				if ( x < p->data )
				{
					p->left = nullNode;
				}
				else
				{
					p->right = nullNode;
				}
				delete c;
			}
			header->right->color = BLACK;
			return;
		}

		g = p;
		p = c;
		if ( x < p->data )
		{
			c = p->left;
			t = p->right;
		}
		else
		{
			c = p->right;
			t = p->left;
		}
		if ( x == c->data )
		{
			toDelete = c;
		}

		if ( c->left->color == BLACK && c->right->color == BLACK )
		{
			if ( t->left->color == BLACK && t->right->color == BLACK )
			{
				// Case 1
				p->color = BLACK;
				c->color = t->color = RED;
			}
			else
			{
				// Case 2
				if ( c == p->left && t->left->color == RED )
				{
					rightRotate( p->right );
				}
				else if ( c == p->right && t->right->color == RED )
				{
					leftRotate( p->left );
				}
				else
				{
					t->color = RED;
					t->left->color = t->right->color = BLACK;
				}
				rotate( t->data, g );
				c->color = RED;
				p->color = BLACK;
			}
		}
		else
		{
			Node *nc, *nt;
			if ( x < c->data )
			{
				nc = c->left;
				nt = c->right;
			}
			else
			{
				nc = c->right;
				nt = c->left;
			}
			if ( nc->color == RED )
			{
				// Case 3
				g = p;
				p = c;
				c = nc;
				t = nt;
				if ( x == c->data )
				{
					toDelete = c;
				}
			}
			else
			{
				// Case 4
				rotate( nt->data, p );
				rotate( nc->data, nt );
				c = nt;
			}
		}
	}
}

bool RedBlackTree::find( int x, int& found ) { return find( x, found, header->right ); }
