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
		bool available;
		
	public:
		Book(std::string title, std::string author, std::string isbn)
		{
			this -> title = title;
			this -> author = author;
			this -> isbn = isbn;
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

		void setAvailability(bool newAvailability)
		{
			available = newAvailability;
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
		
		void borrowBook(const std::string &bookTitle)
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
			books.push_back(std::make_unique<Book>(title, author, isbn)); 
		}
		
		void removeBook(const std::string &isbn)
		{
			auto thisBook = std::remove_if(books.begin(), books.end(),
			[&isbn](const std::unique_ptr<Book> &book)
			{
				return book -> getIsbn() == isbn;
			});
			
			if(thisBook != books.end())
			{
				books.erase(thisBook, books.end());
				std::cout << "Book removed" << '\n';
			}
			else
			{
				std::cout << "Book not found" << '\n';
			}
		}
		
		void addUser(const std::string &userId, const std::string &name)
		{
			users.push_back(std::make_unique<LibraryUser>(userId, name));
		}
		
		void removeUser(const std::string &userId)
		{
			auto thisUser = std::remove_if(users.begin(), users.end(),
			[&userId](const std::unique_ptr<LibraryUser> &user)
			{
				return user -> getUserId() == userId;
			});
			
			if(thisUser != users.end())
			{
				users.erase(thisUser, users.end());
				std::cout << "User removed" << '\n';
			}
			else
			{
				std::cout << "User not found" << '\n';
			}
		}
		
		void displayAllBooks()
		{
			std::cout << "Library Manager - Books List:" << '\n';
			for(const auto &bookUniquePtr : books)
			{
				std::cout << bookUniquePtr -> getTitle() << '\n'
						  << bookUniquePtr -> getAuthor() << '\n'
						  << bookUniquePtr -> getIsbn() << '\n'
						  << (bookUniquePtr -> getAvailability() ? "Yes" : "No") << '\n';
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
		
		void borrowBook(const std::string &userId, const std::string &isbn)
		{
			auto thisBook = std::find_if(books.begin(), books.end(),
			[&isbn](const std::unique_ptr<Book> &book)
			{
				return book -> getIsbn() == isbn;
			});
			
			if(thisBook != books.end())
			{
				if((*thisBook) -> getAvailability())
				{
					auto thisUser = std::find_if(users.begin(), users.end(),
					[&userId](const std::unique_ptr<LibraryUser> &user)
					{
						return user -> getUserId() == userId;
					});
					
					if(thisUser != users.end())
					{
						(*thisUser) -> borrowBook((*thisBook) -> getTitle());
						(*thisBook) -> setAvailability(false);
						std::cout << "The book is borrowed. Updated system." << '\n';
					}
					else
					{
						std::cout << "User does not exist" << '\n';
					}
				}
				else
				{
					std::cout << "Book is currently borrowed" << '\n';
				}
			}
			else
			{
				std::cout << "Book does not exist" << '\n';
			}
		}
		
		void returnBook(const std::string &userId, const std::string &isbn)
		{
			auto thisUser = std::find_if(users.begin(), users.end(),
			[&userId](const std::unique_ptr<LibraryUser> &user)
			{
				return user -> getUserId() == userId;
			});
			
			if(thisUser	!= users.end())
			{
				auto thisBook = std::find_if(books.begin(), books.end(),
				[&isbn](const std::unique_ptr<Book> &book)
				{
					return book -> getIsbn() == isbn;
				});
				
				if(thisBook != books.end())		
				{
					(*thisUser) -> returnBook((*thisBook) -> getTitle());
					(*thisBook) -> setAvailability(true);
					std::cout << "The book is return. Updated system." << '\n';
				}
				else
				{
					std::cout << "Book does not exist" << '\n';
				}
			}
			else
			{
				std::cout << "User does not exist" << '\n';
			}
		}
		
		void displayBorrowedBooks(const std::string &userId) const
		{
			auto thisUser = std::find_if(users.begin(), users.end(),
			[&userId](const std::unique_ptr<LibraryUser> &user)
			{
				return user -> getUserId() == userId;
			});
			
			if(thisUser	!= users.end())
			{
				(*thisUser) -> displayBorrowedBooks();
			}
			else
			{
				std::cout << "User does not exist" << '\n';
			}
		}

};

int main()
{	
	Library lib;
	lib.addBook("Yo", "Mama", "234");
	lib.addBook("Spam", "Eggs", "123");
	
	lib.displayAllBooks();
	
	
	lib.addUser("2399", "Wazaaa");
	lib.displayAllUsers();
	
	lib.borrowBook("2399", "234");
	lib.displayBorrowedBooks("2399");
	
    lib.returnBook("2399", "234");
    lib.displayBorrowedBooks("2399");
	
	lib.removeUser("2399");
	lib.displayAllUsers();

	return 0;
}