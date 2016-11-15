CC=g++

all: main

main: main.o city.hpp
	$(CC) obj/main.o -o main

main.o: src/main.cpp
	$(CC) -c src/main.cpp -o obj/main.o

city.hpp: entity/city.hxx
	odb -d mysql --generate-query --generate-schema --output-dir odb entity/city.hxx
	
