/*  file_parser.h
    CS530, Spring 2016
*/
#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>
#include <ctype.h>
#include <sstream>
#include <stdio.h>
#include <stdbool.h>

using namespace std;

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
    };
    
    vector<line> container;
    string filename;
    const string* source;
    
    // Reads the entire source file into memory, throws an error if the
    // file cannot be opened or memory cannot be allocated
    const string* get_file_contents();
        
    class tokenizer {
        
    public:
        tokenizer(const string&);
        struct line tokens();
    private:
        string str;
        enum column {none, label, opcode, operand, comment};
        static const char* delimiters;
        
        bool islabel(string islab){
            if(!isalpha(islab[0]))
                return false;
            for(string::size_type i = 1; i<islab.length(); i++){
                if(!isalnum(islab[i]))
                    return false;
            }
            return true;
        }
        
        bool iscomment(string iscom){
            if(iscom[0] != '.')
                return false;
            return true;
        }
        
    };
};

#endif

