set (SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/LocalWorldInteraction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkedWorldInteraction.cpp
    PARENT_SCOPE
)
set (HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/LocalWorldInteraction.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkedWorldInteraction.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldInteractionInterface.hpp
    PARENT_SCOPE
)

