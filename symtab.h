/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
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
      	symtab();
  	void add(string, int*);
 	int* get(string);
 	bool exists(string);

 private:
      	map<string, int*> symbol_table;
	map<string, int*>::iterator symbol_iter;
 };

 #endif
