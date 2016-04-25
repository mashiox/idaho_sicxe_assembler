/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
   masc0832
   Team Idaho
   prog3
   CS530, Spring 2016
*/

#ifndef SICXE_ASM_H
#define SICXE_ASM_H

#include <map>
#include "file_parser.h"
#include "opcodetab.h"
#include "symtab.h"

using namespace std;

class sicxe_asm {
    typedef void (sicxe_asm::*sym_handler)();
    
    string intermed_filen;
    file_parser* parser;
    opcodetab optab;
    symtab symbols;
    map<string, sym_handler> hmap;
    vector<unsigned int> line_addrs;
    unsigned int index;
    unsigned int locctr;
    string label;
    string opcode;
    string operand;
    ofstream listing;
    int nixbpe[6];
    
    struct dhpair {
        string directive;
        sym_handler handler;
    };
    
    static const struct dhpair dhpairs[9];
    
    // Retrives the line tokens from the file parser
    void get_tokens();
    // Setups the listing file with the program name and column headers
    void listing_head(string filename);
    // Writes a line to the listing file
    void listing_lnout();
    // Creates the map for looking up handlers for instructions and directives
    void setup_handler_map();
    // Retreives the symbol handler for the symbol
    sym_handler handler_for_symbol();
    // Symbol handelers for instructions and directives
    void handle_instruction();
    void handle_start();
    void handle_byte_word();
    void handle_resb();
    void handle_resw();
    void handle_equ();
    void handle_directive();
    void handle_empty();
    // Adds the label address to the symbol table if it has one
    void add_symbol_for_label();
    // Throws an error string
    void error_str(string msg);
    // Throws an error string also printing the line contents
    void error_ln_str(string msg);
    
    int getDisplacement( int, int );
    
public:
    // Sets up the handler map and listing file
    sicxe_asm(string file);
    ~sicxe_asm();
    
    // Assigns addresses to each line, adds labels and directives to the symbol
    // table
    void pass1();
    
    void pass2();
    
};

#endif
