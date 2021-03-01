add_definitions(-g -Wall -std=c++2a)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(
    tests 
    
    test_main.cpp 
    engine/grammar/Rule_test.cpp
    engine/grammar/Grammar_test.cpp

    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Rule.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Grammar.h
    ${PROJECT_SOURCE_DIR}/include/bestinshow/engine/grammar/Symbol.h
)
# target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(tests grammar)
target_link_libraries(tests spdlog)