if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()

if (NOT TARGET CONAN_PKG::yaml-cpp)
    find_package(CONAN_PKG::yaml-cpp REQUIRED)
endif()

add_library(
    TrizolamGrammar

    OBJECT

    TrizolamGrammar.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/src/trizolams_tower/player_input/TrizolamGrammar.h
    ${PROJECT_SOURCE_DIR}/src/trizolams_tower/commands/MovementDirections.h
    ${PROJECT_SOURCE_DIR}/src/trizolams_tower/commands/TravelCommand.h
)

target_include_directories(
    TrizolamGrammar

    PRIVATE 

    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(
    TrizolamGrammar

    PRIVATE 
    
    TrizolamEngine
    TrizolamCommandPrcocessors
    CONAN_PKG::spdlog
    CONAN_PKG::yaml-cpp
)