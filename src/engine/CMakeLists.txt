if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()

if(NOT TARGET CONAN_PKG::boost)
    find_package(CONAN_PKG::boost REQUIRED)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(
    TrizolamEngine

    STATIC

    grammar/Grammar.cpp
    grammar/Rule.cpp
    grammar/EarleyParser.cpp
    InputProcessor.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Grammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Rule.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Symbol.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/InputProcessor.h
)

target_link_libraries(
    TrizolamEngine

    PUBLIC

    CONAN_PKG::spdlog
    CONAN_PKG::boost
)
