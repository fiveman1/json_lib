cmake_minimum_required(VERSION 3.10)
project(json)

set(CMAKE_CXX_STANDARD 17)

include_directories(dependencies/include
        .)

add_executable(json
        main.cpp)
