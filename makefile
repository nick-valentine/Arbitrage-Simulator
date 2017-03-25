CC=g++ -std=c++11 -ggdb
CFLAGS=-c -Iinc
LIBS=-lncurses -lboost_system -lboost_thread -lpthread

docs:
	doxygen doxyfile

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
	mkdir obj/Helpers
	mkdir obj/Networking

rmObjFiles:
	rm -rf obj/*

clean: rmObjFiles makeObjFileStructure

rebuild: clean main

server: server.o Managers/Server.o ConfigLoader.o Screen.o Camera.o GameObjects/City.o GameObjects/World.o GameObjects/WorldChunk.o GameObjects/Tile.o GameObjects/Player.o ColorPallete.o WorldGen/NoiseFunc.o Helpers/String.o Networking/Connection.o
	$(CC) \
		obj/Camera.o \
		obj/ColorPallete.o \
		obj/ConfigLoader.o \
		obj/GameObjects/Player.o \
		obj/GameObjects/City.o \
		obj/GameObjects/Tile.o \
		obj/GameObjects/World.o \
		obj/GameObjects/WorldChunk.o \
		obj/Managers/Server.o \
		obj/Screen.o \
		obj/WorldGen/NoiseFunc.o \
		obj/server.o \
		obj/Helpers/String.o \
		obj/Networking/Connection.o \
		-o server $(LIBS)

game: game.o Managers/Game.o ConfigLoader.o Camera.o Screen.o GameObjects/City.o GameObjects/World.o GameObjects/WorldChunk.o GameObjects/Tile.o GameObjects/Player.o ColorPallete.o WorldGen/NoiseFunc.o Helpers/String.o Networking/Connection.o
	$(CC) \
		obj/Camera.o \
		obj/ColorPallete.o \
		obj/ConfigLoader.o \
		obj/GameObjects/Player.o \
		obj/GameObjects/City.o \
		obj/GameObjects/Tile.o \
		obj/GameObjects/World.o \
		obj/GameObjects/WorldChunk.o \
		obj/Managers/Game.o \
		obj/Screen.o \
		obj/WorldGen/NoiseFunc.o \
		obj/game.o \
		obj/Helpers/String.o \
		obj/Networking/Connection.o \
		-o game $(LIBS) 

game.o: src/game.cpp
	$(CC) $(CFLAGS) src/game.cpp -o obj/game.o

server.o: src/server.cpp inc/GameObjects/City.hpp inc/GameObjects/WorldChunk.hpp
	$(CC) $(CFLAGS) src/server.cpp -o obj/server.o

Managers/Game.o: src/Managers/Game.cpp inc/Managers/Game.hpp inc/GameObjects/World.hpp inc/Networking/Connection.hpp
	$(CC) $(CFLAGS) src/Managers/Game.cpp -o obj/Managers/Game.o

Managers/Server.o: src/Managers/Server.cpp inc/Managers/Server.hpp
	$(CC) $(CFLAGS) src/Managers/Server.cpp -o obj/Managers/Server.o

ConfigLoader.o: src/ConfigLoader.cpp inc/ConfigLoader.hpp
	$(CC) $(CFLAGS) src/ConfigLoader.cpp -o obj/ConfigLoader.o

Camera.o: src/Camera.cpp inc/Camera.hpp
	$(CC) $(CFLAGS) src/Camera.cpp -o obj/Camera.o

Screen.o: src/Screen.cpp inc/Screen.hpp
	$(CC) $(CFLAGS) src/Screen.cpp -o obj/Screen.o

ColorPallete.o: src/ColorPallete.cpp inc/ColorPallete.hpp
	$(CC) $(CFLAGS) src/ColorPallete.cpp -o obj/ColorPallete.o

GameObjects/City.o: src/GameObjects/City.cpp inc/GameObjects/City.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/City.cpp -o obj/GameObjects/City.o

GameObjects/WorldChunk.o: src/GameObjects/WorldChunk.cpp inc/GameObjects/WorldChunk.hpp inc/GameObjects/AbstractGameObject.hpp inc/GameObjects/City.hpp inc/Globals.hpp inc/ConfigLoader.hpp inc/ColorPallete.hpp
	$(CC) $(CFLAGS) src/GameObjects/WorldChunk.cpp -o obj/GameObjects/WorldChunk.o

GameObjects/World.o: src/GameObjects/World.cpp inc/GameObjects/World.hpp inc/GameObjects/WorldChunk.hpp inc/GameObjects/Player.hpp
	$(CC) $(CFLAGS) src/GameObjects/World.cpp -o obj/GameObjects/World.o

GameObjects/Tile.o: src/GameObjects/Tile.cpp inc/GameObjects/Tile.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/Tile.cpp -o obj/GameObjects/Tile.o

GameObjects/Player.o: src/GameObjects/Player.cpp inc/GameObjects/Player.hpp
	$(CC) $(CFLAGS) src/GameObjects/Player.cpp -o obj/GameObjects/Player.o

WorldGen/NoiseFunc.o: src/WorldGen/NoiseFunc.cpp inc/WorldGen/NoiseFunc.hpp
	$(CC) $(CFLAGS) src/WorldGen/NoiseFunc.cpp -o obj/WorldGen/NoiseFunc.o

Helpers/String.o: src/Helpers/String.cpp inc/Helpers/String.hpp
	$(CC) $(CFLAGS) src/Helpers/String.cpp -o obj/Helpers/String.o

Networking/Connection.o: src/Networking/Connection.cpp inc/Networking/Connection.hpp
	$(CC) $(CFLAGS) src/Networking/Connection.cpp -o obj/Networking/Connection.o
