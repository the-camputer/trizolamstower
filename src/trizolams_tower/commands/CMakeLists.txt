if(NOT TARGET CONAN_PKG::yaml-cpp)
    find_package(CONAN_PKG::yaml-cpp REQUIRED)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_library(
    TrizolamCommandPrcocessors

    OBJECT

    TravelCommand.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Rule.h
    ${PROJECT_SOURCE_DIR}/include/trizolams_tower/managers/SceneManager.h
)

target_link_libraries(
    TrizolamCommandPrcocessors

    PRIVATE

    TrizolamEngine
    CONAN_PKG::yaml-cpp
)