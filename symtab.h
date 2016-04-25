/* Phillip Domann, Shad Aziz, Melanie Reed, Matt Walther
   masc0832
   Team Idaho
   prog3
   CS530, Spring 2016
*/

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>

#ifndef SYMTAB_H_
#define SYMTAB_H_

using namespace std;

 class symtab {
 public:
     
     struct symbol {
         bool isaddress;
         string value;
     };
     
    symtab();
  	void add(string, struct symbol);
 	struct symbol get(string);
 	bool exists(string);
    void print(); //remove before submission

 private:
    map<string, struct symbol> symbol_table;
	  map<string, struct symbol>::iterator symbol_iter;
 };

 #endif
