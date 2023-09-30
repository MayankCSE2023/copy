compile: BookImplement.cpp libraryImplement.cpp main.cpp
	g++ -g BookImplement.cpp LibraryImplement.cpp main.cpp StudentImplement.cpp FacultyImplement.cpp -o main
