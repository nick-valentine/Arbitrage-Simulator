CC=g++ -std=c++11
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

server: server.o GameObjects/City.o GameObjects/WorldChunk.o GameObjects/Tile.o
	$(CC) \
		obj/server.o \
		obj/GameObjects/City.o \
		obj/GameObjects/WorldChunk.o \
		obj/GameObjects/Tile.o \
		-o server $(LIBS)

game: game.o GameObjects/City.o GameObjects/WorldChunk.o GameObjects/Tile.o
	$(CC) \
		obj/game.o \
		obj/GameObjects/City.o \
		obj/GameObjects/WorldChunk.o \
		obj/GameObjects/Tile.o \
		-o game $(LIBS) 

game.o: src/game.cpp
	$(CC) $(CFLAGS) src/game.cpp -o obj/game.o

server.o: src/server.cpp
	$(CC) $(CFLAGS) src/server.cpp -o obj/server.o

GameObjects/City.o: src/GameObjects/City.cpp inc/GameObjects/City.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/City.cpp -o obj/GameObjects/City.o

GameObjects/WorldChunk.o: src/GameObjects/WorldChunk.cpp inc/GameObjects/WorldChunk.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/WorldChunk.cpp -o obj/GameObjects/WorldChunk.o

GameObjects/Tile.o: src/GameObjects/Tile.cpp inc/GameObjects/Tile.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/Tile.cpp -o obj/GameObjects/Tile.o
