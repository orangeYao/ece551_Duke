#include "bstset.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{

  BstSet<int> z = BstSet<int>();
  z.add(1);
  BstSet<int>  d;
  d.add(2);
  d = z;
  cout << "\n ending \n";
 return 0;


}
