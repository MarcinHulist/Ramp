cmake_minimum_required(VERSION 3.0)

project(Ramp)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../RampLib/include)

set(SRC 
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(Ramp
    ${SRC}
)

target_link_libraries(Ramp
    RampLib
)


