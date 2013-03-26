// bin2h.c
// from: http://read.pudn.com/downloads65/sourcecode/embed/230808/bin2h.c__.htm
// tweaks to functionality by ccfreak2k

#include <stdio.h>


main( int argc, char * argv[])
   {
   FILE * in, * out;
   unsigned uCount, uLen;
   unsigned char ucData;

   if((argc < 3)||(argc > 4)) {
      printf( "Convert binary file to C unsigned char array\n");
      printf( "USE: bin2h <infile> <outfile> [arrayname] \n");
      return -1;
      }

   in = fopen( argv[ 1], "rb");
   if( in == NULL) { 
      printf( "Cannot find input file '%s'..\n", argv[ 1]);
      return -1;
      }

   out = fopen( argv[ 2], "wb");
   if( out == NULL) { 
      printf( "Cannot create output file '%s'..\n", argv[ 2]);
      return -1;
      }

   fseek( in, 0, SEEK_END);
   uLen = ftell( in);
   fseek( in, 0, SEEK_SET);

   fprintf( out, "// filename: %s\n", argv[ 1]);
   fprintf( out, "\n\n");
   fprintf( out, "unsigned char code %s[%u] = {\n   ", (argc == 3 ? "bin" : argv[ 3]), uLen);
   uCount = 0;
   while( 1) {
      if( 1 != fread( &ucData, 1, 1, in))
         break;
      if( uCount)
         fprintf( out, ", ");
      uCount++;
      if( uCount % 16 == 0)
         fprintf( out, "\n   ");
      fprintf( out, "0x%02X", ucData);
      }
   fprintf( out, "\n   };\n");

   fclose( in);
   fclose( out);
   }
