# add_definitions(-g -Wall -std=c++2a)
include_directories(${CMAKE_SOURCE_DIR}/include)

if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()

if(NOT TARGET CONAN_PKG::catch2)
    find_package(CONAN_PKG::catch2 REQUIRED)
endif()

add_executable(
    tests 
    
    test_main.cpp 
    engine/grammar/Rule_test.cpp
    engine/grammar/Grammar_test.cpp
    engine/InputProcessor_test.cpp
    trizolams_tower/player_input/grammar/TrizolamGrammar_test.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Rule.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Grammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Symbol.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/InputProcessor.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
)

target_link_libraries(
    tests

    PRIVATE 

    TrizolamEngine
    TrizolamGrammar
    CONAN_PKG::spdlog
    CONAN_PKG::catch2
)