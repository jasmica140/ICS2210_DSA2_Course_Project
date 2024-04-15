#include <numeric>

#include "Tree.h"

void Tree::printHelper(Node *node, string indent, bool right, treeType tt) {
    // print the tree structure on the screen
    if ((tt == avl && node != nullptr) || (tt == rb && node != leaf)) {
        cout<<indent;
        if (right) {
            cout<<"R----";
            indent += "     ";
        } else {
            cout<<"L----";
            indent += "|    ";
        }

        if(tt == rb){
            string nColour = node->colour?"RED":"BLACK";
            cout<<node->key<<"("<<nColour<<")"<<endl;
        } else {
            cout<<node->key<<endl;
        }
        printHelper(node->left, indent, false, tt);
        printHelper(node->right, indent, true, tt);
    }
}

int Tree::getHeight(Node *node, treeType tt){
    if (tt == avl && node == nullptr) {
        return -1;
    } else if (tt == rb && node == leaf){
        return -1;
    }

    return max(getHeight(node->left, tt), getHeight(node->right, tt)) +1;
}

int Tree::getLeaves(Node *node){
    if(node == nullptr){
        return 0;
    }

    if(node->left == nullptr && node->right == nullptr){ //if node is a leaf
        return 1;
    } else {
        return getLeaves(node->left) + getLeaves(node->right);
    }
}

double Tree::find_median(vector<int> v){
    if (v.empty())
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

void Tree::displayStatsHelper(Node *node, treeType tt) {

    if(tt == avl){
        cout << "AVL Tree Statistics:\n" << endl;
    } else {
        cout << "Red Black Tree Statistics:\n" << endl;
    }

    cout << "Steps: " << endl;

    cout << "Minimum: " << *min_element(steps.begin(), steps.end()) << endl;
    cout << "Maximum: " << *max_element(steps.begin(), steps.end())<< endl;
    double meanSteps = accumulate(steps.begin(), steps.end(), 0.0) / steps.size();
    cout << "Mean: " << meanSteps << endl;
    double sqSumSteps = inner_product(steps.begin(), steps.end(), steps.begin(), 0.0);
    double stdevSteps = sqrt(sqSumSteps / steps.size() - meanSteps * meanSteps);
    cout << "Standard Deviation: " << stdevSteps << endl;
    cout << "Median: " << find_median(steps) << "\n" << endl;

    cout << "Rotations: " << endl;

    cout << "Minimum: " <<  *min_element(rotations.begin(), rotations.end()) << endl;
    cout << "Maximum: " <<  *max_element(rotations.begin(), rotations.end()) << endl;
    double meanRotations = accumulate(rotations.begin(), rotations.end(), 0.0) / rotations.size();
    cout << "Mean: " << meanRotations << endl;
    double sqSumRotations = inner_product(rotations.begin(), rotations.end(), rotations.begin(), 0.0);
    double stdevRotations = sqrt(sqSumRotations / rotations.size() - meanRotations * meanRotations);
    cout << "Standard Deviation: " << stdevRotations << endl;
    cout << "Median: " << find_median(rotations) << endl;
    cout << endl;

    cout << "Height: " << getHeight(node, tt) << "\n" << endl;

    cout << "Leaves: " << getLeaves(node) << endl;
    cout << "---------------------------------------\n" << endl;
}



