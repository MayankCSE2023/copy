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
}

void Library::readBookCsv(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    getline(file, line);

    int bookId, bookCount, isbn;
    std::string authors, original_title;

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;

        if (getline(iss, token, ','))
            bookId = std::stoi(token);

        for (int i = 0; i < 3; i++)
        {
            getline(iss, token, ',');
        }

        if (getline(iss, token, ','))
            bookCount = std::stoi(token);

        if (getline(iss, token, ','))
            isbn = std::stoi(token);

        getline(iss, token, ',');

        if (std::getline(iss, token, ',') || iss.eof())
        {
            authors = token;

            if (token.front() == '\"')
            {
                authors.clear();
                token = token.substr(1, token.length() - 1);
                authors = token;

                while (!iss.eof())
                {
                    std::getline(iss, token, ',');
                    authors += "," + token;

                    if (token.back() == '\"' || iss.peek() == '\n')
                    {
                        break;
                    }
                }
            }
        }

        getline(iss, token, ',');

        if (getline(iss, token, ','))
        {
            original_title = token;
        }

        // Add each book according to its count

        if (item_count < MAX_ITEM)
        { // Check for array bounds
            Book book(item_count, isbn, authors, original_title, bookCount);
            books[item_count++] = book;
        }
    }

    file.close();
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
            // current date/time based on current system
            time_t now = time(0);
            char *dt = ctime(&now);
            
            std::cout << "Student User Id " << user.getId() << " been issued book named " << book.getTitle() << " at " << dt << std::endl;
            Log log(user.getId(), book.getIdFromISBN(isbn), string(dt));
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
            // current date/time based on current system
            time_t now = time(0);
            char *dt = ctime(&now);
            
            std::cout << "Faculty User Id " << user.getId() << " been issued book named " << book.getTitle() << " at " << dt << std::endl;
            Log log(user.getId(), book.getIdFromISBN(isbn), string(dt));
            logs[log_count++] = log;
            return;
        }
    }

    
    std::cout << "Book not found!!" << std::endl;
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
        std::cout << student.getUserName() <<"!! You are regestered in the Library. \n\n"
              << std::endl;
        takeRequest(student);
    }
    else
    {
        std::cout << "Enter Your name:" << std::endl;
        cin >> name;
        Faculty facul(user_count, name);
        faculty[user_count++] = facul;
        std::cout << facul.getUserName() <<"!! You are regestered in the Library. \n\n"
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
                
                std::cout << "\n\n" << std::endl;
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
                 
                std::cout << "\n\n" << std::endl;
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
}

void Library::takeRequest(Faculty &faculty)
{
    std::cout << "----------Thank You---------- \n\n"
              << std::endl;
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
}

void Library::printAllLogs() {
    for (int i = 0; i < log_count; ++i) {
        std::cout << "User ID: " << logs[i].userId << std::endl;
        std::cout << "Item ID: " << logs[i].itemId << std::endl;
        std::cout << "Borrow Time: " << logs[i].borrowTime << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}
