
// Description: A simple linked list that implements a list of Book objects. A user can
//              perform searching, insertion or deletion on the linked list.

#pragma once
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

typedef struct Book
{
    string title, edition;
    int pages;
    double price;
    struct Book* next;
    string titleEdition;

    Book(string t, string e, int p, double pr) : title(t), edition(e), pages(p), price(pr), next(nullptr) {
        titleEdition = title + " " + edition;
    }

} Book;

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

//Constructor
LinkedList::LinkedList()
{
    head = nullptr;
    size = 0;
}

//Destructor
LinkedList::~LinkedList()
{
    Book* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

Book* LinkedList::getHead()
{
    return head;
}

//Return number of books inside the Linked list
int LinkedList::getSize()
{
    return size;
}

//This function does a linear search on the Book list with the given title and edition
//it returns true if the corresponding Book is found, otherwise it returns false.
bool LinkedList::searchBook(string title, string edition)
{
    Book* temp = head;
    string titleEdition = title + " " + edition;
    while (temp != nullptr) {
        if (titleEdition.compare(temp->titleEdition) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//Insert the parameter Book at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertBook(string title, string edition, int pages, double price)
{
    Book* newBook = new Book(title, edition, pages, price);
    string titleEdition = title + " " + edition;
    if (!searchBook(title, edition)) {
        newBook->next = head;
        head = newBook;
        size++;
        return true;
    }
    delete newBook;
    return false;
}

//Delete the Book with the given title and edition from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteBook(string title, string edition)
{
    Book* temp = head;
    Book* prev = nullptr;
    string titleEdition = title + " " + edition;
    while (temp != nullptr) {
        if (titleEdition.compare(temp->titleEdition) == 0) {
            if (prev == nullptr) {
                head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            delete temp;
            size--;
            return true;

        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
    Book* temp = head;
    if (head == nullptr)
    {
        //empty linked list, print nothing here
        return;
    }
    else
    {
        while (temp != nullptr) {
            cout << left << setw(45) << temp->title
                << left << setw(5) << temp->edition
                << right << setw(8) << temp->pages
                << setw(8) << fixed << setprecision(2) << temp->price << "\n";
            temp = temp->next;
        }
    }
}
