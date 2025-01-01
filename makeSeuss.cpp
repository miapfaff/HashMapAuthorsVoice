//
// Mia Pfaff & Emma Judd
//
#include "makeSeuss.hpp"
#include "hashMap.hpp"
#include <iostream>
#include "makeSeuss.hpp"
#include "hashMap.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

makeSeuss::makeSeuss(string f1,string f2,bool h1, bool c1) {
    ht = new hashMap(h1,c1);
    newfile = f2;
    fn = f1;
    readFile();
    writeFile();
}

void makeSeuss::readFile() {
    ifstream infile(fn.c_str(), ios::in);
    if (!infile.is_open()) {
        cout << "Error opening file: " << fn << endl;
        return;
    }

    char bom[3] = {0};
    infile.read(bom, 3);
    if (bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF) {
        cout << "BOM detected, removing..." << endl;
    } else {
        infile.seekg(0);
    }

    string key = "", value = "";
    infile >> key;
    ht->first = key;

    while (infile >> value) {
        cout << "Reading key: " << key << ", value: " << value << endl;
        ht->addKeyValue(key, value);
        key = value;
        value = "";
    }

    ht->addKeyValue(key, value);
    infile.close();
    ht->printMap();
}

void makeSeuss::writeFile() {
    ofstream outfile(newfile.c_str(),ios::out);
    outfile << "\n" << "-------Number of Original Collisions:\t" << ht->collisionct1 << "\n";
    outfile << "-------Number of Post Collisions:\t" << ht->collisionct2 << "\n";

    outfile << ht->first << " ";
    string key = "";
    string value = ht->map[ht->getIndex(ht->first)]->getRandValue();
    int ct = 0;
    int len = 0;
    while (ct < 500 &&  value != "") {
        key = value;
        outfile << key << " ";
        if (len == 11) {
            outfile << "\n";
            len = 0;
        }
        else len++;
        value = ht->map[ht->getIndex(key)]->getRandValue();
        ct ++;
    }
    outfile.close();
}




