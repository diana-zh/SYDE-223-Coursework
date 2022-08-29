#include "doubly-linked-list.h"
#include <iostream>

using namespace std;

// structure declaration of node
DoublyLinkedList::Node::Node(DataType data)
{
    value = data; // value of node
    next = nullptr; // address of next element, currently null
    prev = nullptr; // address of previous element, currently null
}

// empty doubly linked list constructor, initializes the pointers and size of list
DoublyLinkedList::DoublyLinkedList()
{
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

// doubly linked list destructor
DoublyLinkedList::~DoublyLinkedList()
{
    Node* temp = head_; // intialize temp head and set equal to head
    Node* temp2;

    while (temp != nullptr) { // nothing to delete if temp pointer is null
        temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
}

// returns number of elements nodes in the list
unsigned int DoublyLinkedList::size() const
{
    return size_;
}

// returns capacity (max size)
unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

// if list is empty, return true, otherwise return false
bool DoublyLinkedList::empty() const
{
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

// if list reaches capacity, return true, otherwise return false
bool DoublyLinkedList::full() const
{
    if (size_ == CAPACITY) {
        return true;
    } else {
        return false;
    }
}

// returns value at the given index of the list
// if index is invalid, return value of last element
// if list is empty, any index will be invalid; arbitrary return
DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    int counter = 0;
    Node* temp = head_;

    if (index < 0 || index > size_ - 1) {
        return tail_-> value; // last element / arbitrary value
    }

    while (temp != nullptr) {
        if (counter == index) {
            return temp-> value; // returns value that temp pointer is pointing to
        }

        counter++; // iterate counter until we reach desired index
        temp = temp-> next; // keep moving temp to the next as we iterate
    }
}

// search for given value, follow order from head to tail
// return index of value if found (for first time)
// return size if no value found
unsigned int DoublyLinkedList::search(DataType value) const
{
    int counter = 0;
    Node* temp = head_;

    while (temp != nullptr) {
        if (value == temp->value) {
            return counter; // if the value is found, return the counter which will be equal to index
        } else {
            counter++; // search next node
            temp = temp->next;
        }
    }
    return size_; // if not found
}

// print all elements in list to standard output (check validity)
void DoublyLinkedList::print() const
{
    // check validity
    if (size_ == 0) {
        cout << "There are no elements to print." << endl;
        return;
    }

    cout << "["; // print as [(x)<-->(y)<-->(z)]

    Node* temp = head_;

    while (temp != nullptr) {
        cout << "(" << temp->value << ")";
        temp = temp->next;

        if (temp != nullptr) {
            cout << "<-->";
        }
    }
    cout << "]" << endl;
}

// returns pointer to node at index, return null if index is invalid
DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    int counter = 0;
    Node* temp = head_;

    while (temp != nullptr) {
        if (index == counter) {
            return temp;
        } else {
            counter++;
            temp = temp->next;
        }
    }
}

// insert value into list at given index
// returns true if successful, false otherwise
bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    // validity checks

    if (size_ < CAPACITY) {
        if (index < 0 || index > size_) return false;

        //redirect 2 special cases (insert front and insert back)
        if (index == 0) {
            return insert_front(value);
        }

        if (index == size_) {
            return insert_back(value);
        }

        Node* newNode = new Node(value);
        Node* temp = head_;

        int counter = 0;

        // move temp node from last node before index to index
        while (counter < index - 1) {
            temp = temp->next;
            counter++;
        }

        // move around pointers for the new node
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;

        size_++;
        return true; // successful
    } else {
        return false;
    }
}

// insert value at beginning of list
// true = successful, false = otherwise
bool DoublyLinkedList::insert_front(DataType value)
{
    // validity checks
    if (size_ < CAPACITY) {
        Node* temp = head_;
        head_ = new Node(value);
        head_->prev = nullptr; // need to make new node have a null head pointer

        if (temp != nullptr) {
            temp->prev = head_;
        }

        if (size_ == 0) {
            head_->next = nullptr;
            tail_ = head_; // if list is currently empty
        } else {
            head_->next = temp;
        }

        size_++;
        return true; // successful
    } else {
        return false; // unsuccessful
    }
}

// insert value at end of list
// true = successful, false = otherwise
bool DoublyLinkedList::insert_back(DataType value)
{
    // validity checks
    if (size_ < CAPACITY) {
        if (size_ == 0) {
            return insert_front(value); // redirect to prev function
        } else {
            Node* temp = tail_; // some pointer rearranging using temporary pointer
            tail_ = new Node(value);
            temp->next = tail_;
            tail_->prev = temp;
            tail_->next = nullptr;

            size_++;
            return true; // successful
        }
    } else {
        return false;
    }
}

// deletes value at given index
// true if successful, false otherwise
bool DoublyLinkedList::remove(unsigned int index)
{
    // validity check
    if (size_ == 0 || index < 0 || index > size_ - 1) return false;

    // redirect special remove front and back cases to next 2 functions
    if (index == 0) {
        return remove_front();
    }

    if (index == size_ - 1) {
        return remove_back();
    }

    // set up 2 temporary pointers and counter
    Node *temp = head_;
    Node *temp2;
    int counter = 0;

    while (counter < index - 1) {
        temp = temp->next;
        counter++;
    }

    temp2 = temp->next;
    temp->next = temp2->next;
    temp2->next->prev = temp; // get rid of temp2
    size_--;

    delete temp2;
    return true; // successful
}

// delete value from beginning of list
// true if successful, false if otherwise
bool DoublyLinkedList::remove_front()
{
    // ensure list is not empty first
    if (size_ == 0) return false;

    Node *temp = head_;
    head_ = head_->next;

    if (head_ != nullptr) {
        head_->prev = nullptr; // nullify head if not already
    }
    delete temp;
    size_--;

    // special case if there was only one element - make head and tail pointers null
    if (size_ == 0) {
        head_ = nullptr;
        tail_ = nullptr;
    }
    return true; // successful
}

// delete value from end of list
// true if successful, false if otherwise
bool DoublyLinkedList::remove_back()
{
    // ensure list is not empty first
    if (size_ != 0) {
        if (size_ == 1) return remove_front(); // redirect to avoid having to write out again

        Node* temp = tail_;
        tail_ = temp->prev;
        tail_->next = nullptr;

        delete temp;
        size_--;

        return true; // successful
    } else {
        return false; // unsuccessful
    }
}

// replace value at given index with a given value

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    // validity check
    if (size_ == 0 || index < 0 || index > size_ - 1) return false;

    Node* temp = head_;
    int counter = 0;

    while (head_ != nullptr) {
        if (index == counter) {
            temp->value = value; // replace here
            return true; // successful
        } else{
            counter++;
            temp = temp->next;
        }
    }
}

