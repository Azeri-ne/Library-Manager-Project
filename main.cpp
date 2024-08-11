#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

class Book
{
	private:
		std::string title;
		std::string author;
		std::string isbn;
		int stock;
		bool available;
		
	public:
		Book(std::string title, std::string author, std::string isbn, int stock)
		{
			this -> title = title;
			this -> author = author;
			this -> isbn = isbn;
			this -> stock = stock;
			this -> available = true;
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
		std::vector<std::unique_ptr<Book>> books;
		std::vector<std::unique_ptr<LibraryUser>> users;
		
	public:
		void addBook(const std::string &title, const std::string &author, const std::string &isbn)
		{
			books.push_back(std::make_unique<Book>(title, author, isbn)); // Add availability
		}
		
		void removeBook()
		{
			
		}
		
		void addUser(const std::string &userId, const std::string &name) // Add list of borrowed books
		{
			users.push_back(std::make_unique<LibraryUser>(userId, name));
		}
		
		void removeUser()
		{
			
		}
		
		void displayAllBooks()
		{
			std::cout << "Library Manager - Books List:" << '\n';
			for(const auto &bookUniquePtr : books)
			{
				std::cout << bookUniquePtr -> getTitle() << '\n'
						  << bookUniquePtr -> getAuthor() << '\n'
						  << bookUniquePtr -> getIsbn() << '\n';
			}
		}
		
		void displayAllUsers()
		{
			std::cout << "Library Manager - Users List:" << '\n';
			for(const auto &userUniquePtr : users)
			{
				std::cout << userUniquePtr -> getUserId() << '\n'
						  << userUniquePtr -> getName() << '\n';
			}
		}
};

int main()
{		
	Library lib;
	lib.addBook("Yo", "Mama", "234");
	lib.displayAllBooks();
	
	lib.addUser("234", "Wazaaa");
	lib.displayAllUsers();

	return 0;
}