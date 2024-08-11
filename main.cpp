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
		
		const std::vector<std::string> getBorrowedBooks() const
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
		void save(const std::string &filename) const
		{
			std::ofstream outFile(filename);
			
			if(outFile.is_open())
			{
				outFile << books.size() << '\n';
				for(const auto &book : books)
				{
					outFile << book -> getTitle() << '\n'
							<< book -> getAuthor() << '\n'
							<< book -> getIsbn() << '\n'
							<< book -> getAvailability() << '\n';
				}
				
				outFile << users.size() << '\n';
				for(const auto &user : users)
				{
					outFile << user -> getUserId() << '\n'
							<< user -> getName() << '\n';
							
					const auto &borrowedBooks = user -> getBorrowedBooks();
					outFile << borrowedBooks.size() << '\n';
					for(const auto &bookTitle : borrowedBooks)
					{
						outFile << bookTitle << '\n';
					}
				}
				outFile.close();
				std::cout << "Saved successfully" << '\n';
			}
			else
			{
				std::cout << "Failed to save file. Check if directory exists" << '\n';
			}
		}
		
		void load(const std::string &filename)
		{
			std::ifstream inFile(filename);
			
			if(inFile.is_open())
			{
				books.clear();
				users.clear();
				
				size_t bookAmount;
				inFile  >> bookAmount;
				inFile.ignore();
				
				for(size_t i = 0; i < bookAmount; i++)
				{
					std::string title;
					std::string author;
					std::string isbn;
					bool available;
					
					std::getline(inFile, title);
					std::getline(inFile, author);
					std::getline(inFile, isbn);
					inFile >> available;
					inFile.ignore();
					
					books.push_back(std::make_unique<Book>(title, author, isbn));
					books.back() -> setAvailability(available);
				}
				
				size_t userAmount;
				inFile >> userAmount;
				inFile.ignore();
				
				for(size_t i = 0; i < userAmount; i++)
				{
					std::string userId;
					std::string name;
					std::getline(inFile, userId);
					std::getline(inFile, name);
					
					users.push_back(std::make_unique<LibraryUser>(userId, name));
					
					size_t borrowedBookAmount;
					inFile >> borrowedBookAmount;
					inFile.ignore();
					
					for(size_t j = 0; j < borrowedBookAmount; j++)
					{
						std::string bookTitle;
						std::getline(inFile, bookTitle);
						users.back() -> borrowBook(bookTitle);
					}
				}
				
				inFile.close();
				std::cout << "Loaded successfully" << '\n';
			}
			else
			{
				std::cout << "Failed to load file. Check if directory exists" << '\n';
			}
		}
	
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
		
		void displayOptions()
		{
			char choice;
			std::string input;
			
			// do
			{
				std::cout << "Library Manager v2.0" << '\n'
						  << "[A]dd book" << '\n'
						  << "[R]emove book" << '\n'
						  << "A[D]d user" << '\n'
						  << "Re[M]ove user" << '\n'
						  << "[B]orrow book" << '\n'
						  << "Retur[N] book" << '\n';
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
	
	lib.displayOptions();

	return 0;
}