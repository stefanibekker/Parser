# Stefani Bekker - cssc0424
# CS530, Spring 2019
# Assignment 3 Parser 
# main.cpp

OBJS = main.o
CC = g++

exp: $(OBJS)
	$(CC) $(OBJS) -g -o exp

main.o: main.cpp Header.h
	$(CC) -c main.cpp

clean:
	rm exp *.o
