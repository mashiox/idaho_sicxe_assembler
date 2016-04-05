/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
   mascxxxx
   Team Idaho
   prog2
   CS530, Spring 2016
 */

#include <map>
#include <string>
#include <algorithm>
#include "opcodetab.h"
#include "opcode_error_exception.h"

opcodetab{

<<<<<<< HEAD
    opcodeTab << pair<string, struct opcodes* > ( "ADD"   , new struct opcodes(3,  24 ) );
    opcodeTab << pair<string, struct opcodes* > ( "ADDF"  , new struct opcodes(3,  88 ) );
    opcodeTab << pair<string, struct opcodes* > ( "ADDR"  , new struct opcodes(2  ,  144) );
    opcodeTab << pair<string, struct opcodes* > ( "AND"   , new struct opcodes(3,  64 ) );
    opcodeTab << pair<string, struct opcodes* > ( "CLEAR" , new struct opcodes(2  ,  180) );
    opcodeTab << pair<string, struct opcodes* > ( "COMP"  , new struct opcodes(3,  40 ) );
    opcodeTab << pair<string, struct opcodes* > ( "COMPF" , new struct opcodes(3,  136) );
    opcodeTab << pair<string, struct opcodes* > ( "COMPR" , new struct opcodes(2  ,  160) );
    opcodeTab << pair<string, struct opcodes* > ( "DIV"   , new struct opcodes(3,  36 ) );
    opcodeTab << pair<string, struct opcodes* > ( "DIVF"  , new struct opcodes(3,  100) );
    opcodeTab << pair<string, struct opcodes* > ( "DIVR"  , new struct opcodes(2  ,  156) );
    opcodeTab << pair<string, struct opcodes* > ( "FIX"   , new struct opcodes(1  ,  196) );
    opcodeTab << pair<string, struct opcodes* > ( "FLOAT" , new struct opcodes(1  ,  192) );
    opcodeTab << pair<string, struct opcodes* > ( "HIO"   , new struct opcodes(1  ,  224) );
    opcodeTab << pair<string, struct opcodes* > ( "J"     , new struct opcodes(3,  60 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JEQ"   , new struct opcodes(3,  48 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JGT"   , new struct opcodes(3,  52 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JLT"   , new struct opcodes(3,  56 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JSUB"  , new struct opcodes(3,  72 ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDA"   , new struct opcodes(3,  0  ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDB"   , new struct opcodes(3,  104) );
    opcodeTab << pair<string, struct opcodes* > ( "LDCH"  , new struct opcodes(3,  80 ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDF"   , new struct opcodes(3,  112) );
    opcodeTab << pair<string, struct opcodes* > ( "LDL"   , new struct opcodes(3,  8  ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDX"   , new struct opcodes(3,  4  ) );
    opcodeTab << pair<string, struct opcodes* > ( "LPS"   , new struct opcodes(3,  208) );
    opcodeTab << pair<string, struct opcodes* > ( "MUL"   , new struct opcodes(3,  32 ) );
    opcodeTab << pair<string, struct opcodes* > ( "MULF"  , new struct opcodes(3,  96 ) );
    opcodeTab << pair<string, struct opcodes* > ( "MULR"  , new struct opcodes(2  ,  152) );
    opcodeTab << pair<string, struct opcodes* > ( "NORM"  , new struct opcodes(1  ,  200) );
    opcodeTab << pair<string, struct opcodes* > ( "OR"    , new struct opcodes(3,  68 ) );
    opcodeTab << pair<string, struct opcodes* > ( "RD"    , new struct opcodes(3,  216) );
    opcodeTab << pair<string, struct opcodes* > ( "RMO"   , new struct opcodes(2  ,  172) );
    opcodeTab << pair<string, struct opcodes* > ( "RSUB"  , new struct opcodes(3,  76 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SHIFTL", new struct opcodes(2  ,  164) );
    opcodeTab << pair<string, struct opcodes* > ( "SHIFTR", new struct opcodes(2  ,  168) );
    opcodeTab << pair<string, struct opcodes* > ( "SIO"   , new struct opcodes(1  ,  240) );
    opcodeTab << pair<string, struct opcodes* > ( "SSK"   , new struct opcodes(3,  236) );
    opcodeTab << pair<string, struct opcodes* > ( "STA"   , new struct opcodes(3,  12 ) );
    opcodeTab << pair<string, struct opcodes* > ( "STB"   , new struct opcodes(3,  120) );
    opcodeTab << pair<string, struct opcodes* > ( "STCH"  , new struct opcodes(3,  84 ) );
    opcodeTab << pair<string, struct opcodes* > ( "STF"   , new struct opcodes(3,  128) );
    opcodeTab << pair<string, struct opcodes* > ( "STI"   , new struct opcodes(3,  212) );
    opcodeTab << pair<string, struct opcodes* > ( "STL"   , new struct opcodes(3,  20)  );
    opcodeTab << pair<string, struct opcodes* > ( "STS"   , new struct opcodes(3,  124) );
    opcodeTab << pair<string, struct opcodes* > ( "STSW"  , new struct opcodes(3,  232) );
    opcodeTab << pair<string, struct opcodes* > ( "STT"   , new struct opcodes(3,  132) );
    opcodeTab << pair<string, struct opcodes* > ( "STX"   , new struct opcodes(3,  16 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SUB"   , new struct opcodes(3,  28 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SUBF"  , new struct opcodes(3,  92 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SUBR"  , new struct opcodes(2  ,  148) );
    opcodeTab << pair<string, struct opcodes* > ( "SVC"   , new struct opcodes(2  ,  176) );
    opcodeTab << pair<string, struct opcodes* > ( "TD"    , new struct opcodes(3,  224) );
    opcodeTab << pair<string, struct opcodes* > ( "TIO"   , new struct opcodes(1  ,  248) );
    opcodeTab << pair<string, struct opcodes* > ( "TIX"   , new struct opcodes(3,  44 ) );
    opcodeTab << pair<string, struct opcodes* > ( "TIXR"  , new struct opcodes(2  ,  184) );
    opcodeTab << pair<string, struct opcodes* > ( "WD"    , new struct opcodes(3,  220) );
=======
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
>>>>>>> b10a4ebf6cffc3c0db9104d9ec71024b67891289
}



int get_instruction_size(string s){

    if(s.size() == 0)
        throw opcode_error_exception("Error: Opcode is empty string");
    else{
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        if(opmap.find(s) == opmap.end())
            throw opcode_error_exception("Error: Opcode not found");
        struct opcodes* A = opmap.find(s)->second;
        if(A.format() == 3 && s[0] == '+'){
            return 4;
        }
        else if(A.format() != 3 && s[0] == '+'){
            throw opcode_error_exception("Error: Invalid use of + on Opcode");
        }
        else{
            return A.format();
        }
}
