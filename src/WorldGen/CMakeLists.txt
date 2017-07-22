add_subdirectory (Pass)

set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/NoiseFunc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Generator.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/NoiseFunc.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Generator.hpp
    PARENT_SCOPE
)

