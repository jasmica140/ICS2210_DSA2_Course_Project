//
// Created by Jasmine Micallef on 11/04/2024.
//

#include "SkipList.h"
#include <iostream>


void skipList::insert(int data)
{
    int newLevel = 0;


    // Deciding the level of inserting node on the basis of coin toss

    while (newLevel < maxNumberOfLevel and (rand() % 2) == 1) // here rand()%2 is doing the coin toss
    {
        newLevel++;
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
        }
        // Updating the level accordingly

        Update[i] = current;

    }

    current = current->next[0];   // Moves the current to the next node at level 0

    if (current == nullptr or current->data != data) // if the current is null then it does not exit we need to insert the value
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
