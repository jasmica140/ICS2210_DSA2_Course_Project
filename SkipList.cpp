//
// Created by Jasmine Micallef on 11/04/2024.
//

#include "SkipList.h"
#include <iostream>
#include <numeric>

void skipList::insert(int data)
{
    int newLevel = 0;
    int numOfSteps = 0;
    int numOfPromotions = 0;

    // Deciding the level of inserting node on the basis of coin toss
    while (newLevel < maxNumberOfLevel and (rand() % 2) == 1) // here rand()%2 is doing the coin toss
    {
        newLevel++;
        numOfPromotions++; // Increment the number of promotions
    }

    // Resizing the size of the levels to make place for the inserting value
    if (Level < newLevel)
    {
        head->next.resize(newLevel + 1, nullptr);

        Level = newLevel;
    }

    skipNode* current = head; // pointer to the head to traverse through the skip list

    vector<skipNode*> Update(Level + 1, nullptr); // To store the update node at eah level

    // Loop over the levels upto which we want the value to be inserted
    for (int i = Level; i >= 0; i--)
    {
        // Finding the place for the inserting value
        while (current->next[i] and current->next[i]->data < data)
        {
            current = current->next[i];
            numOfSteps++; // Increment the number of steps
        }
        // Updating the level accordingly
        Update[i] = current;
    }

    current = current->next[0];   // Moves the current to the next node at level 0

    if (current == nullptr or current->data!= data) // if the current is null then it does not exit we need to insert the value
    {
        auto* newskipNode = new skipNode(data, Level);

        for (int i = 0; i <= newLevel; i++)
        {
            newskipNode->next[i] = Update[i]->next[i];

            Update[i]->next[i] = newskipNode;  // To insert the value at each level
        }

        cout << "Element " << data << " inserted successfully.\n";
    }
    else
    {
        cout << "Element " << data << " already exists.\n";  // Incase if value already exists
    }

    steps.push_back(numOfSteps);
    promotions.push_back(numOfPromotions);
}

void skipList::display()
{

    cout << "skip List:"<< endl;

    for (int i = Level; i >= 0; i--) //
    {
        skipNode* current = head->next[i]; // Initializes the pointer to the first node of that level

        cout << "Level " << i << ": ";

        while (current != nullptr)       // Start displaying all the values present at that level
        {
            cout << current->data << " ";
            current = current->next[i]; // Moving to the right of the node
        }
        cout << endl;
    }
}

double skipList::find_median(vector<int> v){
    if (v.size() < 1)
        return std::numeric_limits<double>::signaling_NaN();

    const auto alpha = v.begin();
    const auto omega = v.end();

    // Find the two middle positions (they will be the same if size is odd)
    const auto i1 = alpha + (v.size()-1) / 2;
    const auto i2 = alpha + v.size() / 2;

    // Partial sort to place the correct elements at those indexes (it's okay to modify the vector,
    // as we've been given a copy; otherwise, we could use std::partial_sort_copy to populate a
    // temporary vector).
    std::nth_element(alpha, i1, omega);
    std::nth_element(i1, i2, omega);

    return 0.5 * (*i1 + *i2);
}

void skipList::displayStats() {

    cout << "Min Steps: " << *min_element(steps.begin(), steps.end()) << endl;
    cout << "Max Steps: " << *max_element(steps.begin(), steps.end())<< endl;
    double meanSteps = accumulate(steps.begin(), steps.end(), 0.0) / steps.size();
    cout << "Mean Steps: " << meanSteps << endl;
    double sqSumSteps = inner_product(steps.begin(), steps.end(), steps.begin(), 0.0);
    double stdevSteps = sqrt(sqSumSteps / steps.size() - meanSteps * meanSteps);
    cout << "Variance Steps: " << stdevSteps << endl;
    cout << "Median Step: " << find_median(steps) << endl;

    cout << "Min Promotions: " <<  *min_element(promotions.begin(), promotions.end()) << endl;
    cout << "Max Promotions: " <<  *max_element(promotions.begin(), promotions.end()) << endl;
    double meanPromotions = accumulate(promotions.begin(), promotions.end(), 0.0) / promotions.size();
    cout << "Mean Promotions: " << meanPromotions << endl;
    double sqSumPromotions = inner_product(promotions.begin(), promotions.end(), promotions.begin(), 0.0);
    double stdevPromotions = sqrt(sqSumPromotions / promotions.size() - meanPromotions * meanPromotions);
    cout << "Variance Promotions: " << stdevPromotions << endl;
    cout << "Median Promotions: " << find_median(promotions) << endl;

    cout << "Levels: " << Level+1 << endl;
}

