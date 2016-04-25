/* Phillip Domann, Shad Aziz, Melanie Reed, Matt Walther
   masc0832
   Team Idaho
   prog3
   CS530, Spring 2016
*/

#include <map>
#include <string>
#include <sstream>
#include "symtab.h"
#include "symtab_exception.h"

using namespace std;	

symtab::symtab(){}

void symtab::add(string label, struct symbol value){
    transform(label.begin(), label.end(), label.begin(), ::toupper);
	symbol_iter = symbol_table.find(label);
	if( symbol_iter != symbol_table.end() ) {
		throw symtab_exception("Symbol " + label + " already declared");
    }
    	symbol_table[label] = value; 
}

struct symtab::symbol symtab::get(string label){
    transform(label.begin(), label.end(), label.begin(), ::toupper);
	symbol_iter = symbol_table.find(label);
	if( symbol_iter == symbol_table.end() ) {
		throw symtab_exception("Label " + label + " does not exist");
	 }
	return symbol_iter->second;
}
	
bool symtab::exists(string label){
    transform(label.begin(), label.end(), label.begin(), ::toupper);
	if ( symbol_table.find(label) == symbol_table.end() )
		return false;
	else
		return true;
}

// remove before submission
void symtab::print() {
    map<string, struct symbol>::iterator it;
    for (it = symbol_table.begin(); it != symbol_table.end(); ++it) {
        cout << it->first << " " << it->second.value << " " << it->second.isaddress << endl;
    }
}
