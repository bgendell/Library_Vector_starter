#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../includes_usr/fileIO.h"
#include "../includes_usr/library.h"
using namespace std;

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	books.clear();
	fstream myfile;
	myfile.open(filename,ios_base::in);
	if(!myfile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	std::string line;

	string tempString;
	book tempBook;

	while(!myfile.eof()){
		getline(myfile,line);
		stringstream ss(line);
		if(line == ""){
			break;
		}
		//written in reference to 7demo_fileio class example
		getline(ss,tempString,',');
		tempBook.book_id=stoi(tempString,nullptr,10);
		getline(ss,tempBook.title,',');
		getline(ss,tempBook.author,',');
		getline(ss,tempString,',');
		tempBook.state = book_checkout_state(stoi(tempString,nullptr,10));
		getline(ss,tempString,',');
		tempBook.loaned_to_patron_id = stoi(tempString,nullptr,10);
		books.push_back(tempBook);
		ss.clear();
	}
	if (books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}
	return SUCCESS;
}
/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	if(books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}
	fstream myfile;
	myfile.open(filename,ios_base::out);
	if(!myfile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	else{
		for(int i = 0; i<books.size();i++){
			myfile << books[i].book_id;
			myfile << ",";
			myfile << books[i].title;
			myfile << ",";
			myfile << books[i].author;
			myfile << ",";
			myfile << books[i].state;
			myfile << ",";
			myfile << books[i].loaned_to_patron_id;
			myfile << "\n";
		}
		myfile.close();
		return SUCCESS;
	}
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	patrons.clear();
		fstream myfile;
			myfile.open(filename,ios_base::in);
			if(!myfile.is_open()){
				return COULD_NOT_OPEN_FILE;
			}

			std::string line;
			string tempString;
			patron tempPatron;

			while(!myfile.eof()){
				getline(myfile,line);
				stringstream ss(line);
				if(line == ""){
					break;
				}
				//written in reference to 7demo_fileio class example
				getline(ss,tempString,',');
				tempPatron.patron_id=stoi(tempString,nullptr,10);
				getline(ss,tempPatron.name,',');
				getline(ss,tempString,',');
				tempPatron.number_books_checked_out = stoi(tempString,nullptr,10);
				patrons.push_back(tempPatron);
				ss.clear();
			}
		if(patrons.empty()){
			return NO_PATRONS_IN_LIBRARY;
		}
		return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	if(patrons.empty()){
		return NO_PATRONS_IN_LIBRARY;
	}
	fstream myfile;
	myfile.open(filename,ios_base::out);
	if(!myfile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	else{
		for(int i = 0; i<patrons.size();i++){
			myfile << patrons[i].patron_id;
			myfile << ",";
			myfile << patrons[i].name;
			myfile << ",";
			myfile << patrons[i].number_books_checked_out;
			myfile << "\n";
		}

		myfile.close();
		return SUCCESS;
	}
}
