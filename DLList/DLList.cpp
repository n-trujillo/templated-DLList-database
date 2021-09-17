// implementation of the DLList class

#include "DLList.h"
#include <iostream>
using namespace std;


// first node
DLListNode* DLList::first_node() const {
	return header.next;
}

// last node
const DLListNode* DLList::after_last_node() const{
	return &trailer;
}

// is_empty
bool DLList::is_empty() const {
	return header.next ==  &trailer;
}

DLList::DLList(){
	header.next = &trailer;
	trailer.prev = &header;
}

// first 
int DLList::first() const{
	// dereference and access
	return header.next->obj;
}

// last
int DLList::last() const{
	// dereference and access
	return trailer.prev->obj;
}

// insert_first
void DLList::insert_first(int obj) {
	// create a new node on the heap with specified obj
	DLListNode* newNode = new DLListNode(obj, &header, header.next);

	header.next->prev = newNode;
	header.next = newNode;
}

// insert_last
void DLList::insert_last(int obj) {
	// create new node with specified obj
	DLListNode* newNode = new DLListNode(obj, trailer.prev, &trailer);

	trailer.prev->next = newNode;
	trailer.prev = newNode;
}

// remove_first
int DLList::remove_first() {
	if (is_empty()) {
		throw runtime_error("Empty list.");
	}
	DLListNode *node = header.next;
	node->next->prev = &header;
	header.next = node->next;
	int obj = node->obj;
	delete node;
	return obj;
}

// remove_last
int DLList::remove_last() {
	if(is_empty()) {
		throw runtime_error("Empty list.");
	}
	DLListNode *node = trailer.prev;
	node->prev->next = &trailer;
	trailer.prev = node->prev;
	int obj = node->obj;
	delete node;
	return obj;
}

// insert_before
void DLList::insert_before(DLListNode &p, int obj) {

	// create a newNode with specified obj
	DLListNode* newNode = new DLListNode(obj, p.prev, &p);

	// update newNode's prev to point to newNode
	p.prev->next = newNode;
	// update newNode's next to point back to newNode
	p.prev = newNode;

}

// insert_after
void DLList::insert_after(DLListNode &p, int obj) {

	// create a newNode with specified obj
	DLListNode* newNode = new DLListNode(obj);
	DLListNode* oldNextNode = p.next;

	// update newNode prev
	newNode->prev = &p;
	// update newNode next
	newNode->next = oldNextNode;

	// update newNode's prev to point to newNode
	p.next = newNode;
	// update newNode's next to point back to newNode
	oldNextNode->prev = newNode;
}

// remove_before
int DLList::remove_before(DLListNode &p) {
	int obj = 0;

	if (is_empty()) {
		throw runtime_error("Empty list.");
	}

	// if p is header
	if (&p == first_node()) {
		throw runtime_error("Cannot remove before a header.");
	}

	DLListNode* node = p.prev;
	DLListNode* newPrev = node->prev;

	// update prev
	p.prev = newPrev;
	// update newPrev to point to p
	newPrev->next = &p;

	obj = node->obj;
	delete node;
	return obj;
}

// remove_after
int DLList::remove_after(DLListNode &p) {
	int obj = 0;

	if (is_empty()) {
		throw runtime_error("This is a Empty list.");
	}

	// if p is trailer
	if (&p == after_last_node()->prev) {
		throw runtime_error("Cannot remove after a trailer.");
	}

	DLListNode* node = p.next;
	DLListNode* newNext = node->next;

	// update next
	p.next = newNext;
	// update newNext to point back to p
	newNext->prev = &p;

	obj = node->obj;
	delete node;
	return obj;
}

// copy constructor
DLList::DLList(const DLList& dll) {
	if(dll.is_empty()) {
		header.next = &trailer;
		trailer.prev = &header;
		return;
	}

	header.next = &trailer;
	trailer.prev = &header;
	for (DLListNode *marker = dll.first_node(); marker != dll.after_last_node(); marker = marker->next ) {
		insert_last(marker->obj);
    }
}

// copy assignment operator
DLList& DLList::operator=(const DLList& dll) {
	// self assignment check
	if (this == &dll) {
		return *this;
	}

	if(dll.is_empty()) {
		header.next = &trailer;
		trailer.prev = &header;
		return *this;
	}

	header.next = &trailer;
	trailer.prev = &header;
	for (DLListNode *marker = dll.first_node(); marker != dll.after_last_node(); marker = marker->next ) {
		insert_last(marker->obj);
    }

	return *this;
}


// move contructor
DLList::DLList(DLList&& dll) {
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

// move assignment operator
DLList& DLList::operator=(DLList&& dll) {
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

// destructor
DLList::~DLList() {
	DLListNode *prev_node, *node = header.next;
	while (node != &trailer) {
		prev_node = node;
		node = node->next;
		delete prev_node;
	}
	header.next = &trailer;
	trailer.prev = &header;
}

// output operator
ostream& operator<<(ostream& out, const DLList& dll) {

	for (DLListNode *marker = dll.first_node(); marker != dll.after_last_node(); marker = marker->next )
    {
        out << marker->obj << ", ";
    }

	return out;
}