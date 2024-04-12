#ifndef ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H
#define ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H

#include <string>
#include <vector>
using namespace std;

class Node {
public:
    int key{};
    Node *left;
    Node *right;
    int height;

    explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {

private:
    vector<int> steps;
    vector<int> rotations;

    static int height(Node *N);
    static Node *rightRotate(Node *y);
    static Node *leftRotate(Node *x);
    Node* insertHelper(Node* node, int key);
    void preOrder(Node *node, int level, bool isLeft);
    void printHelper(Node *node, string indent, bool last);
    int getLeaves(Node *node);
    double find_median(vector<int> v);

public:
    Node *root;

    AVLTree() : root(nullptr) {}

    Node* insert(Node* node, int key);
    void prettyPrint();
    void displayStats();
};


#endif //ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H
