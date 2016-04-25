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

void symtab::add(string label, string value){
	symbol_iter = symbol_table.find(label);
	if( symbol_iter != symbol_table.end() ) {
		throw symtab_exception("Symbol " + label + " already declared");
    }
    	symbol_table[label] = value; 
}

string symtab::get(string label){
	symbol_iter = symbol_table.find(label);
	if( symbol_iter == symbol_table.end() ) {
		throw symtab_exception("Label " + label + " does not exist");
	 }
	return symbol_iter->second;
}
	
bool symtab::exists(string label){
	if ( symbol_table.find(label) == symbol_table.end() )
		return false;
	else
		return true;
}
