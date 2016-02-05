#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

/**
 * Constrctor
 */
file_parser::file_parser(string filename){
	infile.open( filename, ios::in );
}

/**
 * Destructor
 */
file_parser::~file_parser(){
	free infile;
	free outfile;
	free container;
}

/**
 * Reads a file by line,
 */
file_parser::read_file(){
	if ( !infile ) cout << "wat" << endl;

	string line;
	while ( !infile.eof() ){
		getline( infile, line );
		container.push_back(line);
	}
	infile.close();
}

/**
 * Prints the contents of the file to stdout
 */
file_parser::print_file(){
	std::vector<string>::iterator iter;
	for ( it = container.begin() ; it < container.end() ; it++ ){
		cout << *it << endl;
	}
}

/**
 * Returns the number of lines of the file.
 */
file_parser::size(){
	return container.size();
}