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
  //d = *a;

  delete a;
  cout << "\n ending \n";
  return 0;
}
