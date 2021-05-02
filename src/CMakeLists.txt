# add_definitions(-g -Wall -std=c++2a)
add_subdirectory(engine/grammar)
add_subdirectory(trizolams_tower/player_input)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/external/lib
)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

add_executable(
    TrizolamsTower

    trizolams_tower/TrizolamsTower.cpp

    trizolams_tower/player_input/InputProcessor.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyItem.h
)
target_link_libraries(
    TrizolamsTower
    PRIVATE
    EarleyParser
    grammar
    TrizolamGrammar
    InputProcessor
    spdlog::spdlog
)

# add_executable(
#     testing_trizolam_grammar

#     trizolams_tower/player_input/grammar/TrizolamGrammar.cpp

#     ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Grammar.h
#     ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
#     trizolams_tower/player_input/grammar/TrizolamGrammarRules.h
#     ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
# )
# target_link_libraries(testing_trizolam_grammar grammar EarleyParser)