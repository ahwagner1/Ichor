# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ichor_lang VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES
    src/main.c
    src/lexer.c
)

include_directories(include)

add_executable(ichor ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ichor PRIVATE -fsanitize=address -g)
    target_link_options(ichor PRIVATE -fsanitize=address)
endif()

install(TARGETS ichor DESTINATION bin)
