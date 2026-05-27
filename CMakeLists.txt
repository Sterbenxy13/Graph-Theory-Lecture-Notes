
cmake_minimum_required(VERSION 3.15)
project(GraphDataStructuresAndAlgorithms)

# Define a versão do c++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# target_include_directories(utils PRIVATE /utils)
# target_include_directories(matrix PRIVATE /matrix)

add_library(myUtils
    utils/printing.cpp
    utils/printing.h
)

add_library(myMatrix
    matrix/MyMatrix.cpp
    matrix/MyMatrix.h
)

add_executable(main_app main.cpp)

target_link_libraries(main_app PRIVATE myMatrix myUtils)
