#ifndef ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H
#define ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H

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

    static int height(Node *N);
    static Node *rightRotate(Node *y);
    static Node *leftRotate(Node *x);
    void preOrder(Node *node, int level, bool isLeft);

public:
    Node *root;

    AVLTree() : root(nullptr) {}

    Node* insert(Node* node, int key);
    void printTree();
};


#endif //ICS2210_DSA2_COURSE_PROJECT_AVLTREE_H
