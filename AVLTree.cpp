#include "AVLTree.h"

#include <algorithm>
#include <iostream>

using namespace std;

int AVLTree::height(Node *N)
{
    if (N == nullptr)
        return 0;
    return N->height;
}

Node *AVLTree::rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

Node *AVLTree::leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

Node *AVLTree::insert(Node* node, int key) {

    if (node == nullptr){
        root = new Node(key);
        return root;
    }

    /* 1. Perform the normal BST insertion */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else { // Equal keys are not allowed in BST
        root = node;
        return root;
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
    node to check whether this node became
    unbalanced */
    int balance = height(node->left) - height(node->right);


    if (balance > 1){
        if (key < node->left->key){     // Left Left Case
            root = rightRotate(node);

        } else if (key > node->left->key) { // Left Right Case
            node->left = leftRotate(node->left);
            root = rightRotate(node);
        }

    } else if (balance < -1){
        if (key > node->right->key){ // Right Right Case
            root = leftRotate(node);

        } else if ( key < node->right->key){ // Right Left Case
            node->right = rightRotate(node->right);
            root = leftRotate(node);
        }
    } else {
        root = node;
    }

    return root;
}

void AVLTree::preOrder(Node *node, int level, bool isLeft) {
    if (node == nullptr) {
        return;
    }

    if (level == 1) {
        if (isLeft) {
            cout << " ";
        }
        cout << node->key << " ";
    } else if (level > 1) {
        preOrder(node->left, level - 1, true);
        preOrder(node->right, level - 1, false);
    }
}

void AVLTree::printTree() {
    int height = this->height(root);
    int maxWidth = 1 << height;
    for (int i = 1; i <= height; i++) {
        int start = maxWidth >> i;
        int end = (start << 1) - 1;
        cout << "Level " << i << ": ";
        preOrder(root, i, false);
        cout << endl;
//        for (int j = start; j <= end; j++) {
//            cout << " ";
//        }
    }
}