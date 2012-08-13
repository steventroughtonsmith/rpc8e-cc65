#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv )
{
	printf( "Padding %s... ", argv[1] );
	FILE *f = NULL;
	int b = 0;
	char *zerobuf;

	f = fopen( argv[1], "a+" );
	b = ftell( f );
	b = (b/128+1) * 128 - b;
	zerobuf = calloc( 1, b );
	fwrite( zerobuf, 1, b, f );
	printf( "%d sectors.\n", (int)ftell( f ) / 128 );
	fclose( f );
	free( zerobuf );
	return 0;
}
