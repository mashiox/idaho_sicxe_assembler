/*
 * mascxxxx
 * prog1
 * CS530, Spring 2016
 */

#include <iostream>
#include "file_parser.h"
#include "file_parse_exception.h"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "proper usage is " << argv[0] << " filename\n";
		return -1;
	}

	file_parser fp (argv[1]);
    try {
        fp.read_file();
    } catch (file_parse_exception e) {
        cout << e.getMessage() << "\n";
        return -1;
    }
    
    fp.print_file();
    
	return 0;
}
