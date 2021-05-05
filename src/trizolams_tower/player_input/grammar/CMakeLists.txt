if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()
add_library(
    TrizolamGrammar

    OBJECT

    TrizolamGrammar.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
    TrizolamGrammarRules.h
)

target_include_directories(TrizolamGrammar PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TrizolamGrammar EarleyParser grammar spdlog::spdlog)