#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include "Item.h"

class Journal : public Item
{
private:
    std::string journalName;

public:
    Journal();
    Journal(int id, std::string name);

    std::string getJournalName();
    
};

#endif 
