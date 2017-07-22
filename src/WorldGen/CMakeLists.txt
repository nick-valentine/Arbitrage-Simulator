add_subdirectory (Pass)

set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/NoiseFunc.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/NoiseFunc.hpp
    PARENT_SCOPE
)

