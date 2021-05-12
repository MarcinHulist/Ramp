cmake_minimum_required(VERSION 3.0)

project(UnitTests)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../RampLib/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SRC 
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/Constants.h
${CMAKE_CURRENT_SOURCE_DIR}/src/InputParserTests.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/RGB565ColourTests.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/PatternTests.cpp
)


add_executable(UnitTests
    ${SRC}
)

target_link_libraries(UnitTests
    RampLib
)

set(UNIT_TEST UnitTests)

add_custom_command(
     TARGET ${UNIT_TEST}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${UNIT_TEST}
)

