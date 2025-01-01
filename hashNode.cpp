#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

hashNode::hashNode(string s){
    keyword = s;
    values = new string[100];
    valuesSize = 100;
    currSize = 0;
    srand(time(NULL));
}
hashNode::hashNode(){
    keyword = "";
    values = new string[100];
    valuesSize = 100;
    currSize = 0;
    srand(time(NULL));
}
hashNode::hashNode(string s, string v){
    keyword = s;
    values = new string[100];
    values[0] = v;
    valuesSize = 100;
    currSize = 1;
}
void hashNode::addValue(std::string v) {
    if (currSize >= valuesSize) {
        dblArray(); // Double array size if needed
    }
    values[currSize++] = v; // Add value and increment current size
}

void hashNode::dblArray() {
    valuesSize *= 2; // Double the size
    string* newValues = new std::string[valuesSize];
    for (int i = 0; i < currSize; i++) {
        newValues[i] = values[i]; // Copy old values
    }
    delete[] values; // Free old array
    values = newValues; // Point to the new, larger array
}


string hashNode::getRandValue() {
    if (currSize == 0) {
        return ""; // No values in the array
    }
    int randIndex = rand() % currSize; // Pick random index
    if (randIndex < 0 || randIndex >= currSize) {
        // Should never happen, but it's a good sanity check
        cout << "Error: Invalid random index: " << randIndex << endl;
        return "";
    }

    // Check if the value is null or empty (if needed)
    if (values[randIndex].empty()) {
        cout << "Error: Value at index " << randIndex << " is empty." << endl;
        return "";
    }

    return values[randIndex];
}
