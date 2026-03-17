#include "LinkedList.h"

// Constructor
LinkedList::LinkedList()
{
    head = nullptr;
    size = 0;
}

// Destructor
LinkedList::~LinkedList()
{
    Book* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;      // advance head before deletion
        delete temp;
    }
}

// return ptr to first node
Book* LinkedList::getHead()
{
    return head;
}

// return number of books inside the Linked list
int LinkedList::getSize()
{
    return size;
}

// This function does a linear search on the Book list with the given title and edition
// it returns true if the corresponding Book is found, otherwise it returns false.
bool LinkedList::searchBook(string title, string edition)
{
    Book* temp = head;
    string titleEdition = title + " " + edition;
    while (temp != nullptr) {
        if (titleEdition.compare(temp->titleEdition) == 0) {
            return true;                // match found
        }
        temp = temp->next;
    }
    return false;              // no match
}

// Insert the parameter Book at the head of the linked list.
// return true if it is inserted successfully and false otherwise
bool LinkedList::insertBook(string title, string edition, int pages, double price)
{
    Book* newBook = new Book(title, edition, pages, price);
    string titleEdition = title + " " + edition;
    if (!searchBook(title, edition)) {            // check if there is a duplicate before inserting
        newBook->next = head;
        head = newBook;
        size++;
        return true;
    }
    delete newBook;
    return false;
}

// Delete the Book with the given title and edition from the linked list.
// Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteBook(string title, string edition)
{
    Book* temp = head;
    Book* prev = nullptr;
    string titleEdition = title + " " + edition;
    while (temp != nullptr) {
        if (titleEdition.compare(temp->titleEdition) == 0) {
            if (prev == nullptr) {                 // if this is the head node
                head = temp->next;              
            }
            else {                               // any other node
                prev->next = temp->next;
            }
            delete temp;
            size--;
            return true;

        }
        prev = temp;
        temp = temp->next;
    }
    return false;              // the given book doesnt exist
}

// This function displays the content of the linked list.
void LinkedList::displayList()
{
    Book* temp = head;
    if (head == nullptr)
    {
        // empty linked list, print nothing here
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