#include "function.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): 
										remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};


int binarySearchForZero(Function<int, int> * f, int low, int high);



int binarySearchForZero2(Function<int, int> * f, int low, int high)
{
  int l = low;
  int h = high;
  int x, tmp, result;
  if (l == h)
  {
    result = f->invoke(l);
    if (result > 0)
      return h-1;
    else
      return l;
  }

  while (true)
  {
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



unsigned calLimit(int low, int high)
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
    return -10 + arg/100000;
  }
};


void check(Function<int,int> * f,
           int low,
       int high,
       int expected_ans,
       const char * mesg)
{
  unsigned limit = calLimit(low, high);
  Function <int, int>* cf = new CountedIntFn(limit , f, mesg);
  int test_ans = binarySearchForZero(cf, low, high);
  if (expected_ans != test_ans)
  {
	fprintf(stderr,"Wrong answer! \n");
	exit(-1);
  }

}


int main()
{
  int low = 0, high = 150000;
  Function <int, int>* sf = new  SinFunction();
  check(sf, low, high, binarySearchForZero2(sf,low,high), "error in countedF");

  low = 52359; 
  high = 52359;
  check(sf, low, high, binarySearchForZero2(sf,low,high), "error in countedF");
 
  low = 140000; 
  high = 150000;
  check(sf, low, high, binarySearchForZero2(sf,low,high), "error in countedF");

  low = 1000; 
  high = 1500;
  check(sf, low, high, binarySearchForZero2(sf,low,high), "error in countedF");

  low = 149990; 
  high = 150000;
  check(sf, low, high, binarySearchForZero2(sf,low,high), "error in countedF");

  Function <int, int>* consf = new constFunction();
  low = 1000; 
  high = 1500000;
  check(consf, low, high, binarySearchForZero2(consf,low,high), "error in countedF");

  return 0;
}



