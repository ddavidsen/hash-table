
// Description: Hash functions

#pragma once
#include "LinkedList.h"
#include <cmath>

using namespace std;

class Hash
{
private:
    int m;                      //size of the hash table
    LinkedList* hashTable;      //hashTable is a one-dimensional array of LinkedList
    int numOfElements;          //total number of elements inside the hash table

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

    int hashFunction(string key);
};

//constructor
Hash::Hash(int size)
{
    m = size;
    numOfElements = 0;
    hashTable = new LinkedList[m];
}

//Destructor
Hash::~Hash()
{
    delete[] hashTable;
}

int Hash::getNumOfElements() {
    return numOfElements;
}

int Hash::getSize() {
    return m;
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of title and edition
bool Hash::hashSearch(string title, string edition)
{
    bool found = false;

    for (int i = 0; i < m; i++) {
        if (hashTable[i].searchBook(title, edition)) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "\nBook: \"" << title << "\", " << edition << " edition is Found inside the hash table.\n";
    }
    else {
        cout << "\nBook: \"" << title << "\", " << edition << " edition is NOT found inside the hash table.\n";
    }

    return found;
}

//hashInsert inserts a Book with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string title, string edition, int pages, double price)
{
    int slotToInsert = hashFunction(title + " " + edition);

    if (hashTable[slotToInsert].searchBook(title, edition)) {
        return false;
    }

    numOfElements++;
    return hashTable[slotToInsert].insertBook(title, edition, pages, price);
}

//hashDelete deletes a Book with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of title and edition
bool Hash::hashDelete(string title, string edition)
{
    string fullKey = title + " " + edition;
    bool found = false;

    int slotToDelete = hashFunction(title + " " + edition);

    if (this->hashSearch(title, edition)) {
        found = hashTable[slotToDelete].deleteBook(title, edition);
    }

    if (found) {
        cout << "\nBook: \"" << title << "\", " << edition << " edition is deleted from hash table.\n";
        numOfElements--;
    }
    else {
        cout << "\nBook: \"" << title << "\", " << edition << " edition is NOT deleted from hash table.\n";
    }

    return found;
}

//This function computes your hash table real load factor
//it is the longest linked list size
double Hash::hashLoadFactor()
{
    double longestSize = 0;
    for (int i = 0; i < m; i++) {
        if (hashTable[i].getSize() > longestSize) {
            longestSize = static_cast<double>(hashTable[i].getSize());
        }
    }
    return longestSize;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
    for (int i = 0; i < m; i++) {
        cout << "HashTable[" << i << "], size = " << hashTable[i].getSize() << endl;
        hashTable[i].displayList();
        cout << endl;
    }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we should hash the key to

//using hash by multiplication as shown in class
int Hash::hashFunction(string key)
{
    double goldenRatio = (sqrt(5) - 1) / 2;
    int keyAsNum = 0;

    for (int i = 0; i < key.length(); i++) {
        keyAsNum += static_cast<int>(static_cast<int>(key[i])) * (i + 1);
    }

    return static_cast<int>(floor(m * fmod(keyAsNum * goldenRatio, 1.0)));
}

//alternate hash function

//int Hash::hashFunction(string key)
//{
//    double goldenRatio = (sqrt(5) - 1) / 2;
//    int keyAsNum = 0;
//
//    for (int i = 0; i < key.length(); i++) {
//        keyAsNum += static_cast<int>(key[i]);
//    }
//
//    return static_cast<int>(floor(m * fmod(keyAsNum * goldenRatio, 1.0)));
//}