#include "AVLTree.h"

#include <algorithm>
#include <iostream>
#include <numeric>

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

Node *AVLTree::insertHelper(Node* node, int key) {

    if (node == nullptr){
        root = new Node(key);
        return root;
    }

    int lastSteps = steps.size() -1 ;
    int lastRotations = rotations.size() - 1;

    /* 1. Perform the normal BST insertion */
    if (key < node->key){
        steps[lastSteps]++;
        node->left = insertHelper(node->left, key);
    } else if (key > node->key){
        steps[lastSteps]++;
        node->right = insertHelper(node->right, key);
    } else { // Equal keys are not allowed in BST
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
        rotations[lastRotations]++;

    } else if (balance < -1){
        if (key > node->right->key){ // Right Right Case
            root = leftRotate(node);

        } else if ( key < node->right->key){ // Right Left Case
            node->right = rightRotate(node->right);
            root = leftRotate(node);
        }
        rotations[lastRotations]++;

    } else {
        root = node;
    }

    return root;
}

Node *AVLTree::insert(Node* node, int key) {
    steps.push_back(0);
    rotations.push_back(0);
    insertHelper(node, key);
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

void AVLTree::printHelper(Node *node, string indent, bool last) {
    // print the tree structure on the screen
    if (node != nullptr) {
        cout<<indent;
        if (last) {
            cout<<"R----";
            indent += "     ";
        } else {
            cout<<"L----";
            indent += "|    ";
        }

        cout<<node->key<<endl;
        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }
    // cout<<root->left->data<<endl;
}

// print the tree structure on the screen
void AVLTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
    cout << endl;
}


double AVLTree::find_median(vector<int> v){
    if (v.empty())
        return std::numeric_limits<double>::signaling_NaN();

    const auto alpha = v.begin();
    const auto omega = v.end();

    // Find the two middle positions (they will be the same if size is odd)
    const auto i1 = alpha + (v.size()-1) / 2;
    const auto i2 = alpha + v.size() / 2;

    // Partial sort to place the correct elements at those indexes (it's okay to modify the vector,
    // as we've been given a copy; otherwise, we could use std::partial_sort_copy to populate a
    // temporary vector).
    std::nth_element(alpha, i1, omega);
    std::nth_element(i1, i2, omega);

    return 0.5 * (*i1 + *i2);
}

int AVLTree::getLeaves(Node *node){
    if(node == nullptr){
        return 0;
    }

    if(node->left == nullptr && node->right == nullptr){ //if node is a leaf
        return 1;
    } else {
        return getLeaves(node->left) + getLeaves(node->right);
    }
}

void AVLTree::displayStats() {

    cout << "steps: ";
    for (int step : steps) {
        cout << step << " ";
    }
    cout << endl;

    cout << "Minimum: " << *min_element(steps.begin(), steps.end()) << endl;
    cout << "Maximum: " << *max_element(steps.begin(), steps.end())<< endl;
    double meanSteps = accumulate(steps.begin(), steps.end(), 0.0) / steps.size();
    cout << "Mean: " << meanSteps << endl;
    double sqSumSteps = inner_product(steps.begin(), steps.end(), steps.begin(), 0.0);
    double stdevSteps = sqrt(sqSumSteps / steps.size() - meanSteps * meanSteps);
    cout << "Standard Deviation: " << stdevSteps << endl;
    cout << "Median: " << find_median(steps) << endl;
    cout << endl;

    cout << "rotations: ";
    for (int rot : rotations) {
        cout << rot << " ";
    }
    cout << endl;

    cout << "Minimum: " <<  *min_element(rotations.begin(), rotations.end()) << endl;
    cout << "Maximum: " <<  *max_element(rotations.begin(), rotations.end()) << endl;
    double meanRotations = accumulate(rotations.begin(), rotations.end(), 0.0) / rotations.size();
    cout << "Mean: " << meanRotations << endl;
    double sqSumRotations = inner_product(rotations.begin(), rotations.end(), rotations.begin(), 0.0);
    double stdevRotations = sqrt(sqSumRotations / rotations.size() - meanRotations * meanRotations);
    cout << "Standard Deviation: " << stdevRotations << endl;
    cout << "Median: " << find_median(rotations) << endl;
    cout << endl;

    cout << "Height: " << root->height << endl;
    cout << endl;

    cout << "Leaves: " << getLeaves(root) << endl;
    cout << endl;
}
