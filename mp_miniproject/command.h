#ifndef __command_H__
#define __command_H__
#include <string>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Command
{
private:
  char **newargv; // argument array
  size_t size; // size of newargv, doubled when not enough
  size_t arg_cnt; // actual length of newargv

  string backslashToSpace(string s)
  {
    string arg = "";
    size_t len = s.length(); 
    for (size_t i=0; i<len; i++)
    {
      if (s[i] != '\\')
        arg += s[i];
      else if (i+1 == len || s[i+1] != ' ')
        arg += s[i];
    }
    return arg;
  }

public:
  Command(): newargv(NULL), size(5), arg_cnt(0) {}

  Command(string input): newargv(NULL), size(5), arg_cnt(0) 
  {
    parseCommand (input);
  }
  // ToDo: copy constructor and assignment operator

  ~Command()
  {
    for (size_t i=0; i<=arg_cnt; i++)
      free(newargv[i]);
    free (newargv);
  }

  size_t length()
  {
	return arg_cnt;
  }

  char ** getArgv()
  {
    return newargv;
  }

  void setArgv(string s, int i)
  {
    // test here
    newargv[i] = (char *) realloc (newargv[i], s.length()+1);
    strcpy(newargv[i], s.c_str());
  }

  void parseCommand (string input)
  {
    newargv = (char **) malloc(size * sizeof(char*));
    size_t len = input.length(), prev = 0;

    for (size_t i=0; i<len; i++)
    {
      if (input[i] == ' ')
      {
        if (i == prev) // previous also (real) space
        {
          prev = i+1;

        } else if (input[i-1] != '\\') {
          string arg = input.substr(prev, i-prev);
          arg = backslashToSpace(arg);

          newargv[arg_cnt] = (char *) malloc(arg.length() + 1);
          strcpy (newargv[arg_cnt], arg.c_str());
          arg_cnt++;
          prev = i+1; 
        }
      }
      else if (i == len-1)
      {
        string arg = input.substr(prev, i-prev+1);
        arg = backslashToSpace(arg);

        newargv[arg_cnt] = (char *) malloc(arg.length() + 1);
        strcpy (newargv[arg_cnt], arg.c_str());
        arg_cnt++;
      }

      if (arg_cnt >= size)
      {
        size *= 2; //double the size
        newargv = (char **) realloc(newargv, size * sizeof(char*));
      }
    }
    newargv[arg_cnt] = NULL;
  }
};
#endif
