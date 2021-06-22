
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
   for (int i =0; i < 100; i++){
       float b=rand()/(RAND_MAX+1.0);
       cout << 5*b<<endl;
   }
}