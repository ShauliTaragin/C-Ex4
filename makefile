
CC = gcc
Flags = -Wall -g 

all: graph
 
graph : main.o algo.o
	$(CC) $(Flags) main.o algo.o -o graph

algo.o : algo.c Graph.h
	$(CC) -c algo.c

main.o : main.c Graph.h
	$(CC) -c main.c	

.PHONY:clean all

clean:
	rm -f *.o graph