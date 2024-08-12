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
			std::cout << "Borrowed Books | " << "User: " << name << '\n' << '\n';
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
				std::cout << "Saved successfully" << '\n' << '\n';
			}
			else
			{
				std::cout << "Failed to save file. Check if directory exists" << '\n' << '\n';
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
				std::cout << "Loaded successfully" << '\n' << '\n';
			}
			else
			{
				std::cout << "Failed to load file. Check if directory exists" << '\n' << '\n';
			}
		}

		void addBook(const std::string &title, const std::string &author, const std::string &isbn)
		{
			books.push_back(std::make_unique<Book>(title, author, isbn));
            std::cout << "Book added!" << '\n';
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
				std::cout << "Book removed" << '\n' << '\n';
			}
			else
			{
				std::cout << "Book not found" << '\n' << '\n';
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
                std::cout << std::endl;
			});

			if(thisUser != users.end())
			{
				users.erase(thisUser, users.end());
				std::cout << "User removed" << '\n' << '\n';
			}
			else
			{
				std::cout << "User not found" << '\n' << '\n';
			}
		}

		void displayAllBooks()
		{
			std::cout << "Library Manager - Books List:" << '\n' << '\n';
			for(const auto &bookUniquePtr : books)
			{
				std::cout << "Title: " << bookUniquePtr -> getTitle() << '\n'
						  << "Author: " << bookUniquePtr -> getAuthor() << '\n'
						  << "ISBN: " << bookUniquePtr -> getIsbn() << '\n'
						  << "Available: " << (bookUniquePtr -> getAvailability() ? "Yes" : "No") << '\n' << '\n';
			}
		}

		void displayAllUsers()
		{
			std::cout << "Library Manager - Users List:" << '\n' << '\n';
			for(const auto &userUniquePtr : users)
			{
				std::cout << "User ID: " << userUniquePtr -> getUserId() << '\n'
						  << "Name: " << userUniquePtr -> getName() << '\n' << '\n';
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
						std::cout << "The book is borrowed. Updated system." << '\n' << '\n';
					}
					else
					{
						std::cout << "User does not exist" << '\n' << '\n';
					}
				}
				else
				{
					std::cout << "Book is currently borrowed" << '\n' << '\n';
				}
			}
			else
			{
				std::cout << "Book does not exist" << '\n' << '\n';
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
					std::cout << "The book is return. Updated system." << '\n' << '\n';
				}
				else
				{
					std::cout << "Book does not exist" << '\n' << '\n';
				}
			}
			else
			{
				std::cout << "User does not exist" << '\n' << '\n';
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
                std::cout << std::endl;
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
			std::string title;
			std::string author;
			std::string isbn;
			std::string userId;
			std::string name;

			do
			{
				std::cout << '\n' << "=========================" << '\n' << '\n'
					      << "Library Manager v2.0" << '\n' << '\n'
						  << "[A]dd book" << '\n'
						  << "[R]emove book" << '\n'
						  << "A[D]d user" << '\n'
						  << "Re[M]ove user" << '\n'
						  << "[B]orrow book" << '\n'
						  << "Retur[N] book" << '\n'
						  << "Display all bo[O]ks" << '\n'
						  << "Display all us[E]rs" << '\n'
						  << "Displa[Y] borrowed books" << '\n'
						  << "[S]ave" << '\n'
						  << "[L]oad" << '\n'
						  << "E[X]it" << '\n' << '\n'
						  << "Enter command: ";
				std::cin >> choice;
				std::cin.ignore(100, '\n');

				switch(choice)
				{
					case 'A':
					{
						std::cout << "Title: ";
						std::getline(std::cin, title);
						std::cout << "Author: ";
						std::getline(std::cin, author);
						std::cout << "ISBN: ";
						std::getline(std::cin, isbn);
						std::cout << std::endl;
						if (title.empty() || author.empty() || isbn.empty()) {
							std::cout << "Missing input. Please try again.";
						}
						else {
							addBook(title, author, isbn);
						}
						std::cout << std::endl;
						break;
					}

					case 'R':
					{
						std::cout << "ISBN to remove: ";
						std::getline(std::cin, isbn);
						std::cout << std::endl;
						if (isbn.empty()) {
							std::cout << "Missing input. Please try again.";
						}
						else {
							removeBook(isbn);
						}
						std::cout << std::endl;
						break;
					}

					case 'D':
					{
						std::cout << "User ID: ";
						std::getline(std::cin, userId);
						std::cout << "Name: ";
						std::getline(std::cin, name);
						std::cout << std::endl;
						if (userId.empty() || name.empty()) {
							std::cout << "Missing input. Please try again.";
						}
						else {
							addUser(userId, name);
						}
                        std::cout << std::endl;
						break;
					}

					case 'M':
					{
						std::cout << "User ID to remove: ";
						std::getline(std::cin, userId);
						std::cout << std::endl;
						if (userId.empty()) {
							std::cout << "Missing input. Please try again.";
						}
						else {
							removeUser(userId);
						}
						std::cout << std::endl;
						break;
					}

					case 'B':
					{
						std::cout << "User ID: ";
						std::getline(std::cin, userId);
						std::cout << "ISBN to borrow: ";
						std::getline(std::cin, isbn);
						std::cout << std::endl;
						if (userId.empty() || isbn.empty()) {
							std::cout << "Missing input. Please try again.";
						}
						else {
							borrowBook(userId, isbn);
						}
						std::cout << std::endl;
						break;
					}

					case 'N':
					{
						std::cout << "User ID: ";
						std::getline(std::cin, userId);
						std::cout << "ISBN to return: ";
						std::getline(std::cin, isbn);
						std::cout << std::endl;
						if (userId.empty() || isbn.empty()) {
							std::cout << "Missing input. Please try again.";
						}
						else {
							returnBook(userId, isbn);
						}
						std::cout << std::endl;
						break;
					}

					case 'O':
					{
						displayAllBooks();
						break;
					}

					case 'E':
					{
						displayAllUsers();
						break;
					}

					case 'Y':
					{
						std::cout << "User ID: ";
						std::getline(std::cin, userId);
						std::cout << std::endl;
						if (userId.empty() || isbn.empty()) {
							std::cout << "Missing input. Please try again.";
						}
						else {
							displayBorrowedBooks(userId);
						}
						std::cout << std::endl;
						break;
					}

					case 'S':
					{
						std::string filename = "data.txt";
						save(filename);
						break;
					}

					case 'L':
					{
						std::string filename = "data.txt";
						load(filename);
						break;
					}

					case 'X':
						std::cout << "Exiting, thanks for using the Library Manager" << '\n';
						break;

					default:
						std::cout << "Command not recognized" << '\n';
				}
			}
			while(choice != 'X');
		}

};

int main()
{
	Library lib;
	lib.displayOptions();

	return 0;
}
