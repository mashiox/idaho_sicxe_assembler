/* Phillip Domann, Shad Aziz, Melanie Reed, Matt Walther
   masc0832
   Team Idaho
   prog3
   CS530, Spring 2016
*/

#ifndef SYMTAB_EXCEPTION_H
#define SYMTAB_EXCEPTION_H

#include <sstream>

using namespace std;

class symtab_exception {

public:
    symtab_exception(string s) {
        message = s;
    }

    symtab_exception() {
        message = "An error has occurred";
    }

    string getMessage() {
        return message;
    }

private:
    string message;
    
};

#endif
