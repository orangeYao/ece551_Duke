#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

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
  for (int i=0; i<257; i++)
    cout << i << ", " << char(i) << ", " << array[i] << endl;

  return array;
}

int main()
{
  //uint64_t * counts = readFrequencies("/usr/share/dict/words");
  uint64_t * counts = readFrequencies("/usr/share/dict/words");
  delete[] counts;
  return EXIT_SUCCESS;
}
