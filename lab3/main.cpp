#include <cstdio>

#include "avl.h"
#include "bst.h"
#include "rbt.h"

int n, x, f;
char op[10];

int main()
{
	BinarySearchTree* tree = new RedBlackTree();
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
			bool found = tree->find( x, f );
			printf( "%d\n", found ? f : -1 );
			break;
		}
	}
}