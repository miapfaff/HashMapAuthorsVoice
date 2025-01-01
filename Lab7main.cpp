
#include <cassert>
#include <iostream>
#include "makeSeuss.hpp"
#include <time.h>
#include <stdlib.h>

using namespace std;
int main() {
    srand(time(NULL));

    /* NOTE - FOR TESTING:
    hashMap map(true, true); // Using first hash and collision methods

    // Test addKeyValue and printMap functions
    map.addKeyValue("apple", "fruit");
    map.addKeyValue("banana", "fruit");
    map.addKeyValue("carrot", "vegetable");
    map.printMap();

    // Test getIndex function
    int appleIndex = map.getIndex("apple");
    cout << "Index of 'apple': " << appleIndex << endl;

    // Test reHash by adding enough keys
    map.addKeyValue("date", "fruit");
    map.addKeyValue("eggplant", "vegetable");

    // Print map again to check rehashing
    map.printMap();

    // Test findKey
    int index = map.findKey("carrot");
    cout << "Index of 'carrot': " << index << endl;

    index = map.findKey("nonexistent");
    cout << "Index of 'nonexistent': " << index << endl;

    // Test rehashing and closest prime finder
    cout << "Closest prime to 50: " << map.getClosestPrime(50) << endl;
*/
//    makeSeuss voice1("DrSeuss.txt", "Seussout1.txt", true, true);
    makeSeuss voice2("DrSeuss.txt", "Seussout2.txt", true, false);
//    makeSeuss voice3("DrSeuss.txt", "Seussout3.txt", false, true);
//    makeSeuss voice4("DrSeuss.txt", "Seussout4.txt", false, false);
    return 0;
}