cmake_minimum_required(VERSION 3.0)

project(taxi)

add_executable(taxi main.cpp)

install(TARGETS taxi RUNTIME DESTINATION bin)
