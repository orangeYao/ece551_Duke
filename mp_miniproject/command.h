#ifndef __command_H__
#define __command_H__
#include <string>
#include <cstring>
#include <stdlib.h>

// This class stores all information about one line of user input (command)
// User command is parsed into an argument array newargv, which can be
// taken as the second argument of execve() 

class Command
{
private:
  char **newargv; // argument array
  size_t size; // size of newargv, doubled when not enough
  size_t arg_cnt; // actual length of newargv
  int redirect [3]; // Rediction file at which argument, 
                    // for stdin, stdout, stderr. 0 means no redirection 

  // Parse the '\ ' to ' '
  std::string backslashToSpace(std::string s)
  {
    std::string arg = "";
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

  Command(std::string input): newargv(NULL), size(5), arg_cnt(0) 
  {
    parseCommand (input);
  }

  Command(const Command &cmd):  newargv(NULL), size(5), arg_cnt(0)
  {
	copyHelper(cmd);
  }

  Command &operator=(const Command &cmd) 
  {
    if (this != &cmd) {
      for (size_t i=0; i<=arg_cnt; i++)
        free(newargv[i]);
      free (newargv);

	  copyHelper(cmd);
      return *this;
    }
  }

  // Make deep copy, called by copy constructor and
  // assignment operator
  void copyHelper(const Command &cmd)
  {
      size = cmd.getsize();
      arg_cnt = cmd.length();

      int * cmd_rdt = cmd.getRedirect();
      char ** cmd_argv = cmd.getArgv();

      for (int i=0; i<3; i++)
        redirect[i] = cmd_rdt[i];

      newargv = (char **) malloc(size * sizeof(char*));
      for (size_t i=0; i<arg_cnt; i++) {
        newargv[i] = (char *) malloc(strlen(cmd_argv[i]) + 1);
        strcpy(newargv[i], cmd_argv[i]);
      }
      newargv[arg_cnt] = NULL;
  }

  ~Command()
  {
    for (size_t i=0; i<=arg_cnt; i++)
      free(newargv[i]);
    free (newargv);
  }

  int * getRedirect() const
  {
    return (int *) redirect;
  }

  size_t length() const
  {
	return arg_cnt;
  }

  size_t getsize() const
  {
    return size;
  }

  char ** getArgv() const
  {
    return newargv;
  }

  // Change content in newargv[i] to be s
  // e.g. change newargv[0] from 'ls' to '/bin/ls'
  void setArgv(std::string s, int i)
  {
    newargv[i] = (char *) realloc (newargv[i], s.length()+1);
    strcpy(newargv[i], s.c_str());
  }

  // Parse command with <, >, 2>
  // Record redirection file location (ith argument) in redirect[k] = i
  // k = 0,1,2 refers stdin, stdout, stderr respectively
  // Called by parseCommand() only
  void parseRedirect (std::string &input, size_t prev,  size_t i)
  {
    if (input[i] == '<') {
      if (prev != i)
        redirect[0] = arg_cnt+1;
      else
        redirect[0] = arg_cnt;

      input[i] = ' ';
    }

    if (input[i] == '>') {
      if (prev != i)
        redirect[1] = arg_cnt+1;
      else
        redirect[1] = arg_cnt;
      input[i] = ' ';
    }    

    if (input[i] == '2' && i+1 < input.length() 
                        && input[i+1] == '>' && prev == i) {
        redirect[2] = arg_cnt;
        input[i] = ' ';
        input[i+1] = ' ';
    }
  }

  // Parse user command into argument array char** newargv,
  // Each char* stores one argument
  // Argument array end with NULL, to be taken by evecue
  void parseCommand (std::string input)
  {
    newargv = (char **) malloc(size * sizeof(char*));
    memset (redirect, 0, sizeof(redirect));

    size_t len = input.length(); 
    size_t prev = 0; // prev stores place of the end of previous argument

    for (size_t i=0; i<len; i++)
    {
	  parseRedirect(input, prev, i);

      if (input[i] == ' ') {
        if (i == prev) { // previous also a space, continue searching
          prev = i+1;

        } else if (input[i-1] != '\\') {
          std::string arg = input.substr(prev, i-prev);
          arg = backslashToSpace(arg);

          newargv[arg_cnt] = (char *) malloc(arg.length() + 1);
          strcpy (newargv[arg_cnt], arg.c_str());
          arg_cnt++;
          prev = i+1; 
        }

      } else if (i == len-1) {
        std::string arg = input.substr(prev, i-prev+1);
        arg = backslashToSpace(arg);

        newargv[arg_cnt] = (char *) malloc(arg.length() + 1);
        strcpy (newargv[arg_cnt], arg.c_str());
        arg_cnt++;
      }

      if (arg_cnt >= size) {
        size *= 2; //double the size
        newargv = (char **) realloc(newargv, size * sizeof(char*));
      }
    }
    newargv[arg_cnt] = NULL;
  }
};
#endif
