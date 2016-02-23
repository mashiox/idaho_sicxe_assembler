# Phillip Domann, Shad, Melanie, Matt
# mascxxxx
# Team Idaho
# prog1
# CS530, Spring 2016

TORM = parsesicxe parsesicxe.o file_parser.o file_parse_exception.o
CC = g++
CCFLAGS = -g -O3 -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings

parsesicxe: parsesicxe.o file_parser.o file_parse_exception.o
	${CC} ${CCFLAGS} -o parsesicxe parsesicxe.o file_parser.o file_parse_exception.o

parsesicxe.o: parsesicxe.cpp
	${CC} ${CCFLAGS} -c parsesicxe.cpp

file_parser.o: file_parser.cc file_parser.h
	${CC} ${CCFLAGS} -c file_parser.cc

file_parse_exception.o: file_parse_exception.cc file_parse_exception.h
	${CC} ${CCFLAGS} -c file_parse_exception.cc

clean:
	rm -f ${TORM}
