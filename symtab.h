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
  	void add(string, string);
 	string get(string);
 	bool exists(string);
     void print(); //remove before submission

 private:
      	map<string, string> symbol_table;
	map<string, string>::iterator symbol_iter;
 };

 #endif
