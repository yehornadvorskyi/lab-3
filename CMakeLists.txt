cmake_minimum_required(VERSION 3.20)
project(lab-3 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4 /EHsc)
endif()

add_executable(lab-3
    main.cpp
    action.cpp
    action.h
)