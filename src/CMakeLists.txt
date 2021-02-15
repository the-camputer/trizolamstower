# add_definitions(-g -Wall -std=c++2a)
add_subdirectory(engine/grammar)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(
    parsing_example

    parsing_example.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/ExampleGrammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyParser.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/EarleyItem.h
)
target_link_libraries(parsing_example EarleyParser)
target_link_libraries(parsing_example ExampleGrammar)
target_link_libraries(parsing_example grammar)