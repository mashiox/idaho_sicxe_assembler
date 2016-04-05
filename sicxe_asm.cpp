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

string itos(int integer) {
    stringstream itoss;
    itoss << integer;
    return itoss.str();
}

bool is_hex_string( string hex ){
	if ( hex.length() == 0 ) return false;
	
	if ( hex.compare(0, 1, "x" ) == 0 ) return true;
	return false;
}

bool is_char_string( string char_string ){
	if ( char_string.length() == 0 ) return false;
	
	if ( char_string.compare(0, 1, "c" ) == 0 ) return true;
	return false;
}

string get_byte_literal( string literal ){
	// This is the wrong thing to do, we need to throw an exception instead.
	if ( literal.length() == 0 ) return string("");
	
	return literal.substr( 2, literal.length()-3 );
}

int* string_to_int( string key ){
	int* iptr = new int[ key.length() ];
	for ( size_t idx = 0 ; idx < key.length() ; idx++ ){
		( iptr +idx ) = (int)key[idx];
    }
    return iptr;
}

int* string_to_hex( string literal ){
	int *iptr = new int[ 1 ];
	stringstream ss;
	ss << std::hex << literal;
    ss >> *iptr;
	return iptr;
}

bool is_start( string opcode ){
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    return ( opcode.compare("START") == 0 ? true : false );
}

bool is_end( string opcode ){
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    return ( opcode.compare("END") == 0 ? true : false );
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
    for (index = 0; index < nlines; ++index) {
        get_tokens();
        if (is_start(opcode)) {
            handle_start();
            break;
        } else if (!opcode.empty()) {
            throw string("Error: Line "+itos(index+1)+", There must be no operations before start directive.");
        } else {
            handle_empty();
        }
    }
    
    if (index == nlines) {
        throw string("Error: There is no start directive in sourcefile.");
    }
    sym_handler handle_symbol;
    for (++index; index < nlines; ++index) {
        get_tokens();
        if (is_end(opcode)) {
            handle_end();
            break;
        }
        else {
            handle_symbol = handler_for_symbol();
            (this->*handle_symbol)();
        }
    }
    
    if (index == nlines) {
        throw string("Error: There is no end directive in sourcefile.");
    }
    for (++index; index < nlines; ++index) {
        get_tokens();
        if (!opcode.empty()) {
            throw string("Error: Line "+itos(index+1)+" Additional operations exist after end directive.");
        }
        handle_empty();
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
    if (opcode.empty()) {
        return &sicxe_asm::handle_empty;
    }
    string symbol = (opcode[0] == '+') ? opcode.substr(1, string::npos) : opcode;
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
    map<string, sym_handler>::iterator iter = hmap.find(symbol);
    if (iter == hmap.end()) {
        throw string("Error: Line "+itos(index+1)+", invalid opcode "+opcode+".");
    }
    return iter->second;
}

void sicxe_asm::handle_instruction() {
    int size = optab.get_instruction_size(opcode);
    addto_listing();
    locctr += size;
}
void sicxe_asm::handle_start() {
    /**
    * NB
	* start_address comes off the file as a hex string
	* use string_to_hex( string ) to convert to int*.
 	*/
	
	/**
	* TODO
	* Save symtab[label] = start_address
	*
	* Set LOCCTR to start_address
	*
	* Aux function to write intermediate file.
	*/

	
    addto_listing();
}

void sicxe_asm::handle_end() {
    /**
	* TODO
	* Set program length to LOCCTR.
	*/
	addto_listing();
}

void sicxe_asm::handle_byte() {
    string literal;
	size_t byte_length;
	int* int_code;
	/**
	* BYTE x'abcd' case
	*/
	if ( is_hex_string(operand) ){
		literal = get_byte_literal( operand );
		if ( literal.length() != 4 ) return; // TODO, THROW EXCEPTION
		byte_length = 4;
        int_code = string_to_hex( literal );
    }
	/**
	* BYTE c'abcdefg' case
	*/
	else if ( is_char_string(operand) ){
		literal = get_byte_literal( operand );
		byte_length = literal.length();
		int_code = string_to_int( literal );
    }
	else {
	// THROW EXCEPTION
	/**
	* TODO
	* Save symtab[label] = int_code
	* increment locctr by byte_length. locctr += byte_length.
	*/
    }
	addto_listing();
}

void sicxe_asm::handle_word() {
    /**
	* Save symtab[label] = constant
	* Increment LOCCTR by 3, locctr += 3
	*/
	addto_listing();
}

void sicxe_asm::handle_resb() {
    /**
	* Same issue as handle_resw()
	*/
    //convert operand to int and add to locctr
	//int* reserved_space = new int[ operand ];
	/**
    * TODO
	* save symtab[label] = reserved_space
	* increment locctr by constant, locctr += constant
	*/
	addto_listing();
}

void sicxe_asm::handle_resw() {
    /**
	WARN: Unsure if this is the right approach to be compatible with SYMTAB.
	However, even if chars are stored in this space, they can be interpreted as ints
	because of ASCII.
	It might be good if SYMTAB was a map of int*s though... then everything is consistent.
	*/
    //convert operand to int and add to locctr
	//int* reserved_space = new int[ 3*operand ];
	/**
	* Save symtab[label] = reserved_space;
	*
	* Increment locctr by 3*constant, locctr += 3*constant
	*/
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

void sicxe_asm::handle_empty() {
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
    	assembler.print_listing();
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
