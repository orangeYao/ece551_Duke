#ifndef __EXECUTE__
#define __EXECUTE__
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "command.h"
#include "environ.h"

// This file contains all functions about executing executable files
// by fork() + execve()
// These functions also deal with Pipe and Redirection 
//

void redirect(Command *cmd);
void child (Command *cmd, Environ *env);
void setPipe(Command ** cmd_array, size_t count, Environ *env);
void executeCommand (Command *cmd, Environ *env);


// redirect stdin, stdout, stderr to files
void redirect(Command *cmd)
{
  int *red = cmd->getRedirect();
  char ** newargv = cmd->getArgv();

  if (red[0] != 0) { // redirect stdin
    int fd = open(newargv[red[0]], O_RDONLY, S_IRUSR);
	if (dup2(fd, 0) < 0)
	{
	  perror("dup2");
	  exit(EXIT_FAILURE);
	}
    close (fd);
  }

  for (int i=1; i<3; i++) { // redirect stdout, stderr
    if (red[i] != 0) {
      int fd = open(newargv[red[i]], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      if (dup2(fd, i) < 0)
      {
        perror("dup2");
        exit(EXIT_FAILURE);
      }
      close (fd);
    }
  }

  for (int i=0; i<3; i++) // ignore command after <, >, 2>
    if (red[i] != 0)
      newargv[red[i]] = NULL;
}

//The function called by every child after fork
//Take command argument and environment, 
//execve() and error checking
void child (Command *cmd, Environ *env)
{
    char ** newargv = cmd->getArgv();
    char **newenviron = env->getEnviron();
    redirect(cmd);
    execve(newargv[0], newargv, newenviron);
    perror("execve");
    exit(EXIT_FAILURE);
}

// This function takes an array of commands, and lenth of the array
// (N-1) sequential pipes are built among n commands
// N childs are forked
// End of pipes are properly duplicated by dup2() and closed
// For child k, it should read pipe[(k-1)*2], write pipe[i*2+1]
// The first child takes STDIN and last child gives STDOUT
//
// Parent close all pipe ends and wait for all N child
void setPipe(Command ** cmd_array, size_t count, Environ *env)
{
  int * mypipe = new int [2*count];
  pid_t * pids = new pid_t [count]; 

  for (size_t i=0; i<count; i++) {
    if (pipe (mypipe + i*2)) {
      fprintf (stderr, "Pipe failed.\n");
      exit (EXIT_FAILURE);
    }
  }

  for (size_t i=0; i<count; i++) {
    int r = (i-1)*2;
    int w = i*2+1;
    if (!(pids[i] = fork())) {
      if (i != 0) {
        if(dup2 (mypipe[r], 0) < 0) {
          perror("dup1");
          exit(EXIT_FAILURE);
        }
      } 
      
      if (i != count-1){
        if (dup2(mypipe[w], 1) < 0) {
          perror("dup2");
          exit(EXIT_FAILURE);
        }
      } 

      for (size_t j=0; j<count*2; j++)
        close(mypipe[j]);

      child(cmd_array[i], env);
    }
  }
  for (size_t i=0; i<count*2; i++)
    close(mypipe[i]);

  pid_t wpid;
  int status = 0;
  //while ((wpid = wait(&status)) > 0);
  while ((wpid = wait(&status)) > 0)
  {
    if (WIFEXITED(status)) {
      printf("Program exited with status %d\n", WEXITSTATUS(status));
    }
  }

  delete [] pids;
  delete [] mypipe;
  for (size_t i=0; i<count; i++)
    delete cmd_array[i];
}

//Execute single command by fork()
//child calls function child() after fork, 
//parent wait child to finish
void executeCommand (Command *cmd, Environ *env) {
  pid_t cpid, w;
  int status;

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }  
  
  if (cpid == 0) {
    child (cmd, env);
  } else {
    do {  
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
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  delete cmd;
}
#endif
