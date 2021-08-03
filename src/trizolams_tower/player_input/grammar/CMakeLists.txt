if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()
add_library(
    TrizolamGrammar

    OBJECT

    TrizolamGrammar.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
)

target_include_directories(TrizolamGrammar PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TrizolamGrammar EarleyParser grammar CONAN_PKG::spdlog)