if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
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
target_link_directories(
    EarleyParser
    PRIVATE
    ${CMAKE_SOURCE_DIR}/external/include
)
target_link_libraries(
    EarleyParser
    PRIVATE
    grammar
    spdlog::spdlog
)

add_library(
    ExampleGrammar

    OBJECT

    ExampleGrammar.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/ExampleGrammar.h
)
target_include_directories(ExampleGrammar PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(ExampleGrammar grammar)