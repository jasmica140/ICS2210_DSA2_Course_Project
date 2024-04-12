#include "RedBlackTree.h"

#include <iostream>
#include <numeric>

// fix the red-black tree
void RedBlackTree::fixInsert(RBNodePtr k, int& numSteps, int& numRotations){

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
                numRotations++;
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
                numRotations++;
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
void RedBlackTree::insert(int key)
{
    // Ordinary Binary Search Insertion
    auto node = new RBNode;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1; // new node must be red

    RBNodePtr y = nullptr;
    RBNodePtr x = this->root;

    int numSteps = 0;
    int numRotations = 0;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
        numSteps++;
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
        steps.push_back(numSteps);
        rotations.push_back(numRotations);
        return;
    }

    // if the grandparent is null, simply return
    if (node->parent->parent == nullptr) {
        steps.push_back(numSteps);
        rotations.push_back(numRotations);
        return;
    }

    // Fix the tree
    fixInsert(node, numSteps, numRotations);
    steps.push_back(numSteps);
    rotations.push_back(numRotations);
}


// print the tree structure on the screen
void RedBlackTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
    cout << endl;
}

int RedBlackTree::getHeight(RBNode *node){
    if(node == nullptr){
        return -1;
    }
    return max(getHeight(node->left),getHeight(node->right)) +1;
}

int RedBlackTree::getLeaves(RBNode *node){
    if(node == nullptr){
        return 0;
    }

    if(node->left == nullptr && node->right == nullptr){ //if node is a leaf
        return 1;
    } else {
        return getLeaves(node->left) + getLeaves(node->right);
    }
}

double RedBlackTree::find_median(vector<int> v){
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

void RedBlackTree::displayStats() {

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

    cout << "Height: " << getHeight(root) << endl;
    cout << endl;

    cout << "Leaves: " << getLeaves(root) << endl;
    cout << endl;
}
