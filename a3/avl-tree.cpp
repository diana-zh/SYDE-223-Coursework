#include "avl-tree.h";
#include <algorithm>
#include <iostream>
using namespace std;

int AVLTree::height(Node* n) {
    if (n == nullptr) {
        return -1;
    } else if (n->left == nullptr && n->right == nullptr){
        return 0;
    } else {
        return 1 + ::max(height(n->left), height(n->right));
    }
}

void AVLTree::singleRightRotation (Node* parent, Node* alpha) {
    // input: alpha, A is alpha's left and alpha is A's right
    Node* A = alpha->left;
    alpha->left = A->right;
    A->right = alpha;

    // if alpha is root, make A the new root
    if (parent == alpha) {
        Node** rootAddress = getRootNodeAddress();
        *rootAddress = A;
    } else {
        // alpha's parent takes A as new child
        Node* temp = parent;
        Node** parentPtrAlpha = nullptr;

        do {
            if (alpha->val > temp->val) {
                parentPtrAlpha = &temp->right;
                temp = temp->right;
            } else if (alpha->val < temp->val) {
                parentPtrAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);

        *parentPtrAlpha = A;
    }
}

void AVLTree::singleLeftRotation(Node* parent, Node* alpha) {
    // input: alpha, A is alpha's right and alpha is A's left
    Node* A = alpha->right;
    alpha->right = A->left;
    A->left = alpha;

    // if alpha is root, make A the new root
    if (parent == alpha) {
        Node** rootAddress = getRootNodeAddress();
        *rootAddress = A;
    } else {
        // alpha's parent takes A as new child
        Node* temp = parent;
        Node** parentPtrAlpha = nullptr;

        do {
            if (alpha->val > temp->val) {
                parentPtrAlpha = &temp->right;
                temp = temp->right;
            } else if (alpha->val < temp->val) {
                parentPtrAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);

        *parentPtrAlpha = A;
    }
}

void AVLTree::leftRightRotation(Node* parent, Node* alpha) {
    Node* A = alpha->left;
    singleLeftRotation(parent, A);
    singleRightRotation(parent, alpha);
}

void AVLTree::rightLeftRotation(Node* parent, Node* alpha) {
    Node* A = alpha->right;
    singleRightRotation(parent, A);
    singleLeftRotation(parent, alpha);
}

bool AVLTree::insert(DataType val) {
    // using insert from BST
    bool result = BinarySearchTree::insert(val);
    if (result == false) {
        return false;
    }

    Node* root = getRootNode();

    // if insert is to the root node, it is already balanced
    if (root->val == val) {
        return true;
    }

    // initialize some pointers
    Node* temp;
    temp = root;
    Node* parentTemp;
    Node* alpha = nullptr;

    do {
        parentTemp = temp;
        if (val > temp->val) {
            temp = temp->right;
        } else if (val < temp->val) {
            temp = temp->left;
        }
        // check if the temp parent is unbalanced
        int leftH = height(parentTemp->left);
        int rightH = height(parentTemp->right);
        if (abs(leftH - rightH) >= 2) {
            alpha = parentTemp;
        }
    }
    while (temp->val != val);

    if (!alpha) return true; // done

    // balance based on case
    if (val < alpha->val && val < alpha->left->val) {
        singleRightRotation(root, alpha);
    } else if (val > alpha->val && val > alpha->right->val) {
        singleLeftRotation(root, alpha);
    } else if (val < alpha->val && val > alpha->left->val) {
        leftRightRotation(root, alpha);
    } else if (val > alpha->val && val < alpha->right->val) {
        rightLeftRotation(root, alpha);
    }
    return true;
}

bool AVLTree::remove(DataType val)
{
    return true;
}

