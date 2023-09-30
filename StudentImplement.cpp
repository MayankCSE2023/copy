#include "Student.h"


Student ::Student() {
}

Student ::Student(int id,string name): User(id),userName(name) {
    userType="Student";
}

string Student:: getUserName(){
    return userName;
}
