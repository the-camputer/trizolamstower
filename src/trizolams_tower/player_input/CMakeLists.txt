add_subdirectory(grammar)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(commands)

add_library(
    InputProcessor

    OBJECT

    InputProcessor.cpp

    InputProcessor.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
)
target_link_libraries(InputProcessor PRIVATE grammar EarleyParser TrizolamGrammar)
target_link_libraries(InputProcessor)