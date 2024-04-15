#include "SkipList.h"
#include <iostream>
#include <numeric>

void skipList::insert(int value)
{
    int newLevel = 0;       // initialize new level of node to be inserted
    int numSteps = 0;       // initialize number of steps taken during insertion
    int numPromotions = 0;  // initialize number of promotions

    // deciding level of inserting node based on coin toss
    while ((rand() % 2) == 1) {
        newLevel++;         // increment new level
        numPromotions++;    // increment number of promotions
    }

    // resizing size of levels to make space for inserting value
    if (Level < newLevel){
        head->next.resize(newLevel + 1, nullptr);   // resize levels of skip list
        Level = newLevel;                                  // update maximum level of skip list
    }

    skipNode* current = head; // initialize pointer to traverse through skip list starting from head

    vector<skipNode*> Update(Level + 1, nullptr); // vector to store update node at each level

    // loop over levels up to which we want value to be inserted
    for (int i = Level; i >= 0; i--) {
        // finding position for inserting value
        while (current->next[i] && current->next[i]->value < value) {
            current = current->next[i];      // move to next node
            numSteps++;                      // increment number of steps
        }
        Update[i] = current; // store update node at each level
    }

    current = current->next[0]; // move current to next node at level 0

    // if current node is null or its value is not equal to value to be inserted
    if (current == nullptr || current->value != value) {
        // create new skipNode with given value and level
        auto* newSkipNode = new skipNode(value, Level);

        // insert value at each level
        for (int i = 0; i <= newLevel; i++) {
            newSkipNode->next[i] = Update[i]->next[i];
            Update[i]->next[i] = newSkipNode;
        }
    }

    steps.push_back(numSteps);              // record steps
    promotions.push_back(numPromotions);    // record promotions
}


void skipList::display()
{
    cout << "skip List:" << endl;

    // loop through each level of skip list
    for (int i = Level; i >= 0; i--) {
        skipNode* current = head->next[i]; // initialize pointer to first node of that level

        cout << "Level " << i << ": ";

        // display all the values present at that level
        while (current != nullptr) {
            cout << current->value << " ";      // print the value
            current = current->next[i];         // move to right of node
        }
        cout << endl;
    }
    cout << endl;
}


double skipList::find_median(vector<int> v){
    if (v.size() < 1)
        return std::numeric_limits<double>::signaling_NaN();

    const auto alpha = v.begin();
    const auto omega = v.end();

    // Find middle positions
    const auto i1 = alpha + (v.size()-1) / 2;
    const auto i2 = alpha + v.size() / 2;

    // Partial sort to place correct elements at those indexes
    std::nth_element(alpha, i1, omega);
    std::nth_element(i1, i2, omega);

    return 0.5 * (*i1 + *i2);
}



void skipList::displayStats() {

    cout << "Skip List Statistics:\n" << endl;

    cout << "Steps: " << endl;

    cout << "Minimum: " << *min_element(steps.begin(), steps.end()) << endl;
    cout << "Maximum: " << *max_element(steps.begin(), steps.end())<< endl;
    double meanSteps = accumulate(steps.begin(), steps.end(), 0.0) / steps.size();
    cout << "Mean: " << meanSteps << endl;
    double sqSumSteps = inner_product(steps.begin(), steps.end(), steps.begin(), 0.0);
    double stdevSteps = sqrt(sqSumSteps / steps.size() - meanSteps * meanSteps);
    cout << "Standard Deviation: " << stdevSteps << endl;
    cout << "Median: " << find_median(steps) << "\n" << endl;

    cout << "Promotions: " << endl;

    cout << "Minimum: " <<  *min_element(promotions.begin(), promotions.end()) << endl;
    cout << "Maximum: " <<  *max_element(promotions.begin(), promotions.end()) << endl;
    double meanRotations = accumulate(promotions.begin(), promotions.end(), 0.0) / promotions.size();
    cout << "Mean: " << meanRotations << endl;
    double sqSumRotations = inner_product(promotions.begin(), promotions.end(), promotions.begin(), 0.0);
    double stdevRotations = sqrt(sqSumRotations / promotions.size() - meanRotations * meanRotations);
    cout << "Standard Deviation: " << stdevRotations << endl;
    cout << "Median: " << find_median(promotions) << endl;
    cout << endl;

    cout << "Levels: " << Level+1  << endl;
    cout << "---------------------------------------\n" << endl;
}