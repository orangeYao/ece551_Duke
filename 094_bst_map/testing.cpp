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
//  cout << a-> lookup(1) << endl;
//  cout << a-> lookup(2) << endl;
//  a -> remove(100);
//  a -> remove(10);
//  a -> remove(-10);
//  a -> remove(1);
//  a -> remove(-1);
//  a -> remove(0);
//  a -> remove(2);
//  a -> add(1,100);
  a -> add(-1,-1);
  a -> add(0,0);
//  a -> remove(2);
//  a -> remove(-1);
  a -> printTesting();
  cout << '\n';

  cout << "\n mid \n";
  BstMap<int, int>  d ( *a);
  d.printTesting();
  //d = *a;
  cout << "\n ending \n";

  delete a;
  a = NULL;


  BstMap<int, int> * b = new BstMap<int, int>();
  b -> add(6, 3);
  b -> add(1, 1);
  b -> add(2, 2);
  b -> add(9, 3);
  b -> add(14, 4);
  b -> add(16, 4);
  b -> add(5, 3);
  b -> add(13, 3);
  b -> add(7, 3);
  b -> add(10, 3);
  b -> add(12, 5);
  b -> add(11, 6);
  b -> remove(14);
  b -> remove(4);
  b -> remove(5);
  b -> remove(6);
  b -> add(6, 3);
  b -> remove(6);
  b -> add(4, 4);
  cout << b-> lookup(4) << endl;
  delete b;

  BstMap<string, string> * c = new BstMap<string, string>();
  c -> add("1","one");
  c -> add("2","two");
  cout << c-> lookup("1") << endl;
  delete c;

  return 0;
}
