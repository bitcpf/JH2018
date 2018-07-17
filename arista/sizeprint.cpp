
#include <stdio.h>
#include <string.h>



/* Find the size */
int main() {
   const char *s1 = "hello";
   char *s3 = "hello";
   char s2[] = "world";

   printf( "sizeof s1 : %ld sizeof s2 : %ld\n", sizeof(s1), sizeof(s2) );
   printf( "sizeof s3 : %ld\n", sizeof(s3) );
   printf( "lenof s2 : %ld\n", strlen(s2) );
}
