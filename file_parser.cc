#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

/**
 * Constrctor
 */
file_parser::file_parser(string filename){
    this->filename = filename;
    source = NULL;
}

/**
 * Destructor
 */
file_parser::~file_parser(){
    delete source;
}

/**
 * Reads a file by line,
 */
void file_parser::read_file(){
    source = get_file_contents();

    istringstream sstream (*source);
    string str;
    while (getline(sstream, str)) {
        tokenizer toke (str);
        struct line tstruct = toke.tokens();
        container.push_back(tstruct);
    }
}

/**
 *  
 */
string file_parser::get_token(unsigned int row, unsigned int column){
    try {
        switch (column) {
            case 0:
                return container.at(row).getlabel();
            case 1:
                return container.at(row).getopcode();
            case 2:
                return container.at(row).getoperand();
            case 3:
                return container.at(row).getcomment();
            default:
                throw file_parse_exception("Get token column is out of bounds, must be between 0 and 3");
        }
    } catch (out_of_range &oor) {
        throw file_parse_exception("Get token row is out of bounds, must be between 0 and size()-1");
    }
}

/**
 * Prints the contents of the file to stdout
 */
void file_parser::print_file(){
	vector<line>::iterator iter;
	for ( iter = container.begin() ; iter < container.end() ; iter++ ){
	cout.setf(ios::left);
	cout.width(16);
	cout << iter->getlabel() << setw(16) << iter->getopcode() << setw(16) << iter->getoperand() << setw(36) << iter->getcomment() << endl;
	}
}

/**
 * Returns the number of lines of the file.
 */
int file_parser::size(){
	return (int)container.size();
}

/**
 * Returns a pointer to a string with the file's contents
 */

const string* file_parser::get_file_contents() {
    if (source != NULL) {
        delete source;
    }
    
    ifstream stream;
    stream.open(filename.c_str(), ios::in);
    
    if (!stream.is_open()) {
        throw file_parse_exception("Could not open file "+filename+". Check that the file exists or was properly entered.");
    }
    stream.seekg(0, ios::end);
    long long filesize = stream.tellg();
    stream.seekg(0, ios::beg);
    
    char* buffer = NULL;
    buffer = new (nothrow) char[filesize+1];
    if (buffer == NULL) {
        stream.close();
        throw file_parse_exception("Could not allocate memory to read source file.");
    }
    stream.read(buffer, filesize);
    buffer[filesize] = '\0';
    string* contents = new (nothrow) string(buffer);
    
    stream.close();
    delete[] buffer;
    return contents;
}

const char* file_parser::tokenizer::delimiters = " \t";

file_parser::tokenizer::tokenizer(const string& str) {
    this->str = str;
}

struct file_parser::line file_parser::tokenizer::tokens() {
    static int lineno = 0;
    ++lineno;
    column previous = none;
    struct line tokenstruct;
    size_t last = 0, first = 0;
    
    last = str.find_first_not_of(delimiters, 0);
    first = str.find_first_of(delimiters, last);
retoken:
    while (first != string::npos || last != string::npos) {
        ptrdiff_t quotes;
        string token = str.substr(last, first-last);
        if (iscomment(token)) {
            token = str.substr(last, string::npos);
            tokenstruct.setcomment(token);
            break;
        } else if (last == 0) {
            if (islabel(token)) {
                tokenstruct.setlabel(token);
                previous = label;
                goto next_token;
            } else {
                throw file_parse_exception("Invalid label, a label starts with a letter and contains only alphanumeric characters.",
                    lineno, str);
            }
        }
        quotes = count(token.begin(), token.end(), '\'');
        if (quotes%2) {
            if (first == string::npos) {
                throw file_parse_exception("Check that quoted characters are correctly terminated.", lineno, str);
            }
            first = str.find_first_of(delimiters, first+1);
            goto retoken;
        }
        if ((previous == none) | (previous == label)) {
            tokenstruct.setopcode(token);
            previous = opcode;
        } else if (previous == opcode) {
            tokenstruct.setoperand(token);
            previous = operand;
        } else {
            throw file_parse_exception("There are too many instructions."
                "\nProper format may include only the following: label opcode operand(s) .comment",
                lineno, str);
        }
    next_token:
        last = str.find_first_not_of(delimiters, first);
        first = str.find_first_of(delimiters, last);
    }
    return tokenstruct;
}
