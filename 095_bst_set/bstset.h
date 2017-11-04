#ifndef __bstSET_H__
#define __bstSET_H__
#include "set.h"
#include <iostream>
using namespace std;

template<typename T>
class BstSet: public Set<T> {
  private:
  class Node {
    public:
    T key;
    Node* left;
    Node* right;

    Node(T t): key(t), left(NULL), right(NULL) {} 
  };
  Node *root;

  public:
  BstSet(): root(NULL){}

  BstSet(const BstSet & bset):root(NULL)
  {
    assignmentHelper(bset.root);
  }

  void assignmentHelper(Node * current)
  {
    if (current != NULL)
    {
      add(current->key);
      assignmentHelper(current->left);
      assignmentHelper(current->right);
    }
  }
  

  ~BstSet()
  {
    freeHelper(root);
  }


  void freeHelper(Node * current)
  {
    if (current != NULL)
    {
      freeHelper(current -> left);
      freeHelper(current -> right);
      delete current;
    }
  }


  bool contains(const T& key) const
  {
    Node * current = root;
    while (current != NULL)
    {
      if (key == current -> key)
        break;
      else if (key < current -> key)
        current = current -> left;
      else
        current = current -> right;
    }
    if (current == NULL)
        return false;

    return true;
  }



  BstSet & operator= (const BstSet & bset)
  {
    if (this == &bset)
      return *this;
    freeHelper(root);
    root = NULL;
    assignmentHelper(bset.root);
    return *this;
  }

  void remove(const T& key)
  {
    root = removeHelper(root, key);
  }


  Node * removeHelper (Node *current, const T& key)
  {
    if (current == NULL)
      return current;

    if (key == current->key)
    {
      if (current->left == NULL)
      {
        Node* tmp = current->right;
        delete current;
        return tmp;
      }
      else if (current->right == NULL)
      {
        Node* tmp = current->left;
        delete current;
        return tmp;
      }
      else
      {
        // right once then going left
        Node *tmp = current->right;
        Node *parent = current;
        bool right_null = true;

        while (tmp->left != NULL)
        {
          parent = tmp;
          tmp = tmp->left;
          right_null = false;
        }
        // tmp now is the leftmost node
        current->key = tmp->key;

        if (right_null)
          parent-> right = tmp->right;
        else
          parent-> left = tmp->right;

        delete tmp;
        return current;
      }
    }
    else if (key < current->key)
    {
      current->left = removeHelper(current->left, key);
      return current;
    }
    else
    {
      current->right = removeHelper(current->right, key);
      return current;
    }
  }



  void add(const T & key)
  {
    root = add(root, key);
  }

  Node * add (Node *current, const T & key)
  {
    if (current == NULL)
    {
      Node *tmp = new Node(key);
      return tmp;
    }
    else if (key == current->key)
    {
      return current;
    }

    if (key < current->key)
      current->left = add(current->left, key);
    else
      current->right = add(current->right, key);

    return current;
  }


};

#endif
