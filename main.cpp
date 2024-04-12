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
    avlTree1.prettyPrint();

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

    //AVL Tree
    AVLTree avlTree2;

    for (int integer : integers2) {
        avlTree2.insert(avlTree2.root, integer);
    }
    avlTree2.prettyPrint();
    avlTree2.displayStats();

    //Red Black Tree
    RedBlackTree RBTree2;

    for (int integer : integers2) {
        RBTree2.insert(integer);
    }

    RBTree2.prettyPrint();
    RBTree2.displayStats();

    //Skip List
    skipList skipList2;

    for (int integer : integers2) {
        skipList2.insert(integer);
    }
    skipList2.display();
    skipList2.displayStats();

//    int integers1[] = {37, 3, 28, 31, 37, 1, 14, 30, 32, 18, 42, 11, 3, 34, 32, 21, 5, 16, 48, 24};

    return 0;
}

