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
    string comment;
    ofstream listing;
    
    struct dhpair {
        string directive;
        sym_handler handler;
    };
    
    static const struct dhpair dhpairs[9];
    
    void get_tokens();
    void listing_head(string filename);
    void listing_lnout();
    
    void setup_handler_map();
    sym_handler handler_for_symbol();
    void handle_instruction();
    void handle_start();
    void handle_byte_word();
    void handle_resb();
    void handle_resw();
    void handle_equ();
    void handle_directive();
    void handle_empty();
    
    void add_symbol_for_label();
    
    void error_str(string msg);
    void error_ln_str(string msg);
    
    int getDisplacement( int, int );
    
public:
    sicxe_asm(string file);
    ~sicxe_asm();
    
    void pass1();
    
    void pass2();
    
};

#endif
