#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <pwd.h>
#include <map>
#include "command.h"
#include "environ.h"
using namespace std;

string findCommandHelper(const char * c_cmd)
{
  char *pPath_origin, *pPath, *pch;
  DIR *d;
  struct dirent *dir;

  pPath_origin = getenv ("PATH");
  pPath = (char *) malloc (strlen(pPath_origin) + 10);
  strcpy(pPath, pPath_origin);

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


string findCommand(char * c_cmd)
{
  if (strchr(c_cmd, '/') != NULL) { // path given by user

    if(access(c_cmd, X_OK) < 0) // path not accessible
      return "";
    else
      return string(c_cmd);

  } else {
    return findCommandHelper(c_cmd); 
  }
}


void parseEnviron(char **env, map <string, string> & env_map)
{
  int i = 0;
  while(environ[i]) {
     char * pch = strchr(environ[i], '=');

     *pch = '\0';
     string key = string(environ[i]);
     string value = string(pch+1);
     *pch = '=';

     env_map[key] = value;
     i++;
  }
}

void cdChangeDir (Command *cmd)
{
	char ** newargv = cmd->getArgv();

	if (newargv[1] == NULL) // cd without argument
    {
      const char *homedir;
	  if ((homedir = getenv("HOME")) == NULL) {
	    homedir = getpwuid(getuid())->pw_dir;
	  }
	  cmd->setArgv(homedir, 1);
    }

	if (chdir (newargv[1]) == -1)
      cout << "cd: " << newargv[1]  <<": No such file or directory" << endl;
}

bool commandPreprocess(Command *cmd)
{
  char ** newargv = cmd->getArgv();
    string cmd_result = findCommand (newargv[0]);
    if (cmd_result == "") {
      cout << "Command " << newargv[0] << " not found" << endl;
      return true;
    }
    cmd->setArgv(cmd_result, 0); // replace command with full path
    return false;
}

bool builtInFunc(Command *cmd, Environ* env)
{
  char ** newargv = cmd->getArgv();

  if (cmd->length() == 0)
	return true;

  if (strcmp(newargv[0], "cd") == 0) {
    cdChangeDir(cmd);
	return true;
  }

  if (strcmp(newargv[0], "set") == 0) {
    if (newargv[1] != NULL && newargv[2] != NULL) // some restrict on [1]
      env->insertMap(newargv[1], newargv[2]);
    return true;
  }

  if (strcmp(newargv[0], "export") == 0) {
    if (newargv[1] != NULL)
    {
      bool exist;
      string key = string(newargv[1]);
      string value = env->searchMap(key, exist);
      if (exist)
        env->insertEnviron(key, value);
    }
    return true;
  }
  return false; 
}

void parseVar (Command *cmd, Environ* env) 
{
  char ** newargv = cmd->getArgv();
  map <string, string> env_map = env->getEnvMap();

  if (cmd->length() > 1 && newargv[1][0] == '$')
  {
    bool exist;
    string value = env->searchMap(string(newargv[1] + 1), exist);
    cmd->setArgv(value, 1);
  }
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
  map <string, string> env_map = env->getEnvMap();

  while(getline (cin, input)) { //check getline error

      if (isExit(input))
        break;

      Command *cmd = new Command (input);

      bool skip_cmd = builtInFunc(cmd, env);

      if (!skip_cmd)
        skip_cmd = commandPreprocess(cmd);
      
      if (skip_cmd) {
        delete cmd;
        promptMyShell();
        continue;
      }

      parseVar(cmd, env);
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
