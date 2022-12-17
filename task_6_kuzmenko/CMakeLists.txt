cmake_minimum_required(VERSION 3.2)

project(polinomial_calc LANGUAGES CXX)

set(CMAKE_CCX_STANDART 17)

add_executable(main Poly.h main.cpp Poly.cpp)