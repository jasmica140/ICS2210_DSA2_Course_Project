#ifndef ICS2210_DSA2_COURSE_PROJECT_TREE_H
#define ICS2210_DSA2_COURSE_PROJECT_TREE_H

#include <iostream>

using namespace std;

enum treeType{
    avl,
    rb
};

// data structure that represents a node in the tree
class Node{
public:
    int key{};          // holds the key
    Node *left;         // pointer to left child
    Node *right;        // pointer to right child
    Node *parent{};     // pointer to the parent
    int colour{};       // 1 = Red, 0 = Black

    explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
    Node(Node *left, Node *right, int colour) : left(left), right(right), colour(colour) {}
};

class Tree {
private:
    int getLeaves(Node *node);
    static double find_median(vector<int> v);

public:
    vector<int> steps;
    vector<int> rotations;
    Node *leaf;

    Tree() {
        leaf = new Node(nullptr, nullptr, 0);
    }

    void printHelper(Node *node, string indent, bool right, treeType tt);
    void displayStatsHelper(Node *node, treeType tt);

    int getHeight(Node *node, treeType tt);
};


#endif //ICS2210_DSA2_COURSE_PROJECT_TREE_H
