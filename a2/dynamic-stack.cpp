#include "dynamic-stack.h"
#include <iostream>
using namespace std;

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -9999; // indicates empty stack

DynamicStack::DynamicStack() {
    // initialize member variables
    size_ = 0;
    capacity_ = 16;
    init_capacity_ = 16;
    items_ = new StackItem[init_capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity){ // constructor
    size_ = 0;
    capacity_ = capacity;
    init_capacity_ = capacity;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack() { // destructor
    delete [] items_;
    items_ = nullptr;
}

bool DynamicStack::empty() const {
    // checks for empty stack
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

int DynamicStack::size() const { // return size of stack
    return size_;
}

void DynamicStack::push(StackItem value) { // push value to stack
    // doubles capacity if needed
    if (size_ >= capacity_) {
        capacity_ = 2 * capacity_;

        StackItem* temp = new DynamicStack::StackItem[capacity_];

        // move elements of stack into temp
        for (int i = 0; i < size_; i++) {
            temp[i] = items_[i];
        }
        // can delete the array now
        delete [] items_;

        // move content from temp into items_
        items_ = temp;
    }
    // if capacity does not need to be enlarged can just add to stack
        items_[size_] = value;
        size_++;
}

DynamicStack::StackItem DynamicStack::pop() { // pop value from stack
    if (size_ == 0) {
        return EMPTY_STACK;
    } else {
        int returnVal = items_[size_ - 1];
        items_[size_ - 1] = NULL;
        size_--;

        // create smaller array if necessary
        if (size_ <= (capacity_ / 4) && (capacity_ / 2 >= init_capacity_)) {
            capacity_ = capacity_ / 2;
        }
        return returnVal;
    }
}

DynamicStack::StackItem DynamicStack::peek() const { // returns value at top of stack without removing
    if (size_ > 0) {
        return items_[size_ - 1];
    } else {
        return EMPTY_STACK;
    }
}

void DynamicStack::print() const {
    // print stack items sequentially
    for (int i = 0; i < size_ - 1; i++) {
        cout << items_[i] << ", ";
    }
}