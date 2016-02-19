/*  file_parser.h
    CS530, Spring 2016
*/
#ifndef FILE_PARSER_H
#define FILE_PARSER_H
#include<fstream>
#include<string>
#include<vector>
#include<ctype.h>
#include<stdio.h>
#include<stdbool.h>

using namespace std;

struct line{
    string label,
           opcode,
           operand,
           comment;
    line(){
    label = "";
	opcode = "";
	operand = "";
	comment = "";
	}
    string getlabel(){
        return label;
	}
    string getopcode(){
        return opcode;
	}
    string getoperand(){
        return operand;
	}
    string getcomment(){
        return comment;
	}
    void setlabel(string lab){
	if(lab.length() > 7)
    		lab.resize(8);
        label = lab;
	}
    void setopcode(string op){
    	opcode = op;
	}
    void setoperand(string oper){
        operand = oper;
	}
    void setcomment(string com){
        comment = com; 
	}
    bool islabel(string islab){
    	if(!isalpha(islab[0]))
		return false;
		   	for(int i = 0; i<sizeof(islab); i++){
   	if(!isdigit(islab[i]) || !isalpha(islab[i]))
           	return false;
	}
	   return true;    
	}
/*	
    bool isopcode(string isop){
   	string validop[1000] = ("ADD", "ADDF", "ADDR", "AND", "CLEAR", "COMP",
	"COMPF", "COMPR", "DIV", "DIVF", "DIVR", "FIX", "FLOAT", "HIO", "J",
	"JEQ", "JGT", "JLT", "JSUB", "LDA", "LDB", "LDCH", "LDF", "LDL", "LDS",
	"LDT", "LDX", "LPS", "MUL", "MULF", "MULR", "NORM", "OR", "RD", "RMO",
	"SHIFTL", "SHIFTR", "SIO", "SSK", "STA", "STB", "STCH", "STF", "STI",
	"STL", "STS", "STSW", "STT", "STX", "SUB", "SUBF", "SUBR", "SUBR",
	"SVC", "TD", "TIO", "TIX", "TIXR", "WD");
        for(int i = 0; i<sizeof(validop);i++)
           if(isop == validop[i])
           	return true;   
   	return false;           
	}
*/	
    bool iscomment(string iscom){
        if(iscom[0] != '.')
            return false;
        return true;      
	}
    
    
};

class file_parser {
    public:
        // ctor, filename is the parameter.  A driver program will read
        // the filename from the command line, and pass the filename to
        // the file_parser constructor.  Filenames must not be hard-coded.
        file_parser(string);

        // dtor
        ~file_parser();

        // reads the source file, storing the information is some
        // auxiliary data structure you define in the private section.
        // Throws a file_parse_exception if an error occurs.
        // if the source code file fails to conform to the above
        // specification, this is an error condition.
        void read_file();

        // returns the token found at (row, column).  Rows and columns
        // are zero based.  Returns the empty string "" if there is no
        // token at that location. column refers to the four fields
        // identified above.
        string get_token(unsigned int, unsigned int);

        // prints the source code file to stdout.  Should not repeat
        // the exact formatting of the original, but uses tabs to align
        // similar tokens in a column. The fields should match the
        // order of token fields given above (label/opcode/operands/comments)
        void print_file();

        // returns the number of lines in the source code file
        int size();
        

    private:
        // your variables and private methods go here
        vector<line> container;
        string filename;
        const string* source;
    
        // Reads the entire source file into memory, throws an error if the
        // file cannot be opened or memory cannot be allocated
        const string* get_file_contents();
        
        // Sets the token as a struct line
        void set_token(struct line);
        string tokenize_comment(string);
        string file_parser::tokenize_label(string line, struct line &line_item);
    
};

#endif

