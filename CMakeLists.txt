cmake_minimum_required(VERSION 3.16)

project(NetworkGuardian)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(NetworkGuardian
    src/main.cpp
    src/Host.cpp
)
