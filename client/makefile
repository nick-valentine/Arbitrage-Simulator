CC=g++
LIBS=-lncurses


all: main

main: main.o
	$(CC) obj/main.o -o main $(LIBS) 

main.o: src/main.cpp
	$(CC) -c src/main.cpp -o obj/main.o
