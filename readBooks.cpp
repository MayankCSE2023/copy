#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class LibraryItems
{
protected:
    int id;
    std::string type;

public:
    LibraryItems(int id, std::string type)
        : id(id), type(type) {}

    ~LibraryItems() {}
};

// Books//Books//Books//Books//Books//Books//Books//Books//Books//Books//Books//Books//Books//Books

class Book : public LibraryItems
{
private:
    int isbn;
    std::string author;
    std::string title;
    bool available;
    int book_count; // Number of available copies in the library

public:
    Book();
    Book(int id, std::string type, int isbn, std::string author, std::string title, int book_count)
        : LibraryItems(id, type), isbn(isbn), author(author), title(title), available(true), book_count(book_count) {}

    ~Book() {}

    int getId() const
    {
        return id;
    }

    // Getter for ISBN
    int getISBN() const
    {
        return isbn;
    }

    // Getter for author
    std::string getAuthor() const
    {
        return author;
    }

    // Getter for title
    std::string getTitle() const
    {
        return title;
    }

    bool isAvailable() const
    {
        return available;
    }

    bool borrow()
    {
        if (book_count > 0)
        {

            if (--book_count == 0)
            {
                available = false; // Mark the bookCount as unavailable when all copies are borrowed
            }
            return true; // Book is successfully borrowed
        }

        return false; // Book is not available for borrowing
    }

    int getCount() const
    {
        return book_count;
    }
};

class User
{
private:
    int userId;
    std::string userName;

public:
    User(int id, const std::string &uname)
        : userId(id), userName(uname) {}

    int getUserId() const
    {
        return userId;
    }

    std::string getUsername() const
    {
        return userName;
    }

    void displayUserInfo() const
    {
        std::cout << "User ID: " << userId << std::endl;
        std::cout << "Username: " << userName << std::endl;
    }
};

class Student : public User
{
private:
    std::vector<Book *> borrowedBooks;
    std::string userType;
    std::string userRoll;
    std::string course;

public:
    Student(int id, const std::string &uname, const std::string &nameR, const std::string &course)
        : User(id, uname), userRoll(nameR), course(course), userType("Student") {}

    std::string getUserType() const
    {
        return userType;
    }

    std::string getFullName() const
    {
        return userRoll;
    }

    std::string getCourse() const
    {
        return course;
    }

    void borrowBook(Book *book)
    {
        borrowedBooks.push_back(book);
    }

    void displayUserInfo() const
    {
        User::displayUserInfo();
        std::cout << "User Type: " << userType << std::endl;
        std::cout << "Full Name: " << userRoll << std::endl;
        std::cout << "Course: " << course << std::endl;

        if (!borrowedBooks.empty())
        {
            std::cout << "Borrowed Books:" << std::endl;
            for (const Book *book : borrowedBooks)
            {
                std::cout << " - " << book->getTitle() << " (ISBN: " << book->getISBN() << ")" << std::endl;
            }
        }
    }
};

class Faculty : public User
{
private:
    std::vector<Book *> borrowedBooks;
    std::string userType;

public:
    Faculty(int id, const std::string &uname)
        : User(id, uname), userType("Faculty") {}

    std::string getUserType() const
    {
        return userType;
    }

    void borrowBook(Book *book)
    {
        borrowedBooks.push_back(book);
    }

    void displayUserInfo() const
    {
        User::displayUserInfo();
        std::cout << "User Type: " << userType << std::endl;

        if (!borrowedBooks.empty())
        {
            std::cout << "Borrowed Books:" << std::endl;
            for (const Book *book : borrowedBooks)
            {
                std::cout << " - " << book->getTitle() << " (ISBN: " << book->getISBN() << ")" << std::endl;
            }
        }
    }
};

static int bookCount = 0;
static int userCount = 0;

class Library
{
private:
    static const int MAX_BOOKS = 100000; // Maximum number of books
    static const int MAX_USERS = 1000;   // Maximum number of users
    Book *books[MAX_BOOKS];              // Array to store books
    Student *students[MAX_USERS];        // Array to store students
    Faculty *faculty[MAX_USERS];         // Array to store faculty
    int studentCount = 0;
    int facultyCount = 0;

public:
    Library()
    {
        readBooksFromCSV("books.csv");
    }

   void readBooksFromCSV(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Unable to open file." << endl;
            return;
        }

        string line;
        getline(file, line);

        int book_id, books_count, isbn;
        string authors, original_title;
        int id = 1; // Initialize id to 1

        while (getline(file, line))
        {
            istringstream iss(line);
            string token;

            if (getline(iss, token, ','))
                book_id = stoi(token);

            for (int i = 0; i < 3; i++)
            {
                getline(iss, token, ',');
            }

            if (getline(iss, token, ','))
                books_count = stoi(token);

            if (getline(iss, token, ','))
                isbn = stoi(token);

            getline(iss, token, ',');

            if (std::getline(iss, token, ',') || iss.eof())
            {
                authors = token;

                if (token.front() == '\"')
                {
                    authors.clear();
                    token = token.substr(1, token.length() - 1);
                    authors = token;

                    while (!iss.eof())
                    {
                        std::getline(iss, token, ',');
                        authors += "," + token;

                        if (token.back() == '\"' || iss.peek() == '\n')
                        {
                            break;
                        }
                    }
                }
            }

            getline(iss, token, ',');

            if (getline(iss, original_title, ','))
                ;

            Book book(bookCount, "Book", isbn, authors, original_title, books_count); // Use bookCount as ID
            addBook(book);
            bookCount++; // Increment bookCount
        }

        file.close();
    }

    void createUser()
    {
        // Ask for user details
        static int userId = 1;

        std::string userName;
        std::string userRoll;
        std::string course;
        std::string type;
        int input;

        std::cout << "Are you a Student or a Faculty : \n1.Student \n2.Faculty " << std::endl;
        cin >> input;

        if (input == 1)
        {
            std::cout << "Enter Your name: ";
            cin >> userName;

            std::cout << "Enter your roll no: ";
            cin >> userRoll;
            std::cout << "Enter Course: ";
            cin >> course;
            type = "Student";

            Student *newUser = nullptr;

            newUser = createStudent(userId, userName, userRoll, course);
            borrow(newUser->getUserId(), type);
        }
        else if (input == 2)
        {
            std::cout << "Enter Your name: ";
            cin >> userName;
            type = "Faculty";

            Faculty *newUser = nullptr;

            newUser = createFaculty(userId, userName);
            borrow(newUser->getUserId(), type);
        }
        else
        {
            std::cout << "Invalid Input" << std::endl;
        }
    }

    // Create a Student object and add it to the library
    Student *createStudent(int id, const std::string &uname, const std::string &name, const std::string &course)
    {
        Student *newStudent = new Student(id, uname, name, course);
        addStudent(*newStudent);
        return newStudent;
    }

    // Create a Faculty object and add it to the library
    Faculty *createFaculty(int id, const std::string &uname)
    {
        Faculty *newFaculty = new Faculty(id, uname);
        addfaculty(*newFaculty);
        return newFaculty;
    }

    void addStudent(const Student &student)
    {
        if (studentCount < MAX_USERS)
        {
            students[studentCount++] = new Student(student);
        }
        else
        {
            std::cout << "Library has reached the maximum number of users." << std::endl;
        }
    }
    void addfaculty(const Faculty &fac)
    {
        if (facultyCount < MAX_USERS)
        {
            faculty[facultyCount++] = new Faculty(fac);
        }
        else
        {
            std::cout << "Library has reached the maximum number of users." << std::endl;
        }
    }

   void addBook(const Book &book)
    {
        if (bookCount < MAX_BOOKS)
        {
            books[bookCount] = new Book(book);
        }
        else
        {
            std::cout << "Library is full. Cannot add more books." << std::endl;
        }
    }

    void borrow(int userId, string type)
    {
        int input;
        int isbn;
        cout << "Which item you want to borrow?\n 1. Book\n2. Magazine\n 3.Journal";
        cin >> input;

        if (input == 1)
        {
            cout << "Enter Book ISBN: ";
            cin >> isbn;

            requestToBorrowBook(userId, isbn, type);
        }
    }

    // Inside the Library class
    void requestToBorrowBook(int userId, int isbn, string type)
    {
        // Find the user by user ID
        Student *studentUser;
        Faculty *facultyUser;

        if (type == "Student")
        {
            studentUser = findStudentById(userId);
        }
        else
        {
            facultyUser = findFacultyById(userId);
        }

        // Find the bookCount by ISBN
        Book *book = findBookByISBN(isbn);
        if (book == nullptr)
        {
            std::cout << "Book not found." << std::endl;
            return;
        }

        // Check if the bookCount is available for borrowing
        if (book->isAvailable())
        {
            // Book is available, mark it as borrowed and print a message
            book->borrow();
            std::cout << "Book borrowed successfully!" << std::endl;

            // You can also keep track of user's borrowed books here if needed
        }
        else
        {
            std::cout << "Book is not available for borrowing." << std::endl;
        }
    }

    // Inside the Library class
    Student *findStudentById(int userId)
    {
        for (int count = 0; count < studentCount; ++count)
        {
            if (students[count]->getUserId() == userId)
            {
                return students[count];
            }
        }
        return nullptr; // User not found
    }

    Faculty *findFacultyById(int userId)
    {
        for (int count = 0; count < facultyCount; ++count)
        {
            if (students[count]->getUserId() == userId)
            {
                return faculty[count];
            }
        }
        return nullptr; // User not found
    }

    // Inside the Library class
    Book *findBookByISBN(int isbn)
    {
        for (int count = 0; count < bookCount; count++)
        {
            if (books[count]->getISBN() == isbn)
            {
                return books[count];
            }
        }
        return nullptr; // Book not found
    }

    void printAllBooks() const
    {
        cout << "List of Books in the Library:" << endl;
        for (int i = 0; i < bookCount; ++i)
        {
            cout << "Book ID: " << books[i]->getId() << endl;
            cout << "Title: " << books[i]->getTitle() << endl;
            cout << "Author: " << books[i]->getAuthor() << endl;
            cout << "ISBN: " << books[i]->getISBN() << endl;
            cout << "Available Copies: " << books[i]->getCount() << endl;
            cout << "-------------------" << endl;
        }
    }

    ~Library() {}
};

int main(int argc, char const *argv[])
{
    Library library;
    Student *student;
    Faculty *faculty;
    int id;

    library.printAllBooks();

    while (true)
    {
    // Print a welcome message
    cout << "Welcome to the Library!" << endl;

    // Ask the user if they have signed up
    cout << "Have you signed up? (yes/no): ";
    string response;
    cin >> response;

    // Check the user's response
    if (response == "yes")
    {
        // Implement code for signed-up users here
        cout << "Are you\n 1.Faculty \n 2.Student:\n";
        int res;
        cin >> res;

        if (res == 1)
        {
            cout << "Enter your Id:";
            cin >> id;

            if (library.findStudentById(id) == nullptr)
            {
                std::cout << "Wrong id." << std::endl;
                return 0;
            }
            library.borrow(id, "Student");
        }
        else if (res == 2)
        {
            cout << "Enter your Id:";
            cin >> id;
            library.findStudentById(id);

            if (library.findFacultyById(id) == nullptr)
            {
                std::cout << "Wrong id." << std::endl;
                return 0;
            }
            library.borrow(id, "Faculty");
        }
        else
        {
            std::cout << "Wrong input!!" << std::endl;
        }

        return 0;

        // You can add functionality for users who have signed up
        // For example, allowing them to borrow books, etc.
    }
    else if (response == "no")
    {
        // Implement code for users who haven't signed up
        library.createUser();
        // You can prompt them to sign up or provide options for browsing the library without signing up
    }
    else
    {
        cout << "Invalid response. Please enter 'yes' or 'no'." << endl;
        continue;
    }

    }
    return 0;
}
