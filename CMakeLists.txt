cmake_minimum_required(VERSION 3.27)
project(WhaleProject LANGUAGES CXX)

# C++
set(CMAKE_CXX_STANDARD 20)


# Compiler
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_compile_options(-utf-8)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)

else ()
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

# Wall
# add_compile_options(-Wall)

# no exception
# add_compile_options(-fno-exceptions)

# UNICODE
add_definitions(-DUNICODE -D_UNICODE)

# output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# include
include_directories(".")

# sub
add_subdirectory(eigen-3.4.0)
add_subdirectory(GLAD)
add_subdirectory(Test)
add_subdirectory(Whale)
