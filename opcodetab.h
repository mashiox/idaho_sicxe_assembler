/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
   mascxxxx
   Team Idaho
   prog2
   CS530, Spring 2016
 */

#ifndef OPCODETAB_H
#define OPCODETAB_H

#include <map>

using namespace std;

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
        int get_instruction_size(string);
                        
    private:
        // instruction menmonic and details pair
        struct instr {
            string menmonic;
            struct details {
                short format;
                string opcode;
            } details;
        };
    
        // instruction array to load map
        static const struct instr instrs[];
        // instruction map
        map<string, struct instr::details> opcodeTab;

};

#endif    
