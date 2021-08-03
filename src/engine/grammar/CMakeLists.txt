if(NOT TARGET CONAN_PKG::spdlog)
    # Stand-alone build
    find_package(CONAN_PKG::spdlog REQUIRED)
endif()

add_library(
    grammar 
    
    STATIC
    
    Grammar.cpp
    Rule.cpp
    
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Grammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Rule.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Symbol.h
)

target_include_directories(grammar PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(grammar PUBLIC CONAN_PKG::spdlog)

add_library(
    EarleyParser

    OBJECT

    EarleyParser.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyItem.h
)
target_include_directories(
    EarleyParser
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    EarleyParser
    PRIVATE
    grammar
    CONAN_PKG::spdlog
)