//
// Created by Jasmine Micallef on 11/04/2024.
//

#ifndef ICS2210_DSA2_COURSE_PROJECT_SKIPLIST_H
#define ICS2210_DSA2_COURSE_PROJECT_SKIPLIST_H

#include <vector>
using namespace std;

const int maxNumberOfLevel = 5; // Maximum Level of the skip list

class skipNode
{
public:

    int data;
    vector<skipNode*> next;     // To maintain the levels of the skip list
    skipNode(int data, int Level) : data(data), next(Level + 1, nullptr) {} // declaring the data and the level of the node
};


class skipList
{
private:
    skipNode* head;
    int Level;

public:

   skipList(){
        head = new skipNode(0, maxNumberOfLevel);    // Initializing the skip list with the max number of levels
        Level = 0;                               // At start the level is 0
    }

    void insert(int data);  // To insert the value
    void display();         // Function to display a skip List

};


#endif //ICS2210_DSA2_COURSE_PROJECT_SKIPLIST_H
