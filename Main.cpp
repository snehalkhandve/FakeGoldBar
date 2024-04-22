#include <bits/stdc++.h>
using namespace std;

/**
 * Simulates the weighing of two groups of gold bars on a balance scale.
 * 
 * @param left A vector of integers representing the indices of gold bars in the left bowl.
 * @param right A vector of integers representing the indices of gold bars in the right bowl.
 * @param counterfeit The index of the counterfeit bar which is lighter than the others.
 * @return int Returns -1 if the left side is lighter, 1 if the right side is lighter, and 0 if both sides are equal.
 */
int weigh(const vector<int>& left, const vector<int>& right, int counterfeit) {
    int leftWeight = 0, rightWeight = 0;
    for (int bar : left) {
        leftWeight += (bar == counterfeit ? 0 : 1);
    }
    for (int bar : right) {
        rightWeight += (bar == counterfeit ? 0 : 1);
    }
    if (leftWeight < rightWeight) {
        return -1;  // Left side is lighter
    } else if (leftWeight > rightWeight) {
        return 1;   // Right side is lighter
    }
    return 0;       // Both sides are equal
}

/**
 * Determines the counterfeit gold bar from a set of 9 using two weighings on a balance scale.
 * 
 * @param counterfeit The index of the counterfeit bar known to be lighter.
 * @return int The index of the counterfeit gold bar.
 */
int findCounterfeit(int counterfeit) {
    vector<int> bars(9);
    iota(bars.begin(), bars.end(), 0);  // Initialize bars with indices 0 to 8

    // First weighing: Compare the first two groups of three bars each
    vector<int> group1 = {bars[0], bars[1], bars[2]};
    vector<int> group2 = {bars[3], bars[4], bars[5]};
    int result = weigh(group1, group2, counterfeit);

    vector<int> suspectGroup;
    if (result == -1) {
        suspectGroup = group1;  // Counterfeit is in the first group
    } else if (result == 1) {
        suspectGroup = group2;  // Counterfeit is in the second group
    } else {
        suspectGroup = {bars[6], bars[7], bars[8]};  // Counterfeit is in the third group
    }

    // Second weighing: Isolate the counterfeit from the suspected group
    vector<int> left = {suspectGroup[0]};
    vector<int> right = {suspectGroup[1]};
    result = weigh(left, right, counterfeit);

    if (result == -1) {
        return suspectGroup[0];  // The first bar of the suspect group is counterfeit
    } else if (result == 1) {
        return suspectGroup[1];  // The second bar of the suspect group is counterfeit
    }
    return suspectGroup[2];      // The third bar is counterfeit (since first two weighed the same)
}

/**
 * Main function to run the counterfeit bar detection logic.
 */
int main() {
    int counterfeit;
    cout << "Enter the index of the counterfeit bar (0 to 8): ";
    cin >> counterfeit;

    int result = findCounterfeit(counterfeit);
    cout << "The counterfeit bar is: " << result << endl;
    return 0;
}
