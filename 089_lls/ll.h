#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <iostream>
using namespace std;

class listException: public exception
{
  virtual const char* what() const throw()
  {
    return "Index exceed list size";
  }

}list_ex;

//YOUR CODE GOES HERE
template <typename T>
class LinkedList {
  private:
  class Node {
    public:
    T data;
    Node* previous;
    Node* next;
    Node(const T& d): data(d), previous(NULL), next(NULL){}
    Node(const T& d, Node* n): data(d), previous(NULL), next(n){}
    Node(const T& d, Node *p,  Node* n): data(d), previous(p), next(n){}
  };
  Node *head;
  Node *tail;
  int size;

  Node* remove (const T &item, Node * current)
  {
    if (current == NULL)
      return NULL;
    if (item == current -> data)
    {
      Node *tmp = current -> next;
      delete current;
      size --;
      return tmp; // stop recursion
    }
    current->next = remove (item, current->next);
    return current;
  }

  public:
  LinkedList(): head(NULL), tail(NULL), size(0){}
  LinkedList(const LinkedList &ll): head(NULL), tail(NULL), size(0)
  {
    Node *tmp = ll.getHead();
    while (tmp != NULL)
    {
      addBack(tmp -> data);
      tmp = tmp -> next;
    }
  } 

  Node * getHead() const
  {
    return head;
  }

  Node * getTail() const
  {
    return tail;
  }

  void addFront(const T& item)
  {
    head = new Node(item, head);
    if (tail == NULL)
      tail = head;
    else 
      head->next->previous = head;

    size ++;
  }

  void addBack(const T& item)
  {
    tail = new Node(item, tail, NULL);
    if (head == NULL)
      head = tail;
    else 
      tail->previous->next = tail;

    size ++;
  }

  bool remove(const T &item)
  {
    int tmp = size;
    head = remove(item, head);
    return !(size == tmp);
  }


  T& operator[] (int index)
  {
    if (index >= size )
      throw list_ex; 

    Node *tmp = head;
    while(index --)
      tmp = tmp->next;
    return tmp->data;
  }

  const T& operator[] (int index) const
  {
    if (index >= size )
      throw list_ex; 

    Node *tmp = head;
    while(index --)
      tmp = tmp->next;
    return tmp->data;
  }

  int find (const T &item) const
  {
    Node *tmp = head;
    int i = 0;
    while (tmp != NULL)
    {
      if (tmp->data == item)
        return i; 
      tmp = tmp->next;
      i++;
    }
    return -1;
  }

  LinkedList & operator=(const LinkedList & ll)
  {
    if (this == & ll)
      return *this;
    while(head != NULL)
    {
      Node *tmp = head->next;
      delete head;
      head = tmp;
    }

    size = 0;
    Node *tmp = ll.getHead();
    while (tmp != NULL)
    {
      addBack(tmp -> data); 
      tmp = tmp -> next;
    }
    return *this;
  }

  ~LinkedList() {
    while(head != NULL)
    {
      Node *tmp = head->next;
      delete head;
      head = tmp;
    }
  }

  int getSize() const
  {
    return int(size);
  }
};



#endif
