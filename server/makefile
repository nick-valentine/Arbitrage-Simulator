CC=g++
CFLAGS= -c -Iinc

all: main

main: main.o City.o
	$(CC) obj/main.o obj/City.o -o main

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o

City.o: src/GameObjects/City.cpp inc/GameObjects/City.hpp
	$(CC) $(CFLAGS) src/GameObjects/City.cpp -o obj/City.o
