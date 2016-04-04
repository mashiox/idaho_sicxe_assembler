//#include <string>
#include <sstream>
#include "sicxe_asm.h"

using namespace std;

/**
* Auxiliary function,
*/
bool is_hex_string( string hex ){
    if ( hex.length() == 0 ) return false;
    
    if ( hex.compare(0, 1, "x" ) == 0 ) return true;
    return false;
}

/**
* Auxiliary function, 
*/
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

void sicxe_asm::handle_start( int* start_address, string label ){
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
     
     /**
      * NEEDS
      * Aux function for hex str -> int
      */
}

void sicxe_asm::handle_end( string label ){
    /**
     * TODO
     * Set program length to LOCCTR.
     */
}

void sicxe_asm::handle_end(){
    handle_end("");
}

void sicxe_asm::handle_word( int constant, string label ){
    /**
     * Save symtab[label] = constant
     * Increment LOCCTR by 3, locctr += 3
     */ 
}

void sicxe_asm::handle_resw( int constant, string label ){
    /**
        WARN: Unsure if this is the right approach to be compatible with SYMTAB.
        However, even if chars are stored in this space, they can be interpreted as ints
            because of ASCII.
        It might be good if SYMTAB was a map of int*s though... then everything is consistent.
     */
    int* reserved_space = new int[ 3*constant ];
    /**
     * Save symtab[label] = reserved_space;
     * 
     * Increment locctr by 3*constant, locctr += 3*constant
     */
}


void sicxe_asm::handle_resb( int constant, string label ){
    /**
     * Same issue as handle_resw()
     */
    int* reserved_space = new int[ constant ];
    /**
     * TODO
     * save symtab[label] = reserved_space
     * increment locctr by constant, locctr += constant
     */
}

int* string_to_int( string key ){
    int* iptr = new int[ key.length() ];
    for ( size_t index = 0 ; index < key.length() ; index++ ){
        *( iptr + index ) = (int)key[index];
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

void handle_byte( string byte_code, string label ){
    string literal;
    size_t byte_length;
    int* int_code;
    /**
     * BYTE x'abcd' case
     */ 
    if ( is_hex_string(byte_code) ){
        literal = get_byte_literal( byte_code );
        if ( literal.length() != 4 ) return; // TODO, THROW EXCEPTION
        byte_length = 4;
        int_code = string_to_hex( literal );
    }
    /**
     * BYTE c'abcdefg' case
     */
    else if ( is_char_string(byte_code) ){
        literal = get_byte_literal( byte_code );
        byte_length = literal.length();
        int_code = string_to_int( literal );
    }
    else {
        // THROW EXCEPTION
    }
     
     /**
      * TODO
      * Save symtab[label] = int_code
      * increment locctr by byte_length. locctr += byte_length.
      */
}

