#include "election.h"
#include <stdio.h>
//include any other headers you need here...

void errors(const char * e)
{
  perror(e);
  exit(EXIT_FAILURE);
}

state_t parseLine(const char * line) {
  //STEP 1: write me
  if (line == NULL)
    errors("Null input\n");

  state_t s;
  s.population = 0;
  s.electoralVotes = 0;

  int i = 0;
  for (; line[i] != ':'; i++)
  {
    if (i>=MAX_STATE_NAME_LENGTH-1 || line[i]== '\0') // i+1 = max, excced
      errors("incorrect input, part 1\n");
    s.name[i] = line[i];
  }
  s.name[i] = '\0';
  i++;

  for (; line[i] != ':'; i++)
  {
    if (line[i]== '\0'|| line[i] - '0' < 0 || line[i] - '0' > 9)
      errors("incorrect input, part 2\n");
    s.population = s.population* 10 + (line[i] - '0');
  }
  i++;

  for (; line[i] != '\0'; i++)
  {
    if (line[i] - '0' < 0 || line[i] - '0' > 9)
      errors("incorrect input, part 3\n");
    s.electoralVotes = s.electoralVotes* 10 + (line[i] - '0');
  }

  return s;
}



unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  //STEP 2: write me
  int rtn = 0;
  for (int i=0; i<nStates; i++)
    if (voteCounts[i] * 2 > stateData[i].population)
      rtn += stateData[i].electoralVotes;

  return rtn;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  //STEP 3: write me
  for (int i=0; i<nStates; i++)
  {
    double frc = 100.0 * voteCounts[i]/ stateData[i].population;
    if (frc < 50.5 && frc > 49.5 )
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n", 
                        stateData[i].name, frc);
  }
}

void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  //STEP 4: write me
  double largest = 0, frc;
  const char* cptr;
  for (int i=0; i<nStates; i++)
  {
    frc = 100.0 * voteCounts[i]/ stateData[i].population;
    if (frc > largest)
    {
      largest = frc;
      cptr = stateData[i].name;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", 
                        cptr, largest);
}
