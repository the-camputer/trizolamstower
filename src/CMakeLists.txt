# add_definitions(-g -Wall -std=c++2a)
add_subdirectory(engine)
add_subdirectory(trizolams_tower/player_input)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()

add_executable(
    TrizolamsTower

    trizolams_tower/TrizolamsTower.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/InputProcessor.h
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
    CONAN_PKG::spdlog
)
