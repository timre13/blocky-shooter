cmake_minimum_required(VERSION 3.10)

project(BlockShooter VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

link_libraries(sdl2)

set(CMAKE_CXX_FLAGS "-O2")

file(
    COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/img/
DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/img/)
