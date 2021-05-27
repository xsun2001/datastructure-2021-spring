#include <cstdio>

#include "avl.h"
#include "bst.h"
#include "rbt.h"

int n, x, f;
char op[10];

int main( int argc, char** argv )
{
	BinarySearchTree* tree;
	if ( argc > 1 && argv[1][0] == '1' )
	{
		tree = new AvlTree();
	}
	else
	{
		tree = new RedBlackTree();
	}

	scanf( "%d", &n );
	while ( n-- )
	{
		scanf( " %s %d", op, &x );
		switch ( op[0] )
		{
		case 'A':
			tree->insert( x );
			break;
		case 'B':
			tree->remove( x );
			break;
		case 'C':
			printf( "%d\n", tree->find( x, f ) ? f : -1 );
			break;
		case 'D':
			tree->print();
			break;
		}
	}
}