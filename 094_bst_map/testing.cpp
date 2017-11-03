#include "bstmap.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
  BstMap<int, int> * a = new BstMap<int, int>();
  a -> add(1,1);
  a -> add(3,3);
  a -> add(2,2);
  a -> add(4,4);
  a -> add(-1,-1);
  a -> add(0,0);
  a -> add(-2,-2);
  cout << a-> lookup(1) << endl;
  a -> remove(1);
  a -> remove(-1);
  a -> remove(0);
  a -> remove(2);
//  a -> remove(2);
//  a -> remove(-1);
  a -> printTesting();
  cout << '\n';
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
