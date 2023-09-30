#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"

class Faculty :public User
{
private:
string userName;
string userType;
    
public:
    Faculty();
    Faculty(int id,string name);

    string getUserName();
};

#endif