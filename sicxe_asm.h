/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
 mascxxxx
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

#define line_width     7
#define address_width  8
#define label_width    9
#define opcode_width   8
#define operand_width  28

using namespace std;

class sicxe_asm {
    typedef void (sicxe_asm::*sym_handler)();
    
    file_parser* parser = NULL;
    opcodetab optab;
    symtab symbols;
    map<string, sym_handler> hmap;
    vector<unsigned int> line_addrs;
    unsigned int index;
    unsigned int locctr = 0;
    string label;
    string opcode;
    string operand;
    string comment;
    stringstream listing;
    
    struct dhpair {
        string directive;
        sym_handler handler;
    };
    
    const struct dhpair dhpairs[9] = {
        {"START", &sicxe_asm::handle_start},
        {"END", &sicxe_asm::handle_end},
        {"BYTE", &sicxe_asm::handle_byte},
        {"WORD", &sicxe_asm::handle_word},
        {"RESB", &sicxe_asm::handle_resb},
        {"RESW", &sicxe_asm::handle_resw},
        {"BASE", &sicxe_asm::handle_base},
        {"NOBASE", &sicxe_asm::handle_nobase},
        {"EQU", &sicxe_asm::handle_equ}
    };
    
    void get_tokens();
    void listing_head(string filename);
    void addto_listing();
    
    void setup_handler_map();
    sym_handler handler_for_symbol();
    void handle_instruction();
    void handle_start();
    void handle_end();
    void handle_byte();
    void handle_word();
    void handle_resb();
    void handle_resw();
    void handle_base();
    void handle_nobase();
    void handle_equ();
    void handle_empty();
    
public:
    sicxe_asm(string file);
    ~sicxe_asm();
    
    void pass1();
    void print_listing();
    
};

#endif
