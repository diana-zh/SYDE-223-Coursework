#include "circular-queue.h"
#include <iostream>
using namespace std;

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -9999;

CircularQueue::CircularQueue() {
    // initialize member variables
    size_ = 0;
    capacity_ = 16;
    head_ = 0;
    tail_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::CircularQueue(unsigned int capacity) { // constructor
    capacity_ = capacity;
    size_ = 0;
    head_ = 0;
    tail_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::~CircularQueue() { // destructor
    delete [] items_;
    items_ = nullptr;
}

// returns true if empty queue, false otherwise
bool CircularQueue::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

// returns true if queue is full, false otherwise
bool CircularQueue::full() const {
    if (size_ == capacity_) {
        return true;
    } else {
        return false;
    }
}

int CircularQueue::size() const {
    return size_;
}

// taking argument as enqueue value, inert value at rear of queue if not full
bool CircularQueue::enqueue(QueueItem value) {
    if (size_ == capacity_) {
        tail_ = 0;
        return false;
    } else {
        items_[tail_] = value;
        size_++;
        tail_ = (tail_ + 1) %  capacity_;
        return true;
    }
}

// return item from front of queue and return its value
// return EMPTY_QUEUE constant if empty queue
CircularQueue::QueueItem CircularQueue::dequeue() {
    if (size_ == 0) {
        return EMPTY_QUEUE;
    } else {
        int returnVal = items_[head_];
        items_[head_] = NULL;
        size_--;
        head_ = (head_ + 1) % capacity_;
        return returnVal;
    }
}

// return value at front of queue without removing
// return EMPTY_QUEUE constant if empty queue
CircularQueue::QueueItem CircularQueue::peek() const {
    if (size_ == 0) {
        return EMPTY_QUEUE;
    } else {
        return items_[head_];
    }
}

void CircularQueue::print() const {
    for (int i = 0; i < size_; i++) {
        cout << items_[i] << ", ";
    }
}