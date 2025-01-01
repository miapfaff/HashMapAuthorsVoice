#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;


hashMap::hashMap(bool hash1, bool coll1) {
   h1 = hash1;
   c1 = coll1;
   mapSize = 101;  // initial map size, prime number
   map = new hashNode*[mapSize];
    cout << "map size: " << mapSize << endl;
   numKeys = 0;
   collisionct1 = 0;
   collisionct2 = 0;
   first = "";

   for (int i = 0; i < mapSize; i++) {
       map[i] = nullptr;
   }
}


void hashMap::addKeyValue(string k, string v) {
   reHash();
  int x = calcHash(k); //the initial index

  //If index is empty, create a new hashNode
  if (map[x] == NULL) {
      map[x] = new hashNode(k, v);
      ++numKeys;
  } else if (map[x]->keyword == k) {
      //If  keyword matches, check and resize the values array
      if (map[x]->currSize == map[x]->valuesSize) {
          auto tmp = map[x]->values; //Store current values temporarily
          int tmpSize = map[x]->currSize;
          map[x]->values = new string[map[x]->valuesSize * 2]; //Resize the values arr
          map[x]->valuesSize *= 2; //Update values size
          for (int i = 0; i < tmpSize; i++) {
              map[x]->values[i] = tmp[i]; //Copy old values to new arr
          }
          delete[] tmp;
      }
      map[x]->values[map[x]->currSize] = v; //Add the new value
      ++map[x]->currSize;
  } else {
      //Collision handling
      collisionct1++;
      x = collHash1(x, k);

      if (map[x] == NULL) {
          map[x] = new hashNode(k, v);
          ++numKeys;
      } else if (map[x]->keyword == k) {
          if (map[x]->currSize == map[x]->valuesSize) {
              auto tmp = map[x]->values;
              int tmpSize = map[x]->currSize;
              map[x]->values = new string[map[x]->valuesSize * 2];
              map[x]->valuesSize *= 2;
              for (int i = 0; i < tmpSize; i++) {
                  map[x]->values[i] = tmp[i];
              }
              delete[] tmp;
          }
          map[x]->values[map[x]->currSize] = v;
          ++map[x]->currSize;
      }
  }
}

int hashMap::getIndex(string k) {
    reHash();
    int x = calcHash(k);
    cout << "Index for key '" << k << "': " << x << endl;
    if (map[x] == NULL) {
        return -1;
    }
    if (map[x] != NULL && map[x]->keyword != k) x = collHash1(x, k);
    return x;
}

int hashMap::calcHash(string k){
    if (h1 == true){
        return calcHash1(k);
    }
    return calcHash2(k);

}

int hashMap::calcHash1(string k) {
    int len = k.length(), hash = 0;
    for (int i = len - 1; i > 0; i--){
        hash = (7*hash + (int)k[i]) % mapSize;
    }
    return hash;
}

int hashMap::calcHash2(string k) {
    int hash = 0;
    for (int i = 0; i < k.length(); ++i) {
        hash += k[i];  //Add ASCII value of each character
    }
    return hash % mapSize;
}

int hashMap::collHash(int h, string k){
    if (c1 == true){
        return collHash1(h, k);
    }
    return collHash2(h, k);
}

int hashMap::collHash1(int h, string k) {
    int index = h;

    if (map[index] == NULL || map[index]->keyword == k) {
        return index;
    }

    //Loop for linear probing
    while (map[index] != NULL && map[index]->keyword != k) {
        index = (index + 1) % mapSize; // Wrap around to the beginning if needed
        collisionct1++;

        if (map[index] == NULL || map[index]->keyword == k) {
            break;
        }
    }
    return index;
}


int hashMap::collHash2(int h, string k) {
    int index = h;
    int i = 1;

    //Check if the index is empty or contains the keyword
    if (map[index] == NULL || map[index]->keyword == k) {
        return index;
    }

    //Find a new index if collision
    while (map[index] != NULL && map[index]->keyword != k) {
        index = (h + i * i) % mapSize;  //Quadratic probing
        ++i;
        //Wrap i if it reaches end
        if (i == 10) {
            i = 1;
        }
        collisionct2++; // Increment collision counter
    }

    return index;
}



int hashMap::findKey(string k) {
   int h = calcHash(k); // Calculate hash index for key
   int index = h;

   //Search for key (linear probing)
   while (map[index] != NULL) {
       if (map[index]->keyword == k) {
           return index; //Found, return its index
       }
       index = (index + 1) % mapSize; //Move to the next index, wrapping around if necessary
       //If we come back to the original index, we've looped through the whole array
       if (index == h) {
           break; // Key not found, exit the loop
       }
   }
   return -1; //Key not found so exit
}


void hashMap::printMap() {
   cout << "In printMap()" << endl;

   //Go thru hash map array
   for (int i = 0; i < mapSize; i++) {
       //Check if the current index is occupied
       if (map[i] != NULL) {
           cout << map[i]->keyword << ": ";

           //Print all values
           for (int j = 0; j < map[i]->currSize; j++) {
               cout << map[i]->values[j];
               if (j < map[i]->currSize - 1) {
                   cout << ", ";
               }
           }
           cout << endl;
       }
   }
}

void hashMap::reHash() {
   if (numKeys < mapSize*0.7) return;
   auto old = map;
   int newSize = getClosestPrime(mapSize*2);
   map = new hashNode *[newSize];
   int oldSize = mapSize;
   mapSize = newSize;
   numKeys = 0;


   for (int x = 0; x < mapSize; x++){
       map[x] = NULL;
   }
   for (int i = 0; i < oldSize; i++){
       if (old[i] != NULL){
           for (int j = 0; j < old[i]->currSize; j++){
               addKeyValue(old[i]->keyword, old[i]->values[j]);
           }
       }
   }
}


int hashMap::getClosestPrime(int n) {
   if (n & 1) n -= 2;
   else n--;
   int j;
   for (int i = n; i >= 2; i-=2){
       if (i % 2 == 0) continue;
       for (j = 3; j <= sqrt(i); j += 2){
           if (i % j == 0) break;
       }
       if (j > sqrt(i)) return i;
   }
   return 2;
}
