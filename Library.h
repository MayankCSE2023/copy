#ifndef LIBRARY_H
#define LIBRARY_H

#include "Faculty.h"
#include "Student.h"
#include "Magazine.h"
#include "Book.h"
#include "Journal.h"


struct Log {
    int userId;             // User ID
    std:: string userName;            
    int itemId;             // Item ID
    std:: string itemName;             
    std::string borrowTime; // Borrow timestamp
    std::string dueTime; // Borrow timestamp

    Log(){}

    // Constructor to initialize the log entry
    Log(int uId,const std::string& uName, int iId,const std::string& iName, const std::string& bTime,const std::string& dTime)
        : userId(uId),userName(uName), itemId(iId),itemName(iName), borrowTime(bTime),dueTime(dTime) {}
};


const int MAX_USER = 10;
const int MAX_ITEM = 500;
const int MAX_LOG = 1000;
static int item_count=0;
static int user_count=0;
static int log_count=0;
static int Mag_count=0;
static int jour_count=0;

class Library {
public:
    Student students[MAX_USER];
    Faculty faculty[MAX_USER];
    Book books[MAX_ITEM];
    Magazine magazines[MAX_ITEM];
    Journal journals[MAX_ITEM];
    Log logs[MAX_LOG];


    Library();  // Constructor

    // Add methods to add users and items, borrow items, return items, etc.
      void readBookCsv(const std::string &filename);
      void readMagazineCsv(const std::string &filename);
      void readJournalCsv(const std::string &filename);
      void signUp(int userType);
      void signIn(int id,int userType);
      void takeRequest(Student& student);
      void takeRequest(Faculty& faculty);
      void borrowBook(int isbn,Student& student);
      void borrowBook(int isbn,Faculty& faculty);
      void borrowMagazine(string publication,Student& student);
      void borrowMagazine(string publication,Faculty& faculty);
      void downloadJournal(string name,Student& student);
      void downloadJournal(string name,Faculty& faculty);
      void printAllBooks();
      void printAllLogs();

      
};
     

#endif
