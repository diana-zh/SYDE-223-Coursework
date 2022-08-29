#include "polynomial.h"
#include "doubly-linked-list.h"
#include <iostream>

using namespace std;

// class constructor; creates matching Polynomial instance along with member DoublyLinkedList instance
// inserts all array values into it
Polynomial::Polynomial(int A[], int size) {
    size_ = size; // size of list

    // doubly linked list is called coefficients
    // insert array values into linked list

    for (int i = 0; i < size_; i++) {
        coefficients.insert(A[i], i);
    }
}

// adds the polynomials together
// take as input a second polynomial *rhs, then apply operation
// return resulting polynomial as new Polynomial instance without changing *this or *rhs polynomials
Polynomial* Polynomial::add(Polynomial* rhs) {
    // the size will depend on whichever polynomial has greater terms
    // create pointer which points to greater list

    int shorterPolynomial = size_;
    int longerPolynomial = size_;

    DoublyLinkedList* longerCoefficient = &coefficients;

    // check which polynomial has more terms, then take that one's size
    if (rhs->size_ < size_) {
        shorterPolynomial = rhs->size_;
    } else if (rhs->size_ > size_) {
        longerPolynomial = rhs->size_;
        longerCoefficient = &rhs->coefficients;
    }

    // dynamically allocate memory to array
    // will store the coefficients in the polynomial, getting them using the select function made in doubly
    int* tempArray = new int[longerPolynomial];

    for (int i = 0; i < shorterPolynomial; i++) {
        tempArray[i] = coefficients.select(i) + rhs->coefficients.select(i);
    }

    // add leftover coefficients in the longer polynomial
    for (int i = shorterPolynomial; i < longerPolynomial; i++) {
        tempArray[i] = longerCoefficient->select(i);
    }

    // create new polynomial instance
    Polynomial* sumPolynomial = new Polynomial(tempArray, longerPolynomial);

    // deallocate memory, delete temp array
    delete [] tempArray;

    return sumPolynomial;
}

// subtract rhs polynomial from this polynomial
// can reuse polynomial add function if rhs is made negative
Polynomial* Polynomial::sub(Polynomial* rhs) {
    for (int i = 0; i < rhs->size_; i++) {
        // use replace function in doubly linked list and select to find coefficient at index
        rhs->coefficients.replace(i, rhs->coefficients.select(i) * -1);
    }

    return add(rhs);
}

// multiply 2 polynomials
Polynomial* Polynomial::mul(Polynomial* rhs) {
    // intialize a temp array to use as a placeholder when creating temp polynomial
    int tempArray[] = {0};

    // first temp polynomial stores terms and multiplies them to rhs
    Polynomial* tempPoly1 = new Polynomial(tempArray, 1);

    for (int i = 0; i < size_; i++) {
        int* tempPointerArr = new int[i + (rhs->size_)]; // dynamically allocate memory to a temp pointer

        // if there is no term of nth degree, enter it as 0
        for (int a = 0; a < i; a++) {
            tempPointerArr[a] = 0;
        }

        // multiply "this"'s terms to "rhs"'s and store as second temp polynomial
        for (int k = 0; k < rhs->size_; k++) {
            tempPointerArr[i + k] = coefficients.select(i) * rhs->coefficients.select(k);
        }

        // add temp polynomials so we can delete the pointer array
        Polynomial tempPoly2 (tempPointerArr, (i + rhs->size_));
        tempPoly1 = tempPoly1->add(&tempPoly2);

        delete [] tempPointerArr;
    }
    return tempPoly1;
}

// print polynomial in specified format
void Polynomial::print() {
    // retrieve all the values using select function from doubly
    for (int i = size_ - 1; i >= 0; i--) { // start backwards
        if (coefficients.select(i) != 0) { // omit zero coefficients
            if (coefficients.select(i) < 0) { // put negative coefficients in brackets
                cout << "(" << coefficients.select(i) << ")" << "x^" << i;
            } else {
                cout << coefficients.select(i) << "x^" << i;
            }

            if (i != 0) { // if i hasn't reached zero yet add "+" between the terms
                cout << " + ";
            }
        }

    }
    cout << "\n";
}