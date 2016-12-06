cmake_minimum_required(VERSION 3.6)
project(labirin_trap)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c menu.h menu.c)

add_executable(labirin_trap ${SOURCE_FILES})

target_link_libraries(labirin_trap ncurses menu)
