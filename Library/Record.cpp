//implementation of record class

#include "Record.h"
#include <iostream>
#include <string>

// getters
std::string Record::get_title() const {
	return title;
}

std::string Record::get_author() const {
	return author;
}

std::string Record::get_ISBN() const {
	return ISBN;
}

std::string Record::get_year() const {
	return year;
}

std::string Record::get_edition() const {
	return edition;
}

// setters
void Record::set_title(std::string t) {
	title = t;
}

void Record::set_author(std::string a) {
	author = a;
}

void Record::set_ISBN(std::string i) {
	ISBN = i;
}

void Record::set_year(std::string y) {
	year = y;
}

void Record::set_edition(std::string e) {
	edition = e;
}

// input operator
std::istream& operator>>(std::istream& is, Record& rec) {

	std::string t;
	std::string a;
	std::string i;
	std::string y;
	std::string e;

	std::getline(is, t);
		if (t == "") {
			std::getline(is, t);
		}
	std::getline(is, a);
		if (a == "") {
			std::getline(is, a);
		}
	std::getline(is, i);
		if (i == "") {
			std::getline(is, i);
		}
	std::getline(is, y);
		if (y == "") {
			std::getline(is, y);
		}
	std::getline(is, e);
		if (e == "") {
			std::getline(is, e);
		}

	rec.set_title(t);
	rec.set_author(a);
	rec.set_ISBN(i);
	rec.set_year(y);
	rec.set_edition(e);

	return is;
}


// output operator
std::ostream& operator<<(std::ostream& os, Record& rec) {
	os << rec.get_title() << std::endl;
	os << rec.get_author() << std::endl;
	os << rec.get_ISBN() << std::endl;
	os << rec.get_edition() << std::endl;
	os << std::endl;

	return os;
}

// comparison operator
bool operator==(const Record& r1, const Record& r2) {
	if (r1.get_title() == r2.get_title()) {
		if (r1.get_author() == r2.get_author()) {
			if (r1.get_ISBN() == r2.get_ISBN()) {
				return true;
			}
		}
	}

	return false;
}