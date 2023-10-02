#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
private:
    int id;

public:
    Item() {}
    Item(int id) : id(id) {}

    int getId() const
    {
        return id;
    }

    std::string getDescription() const;
};

#endif
