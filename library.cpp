/* complete this file */
#include <stdio.h>
#include "library.h"
#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>

/* Parent class instantiation for all types of documents */

/* setters and getters implementation*/
void Document::updateTitle(const char *newTitle){
	_title = new char[strlen(newTitle)+1];
	strcpy(_title,newTitle);
}

void Document::updateYear(int newYear){
	_year = newYear;
}

void Document::updateQuantity(int newQuantity){
	_quantity = newQuantity;
}

char *Document::getTitle(){
	return _title;
}

int Document::getYear(){
	return _year;
}

int Document::getQuantity(){
	return _quantity;
}

/* Used when someone tries to borrow a document, should return 0 on success
 * and something else on failure */
int Document::borrowDoc(){
	if(_quantity > 0){
		_quantity --;
		return 0;
	}else{
		return -1;
	}
}

/* Used when someone returns a document */
void Document::returnDoc(){
	_quantity ++;
}


/* Novel methods implementation */
Novel::Novel(const char *title, const char *author, int year, int quantity):Document(){
	_author = new char[strlen(author)+1];
	strcpy(_author,author);
	_title = new char[strlen(title)+1];
	strcpy(_title,title);
	_year = year;
	_quantity = quantity;
}

Novel::~Novel(){
	delete [] _title;
}

document_type Novel::getDocType(){
	return DOC_NOVEL;
}

/* Novel, title: <title>, author: <author>, year: <year>, quantity: <quantity> */
void Novel::print(){
	printf("Novel, title: %s, author: %s, year: %d, quantity: %d", _title, _author, _year, _quantity);
}

/* getters and setters */
void Novel::updateAuthor(const char *newAuthor){
	_author = new char[strlen(newAuthor)+1];
	strcpy(_author,newAuthor);
}

char *Novel::getAuthor(){
	return _author;
}

/* Comic methods implementation */
Comic::Comic(const char *title, const char *author, int issue, int year, int quantity):Document(){
	_author = new char[strlen(author)+1];
	strcpy(_author,author);
	_issue = issue;
	_title = new char[strlen(title)+1];
	strcpy(_title,title);
	_year = year;
	_quantity = quantity;
}

Comic::~Comic(){
	delete [] _title;
}

document_type Comic::getDocType(){
	return DOC_COMIC;
}

/* Comic, title: <title>, author: <author>, issue: <issue>, year: <year>, quantity: <quantity> */
void Comic::print(){
	printf("Comic, title: %s, author: %s, issue: %d, year: %d, quantity: %d", _title, _author, _issue, _year, _quantity);
}

/* getters, setters */
void Comic::updateAuthor(const char *newAuthor){
	_author = new char[strlen(newAuthor)+1];
	strcpy(_author,newAuthor);	
}
void Comic::updateIssue(int newIssue){
	_issue = newIssue;
}

char *Comic::getAuthor(){
	return _author;
}

int Comic::getIssue(){
	return _issue;
}

/* Magazine methods implementation */ 
Magazine::Magazine(const char *title, int issue, int year, int quantity):Document(){
	_issue = issue;
	_title = new char[strlen(title)+1];
	strcpy(_title,title);
	_year = year;
	_quantity = quantity;
}

Magazine::~Magazine(){
	delete [] _title;
	// free(_issue);
}

/* Magazine, title: <title>, issue: <issue>, year: <year>, quantity: <quantity> */
void Magazine::print(){
	printf("Magazine, title: %s, issue: %d, year: %d, quantity: %d", _title, _issue, _year, _quantity);
}

document_type Magazine::getDocType(){
	return DOC_MAGAZINE;
}

/* getters, setters */
void Magazine::updateIssue(int newIssue){
	_issue = newIssue;
}
int Magazine::getIssue(){
	return _issue;
}

/* One instance of that class represents a library */
Library::Library(){}

/* print the entire library on the standard output, one line per document,
 * in the order they were inserted in the library, using the print()
 * methods implemented by the document objects */
void Library::print(){
	for(int i=0; i<_docs.size(); i++){
		_docs[i]->print();
	}
}

/* Dump the library in CSV format in a file, the format is: 1 line per
 * file:
 * <document type>,<title>,<author>,<issue>,<year>,<quantity>
 * A field not relevant for a given document type (e.g. issue for novel)
 * should be left blank. Return 0 on success, something else on failure.
 * Here you should use low-level file I/Os (open, write, etc.) as seen
 * in the course. */
int Library::dumpCSV(const char *filename){
	ofstream fout("library.csv");
	fout << "write here";
}

/* search for a document in the library, based on the title. We assume that
* a title identify uniquely a document in the library, i.e. there cannote
* be 2 documents with the same title Returns a pointer to the document if
* found, NULL otherwise */

Document *Library::searchDocument(const char *title){
	for(int i=0; i<_docs.size(); i++){
		if(_docs[i]->getTitle() == title){
			return _docs[i];
		}
	}
	return NULL;
}

/* Add/delete a document to/from the library, return 0 on success and
 * something else on failure.  */
int Library::addDocument(Document *d){
	_docs.push_back(d);
	return 0;
}
int Library::delDocument(const char *title){
	if(searchDocument(title) != NULL){
		// _docs.erase(searchDocument(title));
		return 0;
	}else{
		return -1;
	}
}

/* Count the number of document of a given type present in the library */
int Library::countDocumentOfType(document_type t){
	int count = 0;
	for(int i=0; i<_docs.size(); i++){
		if(_docs[i]->getDocType() == t){
			count ++;
		}
	}
	return count;
}

/* Borrow/return documents, return 0 on success, something else on
 * failure */
int Library::borrowDoc(const char *title){
	if(searchDocument(title) == NULL || searchDocument(title)->getQuantity() == 0){
		return -1;
	}else{
		if(searchDocument(title)->borrowDoc() == 0){
			return 0;
		}else{
			return -1;
		}

	}
}

int Library::returnDoc(const char *title){
	if(searchDocument(title) == NULL){
		return -1;
	}else{
		searchDocument(title)->returnDoc();
		return 0;
	}
}

int main(int argc, char **argv){
	return 0;
}
/* Holds all documents in the library */
// vector<Document *> _docs;