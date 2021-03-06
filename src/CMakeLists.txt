# add_definitions(-g -Wall -std=c++2a)
add_subdirectory(engine/grammar)
add_subdirectory(trizolams_tower/player_input/grammar)
# add_subdirectory(trizolams_tower/player_input/grammar)

include_directories(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
link_directories(${CMAKE_SOURCE_DIR}/lib)

FIND_PACKAGE(Boost)
# FIND_PACKAGE(spdlog)

add_executable(
    TrizolamsTower

    trizolams_tower/TrizolamsTower.cpp

    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyItem.h
)
target_link_libraries(TrizolamsTower EarleyParser grammar TrizolamGrammar)
target_link_libraries(TrizolamsTower spdlog ${Boost_LIBRARIES})

# add_executable(
#     testing_trizolam_grammar

#     trizolams_tower/player_input/grammar/TrizolamGrammar.cpp

#     ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Grammar.h
#     ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
#     trizolams_tower/player_input/grammar/TrizolamGrammarRules.h
#     ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
# )
# target_link_libraries(testing_trizolam_grammar grammar EarleyParser)