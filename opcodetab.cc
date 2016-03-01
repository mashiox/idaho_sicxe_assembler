// Implementation of opcodetab.h
#include <map>
#include <string>
#include <cstdlib>
#include <iostream>

#include "opcodetab.h"

using namespace std;

opcodetab::opcodetab(){
    opcodeTab << pair<string, struct opcodes* > ( "ADD"   , new struct opcodes("3/4",  24 ) );
    opcodeTab << pair<string, struct opcodes* > ( "ADDF"  , new struct opcodes("3/4",  88 ) );
    opcodeTab << pair<string, struct opcodes* > ( "ADDR"  , new struct opcodes("2"  ,  144) );
    opcodeTab << pair<string, struct opcodes* > ( "AND"   , new struct opcodes("3/4",  64 ) );
    opcodeTab << pair<string, struct opcodes* > ( "CLEAR" , new struct opcodes("2"  ,  180) );
    opcodeTab << pair<string, struct opcodes* > ( "COMP"  , new struct opcodes("3/4",  40 ) );
    opcodeTab << pair<string, struct opcodes* > ( "COMPF" , new struct opcodes("3/4",  136) );
    opcodeTab << pair<string, struct opcodes* > ( "COMPR" , new struct opcodes("2"  ,  160) );
    opcodeTab << pair<string, struct opcodes* > ( "DIV"   , new struct opcodes("3/4",  36 ) );
    opcodeTab << pair<string, struct opcodes* > ( "DIVF"  , new struct opcodes("3/4",  100) );
    opcodeTab << pair<string, struct opcodes* > ( "DIVR"  , new struct opcodes("2"  ,  156) );
    opcodeTab << pair<string, struct opcodes* > ( "FIX"   , new struct opcodes("1"  ,  196) );
    opcodeTab << pair<string, struct opcodes* > ( "FLOAT" , new struct opcodes("1"  ,  192) );
    opcodeTab << pair<string, struct opcodes* > ( "HIO"   , new struct opcodes("1"  ,  224) );
    opcodeTab << pair<string, struct opcodes* > ( "J"     , new struct opcodes("3/4",  60 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JEQ"   , new struct opcodes("3/4",  48 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JGT"   , new struct opcodes("3/4",  52 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JLT"   , new struct opcodes("3/4",  56 ) );
    opcodeTab << pair<string, struct opcodes* > ( "JSUB"  , new struct opcodes("3/4",  72 ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDA"   , new struct opcodes("3/4",  0  ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDB"   , new struct opcodes("3/4",  104) );
    opcodeTab << pair<string, struct opcodes* > ( "LDCH"  , new struct opcodes("3/4",  80 ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDF"   , new struct opcodes("3/4",  112) );
    opcodeTab << pair<string, struct opcodes* > ( "LDL"   , new struct opcodes("3/4",  8  ) );
    opcodeTab << pair<string, struct opcodes* > ( "LDX"   , new struct opcodes("3/4",  4  ) );
    opcodeTab << pair<string, struct opcodes* > ( "LPS"   , new struct opcodes("3/4",  208) );
    opcodeTab << pair<string, struct opcodes* > ( "MUL"   , new struct opcodes("3/4",  32 ) );
    opcodeTab << pair<string, struct opcodes* > ( "MULF"  , new struct opcodes("3/4",  96 ) );
    opcodeTab << pair<string, struct opcodes* > ( "MULR"  , new struct opcodes("2"  ,  152) );
    opcodeTab << pair<string, struct opcodes* > ( "NORM"  , new struct opcodes("1"  ,  200) );
    opcodeTab << pair<string, struct opcodes* > ( "OR"    , new struct opcodes("3/4",  68 ) );
    opcodeTab << pair<string, struct opcodes* > ( "RD"    , new struct opcodes("3/4",  216) );
    opcodeTab << pair<string, struct opcodes* > ( "RMO"   , new struct opcodes("2"  ,  172) );
    opcodeTab << pair<string, struct opcodes* > ( "RSUB"  , new struct opcodes("3/4",  76 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SHIFTL", new struct opcodes("2"  ,  164) );
    opcodeTab << pair<string, struct opcodes* > ( "SHIFTR", new struct opcodes("2"  ,  168) );
    opcodeTab << pair<string, struct opcodes* > ( "SIO"   , new struct opcodes("1"  ,  240) );
    opcodeTab << pair<string, struct opcodes* > ( "SSK"   , new struct opcodes("3/4",  236) );
    opcodeTab << pair<string, struct opcodes* > ( "STA"   , new struct opcodes("3/4",  12 ) );
    opcodeTab << pair<string, struct opcodes* > ( "STB"   , new struct opcodes("3/4",  120) );
    opcodeTab << pair<string, struct opcodes* > ( "STCH"  , new struct opcodes("3/4",  84 ) );
    opcodeTab << pair<string, struct opcodes* > ( "STF"   , new struct opcodes("3/4",  128) );
    opcodeTab << pair<string, struct opcodes* > ( "STI"   , new struct opcodes("3/4",  212) );
    opcodeTab << pair<string, struct opcodes* > ( "STL"   , new struct opcodes("3/4",  20)  );
    opcodeTab << pair<string, struct opcodes* > ( "STS"   , new struct opcodes("3/4",  124) );
    opcodeTab << pair<string, struct opcodes* > ( "STSW"  , new struct opcodes("3/4",  232) );
    opcodeTab << pair<string, struct opcodes* > ( "STT"   , new struct opcodes("3/4",  132) );
    opcodeTab << pair<string, struct opcodes* > ( "STX"   , new struct opcodes("3/4",  16 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SUB"   , new struct opcodes("3/4",  28 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SUBF"  , new struct opcodes("3/4",  92 ) );
    opcodeTab << pair<string, struct opcodes* > ( "SUBR"  , new struct opcodes("2"  ,  148) );
    opcodeTab << pair<string, struct opcodes* > ( "SVC"   , new struct opcodes("2"  ,  176) );
    opcodeTab << pair<string, struct opcodes* > ( "TD"    , new struct opcodes("3/4",  224) );
    opcodeTab << pair<string, struct opcodes* > ( "TIO"   , new struct opcodes("1"  ,  248) );
    opcodeTab << pair<string, struct opcodes* > ( "TIX"   , new struct opcodes("3/4",  44 ) );
    opcodeTab << pair<string, struct opcodes* > ( "TIXR"  , new struct opcodes("2"  ,  184) );
    opcodeTab << pair<string, struct opcodes* > ( "WD"    , new struct opcodes("3/4",  220) );
}