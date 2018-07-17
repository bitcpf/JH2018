#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int a[] = { 4,5,7,8,9 };
int b[] = { 4,5,6,8,9,10};
int c[] = { 4,6,7,8,9,10};
int d[] = { 4,5,6,7,9,10};
int e[] = { 4,5,6,7,8,9};


int findMissing( int* a, int len ) {
    printf("%d", a);



    return 0;

}

main() {

   assert( findMissing( a, 5 ) == 6 );
   assert( findMissing( b, 6 ) == 7 );
   assert( findMissing( c, 6 ) == 5 );
   assert( findMissing( d, 6 ) == 8 );
   assert( findMissing( e, 6 ) == 10 );
}
