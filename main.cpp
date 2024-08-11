#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
		std::vector<std::string> borrowedBooks;
		
	public:
		LibraryUser(std::string userId, std::string name)
		{
			this -> userId = userId;
			this -> name = name;
			this -> borrowedBooks = {};
		}
		
		std::string getUserId()
		{
			return userId;
		}
		
		std::string getName()
		{
			return name;
		}
		
		const std::vector<std::string> getborrowedBooks() const
		{
			return borrowedBooks;
		}
		
		void setUserId(std::string newUserId)
		{
			userId = newUserId;
		}
		
		void setName(std::string newName)
		{
			name = newName;
		}
		
		void borrowBook(const std::string &bookTitle) // the ampersand from ChatGPT was beside std::string
		{
			borrowedBooks.push_back(bookTitle);
		}
		
		void returnBook(const std::string &bookTitle)
		{
			std::vector<std::string>::iterator thisBook =
			std::find(borrowedBooks.begin(), borrowedBooks.end(), bookTitle);
			if(thisBook != borrowedBooks.end())
			{
				borrowedBooks.erase(thisBook);
			}
		}
		
		void displayBorrowedBooks() const
		{
			std::cout << "Borrowed Books | " << "User: " << name << '\n';
			for(const std::string &book : borrowedBooks)
			{
				std::cout << book << '\n';
			}
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
	
	LibraryUser user1("001", "John Library");
	user1.borrowBook("Moldy Duck");
	user1.displayBorrowedBooks();
	user1.returnBook("Moldy Duck");
	user1.displayBorrowedBooks();

	
	return 0;
}