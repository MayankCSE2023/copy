#include <iostream>

#include "Library.h"

int main(int argc, char const *argv[])
{
    Library library;
    // library.printAllBooks();

    while (true)
    {

        std::cout << "-----Welcome to the Library-----" << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Are you a registered user?\n1.Yes\n2.No" << std::endl;
        int input;
        cin >> input;
        if (input == 1)
        {
            std::cout << "Are you Student/Faculty?\n1.Student\n2.Faculty" << std::endl;
            int choice;
            cin >> choice;
            std::cout << "Enter you Id:" << std::endl;
            int id;
            cin >> id;
            if (choice == 1)
            {

                library.signIn(id, 1);
            }
            else if (choice == 2)
            {

                library.signIn(id, 2);
            }else
            {
                std::cout << "Invalid input!!!!!!! ...try again.." << std::endl;
                continue;
            }
            
        }
        else if (input == 2)
        {
            std::cout << "Are you Student/Faculty?\n1.Student\n2.Faculty" << std::endl;
            int choice;
            cin >> choice;
            
            if (choice==1 || choice==2)
            {
            library.signUp(choice);
            }else
            {
                std::cout << "Invalid Input...try Again!!" << std::endl;
            }
            
            
        }
        else
        {
            std::cout << "Invald Input. Try Again!!!!!!" << std::endl;
            continue;
        }

        std::cout << "Do you want to print logs?\n1.Yes\n2.No" << std::endl;
        int ch;
        cin>> ch;
        if (ch==1)
        {
            library.printAllLogs();
        }
        

    }

    return 0;
}
