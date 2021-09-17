// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:

  // contructor
  DLList(){
    header.next = &trailer;
    trailer.prev = &header;
  }

  // copy constructor
  DLList(const DLList<T>& dll) {
    if(dll.is_empty()) {
      header.next = &trailer;
      trailer.prev = &header;
      return;
    }

    header.next = &trailer;
    trailer.prev = &header;
    for (DLListNode<T> *marker = dll.first_node(); marker != dll.after_last_node(); marker = marker->next ) {
      insert_last(marker->obj);
      }
  }

  // move constructor
  DLList(DLList<T>&& dll) {
    if(dll.is_empty()) {
      header.next = &trailer;
      trailer.prev = &header;
      return;
    }

    // move over header and trailer
    header = dll.header;
    trailer = dll.trailer;

    // get nodes to point in correct location
    header.next->prev = &header;
    trailer.prev->next = &trailer;

    // delete the original
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }

  // deconstructor
  ~DLList() {
    DLListNode<T> *prev_node, *node = header.next;
    while (node != &trailer) {
      prev_node = node;
      node = node->next;
      delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
  }

  // copy assignmnet
  DLList<T>& operator=(const DLList<T>& dll){
    if(dll.is_empty()) {
      header.next = &trailer;
      trailer.prev = &header;
      return *this;
    }

    // self assignment check
    if (this == &dll) {
      return *this;
    }

    header.next = &trailer;
    trailer.prev = &header;
    for (DLListNode<T> *marker = dll.first_node(); marker != dll.after_last_node(); marker = marker->next ) {
      insert_last(marker->obj);
      }

    return *this;
  }

  // move assignment
  DLList<T>& operator=(DLList<T>&& dll) {
    if(dll.is_empty()) {
      header.next = &trailer;
      trailer.prev = &header;
      return *this;
    }

    // self assignment check
    if (this == &dll) {
      return *this;
    }

    if(dll.is_empty()) {
      header.next = &trailer;
      trailer.prev = &header;
      return *this;
    }

    // move over header and trailer
    header = dll.header;
    trailer = dll.trailer;

    // get nodes to point in correct location
    header.next->prev = &header;
    trailer.prev->next = &trailer;

    // delete the original
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;

    return *this;
  }

  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }

  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }

  // first
  T first() const{
    return header.next->obj;
  }

  // last
  T last() const{
    return trailer.prev->obj;
  }

  // insert_first
  void insert_first(T obj) {
    // create a new node on the heap with specified obj
    DLListNode<T>* newNode = new DLListNode<T>(obj, &header, header.next);

    header.next->prev = newNode;
    header.next = newNode;
  }

  // remove_first
  T remove_first() {
    if(is_empty()) {
      throw runtime_error("Empty list.");
    }
    DLListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    T obj = node->obj;
    delete node;
    return obj;
  }

  // insert_last
  void insert_last(T obj) {
    // create new node with specified obj
    DLListNode<T>* newNode = new DLListNode<T>(obj, trailer.prev, &trailer);

    trailer.prev->next = newNode;
    trailer.prev = newNode;
  }

  // remove_last
  T remove_last()  {
    if(is_empty()) {
      throw runtime_error("Empty list.");
    }
    DLListNode<T> *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    T obj = node->obj;
    delete node;
    return obj;
  }

  // insert_after
  void insert_after(DLListNode<T> &p, T obj) {
    // create a newNode with specified obj
    DLListNode<T>* newNode = new DLListNode<T>(obj);
    DLListNode<T>* oldNextNode = p.next;

    // update newNode prev
    newNode->prev = &p;
    // update newNode next
    newNode->next = oldNextNode;

    // update newNode's prev to point to newNode
    p.next = newNode;
    // update newNode's next to point back to newNode
    oldNextNode->prev = newNode;
  }

  // insert_before
  void insert_before(DLListNode<T> &p, T obj){

    // create a newNode with specified obj
    DLListNode<T>* newNode = new DLListNode<T>(obj, p.prev, &p);

    // update newNode's prev to point to newNode
    p.prev->next = newNode;
    // update newNode's next to point back to newNode
    p.prev = newNode;

  }

  // remove_after
  T remove_after(DLListNode<T> &p)  {
    T obj;

    if (is_empty()) {
      throw runtime_error("This is a Empty list.");
    }

    // if p is trailer
    if (&p == after_last_node()->prev) {
      throw runtime_error("Cannot remove after a trailer.");
    }

    DLListNode<T>* node = p.next;
    DLListNode<T>* newNext = node->next;

    // update next
    p.next = newNext;
    // update newNext to point back to p
    newNext->prev = &p;

    obj = node->obj;
    delete node;
    return obj;
  }

  // remove_before
  T remove_before(DLListNode<T> &p) {
    T obj;

    if (is_empty()) {
      throw runtime_error("Empty list.");
    }

    // if p is header
    if (&p == first_node()) {
      throw runtime_error("Cannot remove before a header.");
    }

    DLListNode<T>* node = p.prev;
    DLListNode<T>* newPrev = node->prev;

    // update prev
    p.prev = newPrev;
    // update newPrev to point to p
    newPrev->next = &p;

    obj = node->obj;
    delete node;
    return obj;
  }

};

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll){

  for (DLListNode<T> *marker = dll.first_node(); marker != dll.after_last_node(); marker = marker->next )
    {
        out << marker->obj << ", ";
    }

  return out;
}


#endif
