#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

#include "Library.h"

Library::Library()
{
    Library::readBookCsv("books.csv");
    Library::readMagazineCsv("Magazines.csv");
    Library::readJournalCsv("journals.csv");
}

void Library::printAllBooks()
{
    int i = 0;
    while (i < item_count)
    {
        std::cout << "Book ID: " << books[i].getId() << std::endl;
        std::cout << "Title: " << books[i].getTitle() << std::endl;
        std::cout << "Author: " << books[i].getAuthor() << std::endl;
        std::cout << "ISBN: " << books[i].getISBN() << std::endl;
        std::cout << "-------------------" << std::endl;
        i++;
    }
}

void Library::borrowBook(int isbn, Student &user)
{
    for (Book book : books)
    {
        if (book.getISBN() == isbn)
        {
            // Get the current time
            time_t now = time(0);
            std::string dt = ctime(&now);

            // Calculate due time by adding one month (30 days)
            struct tm due_tm = *localtime(&now);
            due_tm.tm_mon += 1; // Add one month
            time_t due = mktime(&due_tm);
            std::string ret = ctime(&due);

            std::cout << "Student User Id " << user.getId() << " been issued book named " << book.getTitle() << " at " << dt << std::endl;
            Log log(user.getId(), user.getUserName(), book.getId(), book.getTitle(), dt, ret);
            logs[log_count++] = log;
            return;
        }
    }

    std::cout << "Book not found!!" << std::endl;
    return;
}

void Library::borrowBook(int isbn, Faculty &user)
{
    for (Book book : books)
    {
        if (book.getISBN() == isbn)
        {
            // Get the current time
            time_t now = time(0);
            std::string dt = ctime(&now);

            // Calculate due time by adding one month (30 days)
            struct tm due_tm = *localtime(&now);
            due_tm.tm_mon += 6; // Add one month
            time_t due = mktime(&due_tm);
            std::string ret = ctime(&due);

            std::cout << "Faculty User Id " << user.getId() << " been issued book named " << book.getTitle() << " at " << dt << std::endl;
            Log log(user.getId(), user.getUserName(), book.getId(), book.getTitle(),dt, ret);
            logs[log_count++] = log;
            return;
        }
    }

    std::cout << "Book not found!!" << std::endl;
    return;
}

void Library::borrowMagazine(string publication, Student &user)
{
    for (Magazine magazine : magazines)
    {
        if (magazine.getPublication() == publication)
        {
            // Get the current time
            time_t now = time(0);
            std::string dt = ctime(&now);

            // Calculate due time by adding one month (30 days)
            struct tm due_tm = *localtime(&now);
            due_tm.tm_mon += 1; // Add one month
            time_t due = mktime(&due_tm);
            std::string ret = ctime(&due);

            std::cout << "Student User Id " << user.getId() << " been issued Magazine named " << magazine.getPublication() << " which is ranked on " << magazine.getRank() << " at " << dt << std::endl;
             Log log(user.getId(),user.getUserName(),magazine.getId() ,magazine.getPublication(),dt,ret);
             logs[log_count++] = log;
            return;
        }
    }

    std::cout << "Magazine not found!!" << std::endl;
    return;
}

void Library::borrowMagazine(string publication, Faculty &user)
{
    for (Magazine magazine : magazines)
    {
        if (magazine.getPublication() == publication)
        {
            // Get the current time
            time_t now = time(0);
            std::string dt = ctime(&now);

            // Calculate due time by adding one month (30 days)
            struct tm due_tm = *localtime(&now);
            due_tm.tm_mon += 6; // Add six month
            time_t due = mktime(&due_tm);
            std::string ret = ctime(&due);

            std::cout << "Faculty User Id " << user.getId() << " been issued Magazine named " << magazine.getPublication() << " which is ranked on " << magazine.getRank() << " at " << dt << std::endl;
            Log log(user.getId(),user.getUserName(),magazine.getId() ,magazine.getPublication(),dt,ret);
            logs[log_count++] = log;
            return;
        }
    }

    std::cout << "Magazine not found!!" << std::endl;
    return;
}

void Library::downloadJournal(std::string name, Student &user)
{

    for (Journal journal : journals)
    {
        if (journal.getJournalName() == name)
        {
            // current date/time based on current system
            time_t now = time(0);
            std::string dt = ctime(&now);

            std::cout << "Student User Id " << user.getId() << " has given access to journal " << journal.getJournalName() << dt << std::endl;
            Log log(user.getId(), user.getUserName(),journal.getId(),journal.getJournalName(), dt,"Not Applicable");
            logs[log_count++] = log;
            return;
        }
    }

    std::cout << "Journal not found!!" << std::endl;
    return;
}

void Library::downloadJournal(std::string name, Faculty &user)
{

    for (Journal journal : journals)
    {
        if (journal.getJournalName() == name)
        {
            // current date/time based on current system
            time_t now = time(0);
            char *dt = ctime(&now);

            std::cout << "Faculty User Id " << user.getId() << " has given access to journal " << journal.getJournalName() << dt << std::endl;
            Log log(user.getId(), user.getUserName(),journal.getId(),journal.getJournalName(), dt,"Not Applicable");
            logs[log_count++] = log;
            return;
        }
    }

    std::cout << "Journal not found!!" << std::endl;
    return;
}

void Library::signUp(int choice)
{

    string name;

    if (choice == 1)
    {
        std::cout << "Enter Your name:" << std::endl;
        cin >> name;
        Student student(user_count, name);
        students[user_count++] = student;
        std::cout << student.getUserName() << "!! You are regestered in the Library. \n\n"
                  << std::endl;
        takeRequest(student);
    }
    else
    {
        std::cout << "Enter Your name:" << std::endl;
        cin >> name;
        Faculty facul(user_count, name);
        faculty[user_count++] = facul;
        std::cout << facul.getUserName() << "!! You are regestered in the Library. \n\n"
                  << std::endl;
        takeRequest(facul);
    }
}

void Library::signIn(int id, int choice)
{

    if (choice == 1)
    {
        for (Student student : students)
        {
            if (student.getId() == id)
            {

                std::cout << "\n\n"
                          << std::endl;
                std::cout << "Welcome " << student.getUserName() << " to the Library!!" << std::endl;

                takeRequest(student);
                return;
            }
        }
    }
    else
    {
        for (Faculty faculty : faculty)
        {
            if (faculty.getId() == id)
            {

                std::cout << "\n\n"
                          << std::endl;
                std::cout << "Welcome " << faculty.getUserName() << " to the Library!!" << std::endl;
                takeRequest(faculty);
                return;
            }
        }
    }
    std::cout << "Id not found!!!!!!!....try Again" << std::endl;
}

void Library::takeRequest(Student &student)
{
    std::cout << "What operation you want to perform?\n1. Borrow Book\n2. Borrow Magzine\n3. Download journal " << std::endl;

    int choice;
    cin >> choice;
    if (choice == 1)
    {
        std::cout << "Do you have book's ISBN Number?(yes/no)" << std::endl;
        string input;
        cin >> input;
        if (input == "yes")
        {
            int isbn;
            std::cout << "Enter ISBN:" << std::endl;
            cin >> isbn;
            borrowBook(isbn, student);
        }
    }
    else if (choice == 2)
    {
        std::cout << "Enter Name of the publication: " << std::endl;
        std::string publication;
        cin.ignore();              // Clear the input buffer
        getline(cin, publication); // Read the entire line
        borrowMagazine(publication, student);
    }
    else if (choice == 3)
    {
        std::cout << "Enter Name of the Journal: " << std::endl;
        std::string journal;
        cin.ignore();          // Clear the input buffer
        getline(cin, journal); // Read the entire line
        downloadJournal(journal, student);
    }
    else
    {
        std::cout << "Invalid Input!!! try again." << std::endl;
        takeRequest(student);
    }
}

void Library::takeRequest(Faculty &faculty)
{
    std::cout << "What operation you want to perform?\n1. Borrow Book\n2. Borrow Magzine\n3. Download journal " << std::endl;

    int choice;
    cin >> choice;
    if (choice == 1)
    {
        std::cout << "Do you have book's ISBN Number?(yes/no)" << std::endl;
        string input;
        cin >> input;
        if (input == "yes")
        {
            int isbn;
            std::cout << "Enter ISBN:" << std::endl;
            cin >> isbn;
            borrowBook(isbn, faculty);
        }
    }
    else if (choice == 2)
    {
        std::cout << "Enter Name of the publication: " << std::endl;
        std::string publication;
        cin.ignore();              // Clear the input buffer
        getline(cin, publication); // Read the entire line
        borrowMagazine(publication, faculty);
    }
    else if (choice == 3)
    {
        std::cout << "Enter Name of the Journal: " << std::endl;
        std::string journal;
        cin.ignore();          // Clear the input buffer
        getline(cin, journal); // Read the entire line

        downloadJournal(journal, faculty);
    }
    else
    {
        std::cout << "Invalid Input!!! try again." << std::endl;
        takeRequest(faculty);
    }
}

void Library::printAllLogs()
{
    for (int i = 0; i < log_count; ++i)
    {
        std::cout << "User ID: " << logs[i].userId << std::endl;         // Print User ID
        std::cout << "User Name: " << logs[i].userName << std::endl;     // Print User Name
        std::cout << "Item ID: " << logs[i].itemId << std::endl;         // Print Item ID
        std::cout << "Item Name: " << logs[i].itemName << std::endl;     // Print Item Name
        std::cout << "Borrow Time: " << logs[i].borrowTime << std::endl; // Print Borrow Time
        std::cout << "Due Time: " << logs[i].dueTime << std::endl;       // Print Due Time
        std::cout << "-------------------" << std::endl;                 // Separator
    }
}
