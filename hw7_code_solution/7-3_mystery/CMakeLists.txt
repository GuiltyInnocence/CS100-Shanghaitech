cmake_minimum_required(VERSION 3.19)
project(kmeans)

set(CMAKE_CXX_STANDARD 14)
#add_compile_options(-Ofast)
add_compile_options(-g -O0 -Wall -Wextra -Werror)
add_executable(kmeans main.cpp kmeans.cpp)