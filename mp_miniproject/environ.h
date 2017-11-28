#ifndef __environ_H__
#define __environ_H__
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <map>
using namespace std;

typedef pair<string, int> pair_v;

#define NOT_FOUND -2       // never set before 
#define NOT_UPDATED_ENV -1 // already set, but not exported

class Environ
{
private:
  map <string, pair_v> env_map; // <varName, pair<varValue, char* of var in newenviron>>
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

  ~Environ ()
  {
    for (size_t i=0; i<var_cnt; i++)
	  free(newenviron[i]); 
	free(newenviron);
  }
  
  size_t length()
  {
    return var_cnt;
  }

  char ** getEnviron()
  {
    return newenviron;
  }

  const map <string, pair_v> & getEnvMap()
  {
    return env_map;
  }

  string searchMap (string key)
  {
    map<string, pair_v>::iterator it;
    it = env_map.find(key);
    if (it != env_map.end()) {
      pair_v result = it->second;
      return result.first;
    } else {
      return "";
    }
  }

  int searchMapIdx (string key)
  {
    map<string, pair_v>::iterator it;
    it = env_map.find(key);
    if (it != env_map.end()) {
      pair_v result = it->second;
      return result.second;
    } else {
      return NOT_FOUND; //
    }
  }

  void enlargeEnviron ()
  {
    if (var_cnt+1 >= size) {
      size *= 2;
      newenviron = (char **) realloc(newenviron, size * sizeof(char*));
	}
	var_cnt++;
	newenviron[var_cnt] = NULL;
  }

  void insertMap (string key, string value) // set
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

  void insertMapIdx (string key, string value, int value_i)
  {
     env_map[key] = make_pair(value, value_i);
  }

  void insertEnviron (string key) // export
  {
    int value_i = searchMapIdx(key);
    if (value_i == NOT_FOUND) // not set before export
      return;

    string value = searchMap(key);
    string to_add = key+ "=" + value;

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
	  if (i >= size)
	  {
	    size *= 2;
		newenviron = (char **) realloc(newenviron, size * sizeof(char*));
	  } 
	}
	newenviron[i] = NULL;
	var_cnt = i;
  }

  void parseEnviron(char **environ)
  {
    int i = 0;
    while(environ[i]) {
      char * pch = strchr(environ[i], '=');

      *pch = '\0';
      string key = string(environ[i]);
      string value = string(pch+1);
      *pch = '=';

      env_map[key] = make_pair(value, i);
      i++;
    }
  }
};
#endif
