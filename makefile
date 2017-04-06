CC=g++ -std=c++11 -ggdb
CFLAGS=-c -Iinc
LIBS=-lncurses -lboost_system -lboost_thread -lpthread


all: main

main: game server

playGame: game
	./game

playServer: server
	./server
	
docs: all
	doxygen doxyfile

makeObjFileStructure:
	mkdir obj/GameObjects
	mkdir obj/WorldGen
	mkdir obj/Window
	mkdir obj/Managers
	mkdir obj/Helpers
	mkdir obj/Networking
	mkdir obj/Services
	mkdir obj/Services/WorldInteraction
	mkdir obj/Services/WindowLayout
	mkdir obj/Services/Logger

rmObjFiles:
	rm -rf obj/*

clean: rmObjFiles makeObjFileStructure

rebuild: clean main

server: obj/server.o obj/Managers/Server.o obj/Managers/ServerSession.o obj/ConfigLoader.o obj/Window/GameWindow.o obj/Camera.o obj/GameObjects/City.o obj/GameObjects/World.o obj/GameObjects/WorldChunk.o obj/GameObjects/Tile.o obj/GameObjects/Player.o obj/ColorPallete.o obj/WorldGen/NoiseFunc.o obj/Helpers/String.o obj/Networking/Connection.o obj/Services/WorldInteraction/LocalWorldInteraction.o obj/Window/CursesWindow.o obj/Services/Logger/Logger.o obj/Services/Logger/BufferLogger.o obj/Services/Logger/ConsoleLogger.o
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
		obj/Managers/ServerSession.o \
		obj/Window/CursesWindow.o \
		obj/Window/GameWindow.o \
		obj/WorldGen/NoiseFunc.o \
		obj/server.o \
		obj/Helpers/String.o \
		obj/Networking/Connection.o \
		obj/Services/WorldInteraction/LocalWorldInteraction.o \
		obj/Services/WindowLayout/GameWindowLayout.o \
		obj/Services/Logger/Logger.o \
		obj/Services/Logger/BufferLogger.o \
		obj/Services/Logger/ConsoleLogger.o \
		-o server $(LIBS)

game: obj/game.o obj/Managers/Game.o obj/ConfigLoader.o obj/Camera.o obj/Window/GameWindow.o obj/GameObjects/City.o obj/GameObjects/World.o obj/GameObjects/WorldChunk.o obj/GameObjects/Tile.o obj/GameObjects/Player.o obj/ColorPallete.o obj/WorldGen/NoiseFunc.o obj/Helpers/String.o obj/Networking/Connection.o obj/Services/WorldInteraction/LocalWorldInteraction.o obj/Services/WorldInteraction/NetworkedWorldInteraction.o obj/Window/CursesWindow.o obj/Services/WindowLayout/GameWindowLayout.o obj/Services/Logger/Logger.o obj/Services/Logger/BufferLogger.o obj/Services/Logger/ConsoleLogger.o
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
		obj/Window/GameWindow.o \
		obj/Window/CursesWindow.o \
		obj/WorldGen/NoiseFunc.o \
		obj/game.o \
		obj/Helpers/String.o \
		obj/Networking/Connection.o \
		obj/Services/WorldInteraction/LocalWorldInteraction.o \
		obj/Services/WorldInteraction/NetworkedWorldInteraction.o \
		obj/Services/WindowLayout/GameWindowLayout.o \
		obj/Services/Logger/Logger.o \
		obj/Services/Logger/BufferLogger.o \
		-o game $(LIBS) 

obj/game.o: src/game.cpp
	$(CC) $(CFLAGS) src/game.cpp -o obj/game.o

obj/server.o: src/server.cpp inc/GameObjects/City.hpp inc/GameObjects/WorldChunk.hpp
	$(CC) $(CFLAGS) src/server.cpp -o obj/server.o

obj/Managers/Game.o: src/Managers/Game.cpp inc/Managers/Game.hpp inc/GameObjects/World.hpp inc/Networking/Connection.hpp
	$(CC) $(CFLAGS) src/Managers/Game.cpp -o obj/Managers/Game.o

obj/Managers/Server.o: src/Managers/Server.cpp inc/Managers/Server.hpp inc/Managers/ServerSession.hpp
	$(CC) $(CFLAGS) src/Managers/Server.cpp -o obj/Managers/Server.o

obj/Managers/ServerSession.o: src/Managers/ServerSession.cpp inc/Managers/ServerSession.hpp
	$(CC) $(CFLAGS) src/Managers/ServerSession.cpp -o obj/Managers/ServerSession.o

obj/ConfigLoader.o: src/ConfigLoader.cpp inc/ConfigLoader.hpp
	$(CC) $(CFLAGS) src/ConfigLoader.cpp -o obj/ConfigLoader.o

obj/Camera.o: src/Camera.cpp inc/Camera.hpp
	$(CC) $(CFLAGS) src/Camera.cpp -o obj/Camera.o

obj/Window/GameWindow.o: src/Window/GameWindow.cpp inc/Window/GameWindow.hpp inc/Window/Window.hpp
	$(CC) $(CFLAGS) src/Window/GameWindow.cpp -o obj/Window/GameWindow.o

obj/ColorPallete.o: src/ColorPallete.cpp inc/ColorPallete.hpp
	$(CC) $(CFLAGS) src/ColorPallete.cpp -o obj/ColorPallete.o

obj/GameObjects/City.o: src/GameObjects/City.cpp inc/GameObjects/City.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/City.cpp -o obj/GameObjects/City.o

obj/GameObjects/WorldChunk.o: src/GameObjects/WorldChunk.cpp inc/GameObjects/WorldChunk.hpp inc/GameObjects/AbstractGameObject.hpp inc/GameObjects/City.hpp inc/Globals.hpp inc/ConfigLoader.hpp inc/ColorPallete.hpp
	$(CC) $(CFLAGS) src/GameObjects/WorldChunk.cpp -o obj/GameObjects/WorldChunk.o

obj/GameObjects/World.o: src/GameObjects/World.cpp inc/GameObjects/World.hpp inc/GameObjects/WorldChunk.hpp inc/GameObjects/Player.hpp
	$(CC) $(CFLAGS) src/GameObjects/World.cpp -o obj/GameObjects/World.o

obj/GameObjects/Tile.o: src/GameObjects/Tile.cpp inc/GameObjects/Tile.hpp inc/GameObjects/AbstractGameObject.hpp inc/Globals.hpp
	$(CC) $(CFLAGS) src/GameObjects/Tile.cpp -o obj/GameObjects/Tile.o

obj/GameObjects/Player.o: src/GameObjects/Player.cpp inc/GameObjects/Player.hpp
	$(CC) $(CFLAGS) src/GameObjects/Player.cpp -o obj/GameObjects/Player.o

obj/WorldGen/NoiseFunc.o: src/WorldGen/NoiseFunc.cpp inc/WorldGen/NoiseFunc.hpp
	$(CC) $(CFLAGS) src/WorldGen/NoiseFunc.cpp -o obj/WorldGen/NoiseFunc.o

obj/Helpers/String.o: src/Helpers/String.cpp inc/Helpers/String.hpp
	$(CC) $(CFLAGS) src/Helpers/String.cpp -o obj/Helpers/String.o

obj/Networking/Connection.o: src/Networking/Connection.cpp inc/Networking/Connection.hpp
	$(CC) $(CFLAGS) src/Networking/Connection.cpp -o obj/Networking/Connection.o

obj/Services/WorldInteraction/LocalWorldInteraction.o: src/Services/WorldInteraction/LocalWorldInteraction.cpp inc/Services/WorldInteraction/LocalWorldInteraction.hpp inc/Services/WorldInteraction/WorldInteractionInterface.hpp
	$(CC) $(CFLAGS) src/Services/WorldInteraction/LocalWorldInteraction.cpp -o obj/Services/WorldInteraction/LocalWorldInteraction.o

obj/Services/WorldInteraction/NetworkedWorldInteraction.o: src/Services/WorldInteraction/NetworkedWorldInteraction.cpp inc/Services/WorldInteraction/NetworkedWorldInteraction.hpp inc/Services/WorldInteraction/WorldInteractionInterface.hpp
	$(CC) $(CFLAGS) src/Services/WorldInteraction/NetworkedWorldInteraction.cpp -o obj/Services/WorldInteraction/NetworkedWorldInteraction.o

obj/Window/CursesWindow.o: src/Window/CursesWindow.cpp inc/Window/CursesWindow.hpp
	$(CC) $(CFLAGS) src/Window/CursesWindow.cpp -o obj/Window/CursesWindow.o

obj/Services/WindowLayout/GameWindowLayout.o: src/Services/WindowLayout/GameWindowLayout.cpp inc/Services/WindowLayout/GameWindowLayout.hpp inc/Window/Window.hpp
	$(CC) $(CFLAGS) src/Services/WindowLayout/GameWindowLayout.cpp -o obj/Services/WindowLayout/GameWindowLayout.o

obj/Services/Logger/Logger.o: src/Services/Logger/Logger.cpp inc/Services/Logger/Logger.hpp
	$(CC) $(CFLAGS) src/Services/Logger/Logger.cpp -o obj/Services/Logger/Logger.o

obj/Services/Logger/BufferLogger.o: src/Services/Logger/BufferLogger.cpp inc/Services/Logger/BufferLogger.hpp inc/Services/Logger/Logger.hpp
	$(CC) $(CFLAGS) src/Services/Logger/BufferLogger.cpp -o obj/Services/Logger/BufferLogger.o

obj/Services/Logger/ConsoleLogger.o: src/Services/Logger/ConsoleLogger.cpp inc/Services/Logger/ConsoleLogger.hpp inc/Services/Logger/Logger.hpp
	$(CC) $(CFLAGS) src/Services/Logger/ConsoleLogger.cpp -o obj/Services/Logger/ConsoleLogger.o

