
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.

#include <sstream>
#include "LinkedList.h"
#include "Hash.h"
#include <limits>

using namespace std;

//This function used to get a Book key which is the combination of title and edition
void getKey(string oneLine, string& title, string& edition);

int main()
{
    int size = 0;
    int numOfCommand = 0;
    string title, edition;
    int pages;
    double price;
    string input, command;
    double idealLoadFactor;

    cout << "Enter the size of the hash table: ";
    cin >> size;
    cin.ignore(20, '\n');

    Hash* hashTable1 = new Hash(size);

    cout << "Enter book details. Enter \"InsertionEnd\" when done." << endl;
    do {
        getline(cin, input);

        if (input.compare("InsertionEnd") == 0) {
            break;
        }

        else {          //collecting book variables
            stringstream ss(input);
            getline(ss, title, ';');
            getline(ss, edition, ';');
            ss >> pages;
            ss.ignore();
            ss >> price;

            hashTable1->hashInsert(title, edition, pages, price);

        }

    } while (true);

    cout << "\nEnter number of commands: ";
    cin >> numOfCommand;
    cin.ignore(20, '\n');

    cout << "Enter commands: " << endl;
    for (int i = 0; i < numOfCommand; i++)
    {
        getline(cin, input);

        stringstream ss(input);
        getline(ss >> ws, command, ';');

        //get one line command, extract the first token, if only one token
        if (command.compare("hashDisplay") == 0)
        {
            hashTable1->hashDisplay();
        }

        else if (command.compare("hashLoadFactor") == 0) {

            idealLoadFactor = static_cast<double>(hashTable1->getNumOfElements()) / static_cast<double>(hashTable1->getSize());

            cout << fixed << setprecision(2);
            cout << "The ideal load factor is: " << idealLoadFactor << endl;
            cout << "My hash table real load factor is: " << hashTable1->hashLoadFactor() << endl;
            cout << "My hash table performance ratio is: " << (hashTable1->hashLoadFactor() / idealLoadFactor) << endl;
            cout << endl;
        }

        else  //more than one tokens, check the command name, extract the remaining tokens
        {
            getline(ss, title, ';');
            getline(ss, edition, ';');

            if (command == "hashSearch") {
                hashTable1->hashSearch(title, edition);
                cout << endl;
            }

            else  if (command.compare("hashDelete") == 0) {
                hashTable1->hashDelete(title, edition);
                cout << endl;
            }

            else {
                cout << "Invalid command" << endl;
                cout << endl;
            }
        }
    } //end for loop
    delete hashTable1;
    return 0;
}

//********************************************************************************
//Given one line, this function extracts title and edition of a Book
//This function is completed and given here as a study guide for extracting tokens
void getKey(string oneLine, string& title, string& edition)
{
    string delimiter = ";";
    int pos = oneLine.find(delimiter);
    string command = oneLine.substr(0, pos);
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    title = oneLine.substr(0, pos);
    oneLine.erase(0, pos + delimiter.length());

    pos = oneLine.find(delimiter);
    edition = oneLine.substr(0, pos);
    oneLine.erase(0, pos + delimiter.length());
}

//alternate getkey

//getKey(input, title, edition);
//
//stringstream ss(input);
//ss >> pages;
//ss.ignore();
//ss >> price;
//
//hashTable1->hashInsert(title, edition, pages, price);
