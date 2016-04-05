/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
   mascxxxx
   Team Idaho
   prog2
   CS530, Spring 2016
 */

#ifndef OPCODE_ERROR_EXCEPTION_H
#define OPCODE_ERROR_EXCEPTION_H

using namespace std;

class opcode_error_exception {
public:
    opcode_error_exception() {
        message = "An opcode error has occured.";
    }
    opcode_error_exception(string s) {
        message = s;
    }
    
    string getMessage() {
        return message;
    }
private:
    string message;
};


#endif
