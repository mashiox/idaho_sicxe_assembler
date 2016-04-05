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

int hextoi(string str) {
    int integer;
    stringstream ss;
    ss << hex << str;
    ss >> integer;
    return integer;
}

bool isdecimal(string& str, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

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

bool isconstant(string& str) {
    if (str.empty())
        return false;
    return (str[0] == '$') ? ishexadecimal(str, 1, str.length())
    	: isdecimal(str, 0, str.length());
}

int ctoi(string& str) {
    return (str[0] == '$') ? hextoi(str.substr(1)): atoi(str.c_str());
}

bool isquoted(string& str) {
    return ((str[1] == '\'') && (str[str.length()-1] == '\'')) ? true : false;
}

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

unsigned int size_for_literal(string& str) {
    return ((str[0] == 'c') || (str[0] == 'C')) ? (unsigned int)str.length()-3
    	: (unsigned int)(str.length()-3)>>1;
}

string itos(int integer) {
    stringstream itoss;
    itoss << integer;
    return itoss.str();
}

bool is_start( string opcode ){
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    return ( opcode.compare("START") == 0 ? true : false );
}

bool is_end( string opcode ){
    transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
    return ( opcode.compare("END") == 0 ? true : false );
}

const struct sicxe_asm::dhpair sicxe_asm::dhpairs[9] = {
    {"START", &sicxe_asm::handle_start},
    {"END", &sicxe_asm::handle_directive},
    {"BYTE", &sicxe_asm::handle_byte_word},
    {"WORD", &sicxe_asm::handle_byte_word},
    {"RESB", &sicxe_asm::handle_resb},
    {"RESW", &sicxe_asm::handle_resw},
    {"BASE", &sicxe_asm::handle_directive},
    {"NOBASE", &sicxe_asm::handle_directive},
    {"EQU", &sicxe_asm::handle_equ}
};

sicxe_asm::sicxe_asm(string file) {
    parser = new file_parser(file);
    locctr = 0;
    setup_handler_map();
    string listingFile = file.substr(0, file.rfind("."));
    listingFile = listingFile + ".lis";
    listing.open(listingFile.c_str());
    listing_head(file);
}

sicxe_asm::~sicxe_asm() {
    listing.close();
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
            listing_lnout();
            break;
        } else if (!opcode.empty()) {
            error_ln_str("There must be no operations before start directive.");
        } else {
            listing_lnout();
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
        listing_lnout();
        if (is_end(opcode)) {
            handle_directive();
            break;
        }
        else {
            handle_symbol = handler_for_symbol();
            (this->*handle_symbol)();
        }
    }
    
    if (index == nlines) {
        error_str("There is no end directive in sourcefile.");
    }
    for (++index; index < nlines; ++index) {
        line_addrs.push_back(locctr);
        get_tokens();
        listing_lnout();
        if (!opcode.empty()) {
            error_ln_str("Additional operations cannot exist after end directive.");
        }
    }
}

void sicxe_asm::get_tokens() {
    label = parser->get_token(index, 0);
    opcode = parser->get_token(index, 1);
    operand = parser->get_token(index, 2);
    comment = parser->get_token(index, 3);
}

void sicxe_asm::listing_head(string filename) {
    int width = 38-(int)(filename.length()>>1);
    listing << setw(width) << "**" << filename << "**" << "\n\n";
    listing << setw(5) << "Line#" << setw(8) << " Address" << setw(16);
    listing << " Label" << setw(16) << "Opcode" << setw(36) << "Operand\n";
    listing << setw(5) << "=====" << setw(8) << " =======" << setw(16);
    listing << " =====" << setw(16) << "======" << setw(36) << "=======\n";
}

void sicxe_asm::listing_lnout() {
    listing << setw(5) << dec << index+1;
    listing << "   " << setw(5) << hex << uppercase << setfill('0') << locctr;
    listing << setw(16) << setfill(' ') << label;
    listing << setw(16) << opcode;
    listing << setw(36) << operand << "\n";
}

void sicxe_asm::setup_handler_map() {
    unsigned int i;
    for (i = 0; i < sizeof(opcodetab::instrs)/sizeof(opcodetab::instr); ++i) {
        string instr = opcodetab::instrs[i].menmonic;
        transform(instr.begin(), instr.end(), instr.begin(), ::toupper);
        hmap.insert(make_pair(instr, &sicxe_asm::handle_instruction));
    }
    
    for (i = 0; i < sizeof(sicxe_asm::dhpairs)/sizeof(sicxe_asm::dhpair); ++i) {
        hmap.insert(make_pair(sicxe_asm::dhpairs[i].directive,
        	sicxe_asm::dhpairs[i].handler));
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
        error_ln_str("Invalid opcode.");
    }
    return iter->second;
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
    
    try {
        symbols.add(opcode, label);
    }
    catch (symtab_exception e) {
        error_ln_str(e.getMessage());
    }
}

void sicxe_asm::handle_byte_word() {
    if (isliteral(operand))
        locctr += size_for_literal(operand);
    else if (isconstant(operand))
        locctr += (opcode[0] == 'b' || opcode[0] == 'B') ? 1: 3;
    else
        error_ln_str("Invalid quoted literal.");
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

void sicxe_asm::handle_directive() {
    try {
        symbols.add(opcode, operand);
    }
    catch (symtab_exception e) {
        error_ln_str(e.getMessage());
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Proper usage is " << argv[0] << " filename. " << endl;
        return 1;
    }
    
    sicxe_asm assembler(argv[1]);
    
    try {
    	assembler.pass1();
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
