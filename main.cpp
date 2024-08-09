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
		
	// idk why we need getters and setters, the Library class is gonna provide the new books anyway?
};

int main()
{
	std::cout << "yo" << '\n';
	
	return 0;
}