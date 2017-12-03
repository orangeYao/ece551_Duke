#ifndef __PREPROCESS__
#define __PREPROCESS__
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "command.h"
#include "environ.h"

// This file include all functions about input processing,
// which includes converting input into series of argument,
// parse argument value by its name, find full path of command in PATH...
// 
// This file also include built-in functions like cd, set, export,
// which do not need fork() and execve(). 
//

std::string findCommandHelper(const char * c_cmd, Environ *env);
std::string findCommand(char * c_cmd, Environ *env);
void cdChangeDir (Command *cmd, Environ* env);
bool commandPreprocess(Command *cmd, Environ *env);
bool isValidName(char c);
void set(Command *cmd, Environ* env, std::string input);
bool builtInFunc(Command *cmd, Environ* env, std::string input);
std::string parseVar (std::string input, Environ* env);

// Search $PATH for a command without '/', like ls, pwd
// Called by findCommand() only
// The PATH is stored in Environ object *env
std::string findCommandHelper(const char * c_cmd, Environ *env)
{
  char *pPath, *pch;
  DIR *d;
  struct dirent *dir;

  std::string path = env->searchMap("PATH");

  pPath = (char *) malloc (path.length() + 10);
  strcpy(pPath, path.c_str());

  pch = strtok (pPath,":");

  while (pch != NULL) {
    d = opendir(pch);
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, c_cmd) == 0) {
          closedir(d);
          std::string rtn = std::string(pch) + "/" + std::string(c_cmd);
          free(pPath);
          return rtn; 
        }
      }
      closedir(d);
    }
    pch = strtok (NULL, ":");
  }
  free(pPath);
  return "";
}

// For a command, return corresponding executable file 
// Return "" when command does not exist
// Call findCommandHelper() when path '/' not given by user
std::string findCommand(char * c_cmd, Environ *env)
{
  if (strchr(c_cmd, '/') != NULL) { // path given by user
    if(access(c_cmd, X_OK) < 0) // path not accessible
      return "";

    struct stat sb;
    if (stat(c_cmd, &sb) == 0 && !S_ISREG(sb.st_mode))
      return "";

    return std::string(c_cmd);
  
  }  else {
    if (!strcmp(c_cmd, ".") || !strcmp(c_cmd, "..")) 
      return "";

    return findCommandHelper(c_cmd, env); 
  }
}


// Implement command 'cd', go to $HOME when argument not given
//   stay in same place when $HOME is not a valid Dir
void cdChangeDir (Command *cmd, Environ* env)
{
  char ** newargv = cmd->getArgv();

  if (newargv[1] == NULL) {// cd without argument
    std::string home = env->searchMap("HOME");
    if (home == "") 
      home = ".";
    cmd->setArgv(home, 1);
  }

  if (chdir (newargv[1]) == -1)
    std::cout << "cd: " << newargv[1]  <<": No such file or directory\n";
}

// Return true when command not found by findCommand(), 
//   the command will be skipped 
// Return false otherwise, 
//   update Command object and command will be executed in child process
bool commandPreprocess(Command *cmd, Environ *env)
{
  char ** newargv = cmd->getArgv();
  std::string cmd_result = findCommand (newargv[0], env);
  if (cmd_result == "") {
    std::cout << "Command " << newargv[0] << " not found\n";
    return true;
  }
  cmd->setArgv(cmd_result, 0); // replace command with full path
  return false;
}

// Whether a char is valid for variable name 
bool isValidName(char c)
{
  if (c >= 'a'  && c <= 'z')
    return true;
  if (c >= 'A'  && c <= 'Z')
    return true;
  if (c >= '0'  && c <= '9')
    return true;
  if (c == '_')
    return true;

  return false;
}

// Implement the 'set' command: set var value
// Update the map in Environ object by calling insertMap()
void set(Command *cmd, Environ* env, std::string input)
{
  char ** newargv = cmd->getArgv();
  if (newargv[1] == NULL)
    return;

  std::string var = newargv[1];
  size_t len = var.length();

  for (size_t i=0; i<len; i++)
    if (!isValidName(var[i])) {
      std::cout << "Var name in set is not valid!!\n";
      return;
    }

  if (newargv[2] == NULL) {
    env->insertMap(newargv[1], "");
    return; 
  }

  size_t value_i = input.find(std::string(newargv[1])) + strlen(newargv[1]);
  while (input[value_i] == ' ')
    value_i ++;  // skip spaces, find start index of value

  env->insertMap(newargv[1], input.substr(value_i));
}


// Implement empty command, cd, set, export
bool builtInFunc(Command *cmd, Environ* env, std::string input)
{
  char ** newargv = cmd->getArgv();

  if (cmd->length() == 0)
	return true;

  if (strcmp(newargv[0], "cd") == 0) {
    cdChangeDir(cmd, env);
	return true;
  }

  if (strcmp(newargv[0], "set") == 0) {
    set(cmd, env, input);
    return true;
  }

  if (strcmp(newargv[0], "export") == 0) {
    if (newargv[1] != NULL) {
      std::string key = std::string(newargv[1]);
      env->insertEnviron(key);
    }
    return true;
  }
  return false; 
}

// Parse variables starting with $ in input 
// like $PATH, $user_defined
std::string parseVar (std::string input, Environ* env)
{
  size_t len = input.length();
  bool at_var = false;
  std::string rtn = "", var = "";

  for (size_t i=0; i<len; i++) {
    if(input[i] == '$') {
      at_var = true;
      continue;
    }

    if (!at_var) {
      rtn += input[i];
    } else if (isValidName(input[i])) {
      var += input[i];
    } else {
      at_var = false;
      rtn += env->searchMap(var);
      var = ""; 
      rtn += input[i]; 
    }
  }
  if (var != "")
    rtn += env->searchMap(var);
  return rtn;
}
#endif
