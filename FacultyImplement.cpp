#include "Faculty.h"

Faculty ::Faculty(){
}

Faculty ::Faculty(int id,std::string name): User(id), userName(name) {
    userType="Faculty";
}

string Faculty::getUserName(){
    return userName;
}