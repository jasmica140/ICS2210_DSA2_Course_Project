#ifndef ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H
#define ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H

#include <iostream>
#include "Tree.h"

using namespace std;

class RedBlackTree {
private:
    Tree *RBTree;
    Node *root;

    void balanceTree(Node *k, int& numRotations);
    void leftRotate(Node *x);
    void rightRotate(Node *x);

public:
    RedBlackTree() {
        RBTree = new Tree();
        root = RBTree->leaf;
    }

    void insert(int key);
    void prettyPrint();
    void displayStats();
};

#endif //ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H
