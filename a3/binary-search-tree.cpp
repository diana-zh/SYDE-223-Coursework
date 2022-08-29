#include "binary-search-tree.h"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// initialize val, set left and right children to null
BinarySearchTree::Node::Node(DataType newval)
{
    left = nullptr;
    right = nullptr;
    val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if (n == nullptr) {
        return 0;
    }

    if (n->left == nullptr && n->right == nullptr) {
        return 1;
    } else {
        // recursive call
        int leftDepth = getNodeDepth(n->left);
        int rightDepth = getNodeDepth(n->right);

        // then compare
        if (leftDepth > rightDepth) {
            return leftDepth + 1;
        } else {
            return rightDepth + 1;
        }
    }
}

// initialize BST
BinarySearchTree::BinarySearchTree()
{
    root_ = nullptr;
    size_ = 0;
}

// destructor
BinarySearchTree::~BinarySearchTree()
{
    delete root_;
}

// returns size of BST
unsigned int BinarySearchTree::size() const
{
    return size_;
}

// finds max value
BinarySearchTree::DataType BinarySearchTree::max() const
{
    // if only root exists it is the max value
    if (size_ == 1) {
        return root_->val;
    }

    Node* current = root_; // initialize pointer at root

    // right child is always higher, so traverse right side to find largest val
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->val;
}

// finds min value
BinarySearchTree::DataType BinarySearchTree::min() const
{
    // if only root exists it is the min value
    if (size_ == 1) {
        return root_->val;
    }

    Node* current = root_; // initialize pointer at root

    // left child is always lower, so traverse left side to find lowest val
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_);
}

/*
void BinarySearchTree::print() const
{

}
 */

// return true if node with value val exists in BST, otherwise false
bool BinarySearchTree::exists(DataType val) const
{
    Node* current = root_;

    // validity check
    while (current != nullptr) {

        if (current->val > val) { // left nodes
            current = current->left;
        } else if (current->val < val) { // right nodes
            current = current->right;
        } else {
            return true; // value found
        }
    }
    return false; // value not found
}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    // root node is the first node added
    if (root_ == nullptr) {
        root_ = new Node(val);
        size_++;
        return true;
    } else { // if val is equal to root node then return false
        if (root_->val == val) {
            return false;
        }

        Node* current = root_; // set up pointer starting at root

        while (current->val != val) {
            if (val < current->val) {
                if (current->left == nullptr) {
                    current->left = new Node(val);
                    size_++;
                    return true;
                }
                current = current->left;
            } else if (val > current->val) {
                if (current-> right == nullptr) {
                    current->right = new Node(val);
                    size_++;
                    return true;
                }
                current = current->right;
            }
        }
    }
}

bool BinarySearchTree::remove(DataType val)
{
    // set up nodes and initial boolean statements
    Node* tree = root_;
    Node* current = tree;
    Node* parent = nullptr;

    bool valFound = false;
    bool rightChild = false;

    // check for the desired value to be deleted
    while (current != nullptr) {
        if (current->val == val) {
            valFound = true;
            break;
        } else if (current-> val < val){
            parent = current;
            current = current->right;
            rightChild = true;
        } else {
            parent = current;
            current = current->left;
            rightChild = false;
        }
    }

    // return false if value was not found
    if (valFound == false) {
        return false;
    }

    // if the node does not have children
    if (current->left == nullptr && current->right == nullptr) {
        if (current == tree) { // current is node
            delete root_;
            root_ = nullptr;
            size_--;
            return true;
        }

        if (rightChild == true) {
            parent->right = nullptr;
        } else {
            parent->left = nullptr;
        }

        delete current;
        size_--;
        return true;
    }

    // if there is one child
    if (current->left != nullptr && current->right == nullptr) { // left child
        if (rightChild) { // set everything to left for deletion
            parent->right = current->left;
        } else {
            parent->left = current->left;
        }

        delete current;
        size_--;
        return true;
    } else if (current->left == nullptr && current->right != nullptr) { // right child
        if (rightChild) {
            parent->right = current->right;
        } else {
            parent->left = current->right;
        }

        delete current;
        size_--;
        return true;
    }

    // 2 children requires predecessor method
    if (current->left != nullptr && current->right != nullptr) {
        rightChild = false;

        Node* predecessor = current->left; // set left for now
        Node* predecessorParent = current;

        while (predecessor->right != nullptr) {
            predecessorParent = predecessor;
            predecessor = predecessor->right;
            rightChild = true;
        }

        current->val = predecessor->val;

        // if predecessor is leaf
        if (predecessor->left == nullptr) {
            if (rightChild) {
                predecessorParent->right = nullptr;
            } else {
                predecessorParent->left = nullptr;
            }
        } else { // branch node then
            if (rightChild) {
                predecessorParent->right = predecessor->left;
            } else {
                predecessorParent->left = predecessor->left;
            }
        }

        delete predecessor;
        size_--;
        return true;
    }
}