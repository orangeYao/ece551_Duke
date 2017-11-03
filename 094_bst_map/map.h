#ifndef __MAP_H__
#define __MAP_H__
#include <stdexcept>

template<typename K, typename V>
class Map {
  private:
  class Node {
    public:
    K key;
    V value;
    Node* left;
    Node* right;

    Node(K k, V v): key(k), value(v), left(NULL), right(NULL) {}
  };
  Node *root;

public:
  virtual void remove(const K& key) = 0;
  virtual void add(const K & key, const V & value) = 0;
  virtual const V & lookup(const K& key) const throw (std::invalid_argument) = 0;


  Map(): root(NULL){};

  virtual ~Map<K,V>()
  {
    freeHelper(root);
  }

  Node * freeHelper(Node * current)
  {
    if (current != NULL)
    {
      freeHelper(current -> left);
      freeHelper(current -> right);
      delete current;
    }
  }

  
  Node * add (Node *current, const K & key, const V & value)
  {
    if (current == NULL)
    {
      Node *tmp = new Node(key, value);
      return tmp; 
    }

    if (key < current->key)
      current->left = add(current->left, key , value);
    else
      current->right = add(current->right, key , value);

    return current;
  }

  Node* lookupHelper(const K& key)
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
      throw std::invalid_argument("key not found!!"); 

	return current;
  }

  Node * removeHelper (Node *current, const K& key)
  {
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
        while (tmp->left != NULL)
        {
          tmp = tmp->left;
        }
        // tmp now is the leftmost node
        current->key = tmp->key;
        current->value = tmp->value;
        delete tmp;
        tmp = NULL;
        return current;
      }
    }
    
    else if (key < current->key)
      current->left = removeHelper(current->left, key);
    else
      current->right = removeHelper(current->right, key);
  }

};

template<typename K, typename V>
void Map<K, V>::add(const K & key, const V & value)
{
  root = add(root, key, value);
}

template<typename K, typename V>
const V & Map<K, V>::lookup(const K& key) const throw (std::invalid_argument)
{
  return lookupHelper(key) -> value;
}

template<typename K, typename V>
void Map<K, V>::remove(const K& key)
{
  removeHelper(root, key);
}

#endif






