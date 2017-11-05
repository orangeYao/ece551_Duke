// hash example
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <streambuf>

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

using namespace std;

string reading(string file)
{
  ifstream t(file);
  string str((istreambuf_iterator<char>(t)),
              istreambuf_iterator<char>());
  return str;
}


size_t hashing (string content) 
{
  hash<string> str_hash;
  return str_hash(content);
}













int main()
{
  

  return 0;
}


