// hash example
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <list>

using namespace std;
const size_t table_size = 19971;
vector<list<string> > table(table_size);

string reading(string file)
{
//  ifstream t(file);
//  string str((istreambuf_iterator<char>(t)),
//              istreambuf_iterator<char>());

  //string str(static_cast<ostringstream&>(
  //              ostringstream{} << t.rdbuf()));

  ifstream in(file);

  ostringstream ss = ostringstream();
  ss << in.rdbuf();
  return ss.str();
}


size_t hashing (string content)
{
  hash<string> str_hash;
  return str_hash(content);
}


size_t reading2(string file)
{
  ifstream t(file);
  string content((istreambuf_iterator<char>(t)),
              istreambuf_iterator<char>());
  hash<string> str_hash;
  return str_hash(content);
}


void addHashing (string file)
{
  cout << file << endl;
  //size_t hash = hashing(reading(file));
  if (file == "/var/dedup/d000/file495")
    cout << reading(file);
  //hashing(reading(file));
  //table[hash%table_size].push_front(file);

  //cout << hash%table_size << endl;
  //cout << file << endl << endl;
}

// reading all files
static int display_info(const char *fpath, 
		const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
  if (tflag == FTW_SL || tflag == FTW_D)
    return 0;

  //printf("%s\n", fpath);
  addHashing(fpath);
  return 0;
}

void fileTreeWalk (const char* dir)
{
  int flags = 0;
  flags |= FTW_PHYS;

  if (nftw(dir, display_info, 20, flags) == -1) {
       perror("nftw");
       exit(EXIT_FAILURE);
  }   
}


void checkSimilar(list <string>& listing)
{
  size_t size = listing.size();
  for (size_t i=0; i<size; i++)
  {
    string to_check = listing.front();
//    size_t hash_check = hashing(reading(to_check));
    string hash_content = reading(to_check);

    listing.pop_front();

    for (list<string>::iterator it=listing.begin(); it!=listing.end(); ++it)
    {
//      if (hash_check == hashing(reading(*it))) 
        if (hash_content == reading(*it))
        {
          cout << "#Removing " << to_check << " (duplicate of "
              << *it << ").\n";
          cout << "rm " <<  to_check << endl;
          break;
        }
    }
  }   
}


void iterate()
{
  for (size_t i=0; i<table_size; i++)
  {
    if (table[i].size() > 1)
    {
    /*
      cout << i << " , " << table[i].size() << endl;
      while (table[i].size() != 0)
      {
        cout << table[i].front() << endl;
        cout << hashing(reading(table[i].front())) << endl;
        table[i].pop_front();
      }
      cout << "###\n";
      */
      checkSimilar(table[i]);   
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    perror("Give arguments!");
    exit(EXIT_FAILURE);
  }

  for (int i=1; i<argc; i++)
    fileTreeWalk(argv[i]);

  cout << "#!/bin/bash\n";
  return 0;
}
