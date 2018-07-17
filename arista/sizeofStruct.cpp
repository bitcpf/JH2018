#include <iostream>

using namespace std;
struct s { 
   double f; // 8
   int i;    // 4
   char c[3];// 3
   void *p;  // 4
   int x[0]; // 4
};

int main( int argc, char ** argv ) { 

    s test;
    cout << sizeof(test) << endl;

}
