#ifndef BOOK_H
#define BOOK_H

#include "Item.h"
#include <string>

class Book : public Item {
private:
    int isbn;
    std::string author;
    std::string title;
    bool available;
    int bookCount;

public:

    Book();
    Book(int id, int isbn, const std::string &author, const std::string &title,int bookCount);

    std::string getDescription() const;

    // Getter and Setter declaration
    int getISBN() const;
    int getIdFromISBN(int isbn) const;
    void setISBN(int newISBN);
    const std::string& getAuthor() const;
    void setAuthor(const std::string &newAuthor);
    const std::string& getTitle() const;
    void setTitle(const std::string &newTitle);
    bool isAvailable() const;
    void setAvailable(bool newAvailable);
    int getBookCount() const;
    void setBookCount(int newBookCount);
    void printBook() const;
    void issueBook();
};

#endif
