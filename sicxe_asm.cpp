/* Phillip Domann, Shad Aziz, Melanie Reed, Matt Walther
   masc0832
   Team Idaho
   prog3
   CS530, Spring 2016
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "sicxe_asm.h"
#include "file_parse_exception.h"
#include "opcode_error_exception.h"
#include "symtab_exception.h"

using namespace std;


bool is_start( string opcode ){
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    return ( opcode.compare("START") == 0 ? true : false );
}

sicxe_asm::sicxe_asm(string file) {
    parser = new file_parser(file);
    setup_handler_map();
    string listingFile = file.substr(0, file.find(".",0));
    listingFile = listingFile + ".lis";
    listing.open(ListingFile);
    listing_head(ListingFile);
}

sicxe_asm::~sicxe_asm() {
    delete parser;
}

void sicxe_asm::pass1() {
    parser->read_file();
    
    unsigned int nlines = (unsigned int)parser->size();
    while (index < nlines) {
        get_tokens();
        if (is_start(opcode)) {
            handle_start();
            break;
        } else if (!(opcode.empty() && operand.empty())) {
            throw string("Error: there must be no operations before start directive.\n");
        } else {
            addto_listing();
        }
        ++index;
    }
    
    if (index == nlines) {
        //no start directive
    }
    sym_handler handle_symbol;
    for (++index; index < nlines; ++index) {
        get_tokens();
        if (opcode.empty()) {
            addto_listing();
            continue;
        }
        //handle to end directive
        handle_symbol = handler_for_symbol();
        (this->*handle_symbol)();
    }
}

void sicxe_asm::get_tokens() {
    label = parser->get_token(index, 0);
    opcode = parser->get_token(index, 1);
    operand = parser->get_token(index, 2);
    comment = parser->get_token(index, 3);
}

void sicxe_asm::listing_head(string filename) {
	listing << "Line#" << setw(16) << "Address" << setw(16) <<"Label" << setw(16) << "Opcode" << setw(36) << "Operand\n";
	listing << "=====" << setw(16) << "=======" << setw(16) <<"=====" << setw(16) << "======" << setw(36) << "=======\n";
}

void sicxe_asm::addto_listing() {
    listing << dec << index+1 << setw(16) << hex << uppercase << setfill("0") << locctr << setw(16) << setfill(" ") << label << setw(16) << opcode << setw(36) << operand << "\n";
}

//void sicxe_asm::write_listing() {
//    listing.str() << ;
//}

//void sicxe_asm::print_listing() {
//    cout << listing.str();
//}

void sicxe_asm::setup_handler_map() {
    unsigned int i;
    for (i = 0; i < sizeof(opcodetab::instrs)/sizeof(opcodetab::instr); ++i) {
        string instruction = opcodetab::instrs[i].menmonic;
        transform(instruction.begin(), instruction.end(), instruction.begin(), ::toupper);
        hmap.insert(make_pair(instruction, &sicxe_asm::handle_instruction));
    }
    
    for (i = 0; i < sizeof(sicxe_asm::dhpairs)/sizeof(sicxe_asm::dhpair); ++i) {
        hmap.insert(make_pair(sicxe_asm::dhpairs[i].directive, sicxe_asm::dhpairs[i].handler));
    }
}

sicxe_asm::sym_handler sicxe_asm::handler_for_symbol() {
    string symbol = (opcode[0] == '+') ? opcode.substr(1, string::npos) : opcode;
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
    map<string, sym_handler>::iterator iter = hmap.find(symbol);
    if (iter == hmap.end()) {
        throw string("Error: unhandeled opcode");
    }
    return iter->second;
}

void sicxe_asm::handle_instruction() {
    int size = optab.get_instruction_size(opcode);
    addto_listing();
    locctr += size;
}
void sicxe_asm::handle_start() {
	addto_listing();
}

void sicxe_asm::handle_end() {
	addto_listing();
}

void sicxe_asm::handle_byte() {
	addto_listing();
}

void sicxe_asm::handle_word() {
	addto_listing();
}

void sicxe_asm::handle_resb() {
	addto_listing();
}

void sicxe_asm::handle_resw() {
	addto_listing();
}

void sicxe_asm::handle_base() {
	addto_listing();
}

void sicxe_asm::handle_nobase() {
	addto_listing();
}

void sicxe_asm::handle_equ() {
	addto_listing();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Proper usage is " << argv[0] << " filename. " << endl;
    }
    
    sicxe_asm assembler(argv[1]);
    
    try {
    	assembler.pass1();
    	//assembler.write_listing();
    	//assembler.print_listing();
        return 0;
    }
    catch (file_parse_exception fpe) {
        cout << fpe.getMessage();
    }
    catch (opcode_error_exception oee) {
        cout << oee.getMessage();
    }
    catch (symtab_exception se) {
        cout << se.getMessage();
    }
    catch (string str) {
        cout << str;
    }
    
    return 1;
}
