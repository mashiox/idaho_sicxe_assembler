/*  opcodetab.h
    CS530, Spring 2016
*/

#ifndef OPCODETAB_H
#define OPCODETAB_H

#include <map>
#include "opcode_error_exception.h"

using namespace std;

// map << operator
// Usage: mymap << std::pair<K, V>(k1, v1) << std::pair<K,V>(k2, v2);
// Equal to: mymap.insert( std::pair<K,V> (k1,v1) );
//           mymap.insert( std::pair<K,V> (k2,v2) );
map<std::string, struct opcodes*>& operator<<(map<std::string,struct opcodes*>& opmap, std::pair<std::string,struct opcodes*> p){
	opmap.insert(p);
	return opmap;
}

struct opcodes {
        int format;
        int opcode;
        opcodes(int f, int o){
            format = f;
            opcode = o;
        }
};

class opcodetab {
    public:
        // ctor
        // creates a new dictionary structure and loads all of the opcodes for 
        // the SIC/XE architecture into the table.  Use the STL
        // map for this.
        opcodetab(); 
        
        // takes a SIC/XE opcode and returns the machine code 
        // equivalent as a two byte string in hexadecimal.
        // Example:  get_machine_code("ADD") returns the value 18
        // Note that opcodes may be prepended with a '+'.
        // throws an opcode_error_exception if the opcode is not 
        // found in the table.
        string get_machine_code(string);  
        
        // takes a SIC/XE opcode and returns the number of bytes 
        // needed to encode the instruction, which is an int in
        // the range 1..4.
        // NOTE: the opcode must be prepended with a '+' for format 4.
        // throws an opcode_error_exception if the opcode is not 
        // found in the table.        

    private:
        // your variables and private methods go here
        map<string, struct opcodes*> opcodeTab;

};

#endif    

