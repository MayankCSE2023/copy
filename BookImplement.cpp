#include "Book.h"
#include <iostream>
// Constructor implementations
Book::Book() {
    // Initialize member variables here if needed
}

Book::Book(int id, int isbn, const std::string &author, const std::string &title,int bookCount)
    : Item(id), isbn(isbn), author(author), title(title), available(true) {
    // Initialize member variables here if needed
}

// getDescription implementation
std::string Book::getDescription() const {
    return "Book: " + title + " (ISBN: " + std::to_string(isbn) + ")";
}


// Getter and Setter implementations
int Book::getISBN() const {
    return isbn;
}

int Book:: getIdFromISBN(int isbn) const{
    return getId();
}

void Book::setISBN(int newISBN) {
    isbn = newISBN;
}

int Book::getBookCount() const {
    return bookCount;
}

void Book::setBookCount(int bookCount) {
    this->bookCount = bookCount;
}


const std::string& Book::getAuthor() const {
    return author;
}

void Book::setAuthor(const std::string &newAuthor) {
    author = newAuthor;
}

const std::string& Book::getTitle() const {
    return title;
}

void Book::setTitle(const std::string &newTitle) {
    title = newTitle;
}

bool Book::isAvailable() const {
    return available;
}

void Book::setAvailable(bool newAvailable) {
    available = newAvailable;
}

void Book::issueBook(){
    std::cout << "Your Book details are:-" << std::endl;
     std::cout << "Id: " << getId() << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
}

void Book::printBook() const {
    std::cout << "Id: " << getId() << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    // You can include other book details as needed
}
