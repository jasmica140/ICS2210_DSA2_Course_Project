#include "RedBlackTree.h"

// fix the red-black tree
void RedBlackTree::fixInsert(RBNodePtr k){
    RBNodePtr u;
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle
            if (u->color == 1) {
                // case 3.1
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    // case 3.2.2
                    k = k->parent;
                    rightRotate(k);
                }
                // case 3.2.1
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle

            if (u->color == 1) {
                // mirror case 3.1
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    // mirror case 3.2.2
                    k = k->parent;
                    leftRotate(k);
                }
                // mirror case 3.2.1
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 0;
}

void RedBlackTree::printHelper(RBNodePtr root, string indent, bool last) {
    // print the tree structure on the screen
    if (root != TNULL) {
        cout<<indent;
        if (last) {
            cout<<"R----";
            indent += "     ";
        } else {
            cout<<"L----";
            indent += "|    ";
        }

        string sColor = root->color?"RED":"BLACK";
        cout<<root->data<<"("<<sColor<<")"<<endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
    // cout<<root->left->data<<endl;
}


// rotate left at node x
void RedBlackTree::leftRotate(RBNodePtr x) {
    RBNodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// rotate right at node x
void RedBlackTree::rightRotate(RBNodePtr x) {
    RBNodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}


// insert the key to the tree in its appropriate position
// and fix the tree
void RedBlackTree::insert(int key) {
    // Ordinary Binary Search Insertion
    auto node = new RBNode;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1; // new node must be red

    RBNodePtr y = nullptr;
    RBNodePtr x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // y is parent of x
    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    // if new node is a root node, simply return
    if (node->parent == nullptr){
        node->color = 0;
        return;
    }

    // if the grandparent is null, simply return
    if (node->parent->parent == nullptr) {
        return;
    }

    // Fix the tree
    fixInsert(node);
}


// print the tree structure on the screen
void RedBlackTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
}