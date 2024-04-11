#include <iostream>

#include "knuthShuffle.h"
#include "AVLTree.h"
#include "RedBlackTree.h"

using namespace std;

int main() {

    int integers[5000];

    for (int i = 0; i < 5000; i++) {
        integers[i] = i;
    }

    knuthShuffle(integers, 5000);

    AVLTree avlTree;

    for (int integer : integers) {
        avlTree.insert(avlTree.root, integer);
    }

    avlTree.printTree();

    RedBlackTree RBTree;

    for (int integer : integers) {
        RBTree.insert(integer);
    }


    return 0;
}
