#include "node.h"
using namespace std;

void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  //b.plusOne()
  if (sym == NO_SYM) //not leaf, don't add  
  {
    left -> buildMap(b.plusZero(), theMap);
    right-> buildMap(b.plusOne(), theMap);
  }  
  else 
  {
    theMap.insert(pair<unsigned,BitString> (sym, b));
  }
}



