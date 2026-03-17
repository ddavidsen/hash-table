// Hash functions
#pragma once
#include "LinkedList.h"
#include <cmath>

using namespace std;

class Hash
{
private:
    int m;                      // size of the hash table
    LinkedList* hashTable;      // hashTable is a one-dimensional array of LinkedList
    int numOfElements;          // total number of elements inside the hash table

public:
    Hash(int size);
    ~Hash();
    int getNumOfElements();
    int getSize();
    bool hashSearch(string title, string edition);
    bool hashInsert(string title, string edition, int pages, double price);
    bool hashDelete(string title, string edition);
    double hashLoadFactor();
    void hashDisplay();
    void rehash();

    int hashFunction(string key);
};
