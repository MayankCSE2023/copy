#include <iostream>
#include <string>
#include "Journal.h"


Journal::Journal(){}

Journal::Journal(int id, std::string name) : Item(id),journalName(name) {}

std::string Journal ::getJournalName()
{
    return journalName;
}
