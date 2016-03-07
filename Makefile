# Shad Aziz, Phillip Domann, Melanie Reed, Matt Walther
# mascxxxx
# Team Idaho
# prog1
# CS530, Spring 2016

TORM = parsesicxe parsesicxe.o file_parser.o sicxeoptab sicxeoptab.o opcodetab.o
CC = g++
CCFLAGS = -g -O3 -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings

all: parsesicxe sicxeoptab

parsesicxe: parsesicxe.o file_parser.o
	${CC} ${CCFLAGS} -o parsesicxe parsesicxe.o file_parser.o

parsesicxe.o: parsesicxe.cpp file_parse_exception.h
	${CC} ${CCFLAGS} -c parsesicxe.cpp

file_parser.o: file_parser.cc file_parser.h
	${CC} ${CCFLAGS} -c file_parser.cc

sicxeoptab: sicxeoptab.o opcodetab.o
	${CC} ${CCFLAGS} -o sicxeoptab sicxeoptab.o opcodetab.o

sicxeoptab.o: sicxeoptab.cpp opcode_error_exception.h
	${CC} ${CCFLAGS} -c sicxeoptab.cpp

opcodetab.o: opcodetab.cc opcodetab.h
	${CC} ${CCFLAGS} -c opcodetab.cc

clean:
	rm -f ${TORM}
