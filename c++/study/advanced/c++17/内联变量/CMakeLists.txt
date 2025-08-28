cmake_minimum_required(VERSION 3.16)

project(inline_variables VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.cpp
        config1.cpp
        config.h
        config2.cpp
)

add_executable(inline_variables
            ${PROJECT_SOURCES}
        )

