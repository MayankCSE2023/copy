#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User
{
private:
string userName;
string userType;
    
public:
    Student(); 
    Student(int id,string name);

    string getUserName();
};

#endif