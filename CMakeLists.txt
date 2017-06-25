cmake_minimum_required(VERSION 2.6.0)
project(jsonc C)

include_directories(include)
file(GLOB_RECURSE sources src/ *.c)

add_library(jsonc SHARED ${sources})
add_library(jsonc_static STATIC ${sources})
