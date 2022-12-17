cmake_minimum_required(VERSION 3.2)

project(Prime LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()



add_executable(prime prime.cpp)