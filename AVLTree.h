#ifndef ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H
#define ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H

#include <string>
#include <vector>

#include "Tree.h"

using namespace std;

class AVLTree {

private:
    static Node *rightRotate(Node *y);
    static Node *leftRotate(Node *x);
    Node* insertHelper(Node* node, int key);

public:
    Tree *avlTree;
    Node *root;

    AVLTree() {
        avlTree = new Tree();
        root = nullptr;
    }

    Node* insert(Node* node, int key);
    void prettyPrint() const;
    void displayStats() const;
};


#endif //ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H
