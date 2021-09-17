#include "Library.h"
#include "TemplatedDLList.h"
#include <iostream>
#include <fstream>

// search
std::vector<Record> Library::search(std::string title) {
	// create a vector to store the found records
	vector<Record> found;

	// figure out 1st letter of the title input
	// convert to an integer by manipulaing ascii
	int pos = tolower(title.at(0)) - 97;

	// go to that dll and specify the linekd list
	DLList<Record> dll = book_db.at(pos);

	// iterate though entire dll
	for (DLListNode<Record> *marker = dll.first_node(); marker != dll.after_last_node(); marker = marker->next ) {
        // check to see if marker's title matches given title
        if (marker->obj.get_title() == title) {
        	// push the marker to the found vector
        	found.push_back(marker->obj);
        }
    }

	// return the found entries
	return found;
}

// import database
int Library::import_database(std::string filename) {
	// open file
	ifstream ifs(filename);

	Record entry;
	int added = 0;

	while (ifs >> entry) {
		add_record(entry);
		added++;
	}

	ifs.close();

	return added;
}

// export database
int Library::export_database(std::string filename) {
	ofstream ofs(filename);

	int written = 0;

	for(int i = 0; i < 26; i++) {
		for (DLListNode<Record> *marker = book_db[i].first_node(); marker != book_db[i].after_last_node(); marker = marker->next ) {
	        // write
	        ofs << marker->obj << std::endl;
	        written++;
	    }
	}

	ofs.close();
	return written;
}

// print database 
void Library::print_database() {
	for(int i = 0; i < 26; i++) {
		for (DLListNode<Record> *marker = book_db[i].first_node(); marker != book_db[i].after_last_node(); marker = marker->next ) {
	        //cout
	        std::cout << marker->obj;
	    }
	}
}

// add record
bool Library::add_record(Record book) {
	// get first character of the record's title
	std::string title = book.get_title();
	char firstChar = tolower(title.at(0));

	// find the index of book_db which corresponds to that character
	int pos = firstChar - 97;

	// insert the book into the linekd list at that inedex of book_db
	// iterate though the linked list while checking values to determine where the record should be added
		// iterate though entire dll
	for (DLListNode<Record> *marker = book_db[pos].first_node(); marker != book_db[pos].after_last_node(); marker = marker->next ) {
        // check for dubplicate
        if (marker->obj == book) {
        	return false;
        }
    }

    book_db[pos].insert_last(book);
    return true;

}

// remove record
void Library::remove_record(Record book) {
	// get first character of the record's title
	std::string title = book.get_title();
	char firstChar = tolower(title.at(0));

	// find the index of book_db which corresponds to that character
	int pos = firstChar - 97;

	for (DLListNode<Record> *marker = book_db[pos].first_node(); marker != book_db[pos].after_last_node(); marker = marker->next ) {
        // look for the entry
        if (marker->obj == book) {
        	book_db[pos].remove_after(*marker->prev);
        }
    }
}

// prompt_yes_no
char Library::prompt_yes_no() {
	char input = '\0';

	std::cout << "Please Enter Y/N: ";
	std::cin >> input;

	return input;
}

// prompt menu
int Library::prompt_menu(std::vector<std::string> v) {

	std::cout << "Please select an option: " << std::endl;
	int input = 0;

	for(int i = 0; i < v.size(); i ++) {
		std::cout << i + 1 << ". " << v.at(i) << std::endl;
	}

	cin >> input;

	return input - 1;
}

// prompt record
Record Library::prompt_record() {
	std::string title = "";
	std::string author = "";
	std::string ISBN = "";
	std::string year = "";
	std::string edition = "";


	std::cout << "Please enter a title: " << std::endl;
	std::cin >> title;

	std::cout << "Please enter a author: " << std::endl;
	std::cin >> author;

	std::cout << "Please enter a ISBN: " << std::endl;
	std::cin >> ISBN;

	std::cout << "Please enter a year: " << std::endl;
	std::cin >> year;

	std::cout << "Please enter a edition: " << std::endl;
	std::cin >> edition;

	Record book;

	book.set_title(title);
	book.set_author(author);
	book.set_ISBN(ISBN);
	book.set_year(year);
	book.set_edition(edition);

	return book;
}

// prompt title
std::string Library::prompt_title() {
	std::string title = "";

	std::cout << "Enter book title: " << std::endl;
	cin >> title;

	return title;
}

// promp string
std::string Library::prompt_string(std::string prompt) {
	std::string input = "";

	std::cout << prompt << std::endl;

	cin >> input;

	return input;
}
