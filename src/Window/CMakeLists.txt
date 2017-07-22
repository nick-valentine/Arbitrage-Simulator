set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CursesWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameWindow.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleWindow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CursesWindow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameWindow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.hpp
    PARENT_SCOPE
)

