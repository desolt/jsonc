cmake_minimum_required(VERSION 2.6.0)
project(jsonc C)

include_directories(include)
file(GLOB_RECURSE sources src/*.c)

add_library(${PROJECT_NAME} SHARED ${sources})

install(TARGETS ${PROJECT_NAME} DESTINATION lib/)

file(GLOB_RECURSE HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
