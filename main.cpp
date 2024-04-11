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
    AVLTree avlTree1;

    for (int integer : integers1) {
        avlTree1.insert(avlTree1.root, integer);
    }
    avlTree1.printTree();

    //Red Black Tree
    RedBlackTree RBTree1;

    for (int integer : integers1) {
        RBTree1.insert(integer);
    }
    RBTree1.prettyPrint();

    //Skip List
    skipList skipList1;

    for (int integer : integers1) {
        skipList1.insert(integer);
    }
    skipList1.display();

    //array of 1,000 random integers with duplicates
    int integers2[1000];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100000);

    for (int & integer : integers2) {
        integer = dis(gen);
    }

    //Skip List
    skipList skipList2;

    for (int integer : integers1) {
        skipList2.insert(integer);
    }
    skipList2.display();
    skipList2.displayStats();

    return 0;
}

