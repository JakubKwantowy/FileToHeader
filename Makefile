all: filetoheader

filetoheader.o: filetoheader.c
	gcc -Wall -o $@ -c $^

filetoheader: filetoheader.o
	gcc -Wall -o $@ $^
