cmake_minimum_required(VERSION 3.13)
project(Forest)
add_executable(${PROJECT_NAME} libs/globals/globals.cpp main.cpp)

add_subdirectory(libs)

add_subdirectory(graphics)


