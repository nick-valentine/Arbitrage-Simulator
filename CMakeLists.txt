cmake_minimum_required (VERSION 3.0)
project (Arbitrage-Simulator)

include_directories ("${PROJECT_SOURCE_DIR}/inc")

SET (GCC_COMPILE_FLAGS "-std=c++11 -ggdb -I${PROJECT_SOURCE_DIR}/src")
SET (GCC_LINK_FLAGS    "-lncurses -lboost_system -lboost_thread -lpthread")

SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )
SET (CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

set (CURSES_NEED_NCURSES ON)
find_package(Curses)
include_directories(${CURSES_INCLUDE_DIR})

find_package(Boost 1.58.0 COMPONENTS system thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory (src)

add_executable (game ${SOURCES} ./src/game.cpp)
add_executable (server ${SOURCES} ./src/server.cpp)

TARGET_LINK_LIBRARIES (game ${CURSES_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES (server ${CURSES_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

