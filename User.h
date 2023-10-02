#ifndef USER_H
#define USER_H

using namespace std;

#include <string>

class User
{
private:
    int userId;

public:
    User(){
    }
    User(int id) : userId(id){};

    int getId(){
        return userId;
    }

    void setId(int id){
        userId=id;
    }
};

#endif
