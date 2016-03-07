/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
   mascxxxx
   Team Idaho
   prog2
   CS530, Spring 2016
 */

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "opcodetab.h"
#include "opcode_error_exception.h"

using namespace std;

struct instr {
	string menmonic;
    short size;
    string opcode;
};

const struct instr instrs[] = {
    {"add", 3, "18"},
    {"addf", 3, "58"},
    {"addr", 2, "90"},
    {"and", 3, "40"},
    {"clear", 2, "b4"},
    {"comp", 3, "28"},
    {"compf", 3, "88"},
    {"compr", 2, "a0"},
    {"div", 3, "24"},
    {"divf", 3, "64"},
    {"divr", 2, "9c"},
    {"fix", 1, "c4"},
    {"float", 1, "c0"},
    {"hio", 1, "f4"},
    {"j", 3, "3c"},
    {"jeq", 3, "30"},
    {"jgt", 3, "34"},
    {"jlt", 3, "38"},
    {"jsub", 3, "48"},
    {"lda", 3, "00"},
    {"ldb", 3, "68"},
    {"ldch", 3, "50"},
    {"ldf", 3, "70"},
    {"ldl", 3, "08"},
    {"lds", 3, "6c"},
    {"ldt", 3, "74"},
    {"ldx", 3, "04"},
    {"lps", 3, "d0"},
    {"mul", 3, "20"},
    {"mulf", 3, "60"},
    {"mulr", 2, "98"},
    {"norm", 1, "c8"},
    {"or", 3, "44"},
    {"rd", 3, "d8"},
    {"rmo", 2, "ac"},
    {"rsub", 3, "4c"},
    {"shiftl", 2, "a4"},
    {"shiftr", 2, "a8"},
    {"sio", 1, "f0"},
    {"ssk", 3, "ec"},
    {"sta", 3, "0c"},
    {"stb", 3, "78"},
    {"stch", 3, "54"},
    {"stf", 3, "80"},
    {"sti", 3, "d4"},
    {"stl", 3, "14"},
    {"sts", 3, "7c"},
    {"stsw", 3, "e8"},
    {"stt", 3, "84"},
    {"stx", 3, "10"},
    {"sub", 3, "1c"},
    {"subf", 3, "5c"},
    {"subr", 2, "94"},
    {"svc", 2, "b0"},
    {"td", 3, "e0"},
    {"tio", 1, "f8"},
    {"tix", 3, "2c"},
    {"tixr", 2, "b8"},
    {"wd", 3, "dc"}
};

opcodetab* tab;
int pass = 0;
int fail = 0;

string strtolower(string&);
string strtorandomcase(string&);
void test_size_n(struct instr);
void test_size_4(struct instr);
void test_opcode_n(struct instr);
void test_opcode_4(struct instr);

string strtolower(string& str) {
    string retstr;
    retstr.reserve(str.length());
    for (string::iterator it = str.begin(); it != str.end(); ++it) {
        retstr.push_back(tolower(*it));
    }
    return retstr;
}

string strtorandomcase(string& str) {
    string retstr;
    retstr.reserve(str.length());
    int r = rand() % 2;
    for (string::iterator it = str.begin(); it != str.end(); ++it, r = rand()%2) {
        if (r) {
            retstr.push_back(toupper(*it));
        } else {
        	retstr.push_back(*it);
        }
    }
    return retstr;
}

void test_size_n(struct instr instr) {
    int test_size;
    string test_instr = strtorandomcase(instr.menmonic);
    try {
        test_size = tab->get_instruction_size(test_instr);
        if (test_size == instr.size) {
            cout << "pass: " << test_instr << " size " << test_size << "\n";
            ++pass;
        } else {
     		cout << "*fail: " << test_instr << " size, expecting size " << instr.size << " but returned " << test_size << "\n";
            ++fail;
        }
    } catch (opcode_error_exception e) {
        cout << "*fail: " << test_instr << " size, expecting size " << instr.size << " but received exception\n";
        ++fail;
    }
}

void test_size_4(struct instr instr) {
    int test_size;
    string test_instr = strtorandomcase(instr.menmonic);
    try {
        test_size = tab->get_instruction_size("+"+test_instr);
        if (test_size == 4 && instr.size == 3) {
            cout << "pass: +" << test_instr << " size " << test_size << "\n";
            ++pass;
        } else if (instr.size == 3) {
            cout << "*fail: +" << test_instr << " size, expecting size 4 but returned " << test_size << "\n";
            ++fail;
        } else {
            cout << "*fail: +" << test_instr << " size, expecting an exception\n";
            ++fail;
        }
    } catch (opcode_error_exception e) {
        if (instr.size == 3) {
            cout << "*fail: +" << test_instr << " size, expecting size 4 but received exception\n";
            ++fail;
        } else {
            cout << "pass: +" << test_instr << " size, caught exception\n";
            ++pass;
        }
    }
}

void test_opcode_n(struct instr instr) {
    string test_opcode;
    string test_instr = strtorandomcase(instr.menmonic);
    try {
        test_opcode = tab->get_machine_code(test_instr);
        if (strtolower(test_opcode).compare(instr.opcode) == 0) {
            cout << "pass: " << test_instr << " opcode " << instr.opcode << "\n";
            ++pass;
        } else {
            cout << "*fail: " << test_instr << " opcode, excpecting " << instr.opcode << " but returned " << test_opcode << "\n";
            ++fail;
        }
    } catch (opcode_error_exception e) {
        cout << "*fail: " << test_instr << " opcode, excpecting " << instr.opcode << " but received exception\n";
        ++fail;
    }
}

void test_opcode_4(struct instr instr) {
    string test_opcode;
    string test_instr = strtorandomcase(instr.menmonic);
    try {
        test_opcode = tab->get_machine_code("+"+test_instr);
        if (strtolower(test_opcode).compare(instr.opcode) == 0 && instr.size == 3) {
            cout << "pass: +" << test_instr << " opcode " << instr.opcode << "\n";
            ++pass;
        } else if (instr.size == 3) {
            cout << "*fail: +" << test_instr << " opcode, excpecting " << instr.opcode << " but returned " << test_opcode << "\n";
            ++fail;
        } else {
            cout << "*fail: +" << test_instr << " opcode, expecting an exception\n";
            ++fail;
        }
    } catch (opcode_error_exception e) {
        if (instr.size == 3) {
            cout << "*fail: +" << test_instr << " opcode, excpecting " << instr.opcode << " but received exception\n";
            ++fail;
        } else {
            cout << "pass: +" << test_instr << " opcode, caught exception\n";
            ++pass;
        }
    }
}

int main(int argc, const char *argv[]) {
    tab = new opcodetab();
    srand((unsigned int)time(NULL));
    
    int instr_count = sizeof(instrs)/sizeof(struct instr);
    for (int i = 0; i < instr_count; ++i) {
        test_size_n(instrs[i]);
        test_size_4(instrs[i]);
        test_opcode_n(instrs[i]);
        test_opcode_4(instrs[i]);
        //empty string test
        //bad input test
    }
    
    int test_count = pass+fail;
    cout << pass << " of " << test_count << " tests passed\n";
    cout.flush();
    
    delete tab;
    return 0;
}
