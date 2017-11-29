#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <map>
#include "command.h"
#include "environ.h"
using namespace std;

string findCommandHelper(const char * c_cmd, Environ *env)
{
  char *pPath, *pch;
  DIR *d;
  struct dirent *dir;

  string path = env->searchMap("PATH");

  pPath = (char *) malloc (path.length() + 10);
  strcpy(pPath, path.c_str());

  pch = strtok (pPath,":");

  while (pch != NULL) {
    d = opendir(pch);
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, c_cmd) == 0) {
          closedir(d);
          string rtn = string(pch) + "/" + string(c_cmd);
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


string findCommand(char * c_cmd, Environ *env)
{
  if (strchr(c_cmd, '/') != NULL) { // path given by user
    if(access(c_cmd, X_OK) < 0) // path not accessible
      return "";

    struct stat sb;
    if (stat(c_cmd, &sb) == 0 && !S_ISREG(sb.st_mode))
      return "";

    return string(c_cmd);
  
  }  else {
    if (!strcmp(c_cmd, ".") || !strcmp(c_cmd, "..")) 
      return "";

    return findCommandHelper(c_cmd, env); 
  }
}


void cdChangeDir (Command *cmd, Environ* env)
{
  char ** newargv = cmd->getArgv();

  if (newargv[1] == NULL) // cd without argument
  {
    string home = env->searchMap("HOME");
    if (home == "") 
      home = ".";
    cmd->setArgv(home, 1);
  }

  if (chdir (newargv[1]) == -1)
    cout << "cd: " << newargv[1]  <<": No such file or directory" << endl;
}

bool commandPreprocess(Command *cmd, Environ *env)
{
  char ** newargv = cmd->getArgv();
  string cmd_result = findCommand (newargv[0], env);
  if (cmd_result == "") {
    cout << "Command " << newargv[0] << " not found" << endl;
    return true;
  }
  cmd->setArgv(cmd_result, 0); // replace command with full path
  return false;
}

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


void set(Command *cmd, Environ* env, string input)
{
  char ** newargv = cmd->getArgv();
  if (newargv[1] == NULL)
    return;

  string var = newargv[1];
  size_t len = var.length();

  for (size_t i=0; i<len; i++)
    if (!isValidName(var[i])) {
      cout << "Var name in set is not valid!!\n";
      return;
    }

  if (newargv[2] == NULL)
  {
    env->insertMap(newargv[1], "");
    return; 
  }

  size_t found = input.find(string(newargv[2]));
  env->insertMap(newargv[1], input.substr(found));
}


bool builtInFunc(Command *cmd, Environ* env, string input)
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
      string key = string(newargv[1]);
      env->insertEnviron(key);
    }
    return true;
  }
  return false; 
}

string parseVar (string input, Environ* env)
// interpret variables starting with $ in input 
{
  size_t len = input.length();
  bool at_var = false;
  string rtn = "", var = "";

  for (size_t i=0; i<len; i++)
  {
    if(input[i] == '$')
    {
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


bool isExit(string &input)
{
  istringstream iss(input);
  string chk_exit;
  iss >> chk_exit;
  return (chk_exit == "exit");
}

void promptMyShell()
{
  char * dir_name = get_current_dir_name();
  cout << "myShell:" << dir_name << " $ ";
  free(dir_name);
}

extern char **environ;
int main()
{
  string command;
  pid_t cpid, w;
  int status;
  string input;

  promptMyShell();

  Environ *env = new Environ (environ);
  char **newenviron = env->getEnviron();
  map <string, pair_v> env_map = env->getEnvMap();

  while(getline (cin, input)) { //check getline error

      if (isExit(input))
        break;

      input = parseVar (input, env);
      Command *cmd = new Command (input);

      bool skip_cmd = builtInFunc(cmd, env, input);

      if (!skip_cmd)
        skip_cmd = commandPreprocess(cmd, env); // here, change envirno
      
      if (skip_cmd) {
        delete cmd;
        promptMyShell();
        continue;
      }

      char ** newargv = cmd->getArgv();

      cpid = fork();
      if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
      }  
      
      if (cpid == 0) {
        execve(newargv[0], newargv, newenviron);
        perror("execve");
        exit(EXIT_FAILURE);

      } else {
        w = waitpid(0, &status, WUNTRACED | WCONTINUED);
        if (w == -1) {
		  perror("waitpid");
		  exit(EXIT_FAILURE);
		} 
	    if (WIFEXITED(status)) {
		  printf("Program exited with status %d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
          printf("Program was killed by signal %d", WTERMSIG(status));
		}
      }
      promptMyShell();
  	  delete cmd;
  }
  delete env;
  return EXIT_SUCCESS;
}
