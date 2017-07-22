add_subdirectory (GameObjects)
add_subdirectory (Helpers)
add_subdirectory (Managers)
add_subdirectory (Networking)
add_subdirectory (Services)
add_subdirectory (Window)
add_subdirectory (WorldGen)

set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ColorPallete.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigLoader.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ColorPallete.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigLoader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Globals.hpp
    PARENT_SCOPE
)

