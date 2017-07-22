set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/BufferLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/BufferLogger.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleLogger.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.hpp
    PARENT_SCOPE
)
