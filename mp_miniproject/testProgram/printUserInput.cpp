#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[])
{
  string name;
  while(getline(cin, name))
  {
    if (name == "exit")
      break;
    cout << name << endl;
  }
  return 0;
}
