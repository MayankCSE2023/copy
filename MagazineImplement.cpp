#include <iostream>
#include <string>
#include "Magazine.h"


Magazine::Magazine(){}

Magazine::Magazine(int id, std::string rank,
                   std::string publication) : Item(id), rank(rank),
                    publication(publication) {}

std::string Magazine ::getRank()
{
    return rank;
}

std::string Magazine ::getPublication()
{
    return publication;
}
