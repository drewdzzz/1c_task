project(1c_task)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    test_prog
    main.cpp
    lib/matrix_lib.cpp
)