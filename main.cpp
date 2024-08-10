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
			
			if(available)
			{
				std::cout << "Available: True" << '\n';
			}
		}
		
		std::string getTitle()
		{
			return title;
		}
		
		std::string getAuthor()
		{
			return author;
		}
		
		std::string getIsbn()
		{
			return isbn;
		}
		
		bool getAvailability()
		{
			return available;
		}
		
		void setTitle(std::string newTitle)
		{
			title = newTitle;
		}
		
		void setAuthor(std::string newAuthor)
		{
			author = newAuthor;
		}

		void setIsbn(std::string newIsbn)
		{
			isbn = newIsbn;
		}

		void setAvailability(std::string newAvailability)
		{
			// Lol idk
		}		
};

class LibraryUser
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

class Library
{
	private:
		// Arrays for books and userIDs
		
	public:
	
};

int main()
{	
	// Test
	Book testBook1("Bible", "Jesus", "3434");
	std::cout << testBook1.getTitle() << testBook1.getAuthor() << testBook1.getIsbn() << '\n';
	testBook1.setTitle("Bible 2");
	testBook1.setAuthor("Jesus 2");
	testBook1.setIsbn("99999");
	std::cout << testBook1.getTitle() << testBook1.getAuthor() << testBook1.getIsbn() << '\n';
	
	return 0;
}