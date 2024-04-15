#include "AVLTree.h"

#include <algorithm>
#include <iostream>

using namespace std;

Node* AVLTree::rightRotate(Node *y) {

    Node *x = y->left;    // set x as left child of y
    Node *z = x->right;   // set z as right child of x

    x->right = y;    // make y right child of x
    y->left = z;     // make z left child of y

    // return new root
    return x;
}

Node* AVLTree::leftRotate(Node *x) {

    Node *y = x->right;    // set y as right child of x
    Node *z = y->left;     // set z as left child of y

    y->left = x;     // make y left child of x
    x->right = z;    // make z right child of x

    // return new root
    return y;
}

Node* AVLTree::insertHelper(Node* node, int key) {

    if (node == nullptr){
        root = new Node(key);
        return root;
    }

    // keep track of number of steps and rotations performed
    int lastSteps = avlTree->steps.size() -1 ;
    int lastRotations = avlTree->rotations.size() - 1;

    // if key < current node's key, go to left subtree
    if (key < node->key){
        avlTree->steps[lastSteps]++;
        node->left = insertHelper(node->left, key);

    // if key > current node's key, go to right subtree
    } else if (key > node->key){
        avlTree->steps[lastSteps]++;
        node->right = insertHelper(node->right, key);

    // if key = current node's key, return current node
    } else {
        root = node;
        return root;
    }

    // balance factor of current node
    int balance = avlTree->getHeight(node->left,avl) - avlTree->getHeight(node->right, avl);

    // if balance factor > 1, perform right rotation
    if (balance > 1){
        if (key < node->left->key){     // Left Left Case
            root = rightRotate(node);

        } else if (key > node->left->key) { // Left Right Case
            node->left = leftRotate(node->left);
            root = rightRotate(node);
        }
        avlTree->rotations[lastRotations]++;

    // if balance factor < -1, perform left rotation
    } else if (balance < -1){
        if (key > node->right->key){ // Right Right Case
            root = leftRotate(node);

        } else if ( key < node->right->key){ // Right Left Case
            node->right = rightRotate(node->right);
            root = leftRotate(node);
        }
        avlTree->rotations[lastRotations]++;

    // otherwise return current node
    } else {
        root = node;
    }

    return root;
}

Node *AVLTree::insert(Node* node, int key) {
    avlTree->steps.push_back(0);
    avlTree->rotations.push_back(0);
    insertHelper(node, key);
}

// print the tree structure on the screen
void AVLTree::prettyPrint() const {
    if (root) {
        avlTree->printHelper(root, "", true, avl);
    }
    cout << endl;
}

// display tree statistics
void AVLTree::displayStats() const{
    if (root) {
        avlTree->displayStatsHelper(root, avl);
    }
}