#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[])
{
  for (int i=1; i<argc; i++)
  {
    cout << argv[i] << endl; 
  }
  return 0;
}
