#include "Hash.h"

// constructor
Hash::Hash(int size)
{
    m = size;
    numOfElements = 0;
    hashTable = new LinkedList[m];
}

// Destructor
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

// This function searches for a key inside the hash table and
// return true if it is found and false otherwise
bool Hash::hashSearch(string title, string edition)
{
    int slot = hashFunction(title + " " + edition);
    bool found = hashTable[slot].searchBook(title, edition);

    if (found) {
        cout << "\nBook: \"" << title << "\", " << edition << " edition is Found inside the hash table.\n";
    }
    else {
        cout << "\nBook: \"" << title << "\", " << edition << " edition is NOT found inside the hash table.\n";
    }

    return found;
}

// hashInsert inserts a Book with the relevant info. into the hashTable.
// it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string title, string edition, int pages, double price)
{
    int slotToInsert = hashFunction(title + " " + edition);

    if (hashTable[slotToInsert].searchBook(title, edition)) {
        return false;                   // duplicate insertion is not allowed
    }

    bool inserted = hashTable[slotToInsert].insertBook(title, edition, pages, price);

    // if load factor is too high after this insertion, rehash
    if (inserted) {
        numOfElements++;

        double loadFactor = (double)numOfElements / m;

        if (loadFactor > 0.9)
        {
            rehash();
        }
    }
    
    return inserted;
}

// hashDelete deletes a Book with the relevant key from the hashTable.
// it returns true if it is deleted successfully and false otherwise
bool Hash::hashDelete(string title, string edition)
{
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

// This function computes hash table real load factor
// it is the longest linked list size
double Hash::hashGetLongestChain()
{
    double longestSize = 0;             // tracks maximum chain across all buckets
    for (int i = 0; i < m; i++) {
        if (hashTable[i].getSize() > longestSize) {
            longestSize = static_cast<double>(hashTable[i].getSize());
        }
    }
    return longestSize;
}

// This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
    for (int i = 0; i < m; i++) {
        cout << "HashTable[" << i << "], size = " << hashTable[i].getSize() << endl;
        hashTable[i].displayList();
        cout << endl;
    }
}

// given a string key, return the slot number where this book should be hashed to.
// **uses hash by multiplication method
int Hash::hashFunction(string key)
{
    double goldenRatio = (sqrt(5) - 1) / 2;
    int keyAsNum = 0;           // numeric representation of the key (title + edition)

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

void Hash::rehash() {
    int oldSize = m;
    int newSize = m + (m / 2);              // increase number of buckets by ~50%
    m = newSize;
    LinkedList* newTable = new LinkedList[newSize];              // make a new table (array of linkedlists)

    for (int i = 0; i < oldSize; i++)
    {
        Book* current = hashTable[i].getHead();

        while (current != nullptr)
        {
            string key = current->title + " " + current->edition;

            // compute this books index in the new, resized table
            int newIndex = hashFunction(key);

            // insert this book into the new table
            newTable[newIndex].insertBook(
                current->title,
                current->edition,
                current->pages,
                current->price
            );

            current = current->next;
        }
    }

    delete[] hashTable;
    hashTable = newTable;
}