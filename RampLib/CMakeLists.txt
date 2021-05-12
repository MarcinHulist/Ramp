cmake_minimum_required(VERSION 3.0)

project(RampLib)

set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SRC 
${CMAKE_CURRENT_SOURCE_DIR}/include/Display.h
${CMAKE_CURRENT_SOURCE_DIR}/src/Display.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/InputParser.h
${CMAKE_CURRENT_SOURCE_DIR}/src/InputParser.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/Types.h
${CMAKE_CURRENT_SOURCE_DIR}/include/Pattern.h
${CMAKE_CURRENT_SOURCE_DIR}/src/Pattern.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/PatternDrawer.h
${CMAKE_CURRENT_SOURCE_DIR}/src/PatternDrawer.cpp
)


add_library(RampLib STATIC
    ${SRC}
)

target_compile_options(RampLib PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall -Werror -Wextra -pedantic>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)
