#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Library.h"
#include "Book.h"


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