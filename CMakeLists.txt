cmake_minimum_required(VERSION 3.28)
project(OpenIRIS)

set(CMAKE_CXX_STANDARD 26)

add_executable(Compiler main.cpp
        lexer/lexer.h
        lexer/lexer.cpp
)
