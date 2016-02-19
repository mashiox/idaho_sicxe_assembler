#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <vector>
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
        // pass to tokenizer
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
                throw file_parse_exception("Error: get token column is out of bounds, must be between 0 and 3");
        }
    } catch (out_of_range &oor) {
        throw file_parse_exception("Error: get token row is out of bounds, must be between 0 and size()-1");
    }
}

/**
 * Prints the contents of the file to stdout
 */
void file_parser::print_file(){
	vector<line>::iterator iter;
	for ( iter = container.begin() ; iter < container.end() ; iter++ ){
        // iomanip
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
        throw file_parse_exception("Error: could not open file "+filename+". Check that the file exists or was properly entered.");
    }
    stream.seekg(0, ios::end);
    long long filesize = stream.tellg();
    stream.seekg(0, ios::beg);
    
    char* buffer = NULL;
    buffer = new char[filesize+1];
    if (buffer == NULL) {
        stream.close();
        throw file_parse_exception("Error: could not allocate memory to read source file.");
    }
    stream.read(buffer, filesize);
    buffer[filesize] = '\0';
    string* contents = new string(buffer);
    
    stream.close();
    delete[] buffer;
    return contents;
}