/* Phillip Domann, Shad, Melanie, Matt
   mascxxxx
   Team Idaho
   prog1
   CS530, Spring 2016
*/

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

const char* file_parser::delimiters = " \t";

file_parser::file_parser(string filename){
    this->filename = filename;
}

file_parser::~file_parser(){
}

void file_parser::read_file(){
    if (!container.empty()) {
        container.clear();
    }
    lineno = 0;
    string source = get_file_contents();

    istringstream sstream (source);
    string str;
    while (getline(sstream, str)) {
        struct line tstruct = tokenize(str);
        container.push_back(tstruct);
    }
}

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
                throw file_parse_exception("Get token column is out of bounds, "
                    "must be between 0 and 3.");
        }
    } catch (out_of_range &oor) {
        throw file_parse_exception("Get token row is out of bounds, "
            "must be between 0 and size()-1.");
    }
}

void file_parser::print_file(){
	vector<line>::iterator iter;
	for ( iter = container.begin() ; iter < container.end() ; iter++ ){
        cout.setf(ios::left);
        cout.width(16);
        cout << iter->getlabel() << setw(16) << iter->getopcode() << setw(16)
             << iter->getoperand() << setw(36) << iter->getcomment() << "\n";
	}
}

int file_parser::size(){
	return (int)container.size();
}

string file_parser::get_file_contents() {
    ifstream stream;
    stream.open(filename.c_str(), ios::in);
    
    if (!stream.is_open()) {
        throw file_parse_exception("Could not open file "+filename
            +". Check that the file exists or was properly entered.");
    }
    stream.seekg(0, ios::end);
    long long filesize = stream.tellg();
    stream.seekg(0, ios::beg);
    
    char* buffer = NULL;
    buffer = new (nothrow) char[filesize+1];
    if (buffer == NULL) {
        stream.close();
        throw file_parse_exception(
            "Could not allocate memory to read source file.");
    }
    stream.read(buffer, filesize);
    buffer[filesize] = '\0';
    string contents (buffer);
    
    stream.close();
    delete[] buffer;
    return contents;
}

struct file_parser::line file_parser::tokenize(const string& str) {
    ++lineno;
    column previous = none;
    struct line tokenstruct;
    size_t last = 0, first = 0;
    
    last = str.find_first_not_of(delimiters, 0);
    first = str.find_first_of(delimiters, last);
retoken:
    while (first != string::npos || last != string::npos) {
        ptrdiff_t nquotes;
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
                throw file_parse_exception("Invalid label at beginning of line."
                "\nA label starts with a letter and contains only alphanumeric "
                "characters.", lineno, str);
            }
        }
        nquotes = count(token.begin(), token.end(), '\'');
        if (nquotes%2) {
            if (first == string::npos) {
                throw file_parse_exception("Check that quoted characters are "
                "correctly terminated.", lineno, str);
            }
            first = str.find_first_of(delimiters, first+1);
            goto retoken;
        }
        if (previous == none || previous == label) {
            tokenstruct.setopcode(token);
            previous = opcode;
        } else if (previous == opcode) {
            tokenstruct.setoperand(token);
            previous = operand;
        } else {
            throw file_parse_exception("There are too many statements."
                "\nProper format may include only the following: "
                "label opcode operand(s) .comment", lineno, str);
        }
    next_token:
        last = str.find_first_not_of(delimiters, first);
        first = str.find_first_of(delimiters, last);
    }
    return tokenstruct;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "Proper usage is " << argv[0] << " sourcefile\n";
        return -1;
    }
    
	file_parser* fp = new file_parser(argv[1]);
    try {
        fp->read_file();
    } catch (file_parse_exception e) {
        cout << e.getMessage() << "\n";
        return 1;
    }

    fp->print_file();
    delete fp;
    
    return 0;
}