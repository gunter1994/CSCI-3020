.PHONY: all clean

out : lab3.c
	clang -Wall -std=c99 -lpthread lab3.c -o lab3

run : lab3 valid_puzzle.txt
	./lab3 valid_puzzle.txt

all : 
	out run clean

clean :
	rm lab3
 
