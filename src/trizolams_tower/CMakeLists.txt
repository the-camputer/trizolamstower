add_subdirectory(player_input)
add_subdirectory(managers)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()

if (NOT TARGET CONAN_PKG::yaml-cpp)
    find_package(CONAN_PKG::yaml-cpp REQUIRED)
endif()

add_executable(
    TrizolamsTower

    TrizolamsTower.cpp

    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/TrizolamGrammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/InputProcessor.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyItem.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/managers/SceneManager.h
    
)

target_link_libraries(
    TrizolamsTower

    PRIVATE
    
    TrizolamEngine
    TrizolamGrammar
    TrizolamManagers
    CONAN_PKG::spdlog
    CONAN_PKG::yaml-cpp
)

file(
    COPY 

    ${PROJECT_SOURCE_DIR}/assets/scenes/Scenes.yml

    DESTINATION

    ${CMAKE_BINARY_DIR}/resources
)