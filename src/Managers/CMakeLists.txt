add_subdirectory (GameState)

set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ServerSession.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ServerSession.hpp
    PARENT_SCOPE
)

