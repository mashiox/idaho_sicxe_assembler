/* Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
   mascxxxx
   Team Idaho
   prog3
   CS530, Spring 2016
*/


#ifndef SIXCE_ASM
#define SIXCE_ASM

#include <string>

using namespace std;

class sicxe_asm {
    private: 
        
    public:
        
        sicxe_asm();
        
        bool is_start( string opcode ){
            return ( opcode.compare("START") == 0 ? true : false );
        }
        
        bool is_end( string opcode ){
            return ( opcode.compare("END") == 0 ? true : false );
        }
        
        bool is_word( string opcode ){
            return ( opcode.compare("WORD") == 0 ? true : false );
        }
        
        bool is_resw( string opcode ){
            return ( opcode.compare("RESW") == 0 ? true : false );
        }
        
        bool is_resb( string opcode ){
            return ( opcode.compare("RESB") == 0 ? true : false );
        }
        
        bool is_byte( string opcode ){
           return ( opcode.compare("BYTE") == 0 ? true : false );
        }
        
        void handle_start( int*, string );
        
        void handle_end( string );
        void handle_end(  );
        
        void handle_word( int, string );
        
        void handle_resw( int, string );
        
        void handle_resb( int, string );
        
        void handle_byte( string, string );
        
        
        
};

#endif