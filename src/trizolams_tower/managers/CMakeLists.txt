if(NOT TARGET CONAN_PKG::yaml-cpp)
    find_package(CONAN_PKG::yaml-cpp REQUIRED)
endif()

add_library(
    TrizolamManagers

    OBJECT

    SceneManager.cpp
    GameManager.cpp

    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/player_input/commands/MovementDirections.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/managers/SceneManager.h
    ${PROJECT_SOURCE_DIR}/src/trizolams_tower/managers/GameManager.h
)

target_include_directories(
    TrizolamManagers

    PRIVATE

    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    TrizolamManagers

    PRIVATE

    CONAN_PKG::yaml-cpp
)