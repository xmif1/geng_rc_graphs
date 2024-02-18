cmake_minimum_required(VERSION 3.23)
project(geng_rc_graphs C)

set(CMAKE_C_STANDARD 99)

set(NAUTY /usr/local/nauty)
include_directories(include ${NAUTY})

add_executable(${PROJECT_NAME} main.c ${NAUTY}/geng.c ${NAUTY}/gtools.h)
target_link_libraries(${PROJECT_NAME} ${NAUTY}/nauty.a)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -DNDEBUG -DMAXN=WORDSIZE -DGENG_MAIN=geng_main -DPREPRUNE=PRUNE -DPRUNE=PRUNE")
