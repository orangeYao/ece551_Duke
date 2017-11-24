#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
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


string findCommand(string command)
{
  const char * c_cmd = command.c_str();
  if (strchr(c_cmd, '/') != NULL) { // path given by user

    if(access(c_cmd, X_OK) < 0) // path not accessible
      return "";
    else
      return command;

  } else {
    return findCommandHelper(c_cmd); 
  }
}


int main()
{
  string command, cmd_result;
  pid_t cpid, w;
  int status;
  char *newargv[] = {NULL, NULL};
  char *newenviron[] = {NULL};

  cout << "myShell $ ";

  while (cin>>command && command != "exit") {
      cmd_result = findCommand(command);
      if (cmd_result == "") { // File doesn't exist or not accessible
        cout << "Command " << command << " not found" << endl;
        cout << "myShell $ ";
        continue;
      }

      cpid = fork();
      if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
      }  
      
      if (cpid == 0) {
        newargv[0] = const_cast<char*> (cmd_result.c_str());
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
      cout << "myShell $ ";
  }
  return EXIT_SUCCESS;
}
