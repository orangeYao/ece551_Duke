#ifndef __environ_H__
#define __environ_H__
#include <string>
#include <string.h>
#include <stdlib.h>
#include <map>
using namespace std;

class Environ
{
private:
  map <string, string> env_map;
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

  const map <string, string> & getEnvMap()
  {
    return env_map;
  }

  void insertMap (string key, string value)
  {
    env_map[key] = value;
  }

  string searchMap (string key, bool &exist)
  {
    map<string, string>::iterator it;
    it = env_map.find(key);
    if (it != env_map.end()) {
      exist = true;
      return it->second;
    } else {
      exist = false;
      return "";
    }
  }

  void insertEnviron (string key, string value)
  {
    if (var_cnt+1 >= size) {
      size *= 2;
      newenviron = (char **) realloc(newenviron, size * sizeof(char*));
	}
	string to_add = key+ "=" + value;
	newenviron[var_cnt] = (char *) malloc(to_add.length() + 1);
	strcpy(newenviron[var_cnt], to_add.c_str());

	var_cnt++;
	newenviron[var_cnt] = NULL;
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

      env_map[key] = value;
      i++;
     //printf("%s\n", environ[i]); // prints in form of "variable=value"
    }
  }
};
#endif
