/* Phillip Domann, Shad Aziz, Melanie Reed, Matt Walther
   mascxxxx
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

void symtab::add(string label,int* value){ // adds label and value into map
	symbol_iter = symbol_table.find(label);
	if( symbol_iter != symbol_table.end() ) { //label already exists
		throw symtab_exception("Symbol " + label + " already declared");
    }
    	symbol_table[label] = value; 
}

int* symtab::get(string label){ //returns value
	symbol_iter = symbol_table.find(label);
	if( symbol_iter == symbol_table.end() ) { //label doesnt exist
		throw symtab_exception("Label " + label + " does not exist");
	 }
	return symbol_table[label];
}
	
bool symtab::exists(string label){
	if ( symbol_table.find(label) == symbol_table.end() ) // label doesnt exist
		return false;
	else
		return true;
}
