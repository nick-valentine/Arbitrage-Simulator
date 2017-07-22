set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/AbstractPass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TypePass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ElevationPass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CityPass.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/AbstractPass.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TypePass.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ElevationPass.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CityPass.hpp
    PARENT_SCOPE
)

