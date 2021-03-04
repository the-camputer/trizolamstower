# add_definitions(-g -Wall -std=c++2a)
add_subdirectory(engine/grammar)
add_subdirectory(trizolams_tower/player_input/grammar)
# add_subdirectory(trizolams_tower/player_input/grammar)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(
    parsing_example

    parsing_example.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/ExampleGrammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyItem.h
)
target_link_libraries(parsing_example EarleyParser ExampleGrammar grammar)
target_link_libraries(parsing_example spdlog)

# add_executable(
#     testing_trizolam_grammar

#     trizolams_tower/player_input/grammar/TrizolamGrammar.cpp

#     ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Grammar.h
#     ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
#     trizolams_tower/player_input/grammar/TrizolamGrammarRules.h
#     ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
# )
# target_link_libraries(testing_trizolam_grammar grammar EarleyParser)