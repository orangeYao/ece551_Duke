#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <iostream> 
#include <fstream> 
using namespace std;


void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t * array = new uint64_t [257];

  for (int i=0; i<257; i++)
    array[i] = 0;
  array[256] = 1;

  ifstream is(fname);
  char c;
  while(is.get(c))
  {
    unsigned char cc = c;
    array[int(cc)] ++;
  }
  return array;
}
