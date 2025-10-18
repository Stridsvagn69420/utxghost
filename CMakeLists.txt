cmake_minimum_required(VERSION 3.18)
project(utxghost C)

add_executable(utxghost main.c)
target_sources(utxghost PRIVATE utx.h utx.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -s -w")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")