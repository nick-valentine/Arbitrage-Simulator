CC=g++ -std=c++11 -ggdb
CFLAGS=-c -Iinc
LIBS=-lncurses


all: main

main: game server

playGame: game
	./game

playServer: server
	./server

makeObjFileStructure:
	mkdir obj/GameObjects
	mkdir obj/WorldGen
	mkdir obj/Managers

rmObjFiles:
	rm -rf obj/*

clean: rmObjFiles makeObjFileStructure

rebuild: clean main

server: server.o ConfigLoader.o GameObjects/City.o GameObjects/World.o GameObjects/WorldChunk.o GameObjects/Tile.o ColorPallete.o WorldGen/NoiseFunc.o
	$(CC) \
		obj/server.o \
		obj/GameObjects/City.o \
		obj/GameObjects/World.o \
		obj/GameObjects/WorldChunk.o \
		obj/GameObjects/Tile.o \
		obj/ConfigLoader.o \
		obj/ColorPallete.o \
		obj/WorldGen/NoiseFunc.o \
		-o server $(LIBS)

game: game.o Managers/Game.o ConfigLoader.o Camera.o GameObjects/City.o GameObjects/World.o GameObjects/WorldChunk.o GameObjects/Tile.o ColorPallete.o WorldGen/NoiseFunc.o
	$(CC) \
		obj/game.o \
		obj/Managers/Game.o \
		obj/GameObjects/City.o \
		obj/GameObjects/World.o \
		obj/GameObjects/WorldChunk.o \
		obj/GameObjects/Tile.o \
		obj/ConfigLoader.o \
		obj/Camera.o \
		obj/ColorPallete.o \
		obj/WorldGen/NoiseFunc.o \
		-o game $(LIBS) 

game.o: src/game.cpp
	$(CC) $(CFLAGS) src/game.cpp -o obj/game.o

server.o: src/server.cpp inc/GameObjects/City.hpp inc/GameObjects/WorldChunk.hpp
	$(CC) $(CFLAGS) src/server.cpp -o obj/server.o

Managers/Game.o: src/Managers/Game.cpp inc/Managers/Game.hpp inc/GameObjects/World.hpp 
	$(CC) $(CFLAGS) src/Managers/Game.cpp -o obj/Managers/Game.o

ConfigLoader.o: src/ConfigLoader.cpp inc/ConfigLoader.hpp
	$(CC) $(CFLAGS) src/ConfigLoader.cpp -o obj/ConfigLoader.o

Camera.o: src/Camera.cpp inc/Camera.hpp
	$(CC) $(CFLAGS) src/Camera.cpp -o obj/Camera.o

ColorPallete.o: src/ColorPallete.cpp inc/ColorPallete.hpp
	$(CC) $(CFLAGS) src/ColorPallete.cpp -o obj/ColorPallete.o

GameObjects/City.o: src/GameObjects/City.cpp inc/GameObjects/City.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/City.cpp -o obj/GameObjects/City.o

GameObjects/WorldChunk.o: src/GameObjects/WorldChunk.cpp inc/GameObjects/WorldChunk.hpp inc/GameObjects/AbstractGameObject.hpp inc/GameObjects/City.hpp inc/Globals.hpp inc/ConfigLoader.hpp inc/ColorPallete.hpp
	$(CC) $(CFLAGS) src/GameObjects/WorldChunk.cpp -o obj/GameObjects/WorldChunk.o

GameObjects/World.o: src/GameObjects/World.cpp inc/GameObjects/World.hpp inc/GameObjects/WorldChunk.hpp
	$(CC) $(CFLAGS) src/GameObjects/World.cpp -o obj/GameObjects/World.o

GameObjects/Tile.o: src/GameObjects/Tile.cpp inc/GameObjects/Tile.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/Tile.cpp -o obj/GameObjects/Tile.o

WorldGen/NoiseFunc.o: src/WorldGen/NoiseFunc.cpp inc/WorldGen/NoiseFunc.hpp
	$(CC) $(CFLAGS) src/WorldGen/NoiseFunc.cpp -o obj/WorldGen/NoiseFunc.o

