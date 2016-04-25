/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
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

// Converts a hex string to an integer value
int hextoi(string str) {
    int integer;
    stringstream ss;
    ss << hex << str;
    ss >> integer;
    return integer;
}

// Checks that a string range contains only digits
bool isdecimal(string& str, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


// Checks that a string range contains only hexadecimal digits
bool ishexadecimal(string& str, size_t start, size_t end) {
    string upper = str;
    transform(upper.begin(),upper.end(), upper.begin(), ::toupper);
    for (size_t i = start; i < end; ++i) {
        if (!(isdigit(upper[i]) || (65 <= upper[i] && upper[i] <= 70))) {
            return false;
        }
    }
    return true;
}

// Verifies that a string contains vaild hex or decimal digits
bool isconstant(string& str) {
    if (str.empty())
        return false;
    return (str[0] == '$') ? ishexadecimal(str, 1, str.length())
    	: isdecimal(str, 0, str.length());
}


// Converts a string constant to an integer
int ctoi(string& str) {
    return (str[0] == '$') ? hextoi(str.substr(1)): atoi(str.c_str());
}

// Verifies that a literal is quoted
bool isquoted(string& str) {
    return ((str[1] == '\'') && (str[str.length()-1] == '\'')) ? true : false;
}

// Verifies that a string is a valid literal string
bool isliteral(string& str) {
    if (str.empty() || str.length() < 3)
        return false;
    if ((str[0] == 'c') || (str[0] == 'C'))
        return isquoted(str);
    else if (((str[0] == 'x') || (str[0] == 'X')) && (str.length()%2 == 1)) {
        return (isquoted(str)) ? ishexadecimal(str, 2, str.length()-1): false;
    }
    return false;
}

// Returns the size for a quoted literal
unsigned int size_for_literal(string& str) {
    return ((str[0] == 'c') || (str[0] == 'C')) ? (unsigned int)str.length()-3
    	: (unsigned int)(str.length()-3)>>1;
}

// Converts an integer to a string
string itos(int integer) {
    stringstream itoss;
    itoss << integer;
    return itoss.str();
}

// Searches for the start directive
bool is_start( string opcode ){
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    return ( opcode.compare("START") == 0 ? true : false );
}

// Searches for the end directive
bool is_end( string opcode ){
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    return ( opcode.compare("END") == 0 ? true : false );
}

const struct sicxe_asm::dhpair sicxe_asm::dhpairs[9] = {
    {"START", {&sicxe_asm::handle_start, &sicxe_asm::empty_objcode}},
    {"END", {&sicxe_asm::handle_end, &sicxe_asm::empty_objcode}},
    {"BYTE", {&sicxe_asm::handle_byte, &sicxe_asm::byte_objcode}},
    {"WORD", {&sicxe_asm::handle_word, &sicxe_asm::word_objcode}},
    {"RESB", {&sicxe_asm::handle_resb, &sicxe_asm::empty_objcode}},
    {"RESW", {&sicxe_asm::handle_resw, &sicxe_asm::empty_objcode}},
    {"BASE", {&sicxe_asm::handle_base, &sicxe_asm::set_base_address}},
    {"NOBASE", {&sicxe_asm::handle_nobase, &sicxe_asm::set_nobase}},
    {"EQU", {&sicxe_asm::handle_equ, &sicxe_asm::empty_objcode}}
};

sicxe_asm::sicxe_asm(string file) {
    parser = new file_parser(file);
    locctr = 0;
    setup_handler_map();
    listing_head(file);
}

sicxe_asm::~sicxe_asm() {
    delete parser;
}

void sicxe_asm::error_str(string msg) {
    string str = "***Error***\n";
    str.append(msg);
    throw str;
}

void sicxe_asm::error_ln_str(string msg) {
    string str = "***Error***\n";
    string lnmsg = "Line "+itos(index+1)+": "+label+" "+opcode+" "+operand+"\n";
    str.append(lnmsg);
    str.append(msg);
    throw str;
}

void sicxe_asm::pass1() {
    parser->read_file();
    
    unsigned int nlines = (unsigned int)parser->size();
    for (index = 0; index < nlines; ++index) {
        get_tokens();
        if (is_start(opcode)) {
            handle_start();
            line_addrs.push_back(locctr);
            break;
        } else if (!opcode.empty()) {
            error_ln_str("There must be no operations before start directive.");
        } else {
            line_addrs.push_back(locctr);
        }
    }
    
    if (index == nlines) {
        error_str("There is no start directive in sourcefile.");
    }
    sym_handler handle_symbol;
    for (++index; index < nlines; ++index) {
        line_addrs.push_back(locctr);
        get_tokens();
        if (is_end(opcode)) {
            handle_end();
            line_addrs.push_back(locctr);
            break;
        }
        else {
            handle_symbol = handler_for_symbol(1);
            (this->*handle_symbol)();
        }
    }
    
    if (index == nlines) {
        error_str("There is no end directive in sourcefile.");
    }
    for (++index; index < nlines; ++index) {
        line_addrs.push_back(locctr);
        get_tokens();
        if (!opcode.empty()) {
            error_ln_str("Additional operations cannot exist after end directive.");
        }
    }
    line_addrs.push_back(locctr);
    
}

void sicxe_asm::pass2() {
    symbols.print(); // remove before submission
    noBase = true;
    unsigned int nlines = (unsigned int)parser->size();

    for (index = 0; index < nlines; ++index) {
        get_tokens();
        sym_handler handle_symbol =  handler_for_symbol(0);
        (this->*handle_symbol)();
        listing_lnout();
    }
}

void sicxe_asm::write_listing(string file) {
    ofstream listingStream;
    string listingFile = file.substr(0, file.rfind("."));
    listingFile = listingFile + ".lis";
    listingStream.open(listingFile.c_str());
    listingStream << listing.str();
    listingStream.close();
}

// remove before submission
void sicxe_asm::print_listing() {
    cout << listing.str();
}

void sicxe_asm::get_tokens() {
    label = parser->get_token(index, 0);
    opcode = parser->get_token(index, 1);
    operand = parser->get_token(index, 2);
}

void sicxe_asm::listing_head(string filename) {
    int width = 38-(int)(filename.length()>>1);
    listing << setw(width) << "**" << filename << "**" << "\n\n";
    listing << left << setw(5) << "Line#";
    listing << setw(8) << " Address";
    listing << setw(9) << " Label";
    listing << setw(16) << " Opcode";
    listing << setw(28) << " Operand";
    listing << setw(12) << " Machine Code";
    listing << endl;
    listing << setw(5) << "=====" << setw(8) << " =======" << setw(9);
    listing << " =====" << setw(16) << " ======" << setw(28) << " =======";
    listing << setw(12) << " ============" << endl;
}

void sicxe_asm::listing_lnout() {
    listing << right << setw(5) << dec << index+1;
    listing << "   " << setw(5) << hex << uppercase << setfill('0') << line_addrs.at(index);
    listing << " " << left << setw(8) << setfill(' ') << label;
    listing << " " << setw(15) << opcode;
    listing << " " << setw(27) << operand;
    listing << " " << setw(11) << objCode;
    listing << endl;
}

void sicxe_asm::setup_handler_map() {
    unsigned int i;
    for (i = 0; i < sizeof(opcodetab::instrs)/sizeof(opcodetab::instr); ++i) {
        string instr = opcodetab::instrs[i].menmonic;
        transform(instr.begin(), instr.end(), instr.begin(), ::toupper);
        struct hpair handlers;
        handlers.pass1 = &sicxe_asm::handle_instruction;
        short format = opcodetab::instrs[i].details.format;
        switch (format) {
            case 1:
                handlers.pass2 = &sicxe_asm::format1_objcode;
                break;
            case 2:
                handlers.pass2 = &sicxe_asm::format2_objcode;
                break;
            case 3:
                handlers.pass2 = &sicxe_asm::format3_objcode;
                break;
        }
        hmap.insert(make_pair(instr, handlers));
    }
    
    for (i = 0; i < sizeof(sicxe_asm::dhpairs)/sizeof(sicxe_asm::dhpair); ++i) {
        hmap.insert(make_pair(sicxe_asm::dhpairs[i].directive,
        	sicxe_asm::dhpairs[i].handlers));
    }
}

sicxe_asm::sym_handler sicxe_asm::handler_for_symbol(bool pass) {
    if (opcode.empty()) {
        return (pass) ? &sicxe_asm::handle_empty : &sicxe_asm::empty_objcode;
    }
    string symbol = (opcode[0] == '+') ? opcode.substr(1, string::npos) : opcode;
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
    map<string, struct sicxe_asm::hpair>::iterator iter = hmap.find(symbol);
    if (iter == hmap.end()) {
        error_ln_str("Invalid opcode.");
    }
    
    return (pass) ? iter->second.pass1: iter->second.pass2;
}

void sicxe_asm::handle_instruction() {
    try {
        locctr += optab.get_instruction_size(opcode);
    }
    catch (opcode_error_exception e) {
        error_ln_str(e.getMessage());
    }
    add_symbol_for_label();
}

void sicxe_asm::handle_start() {
    if (isconstant(operand))
        locctr = ctoi(operand);
    else
        error_ln_str("Invalid constant.");
    add_symbol_for_label();
}

void sicxe_asm::handle_end() {
    if (operand.empty()) {
        error_ln_str("End directive must have label or address.");
    }
    add_symbol_for_label();
}

void sicxe_asm::handle_byte() {
    if (isliteral(operand))
        locctr += size_for_literal(operand);
    else
        error_ln_str("Invalid quoted literal.");
    add_symbol_for_label();
}

void sicxe_asm::handle_word() {
    if(isconstant(operand))
        locctr += 3;
    else
        error_ln_str("Invalid constant");
    add_symbol_for_label();
}

void sicxe_asm::handle_resb() {
    if (isconstant(operand))
        locctr += ctoi(operand);
    else
        error_ln_str("Invalid constant.");
    add_symbol_for_label();
}

void sicxe_asm::handle_resw() {
    if (isconstant(operand))
        locctr += ctoi(operand)*3;
    else
        error_ln_str("Invalid constant.");
    add_symbol_for_label();
}

void sicxe_asm::handle_equ() {
    try {
        symbols.add(label, operand);
    }
    catch (symtab_exception e) {
        error_ln_str(e.getMessage());
    }
}

void sicxe_asm::handle_base() {
    if (operand.empty()) {
        error_ln_str("Base directive requires label or address.");
    }
}

void sicxe_asm::handle_nobase() {
    if (!operand.empty()) {
        error_ln_str("Nobase directive does not use an operand");
    }
}

void sicxe_asm::handle_empty() {
    add_symbol_for_label();
}

void sicxe_asm::add_symbol_for_label() {
    if (!label.empty()) {
        try {
            symbols.add(label, itos(locctr));
        }
        catch (symtab_exception e) {
            error_ln_str(e.getMessage());
        }
    }
}

void sicxe_asm::format1_objcode() {
    objCode = optab.get_machine_code(opcode);
}

void sicxe_asm::format2_objcode() {
    // objCode =
}

void sicxe_asm::format3_objcode() {
    if (opcode[0] == '+') {
        format4_objcode();
        return;
    }
    // objCode =
}

void sicxe_asm::format4_objcode() {
	// objCode =
}

void sicxe_asm::byte_objcode() {
    // objCode =
}

void sicxe_asm::word_objcode() {
    // objCode =
}

void sicxe_asm::set_base_address() {
    objCode.clear();
    noBase = false;
    // get symbol from symtab
}

void sicxe_asm::set_nobase() {
    objCode.clear();
    noBase = true;
}

void sicxe_asm::empty_objcode() {
    objCode.clear();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Proper usage is " << argv[0] << " filename." << endl;
        return 1;
    }
    
    sicxe_asm assembler(argv[1]);
    
    try {
    	assembler.pass1();
        assembler.pass2();
        assembler.print_listing(); // remove before submission
        assembler.write_listing(string(argv[1]));
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
