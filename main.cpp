#include <iostream>
#include <random>

#include "knuthShuffle.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "SkipList.h"

using namespace std;

int main() {

    //array of 5,000 integers1
    int integers1[5000];

    for (int i = 0; i < 5000; i++) {
        integers1[i] = i;
    }

    //Knuth Shuffle
    knuthShuffle(integers1, 5000);

    //AVL Tree
    AVLTree avlTree;

    for (int integer : integers1) {
        avlTree.insert(avlTree.root, integer);
    }

    avlTree.printTree();

    //Red Black Tree
    RedBlackTree RBTree;

    for (int integer : integers1) {
        RBTree.insert(integer);
    }

    RBTree.prettyPrint();

    //Skip List
    skipList skipList;

    for (int integer : integers1) {
        skipList.insert(integer);
    }

    skipList.display();

    //array of 1,000 random integers with duplicates
    int integers2[1000];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100000);

    for (int & integer : integers2) {
        integer = dis(gen);
    }


    return 0;
}

