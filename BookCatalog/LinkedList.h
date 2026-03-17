// A simple linked list that implements a list of Book objects. A user can
// perform searching, insertion or deletion on the linked list.

#pragma once
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Book
{
    string title, edition;
    int pages;
    double price;
    struct Book* next;
    string titleEdition;

    Book(string t, string e, int p, double pr) : title(t), edition(e), pages(p), price(pr), next(nullptr) {
        titleEdition = title + " " + edition;
    }

};

class LinkedList
{
private:
    Book* head;
    int size;      //a variable represents number of Books inside the list
public:
    LinkedList();
    ~LinkedList();
    Book* getHead();
    int getSize();
    bool searchBook(string title, string edition);
    bool insertBook(string title, string edition, int pages, double price);
    bool deleteBook(string title, string edition);
    void displayList();
};
