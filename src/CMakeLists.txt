cmake_minimum_required(VERSION 3.18)
project(utxghost C)

add_executable(utxghost main.c)
target_sources(utxghost PRIVATE cli/flags.h cli/flags.c)
target_sources(utxghost PRIVATE cli/help.h cli/help.c)
target_sources(utxghost PRIVATE cli/version.h cli/version.c)
target_sources(utxghost PRIVATE utx/types.h utx/types.c)
target_sources(utxghost PRIVATE utx/sysfiles.h utx/sysfiles.c)
target_sources(utxghost PRIVATE utx/remove_entries.h utx/remove_entries.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -s -w")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")