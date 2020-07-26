cmake_minimum_required(VERSION 3.17)

project(test CXX)

find_path(lib_header lib/winbgmim.hpp lib/keys_n_colors.hpp)
find_library(lib_dll libwinbgim PATHS ${CMAKE_SOURCE_DIR}/lib)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp 
              ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_executable(test src/main.cpp)
target_link_libraries(test ${lib_dll})