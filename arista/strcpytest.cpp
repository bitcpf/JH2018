#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char* argv[] ){
    char * s1 = "STRING1";
    char s2[] = "STRING2";
    char *s3 = NULL;

    s1[ 1 ] = 'P';
    s2[ 1 ] = 'P';

    s3 = static_cast<char*>(malloc(5));
    strcpy(s3, "test");
    s3[1]= 'P';
}

