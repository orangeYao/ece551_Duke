#include "function.h"
#include <iostream>
#include <math.h>
using namespace std;

int binarySearchForZero(Function<int, int> * f, int low, int high)
{
  int l = low;
  int h = high;
  int x, tmp, result;
  int count = 0;
  if (l == h)
  {
    result = f->invoke(l);
    if (result < 0)
      return h-1;
    else
      return l;
  }


  while (true)
  {
    count ++;
    cout << count << endl;
    x = (l + h)/2;

    result = f->invoke(x);
    if (result > 0)
      h = x;
    else if (result < 0)
      l = x;
    else
      return x;

    if (h - l <= 1)
      return l;

    if (x == high || x== low)
      return x;
  }
}

int calLimit(Function<int, int> * f, int low, int high)
{
  if (low == high)
    return 1;
  else
    return log2(high - low) + 1;
}

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};


class constFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10;
  }
};


int main()
{
  Function <int, int>* sf = new  SinFunction();
  cout << binarySearchForZero(sf, 0, 150000) << endl;
  cout << "limit:" << calLimit(sf, 0, 150000) << endl;
  cout << binarySearchForZero(sf, 100000, 150000) << endl;
  cout << "limit:" << calLimit(sf, 100000, 150000) << endl;
  cout << binarySearchForZero(sf, 52359, 52359) << endl;
  cout << "limit:" << calLimit(sf, 52359, 52359) << endl;

  cout << binarySearchForZero(sf, 1000, 2000) << endl;
  cout << "limit:" << calLimit(sf, 1000, 2000) << endl;

  cout << binarySearchForZero(sf, 1000, 1000) << endl;
  cout << "limit:" << calLimit(sf, 1000, 1000) << endl;

  return 0;
}
