#include "node.h"
#include <iostream>
using namespace std;

Node *  buildTree(uint64_t * counts) {
  priority_queue_t pq;

  for (unsigned i=0; i<257; i++)
    if (counts[i] != 0)
      pq.push(new Node(i, counts[i]));
 
  while(pq.size()>1)
  {
    Node *n1 = pq.top();
    pq.pop();
    Node *n2 = pq.top();
    pq.pop();

    Node *comb = new Node (n1, n2);
    pq.push(comb);
  }
  
  return pq.top();
}  
