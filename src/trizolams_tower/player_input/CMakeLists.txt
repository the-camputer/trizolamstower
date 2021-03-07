add_subdirectory(grammar)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories(${CMAKE_SOURCE_DIR}/lib)

FIND_PACKAGE(Boost)

add_library(
    InputProcessor

    OBJECT

    InputProcessor.cpp


)
target_link_libraries(InputProcessor grammar EarleyParser)
target_link_libraries(InputProcessor ${Boost_LIBRARIES})