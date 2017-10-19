#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

void readFile(ifstream &fstrm)
{
  vector <string> svec; 
  string tmp;
  while ( getline(fstrm, tmp) )
    svec.push_back(tmp + '\n');

  sort (svec.begin(), svec.end());
  for (vector<string>::iterator it = svec.begin(); it < svec.end(); ++it)
    cout << *it ;
}

void readStd()
{
  vector <string> svec; 
  string tmp;
  while ( getline(cin, tmp) )
    svec.push_back(tmp + '\n');

  sort (svec.begin(), svec.end());
  for (vector<string>::iterator it = svec.begin(); it < svec.end(); ++it)
    cout << *it ;
}


int main(int argc, char ** argv)
{
  ifstream fstrm;
  if (argc == 1)
    readStd();

  for (int i=1; i < argc; i++)
  {
    fstrm.open(argv[i]);
    if (fstrm.is_open())
      return -1;

    readFile(fstrm);
    fstrm.close();
  }

  return 0;
}


/*
 - You should use C++'s streams to read the input (opening std::ifstreams to read files,
   or using std::cin to read from standard input).
 - You should use std::vector to hold the strings that you read in.
 - You should use std::sort to sort the vector
    [see http://www.cplusplus.com/reference/algorithm/sort/ for reference ]
 - You should then print the strings using std::cout.
 - You should NOT use FILE, malloc, realloc, qsort, or printf.

*/
