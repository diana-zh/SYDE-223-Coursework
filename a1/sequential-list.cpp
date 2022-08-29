#include "sequential-list.h"
#include <iostream>

using namespace std;

SequentialList::SequentialList(unsigned int cap) // intialize sequential list with given elements
{
    data_ = new DataType[cap]; // dynamically allocate memory here
    capacity_ = cap;
    size_ = 0;
}

SequentialList::~SequentialList() // SequentialList destructor (deallocates memory from dynamically allocated data_)
{
    delete [] data_;
    data_ = NULL;
}

unsigned int SequentialList::size() const // return the size to SequentialList
{
    return size_;
}

unsigned int SequentialList::capacity() const // return the capacity to SequentialList
{
    return capacity_;
}

bool SequentialList::empty() const // returns true if SequentialList is empty and false otherwise
{
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

bool SequentialList::full() const // returns true if the list equals capacity (aka full), false otherwise
{
    if (size_ == capacity_) {
        return true;
    } else {
        return false;
    }
}

// returns value at given index of SequentialList. if index invalid, returns last element. if list is empty, return arbitrary value
SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if (index <= size_ - 1 && index >= 0) { // checks that the index is within the array, and will return given index if valid
        return data_[index];
    } else if (size_ == 0){
        return data_[0]; // returns arbitrary data item if the list is empty
    } else {
        return data_[size_ - 1]; // returns the last element of the array if index is invalid
    }
}

// searches for index of a given value and returns it if found. Otherwise will return the size of the list.
unsigned int SequentialList::search(DataType val) const
{
    for (int index = 0; index <= size_ - 1; index++) {
        if (val == data_[index]) {
            return index; // if val equals the value at a specific index, return that index
        }
    }
    return size_;
}

void SequentialList::print() const // print all elements of list
{
    for (int index = 0; index <= size_ - 1; index++) {
        cout << data_[index] << ", ";
    }
}

// insert value into given index of list. Returns true if successful or false if unsuccessful
bool SequentialList::insert(DataType val, unsigned int index)
{
    // filter out invalid cases
    if (capacity_ <= size_ || index > size_) return false; // need at least an extra spot for the additional value to be added & a valid requested position

    size_++; // frees up a spot so value can be added

    for (int index2 = size_ - 1; index2 > index; index2--) { // index2 keeps count of the spot we are at within the SequentialList
        data_[index2] = data_[index2 - 1]; // the value at each index will be filled by whatever value was in the previous index, starting with the last spot
    }

    data_[index] = val; // put val into whatever index was requested
    return true;
}

bool SequentialList::insert_front(DataType val) // insert value at beginning of SequentialList. return true if successful and false if not
{
    if (capacity_ <= size_) return false; // ensures capacity is not less/equal to size

    if (size_ == 0) {
        size_ += 1; // if current size is 0, make a space for it
        data_[0] = val; // puts the val into the first position
        return true;
    }

    size_++; // frees up a spot so the value can be added in the beginning

    for (int index = size_ - 1; index > 0; index--) {
        data_[index] = data_[index - 1]; // the value at each index will be filled by whatever value was in the previous index, starting with the last spot
    }

    data_[0] = val; // put val into the first spot which has been freed up
    return true;
}

bool SequentialList::insert_back(DataType val) // insert value at end of SequentialList. return true if successful and false if unsuccessful
{
    if (capacity_ <= size_) return false; // check if there is enough capacity in the SequentialList. if not, the insert will be unsuccessful
    if (size_ == 0) return insert_front(val);

    size_++; // frees up a spot in the list so the value can be added

    data_[size_ - 1] = val; // insert value in the last position of the list
    return true;
}

bool SequentialList::remove(unsigned int index) // insert value into SequentialList at given index. return true if successful, false if not
{
    // eliminate some invalid cases (empty list, index less than 0, index greater than highest position)
    if (size_ == 0 || index < 0 || index > size_ - 1) return false;

    data_[index] = NULL; // removes value

    for (int index2 = index; index2 < size_ - 1; index2++) { // index2 is the counter, index is the requested position to remove value from
        data_[index2] = data_[index2 + 1]; // starting at the index at which the value was removed, each subsequent spot in the SequentialList will be filled by the spot that was previously the next spot
    }

    size_ -= 1; // decrease size of SequentialList to account for removed value

    return true; // successful removal
}

bool SequentialList::remove_front()
{
    if (size_ == 0) return false; // cannot remove anything from an empty list

    data_[0] = NULL; // removes value from first index

    for (int index = 0; index < size_; index++) {
        data_[index] = data_[index + 1]; // starting at the index at which the value was removed, each subsequent spot in the SequentialList will be filled by the spot that was previously the next spot
    }

    size_ -=1; // decrease size to account for removed value from front

    return true;
}

bool SequentialList::remove_back()
{
    if (size_ == 0) return false; // cannot remove anything from an empty list

    // Removing from the back does not require shifting all the other values
    data_[size_ - 1] = NULL; // removes value from last position of list
    size_ -= 1; // decrease size to account for removed value

    return true;
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (size_ == 0) return false; // empty list

    if (index >= 0 && index <= size_ - 1) { // check index validity before replacing
        data_[index] = val;
    }
    return true;
}

