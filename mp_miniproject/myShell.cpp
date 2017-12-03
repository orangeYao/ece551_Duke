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
#include <fcntl.h>
#include "command.h"
#include "environ.h"
#include "execute.h"
#include "preprocess.h"

// Check whether user typed 'exit'
bool isExit(std::string &input)
{
  std::istringstream iss(input);
  std::string chk_exit;
  iss >> chk_exit;
  return (chk_exit == "exit");
}

// Print 'myShell:' and current directory
void promptMyShell()
{
  char * dir_name = get_current_dir_name();
  std::cout << "myShell:" << dir_name << " $ ";
  free(dir_name);
}

// Delimit input by '|', store multiple command in a string array
std::string* delimitPipe (std::string str, size_t &count)
{
  size_t pos;
  std::string * input = new std::string [10];
  while ((pos = str.find("|"))!=std::string::npos) {
    input[count] = str.substr(0, pos);
    str.erase(0, pos + 1);
    count ++;
  }
  input[count] =  str;
  count ++;
  return input;
}

// Take a string array containing multiple input,
// Convert it to a array containing Command pointers
// Then delete the string array
Command ** createCmdArray(std::string *delim_input, size_t count)
{
  Command **cmd_array = new Command *[count]();
  for (size_t i=0; i<count; i++) 
    cmd_array[i] = new Command (delim_input[i]); 
  delete[] delim_input;
  return cmd_array;
}

extern char **environ; //Current environment before start 
int main()
{
  std::string command;
  std::string input;

  promptMyShell();

  Environ *env = new Environ (environ); //Initialize environment 
  while(getline (std::cin, input)) { 
      if (isExit(input))
        break;

      input = parseVar (input, env); // Parse the input, replace $var_name by var_value

	  size_t count = 0; // Delimit input by '|'
      std::string * delim_input = delimitPipe(input, count);
      Command **cmd_array = createCmdArray(delim_input, count);
	
      if (count > 1) {  // Pipe exists
	    for (size_t i=0; i<count; i++)
		  commandPreprocess(cmd_array[i], env); // Search for command 
        setPipe(cmd_array, count, env);

      } else {  // No pipe
        Command * cmd = cmd_array[0];

        // Check if it's built-in functions like cd, set, export 
        bool skip_cmd = builtInFunc(cmd, env, input); 
        if (!skip_cmd)
          skip_cmd = commandPreprocess(cmd, env); 
      
        if (skip_cmd) {
          delete cmd;
          promptMyShell();
          delete[] cmd_array;
          continue;
        }
        executeCommand(cmd, env);
      }
      delete[] cmd_array;
      promptMyShell();
  }
  delete env;
  return EXIT_SUCCESS;
}
