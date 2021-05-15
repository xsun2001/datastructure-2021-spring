#include <stdio.h>

int main()
{
	for ( int i = 0, x = 0; i <= 24; i++ )
	{
		printf( "0x%X,", x );
		x = ( x << 1 ) + 1;
	}
}