#ifndef MAGAZINE_H
#define MAGAZINE_H

#include <string>
#include "Item.h"

class Magazine : public Item
{
private:
    std::string rank;
    std::string publication;

public:
    Magazine();
    Magazine(int id, std::string rank, std::string publication);

    std::string getRank();
    std::string getPublication();
};

#endif // MAGAZINE_H
