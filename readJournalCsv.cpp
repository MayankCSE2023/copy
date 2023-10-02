#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Library.h"

void Library ::readJournalCsv(const std::string &filename)
{

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string ieee;

    while (std::getline(file, ieee))
    {
        // Remove leading and trailing whitespaces from the ieee
        size_t firstNotSpace = ieee.find_first_not_of(' ');
        if (firstNotSpace != std::string::npos)
        {
            size_t lastNotSpace = ieee.find_last_not_of(' ');
            ieee = ieee.substr(firstNotSpace, lastNotSpace - firstNotSpace + 1);
        }

        if (!ieee.empty())
        {
            std::cout << ieee << std::endl;
        }

        if (item_count < MAX_ITEM)
        { // Check for array bounds
            Journal journal(item_count, ieee);
            journals[item_count++] = journal;
        }
    }

    file.close();
}