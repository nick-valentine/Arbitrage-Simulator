CC=g++
CFLAGS=-c -Iinc
LIBS=-lncurses


all: main

main: game server

makeObjFileStructure:
	mkdir obj/GameObjects

rmObjFiles:
	rm -rf obj/*

clean: rmObjFiles makeObjFileStructure

rebuild: clean main

server: server.o GameObjects/City.o
	$(CC) obj/server.o -o server $(LIBS)

game: game.o GameObjects/City.o
	$(CC) obj/game.o -o game $(LIBS) 

game.o: src/game.cpp
	$(CC) $(CFLAGS) src/game.cpp -o obj/game.o

server.o: src/server.cpp
	$(CC) $(CFLAGS) src/server.cpp -o obj/server.o

GameObjects/City.o: src/GameObjects/City.cpp inc/GameObjects/City.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/City.cpp -o obj/GameObjects/City.o
