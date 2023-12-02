CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: parse

parse: charcode.o error.o    main.o     parser.o   reader.o   scanner.o  token.o
	${CC} charcode.o error.o    main.o     parser.o   reader.o   scanner.o  token.o -o parse

charcode.o:
	${CC} ${CFLAGS} charcode.c
error.o:
	${CC} ${CFLAGS} error.c
main.o:
	${CC} ${CFLAGS} main.c
parser.o:
	${CC} ${CFLAGS} parser.c
reader.o:
	${CC} ${CFLAGS} reader.c
scanner.o:
	${CC} ${CFLAGS} scanner.c
token.o:
	${CC} ${CFLAGS} token.c

clean:
	rm -f *.o *~ parse
