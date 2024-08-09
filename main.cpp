#include <iostream>
#include <fstream>
#include <string>

class Book
{
	private:
		std::string title;
		std::string author;
		std::string isbn;
		bool available;
		
	public:
		Book(std::string title, std::string author, std::string isbn)
		{
			this -> title = title;
			this -> author = author;
			this -> isbn = isbn;
			this -> available = true;
		}
		
		// Test
		void testPrintInfo()
		{
			std::cout << title << ' ' << author << ' ' << isbn << '\n';
		}
		
	// idk why we need getters and setters, the Library class is gonna provide the new books anyway?
};

class User
{
	private:
		std::string userId;
		std::string name;
		// std::string[] borrowedBooks; (I dunno how to make a list of strings)
		
	public:
		User(std::string userId, std::string name)
		{
			this -> userId = userId;
			this -> name = name;
		}
};

int main()
{
	std::cout << "yo" << '\n';
	
	// Test
	Book testBook1("Bible", "Jesus", "3434");
	testBook1.testPrintInfo();
	
	return 0;
}