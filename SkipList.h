#ifndef ICS2210_DSA2_COURSE_PROJECT_SKIPLIST_H
#define ICS2210_DSA2_COURSE_PROJECT_SKIPLIST_H

#include <vector>
using namespace std;

class skipNode
{
public:

    int value;
    vector<skipNode*> next;     // To maintain the levels of the skip list
    skipNode(int value, int Level) : value(value), next(Level + 1, nullptr) {} // declaring the value and the level of the node
};


class skipList
{
private:
    skipNode* head;
    int Level;
    vector<int> steps;
    vector<int> promotions;

    static double find_median(vector<int> v);

public:

   skipList(){
        head = new skipNode(0, 0);    // Initializing the skip list with the max number of levels
        Level = 0;                               // At start the level is 0
    }

    void insert(int value);  // To insert the value
    void display();         // To display a skip List
    void displayStats();    // To display a skip List stats
};


#endif //ICS2210_DSA2_COURSE_PROJECT_SKIPLIST_H
