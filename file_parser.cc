#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

/**
 * Constrctor
 */
file_parser::file_parser(string filename){
    file = filename;
}

/**
 * Destructor
 */
file_parser::~file_parser(){
}

/**
 * Reads a file by line,
 */
void file_parser::read_file(){
    try {
        infile.open(file.c_str(), ios::in);
    } catch (ios_base::failure fail) {
        throw file_parse_exception("error: failed to open file "+file);
    }
    if (!infile) {
        throw file_parse_exception("error: failed to open file "+file);
    }
    
	string line;
	while ( !infile.eof() ){
		getline( infile, line );
//		container.push_back(line);
	}
	infile.close();
}

/**
 * 
 */
string file_parser::get_token(unsigned int row, unsigned int column){
    try {
        switch (column) {
            case 0:
                return container.at(row).label;
            case 1:
                return container.at(row).opcode;
            case 2:
                return container.at(row).operand;
            case 3:
                return container.at(row).comment;
            default:
                throw file_parse_exception("error: get_token column is out of bounds");
        }
    } catch (out_of_range &oor) {
        throw file_parse_exception("error: get_token row is out of bounds");
    }
}

/**
 * Prints the contents of the file to stdout
 */
void file_parser::print_file(){
	vector<line>::iterator iter;
	for ( iter = container.begin() ; iter < container.end() ; iter++ ){
        cout << iter->label << "\t" << iter->opcode << "\t" << iter->operand << "\t" << iter->comment << "\n";
	}
}

/**
 * Returns the number of lines of the file.
 */
int file_parser::size(){
	return (int)container.size();
}