#ifndef SYDE223_A3_AVL_TREE_H
#define SYDE223_A3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree: public BinarySearchTree
{
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    //The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need
    int height(Node* n);
    void singleRightRotation(Node* parent, Node* alpha);
    void singleLeftRotation(Node* parent, Node* alpha);
    void leftRightRotation(Node* parent, Node* alpha);
    void rightLeftRotation(Node* parent, Node* alpha);
};

#endif //SYDE223_A3_AVL_TREE_H
