#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <fstream>
#include <functional>
#include <stdlib.h>
#include "readFreq.h"
#include "node.h"
using namespace std;


void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char* inFile,
			   const char *outFile,
			   const std::map<unsigned,BitString> &theMap ){
  BitFileWriter bfw(outFile);
  writeHeader(&bfw,theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading

  ifstream is(inFile);
  char c;
  while(is.get(c))
  {
    unsigned char cc = c;
    bfw.writeBitString(theMap.find(unsigned(cc))->second);
  }

  bfw.writeBitString(theMap.find(256)->second);
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter

  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }

  map<unsigned,BitString> theMap;

  uint64_t * counts = readFrequencies(argv[1]);
  Node * tree = buildTree (counts);
  delete[] counts;

  BitString empty;
  tree->buildMap(empty, theMap);
  delete tree;

  writeCompressedOutput(argv[1], argv[2], theMap);
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done. 
  //hint 2: you can look at the main from the previous tester for 90% of this


  return EXIT_SUCCESS;
}
