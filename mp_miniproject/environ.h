#ifndef __environ_H__
#define __environ_H__
#include <string>
#include <cstring>
#include <stdlib.h>
#include <map>

// This class maintains all variables set or exported
// map env_map stores all set variables, 
// char **newenviron stores all exported variables, ended with NULL,
// which can be taken as the third argument of execve()
//
// env_map is type <string, <string, int>>, corresponds to 
// <var name, <var value, index in newenviron>>,
// for data not in newenviron, 
// index can be set to NOT_FOUND(-2), NOT_UPDATED_ENV(-1)

typedef std::pair<std::string, int> pair_v;

#define NOT_FOUND -2       // element never set before 
#define NOT_UPDATED_ENV -1 // element already set, but not exported

class Environ
{
private:
  std::map <std::string, pair_v> env_map; // <varName, pair<varValue, char* of var in newenviron>>
  char **newenviron;
  size_t size; // size of newenviron, doubled when not enough
  size_t var_cnt; // actual length of newenviron

public:
  Environ (): newenviron(NULL), size(5), var_cnt(0) {}

  Environ (char ** environ): newenviron(NULL), size(5), var_cnt(0) 
  {
    initEnviron(environ);   
    parseEnviron(environ);   
  }

  Environ (const Environ &env): newenviron(NULL), size(5), var_cnt(0)
  {
    copyHelper(env);
  }

  Environ &operator=(const Environ &env)
  {
    if (this != &env) {
      for (size_t i=0; i<=var_cnt; i++)
        free(newenviron[i]);
      free(newenviron);

      copyHelper(env);
      return *this;
    }
  }

  void copyHelper(const Environ &env)
  {
      size = env.getsize();
      var_cnt = env.length();

      char ** newenviron = env.getEnviron();
	  env_map = env.getEnvMap();

      newenviron = (char **) malloc(size * sizeof(char*));
      for (size_t i=0; i<var_cnt; i++) {
        newenviron[i] = (char *) malloc(strlen(newenviron[i]) + 1);
        strcpy(newenviron[i], newenviron[i]);
      }
      newenviron[var_cnt] = NULL;
  }

  ~Environ ()
  {
    for (size_t i=0; i<var_cnt; i++)
	  free(newenviron[i]); 
	free(newenviron);
  }
  
  size_t length() const
  {
    return var_cnt;
  }

  size_t getsize() const
  {
    return size;
  }

  char ** getEnviron() const
  {
    return newenviron;
  }

  const std::map <std::string, pair_v> & getEnvMap() const
  {
    return env_map;
  }

  //Search map with variable name,
  //return variable value
  std::string searchMap (std::string key)
  {
    std::map<std::string, pair_v>::iterator it;
    it = env_map.find(key);
    if (it != env_map.end()) {
      pair_v result = it->second;
      return result.first;
    } else {
      return "";
    }
  }

  //Search map with variable name,
  //return its corresponding index in char** newenviron,
  //which can be used for updating or exporting variable
  int searchMapIdx (std::string key)
  {
    std::map<std::string, pair_v>::iterator it;
    it = env_map.find(key);
    if (it != env_map.end()) {
      pair_v result = it->second;
      return result.second;
    } else {
      return NOT_FOUND; //
    }
  }

  // Append a NULL to end of char** newenviron 
  // Double its size by realloc() if space is not enough
  void enlargeEnviron ()
  {
    if (var_cnt+1 >= size) {
      size *= 2;
      newenviron = (char **) realloc(newenviron, size * sizeof(char*));
	}
	var_cnt++;
	newenviron[var_cnt] = NULL;
  }

  // Index a variable into Map, called by 'set' command
  // which may or may not already exists
  void insertMap (std::string key, std::string value) // set
  {
    int value_i = searchMapIdx(key);

    if (value_i == NOT_FOUND) {
      env_map[key] = make_pair(value, NOT_UPDATED_ENV);

    } else { 
      env_map[key] = make_pair(value, value_i);
      if (value_i != NOT_UPDATED_ENV) // var already in env
        insertEnviron(key); // export automatically
    }
  }

  // Index a variable with its index in newenviron into map
  // Used when exporting a variable by insertEnviron(),
  // in this case its index in map should be updated 
  void insertMapIdx (std::string key, std::string value, int value_i)
  {
     env_map[key] = make_pair(value, value_i);
  }

  // Insert variable into newenviron, called by 'export'
  // Need to check whether it is in newenviron already, 
  // or whether it has been set (in map)
  void insertEnviron (std::string key) 
  {
    int value_i = searchMapIdx(key);
    if (value_i == NOT_FOUND) // not set before export
      return;

    std::string value = searchMap(key);
    std::string to_add = key+ "=" + value;

    int index = value_i; 
    if (value_i == NOT_UPDATED_ENV) {// append to newenviron
      index = var_cnt;
      insertMapIdx(key, value, index);
      enlargeEnviron();

    } else { // replace in newenviron
      free (newenviron[index]);
    }

    newenviron[index] = (char *) malloc(to_add.length() + 1);
	strcpy(newenviron[index], to_add.c_str());
  }

  // Initialize char** newenviron from given environment, 
  // called by Constructor 
  void initEnviron (char **environ)
  {
	size_t i=0;
	size_t len; 
	newenviron = (char **) malloc(size * sizeof(char*));

	while(environ[i]) {
	  len = strlen(environ[i]); 
	  newenviron[i] = (char *) malloc(len+1);
      strcpy(newenviron[i], environ[i]);
	  i++;
	  if (i >= size) {
	    size *= 2;
		newenviron = (char **) realloc(newenviron, size * sizeof(char*));
	  } 
	}
	newenviron[i] = NULL;
	var_cnt = i;
  }

  // Initialize map from given environment,
  // It parses 'name=value' into <name, <value, index>> 
  // called by Constructor
  void parseEnviron(char **environ)
  {
    int i = 0;
    while(environ[i]) {
      char * pch = strchr(environ[i], '=');

      *pch = '\0';
      std::string key = std::string(environ[i]);
      std::string value = std::string(pch+1);
      *pch = '=';

      env_map[key] = make_pair(value, i);
      i++;
    }
  }
};
#endif
