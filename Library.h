#ifndef LIBRARY_H
#define LIBRARY_H

#include "Faculty.h"
#include "Student.h"
//#include "Item.h"
#include "Book.h"


struct Log {
    int userId;             // User ID
    int itemId;             // Item ID
    std::string borrowTime; // Borrow timestamp

    Log(){}

    // Constructor to initialize the log entry
    Log(int uId, int iId, const std::string& bTime)
        : userId(uId), itemId(iId), borrowTime(bTime) {}
};


const int MAX_USER = 10;
const int MAX_ITEM = 200;
const int MAX_LOG = 1000;
static int item_count=0;
static int user_count=0;
static int log_count=0;

class Library {
public:
    Student students[MAX_USER];
    Faculty faculty[MAX_USER];
    Book books[MAX_ITEM];
    Log logs[MAX_LOG];


    Library();  // Constructor

    // Add methods to add users and items, borrow items, return items, etc.
      void readBookCsv(const std::string &filename);
      void readMagazineCsv(const std::string &filename);
      void signUp(int userType);
      void signIn(int id,int userType);
      void takeRequest(Student& student);
      void takeRequest(Faculty& faculty);
      void borrowBook(int isbn,Student& student);
      void borrowBook(int isbn,Faculty& faculty);
      void printAllBooks();
      void printAllLogs();

      
};
     

#endif
