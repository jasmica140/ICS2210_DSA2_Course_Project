#include "RedBlackTree.h"

void RedBlackTree::insert(int key) {
    Node *p, *q;  // Traversal temporary node pointers.
    Node *n = new Node(key);  // The new node to be inserted.
    // Initialization of the new node.
    n->color = RED;  // Assume new node is red.
    // Start at root.
    p = root_;
    q = nullptr;
    // If tree is empty, the new node is the root, and we're done.
    if (root_ == nullptr) {
        root_ = n;
        n->parent = nullptr;
    }
    else {
        // Descend tree until a place for the new node is found that does not
        // violate the BST property.
        while (p != nullptr) {
            q = p;
            // If new node's key is larger than current node's key, go down right
            // branch.
            if (p->key < n->key) {
                p = p->right;
            }
                // Otherwise, go down left branch.
            else {
                p = p->left;
            }
        }
        n->parent = q;
        // If the new node has a larger key than its parent, make the new node the
        // right child.
        if (q->key < n->key) {
            q->right = n;
        }
            // Otherwise, make it the left child.
        else {
            q->left = n;
        }
    }
    // Ensure that red-black tree properties are maintained.
    maintainRedBlack(n);
}

void RedBlackTree::maintainRedBlack(Node *n) {
    Node *u;  // n's uncle node.
    if (root_ == n) {
        n->color = BLACK;
        return;
    }
    // Until the root is reached or the current node and its parent are not both
    // red, restore the tree's red-black properties over the current generation
    // and the next two higher generations (current node through grandparent.)
    while ((n != root_) && (n->color != BLACK) && (n->parent->color == RED)) {
        // Since n is red and n.p is red. the 4th property of red-black trees is
        // violated: the children of a red node must be black.
        Node *g = n->parent->parent;  // n's grandparent
        // If n's parent is the left child of g...
        if (g->left == n->parent) {
            // If n's uncle is not null...
            if (g->right != nullptr) {
                u = g->right;  // n's uncle
                // If n's uncle is red, we ensure the 4th property by setting n.p and
                // n's uncle black, and setting g red.  At this point, the subtree
                // rooted at g is taken care of.
                if (u->color == RED) {
                    n->parent->color = BLACK;
                    u->color = BLACK;
                    g->color = RED;
                    n = g;  // Move up to g.
                }
                    // Otherwise, n's uncle is black, and we have to utilize rotations to
                    // maintain the red-black tree properties.
                else {
                    // If n is the right child of its parent, then we need to left-rotate
                    // so is the left child of its parent.
                    if (n->parent->right == n) {
                        n = n->parent;
                        leftRotate(n);
                    }
                    // Now, n's uncle is black and n is a left child.
                    // By setting n's parent to black and grandparent to red, and
                    // rotating right on the grandparent, we can restore the 4th property
                    // of red-black trees without violating any of the other properties.
                    n->parent->color = BLACK;
                    g->color = RED;
                    rightRotate(g);
                }
            }
        }
        else {
            // If n's uncle is not null...
            if (g->left != nullptr) {
                u = g->left;  // n's uncle
                // If n's uncle is red, we ensure the 4th property by setting n.p and
                // n's uncle black, and setting g red.  At this point, the subtree
                // rooted at g is taken care of.
                if (u->color == RED) {
                    n->parent->color = BLACK;
                    u->color = BLACK;
                    g->color = RED;
                    n = g;  // Move up to g.
                }
                    // Otherwise, n's uncle is black, and we have to utilize rotations
                    // to maintain the red-black tree properties.
                else {
                    // If n is the left child of its parent, then we need to left-rotate
                    // so is the right child of its parent.
                    if (n->parent->left == n) {
                        n = n->parent;
                        rightRotate(n);
                    }
                    // Now, n's uncle is black and n is a right child.
                    // By setting n's parent to black and grandparent to red, and
                    // rotating left on the grandparent, we can restore the 4th property
                    // of red-black trees without violating any of the other properties.
                    n->parent->color = BLACK;
                    g->color = RED;
                    leftRotate(g);
                }
            }
        }
        root_->color = BLACK;
    }
}

void RedBlackTree::leftRotate(Node *n) {
    if (n->right == nullptr) {
        return;
    }
    else {
        // Save n's right subtree.
        Node *y = n->right;
        // Set n's right subtree to be y's (potentially null) left subtree.
        // I.e., n->right = n->right->left;
        n->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = n;
        }
        // Set y's parent to n's parent.
        y->parent = n->parent;
        // If n->parent is null, then y is now the root.
        if (n->parent == nullptr) {
            root_ = y;
        }
            // Otherwise, we need to substitute y for n's spot as its parent's child.
        else {
            // If n was a left child, set y to be n's parent's left child.
            if (n == n->parent->left) {
                n->parent->left = y;
            }
                // Otherwise, set y to be n's parent's right child
            else {
                n->parent->right = y;
            }
        }
        // Set n as y's left subtree.
        y->left = n;
        n->parent = y;
    }
}

void RedBlackTree::rightRotate(Node *n) {
    if (n->right == nullptr) {
        return;
    }
    else {
        // Save n's left subtree.
        Node *y = n->left;
        // Set n's left subtree to be y's (potentially null) right subtree.
        // I.e., n->left = n->left->right;
        n->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = n;
        }
        // Set y's parent to n's parent.
        y->parent = n->parent;
        // If n->parent is null, then y is now the root.
        if (n->parent == nullptr) {
            root_ = y;
        }
            // Otherwise, we need to substitute y for n's spot as its parent's child.
        else {
            // If n was a left child, set y to be n's parent's left child.
            if (n == n->parent->left) {
                n->parent->left = y;
            }
                // Otherwise, set y to be n's parent's right child
            else {
                n->parent->right = y;
            }
        }
        // Set n as y's right subtree.
        y->right = n;
        n->parent = y;
    }
}
