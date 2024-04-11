#ifndef ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H
#define ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H



enum Color {RED, BLACK};

// Red-black tree node.
struct Node {
    int key;
    enum Color color;
    Node *parent, *left, *right;

    Node(int key) : key{key}, parent{nullptr}, left{nullptr}, right{nullptr} {}
};

// Red-black tree.
class RedBlackTree {
private:
    Node *root_;  // Tree root.
protected:
    // Maintains the red-black properties of tree.
    void maintainRedBlack(Node *n);
    // Performs a left rotation on given node.
    void leftRotate(Node *n);
    // Performs a right rotation on given node.
    void rightRotate(Node *n);
public:
    RedBlackTree() {
        root_ = nullptr;
    }
    // Inserts a node with supplied key into tree.
    void insert(int key);
};

#endif //ICS2210_DSA2_COURSE_PROJECT_REDBLACKTREE_H
