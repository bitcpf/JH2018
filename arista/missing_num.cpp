#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

using namespace std;

int a[] = { 4,5,7,8,9 };
int b[] = { 4,5,6,8,9,10};
int c[] = { 4,6,7,8,9,10};
int d[] = { 4,5,6,7,9,10};
int e[] = { 4,5,6,7,8,9};

int findMissing( int* a, int len ) {


    printf("%s\n", "PCUI");

    int pre = *a;
    for(int i = 1; i < len; i ++)
    {
        if(*(a+i) != pre + 1) return pre + 1;
        pre = *(a+i);
    }



    return *(a-1+len) + 1;

}

int main() {

   assert( findMissing( a, 5 ) == 6 );
   assert( findMissing( b, 6 ) == 7 );
   assert( findMissing( c, 6 ) == 5 );
   assert( findMissing( d, 6 ) == 8 );
   assert( findMissing( e, 6 ) == 10 );

   return 0;
}
