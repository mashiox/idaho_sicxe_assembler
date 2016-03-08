/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
   mascxxxx
   Team Idaho
   prog2
   CS530, Spring 2016
 */

#include <map>
#include <string>
#include "opcodetab.h"
#include "opcode_error_exception.h"

using namespace std;

const struct opcodetab::instr opcodetab::instrs[] = {
    {"add", {3, "18"}},
    {"addf", {3, "58"}},
    {"addr", {2, "90"}},
    {"and", {3, "40"}},
    {"clear", {2, "B4"}},
    {"comp", {3, "28"}},
    {"compf", {3, "88"}},
    {"compr", {2, "A0"}},
    {"div", {3, "24"}},
    {"divf", {3, "64"}},
    {"divr", {2, "9C"}},
    {"fix", {1, "C4"}},
    {"float", {1, "C0"}},
    {"hio", {1, "F4"}},
    {"j", {3, "3C"}},
    {"jeq", {3, "30"}},
    {"jgt", {3, "34"}},
    {"jlt", {3, "38"}},
    {"jsub", {3, "48"}},
    {"lda", {3, "00"}},
    {"ldb", {3, "68"}},
    {"ldch", {3, "50"}},
    {"ldf", {3, "70"}},
    {"ldl", {3, "08"}},
    {"lds", {3, "6C"}},
    {"ldt", {3, "74"}},
    {"ldx", {3, "04"}},
    {"lps", {3, "D0"}},
    {"mul", {3, "20"}},
    {"mulf", {3, "60"}},
    {"mulr", {2, "98"}},
    {"norm", {1, "C8"}},
    {"or", {3, "44"}},
    {"rd", {3, "D8"}},
    {"rmo", {2, "AC"}},
    {"rsub", {3, "4C"}},
    {"shiftl", {2, "A4"}},
    {"shiftr", {2, "A8"}},
    {"sio", {1, "F0"}},
    {"ssk", {3, "EC"}},
    {"sta", {3, "0C"}},
    {"stb", {3, "78"}},
    {"stch", {3, "54"}},
    {"stf", {3, "80"}},
    {"sti", {3, "D4"}},
    {"stl", {3, "14"}},
    {"sts", {3, "7C"}},
    {"stsw", {3, "E8"}},
    {"stt", {3, "84"}},
    {"stx", {3, "10"}},
    {"sub", {3, "1C"}},
    {"subf", {3, "5C"}},
    {"subr", {2, "94"}},
    {"svc", {2, "B0"}},
    {"td", {3, "E0"}},
    {"tio", {1, "F8"}},
    {"tix", {3, "2C"}},
    {"tixr", {2, "B8"}},
    {"wd", {3, "DC"}}
};

opcodetab::opcodetab(){
    for (unsigned int i = 0; i < sizeof(instrs)/sizeof(instr); ++i) {
        opcodeTab.insert(pair<string, struct instr::details>(instrs[i].menmonic, instrs[i].details));
    }
}

int opcodetab::get_instruction_size(string s){
    
    if(s.size() == 0)
        throw opcode_error_exception("Error: Opcode is empty string");
    else{
        string temp = s;
        if(s[0] == '+')
            s = s.erase(0,1);
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        
        map<string, struct instr::details>::iterator iter = opcodeTab.find(s);
        
        if(iter == opcodeTab.end())
            throw opcode_error_exception("Error: Opcode "+s+" not found");
        
        struct instr::details A = iter->second;
        if(A.format == 3 && temp[0] == '+'){
            return 4;
        }
        else if(A.format != 3 && temp[0] == '+'){
            throw opcode_error_exception("Error: Invalid use of + on Opcode "+s);
        }
        else{
            return A.format;
        }
    }
}

string opcodetab::get_machine_code(string op) {
    bool wasformat4 = false;
    int i = 0;
    
    if (op[0] == '+')	{
        op = op.erase(0,1);
        wasformat4 = true;
    }
    while(op[i])	{
        op[i] = tolower(op[i]);
        i++;
    }
    map<string, struct instr::details>::iterator opct = opcodeTab.find(op);
    
    if(opct == opcodeTab.end())	{
        throw opcode_error_exception("Error: Opcode "+op+" not found");
    }
    else if (opct->second.format != 3 && wasformat4) {
        throw opcode_error_exception("Error: Invalid use of + on Opcode "+op);
    }
    else {
        return opct->second.opcode;
    }
}
