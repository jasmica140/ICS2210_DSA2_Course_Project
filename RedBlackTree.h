#ifndef ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H
#define ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H
// Red Black Tree implementation in C++
// Author: Algorithm Tutor
// Tutorial URL: https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#include <iostream>

using namespace std;

// data structure that represents a node in the tree
struct RBNode {
    int data; // holds the key
    RBNode *parent; // pointer to the parent
    RBNode *left; // pointer to left child
    RBNode *right; // pointer to right child
    int color; // 1 -> Red, 0 -> Black
};

typedef RBNode *RBNodePtr;

// class RedBlackTree implements the operations in Red Black Tree
class RedBlackTree {
private:
    RBNodePtr root;
    RBNodePtr TNULL;

    // initializes the nodes with appropirate values
    // all the pointers are set to point to the null pointer
    void fixInsert(RBNodePtr k);
    void printHelper(RBNodePtr root, string indent, bool last);

public:
    RedBlackTree() {
        TNULL = new RBNode;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void leftRotate(RBNodePtr x);
    void rightRotate(RBNodePtr x);
    void insert(int key);
    void prettyPrint();
};

#endif //ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H
