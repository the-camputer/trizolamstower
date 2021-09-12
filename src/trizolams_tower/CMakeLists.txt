add_subdirectory(player_input)
add_subdirectory(managers)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()

add_executable(
    TrizolamsTower

    TrizolamsTower.cpp

    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/grammar/TrizolamGrammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/InputProcessor.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyItem.h
)

#TODO Figure out how to copy Scenes.yml to build

target_link_libraries(
    TrizolamsTower

    PRIVATE
    
    TrizolamEngine
    TrizolamGrammar
    CONAN_PKG::spdlog
)