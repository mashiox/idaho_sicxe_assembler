/* Phillip Domann, Shad Aziz, Melanie Reed, Matt Walther
   mascxxxx
   Team Idaho
   prog1
   CS530, Spring 2016
*/

#ifndef FILE_PARSE_EXCEPTION_H
#define FILE_PARSE_EXCEPTION_H

#include <sstream>

using namespace std;

class file_parse_exception {

public:
    file_parse_exception(string s) {
        message = s;
    }
    
    file_parse_exception(string s, int lineno, string line) {
        message = "Line "+itos(lineno)+": "+line+"\n"+s;
    }

    file_parse_exception() {
        message = "An error has occurred";
    }

    string getMessage() {
        return "*****Error*****\n"+message;
    }

private:
    string message;
    
    string itos(int integer) {
        stringstream itoss;
        itoss << integer;
        return itoss.str();
    }
};

#endif
