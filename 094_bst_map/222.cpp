#include "bstmap.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{

  BstMap<int, int> z = BstMap<int, int>();
  z.add(1,1);
  z.printTesting();
  cout << "\n mid \n";

  BstMap<int, int>  d;

  d.add(2,2);
  d = z;
  cout << "\n ending \n";
  return 0;
}
