cmake_minimum_required(VERSION 3.9)
project(Ramp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(RampLib)
add_subdirectory(Ramp)
add_subdirectory(UnitTests)
