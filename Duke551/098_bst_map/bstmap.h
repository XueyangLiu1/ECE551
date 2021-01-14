#ifndef _BSTMAP_H__
#define _BSTMAP_H__

#include <cstdlib>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      Node * travesal = root;
      while (true) {
        if (key > travesal->key) {
          if (travesal->right == NULL) {
            travesal->right = new Node(key, value);
            break;
          }
          else {
            travesal = travesal->right;
          }
        }
        else {
          if (travesal->left == NULL) {
            travesal->left = new Node(key, value);
            break;
          }
          else {
            travesal = travesal->left;
          }
        }
      }
    }
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * target = findNode(this->root, key);
    if (target == NULL) {
      throw std::invalid_argument("key not found");
    }
    else {
      return target->value;
    }
  }
  virtual void remove(const K & key) { root = removeHelper(root, key); }
  Node * removeHelper(Node * curr, const K & key) {
    if (curr == NULL) {
      return curr;
    }
    if (curr->key == key) {
      if (curr->left == NULL) {
        Node * temp = curr->right;
        delete temp;
        return temp;
      }
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        return temp;
      }
      else {
        K kTarget = minKey(curr->right);
        V vTarget = lookup(kTarget);
        curr->right = removeHelper(curr->right, kTarget);
        curr->key = kTarget;
        curr->value = vTarget;
        return curr;
      }
    }
    else if (key < curr->key) {
      curr->left = removeHelper(curr->left, key);
      return curr;
    }
    else {
      curr->right = removeHelper(curr->right, key);
      return curr;
    }
  }
  K minKey(Node * curr) {
    assert(curr != NULL);
    Node * travesal = curr;
    K temp = curr->key;
    while (travesal != NULL) {
      temp = travesal->key;
      travesal = travesal->left;
    }
    return temp;
  }
  Node * findNode(Node * curr, const K & key) {
    Node * travesal = curr;
    while (travesal != NULL) {
      if (key == travesal->key) {
        return travesal;
      }
      else if (key > travesal->key) {
        travesal = travesal->right;
      }
      else {
        travesal = travesal->left;
      }
    }
    return travesal;
  }
  virtual ~BstMap<K, V>() {}
};
#endif
