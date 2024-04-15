#include "RedBlackTree.h"

#include <iostream>
#include <numeric>

// rotate left at node x
void RedBlackTree::leftRotate(Node *x) {

    Node *y = x->right;    // Set y to be the right child of x
    x->right = y->left;    // Make y's left child new right child of x

    // If y's left child is not leaf node, update its parent
    if (y->left != RBTree->leaf) {
        y->left->parent = x;
    }

    y->parent = x->parent;    // Update y's parent to be x's parent

    // If x is root, update root of tree
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) { // If x is left child of its parent, make y left child
        x->parent->left = y;
    } else { // Otherwise, make y the right child
        x->parent->right = y;
    }

    y->left = x;      // Make x left child of y
    x->parent = y;    // Update x's parent to be y
}

// rotate right at node x
void RedBlackTree::rightRotate(Node *x) {

    Node *y = x->left;     // Set y to be left child of x
    x->left = y->right;    // Make y's right child new left child of x

    // If y's right child is not leaf node, update its parent
    if (y->right != RBTree->leaf) {
        y->right->parent = x;
    }

    y->parent = x->parent;    // Update y's parent to be x's parent

    // If x is root, update root
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) { // If x is right child of its parent, make y right child
        x->parent->right = y;
    } else { // Otherwise, make y left child
        x->parent->left = y;
    }

    y->right = x;     // Make x right child of y
    x->parent = y;    // Update x's parent to be y
}


// fix Red-Black Tree after insertion to maintain its properties
void RedBlackTree::balanceTree(Node *node, int& numRotations) {
    Node *crazyUncleJo; // pointer to uncle node

    // while node's parent is red
    while (node->parent->colour == 1) {
        // if node's parent is right child of its parent
        if (node->parent == node->parent->parent->right) {
            crazyUncleJo = node->parent->parent->left; // set uncle to be left child of grandparent

            // if uncle is red
            if (crazyUncleJo->colour == 1) {
                crazyUncleJo->colour = 0;           // change uncle's colour to black
                node->parent->colour = 0;           // change parent's colour to black
                node->parent->parent->colour = 1;   // change grandparent's colour to red
                node = node->parent->parent;        // move up to grandparent node
            } else { // uncle is black
                // if node is left child of its parent
                if (node == node->parent->left) {
                    node = node->parent;            // move to parent node
                    rightRotate(node);           // perform right rotation at parent node
                }
                node->parent->colour = 0;           // change parent's colour to black
                node->parent->parent->colour = 1;   // change grandparent's colour to red
                leftRotate(node->parent->parent); // perform left rotation at grandparent node
                numRotations++;                     // increment number of rotations performed
            }
        } else { // if node's parent is left child of its parent
            crazyUncleJo = node->parent->parent->right; // set uncle to be right child of grandparent

            // if uncle is red
            if (crazyUncleJo->colour == 1) {
                crazyUncleJo->colour = 0;           // change uncle's colour to black
                node->parent->colour = 0;           // change parent's colour to black
                node->parent->parent->colour = 1;   // change grandparent's colour to red
                node = node->parent->parent;        // move up to grandparent node
            } else { // uncle is black
                // if node is right child of its parent
                if (node == node->parent->right) {
                    node = node->parent;            // move to parent node
                    leftRotate(node);            // perform left rotation at parent node
                }
                node->parent->colour = 0;               // change parent's colour to black
                node->parent->parent->colour = 1;       // change grandparent's colour to red
                rightRotate(node->parent->parent);   // perform right rotation at grandparent node
                numRotations++;                     // increment number of rotations performed
            }
        }
        // break loop if node is root
        if (node == root) {
            break;
        }
    }
    root->colour = 0; // set root's colour to black to maintain Red-Black Tree property
}

// Insert the key into the tree in its appropriate position
void RedBlackTree::insert(int key) {

    // create new node with left and right children as leaf nodes
    auto node = new Node(RBTree->leaf, RBTree->leaf, 1); // new node must be red
    node->parent = nullptr;                 // initially new node has no parent
    node->key = key;                        // assign key value to new node

    Node *newNode = root;                   // start from the root of the tree
    int numSteps = 0;                       // to count steps taken during insertion
    int numRotations = 0;                   // to count rotations performed during insertion

    // traverse tree to find position for the new node
    while (newNode != RBTree->leaf) {
        node->parent = newNode;             // set parent of new node as current node
        if (node->key < newNode->key) {     // if key of new node < key of current node
            newNode = newNode->left;        // move to left child
        } else {
            newNode = newNode->right;       // otherwise, move to right child
        }
        numSteps++;                         // increment step count
    }

    // attach new node to its parent based on its key value
    if (node->parent == nullptr) {
        root = node;                        // if new node's parent is null, it becomes the root of the tree
    } else if (node->key < node->parent->key) {
        node->parent->left = node;          // if key < parent's key, node becomes left child
    } else {
        node->parent->right = node;         // otherwise, node becomes right child
    }

    // if parent of new node is null, it's the root
    if (node->parent == nullptr) {
        node->colour = 0; // Set colour to black
        RBTree->steps.push_back(numSteps);              // record number of steps
        RBTree->rotations.push_back(numRotations);      // record number of rotations performed
        return;
    } else if (node->parent->parent == nullptr) {       // if grandparent is null, tree is already balanced
        RBTree->steps.push_back(numSteps);              // record number of steps
        RBTree->rotations.push_back(numRotations);      // record number of rotations performed
        return;
    }

    // balance tree to maintain Red-Black Tree properties after insertion
    balanceTree(node, numRotations);
    RBTree->steps.push_back(numSteps); // record number of steps
    RBTree->rotations.push_back(numRotations); // record number of rotations performed
}

// print the tree structure on the screen
void RedBlackTree::prettyPrint() {
    if (root) {
        RBTree->printHelper(root, "", true, rb);
    }
    cout << endl;
}

void RedBlackTree::displayStats(){
    if (root) {
        RBTree->displayStatsHelper(root, rb);
    }
}


