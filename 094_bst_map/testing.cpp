#include "bstmap.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
  BstMap<int, int> * a = new BstMap<int, int>();
  a -> add(1,1);
  a -> add(2,2);
  a -> add(1,4);
  cout << a-> lookup(1) << endl;
  delete a;
  a = NULL;

  BstMap<int, string> * b = new BstMap<int, string>();
  b -> add(1,"one");
  b -> add(2,"two");
  cout << b-> lookup(1) << endl;
  delete b;

  BstMap<string, string> * c = new BstMap<string, string>();
  c -> add("1","one");
  c -> add("2","two");
  cout << c-> lookup("1") << endl;
  delete c;

  return 0;
}
