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

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
        ${PROJECT_SOURCE_DIR}/bin/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG
        ${PROJECT_SOURCE_DIR}/bin/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG
        ${PROJECT_SOURCE_DIR}/bin/Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
        ${PROJECT_SOURCE_DIR}/bin/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE
        ${PROJECT_SOURCE_DIR}/bin/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE
        ${PROJECT_SOURCE_DIR}/bin/Release)

# sub
add_subdirectory(GLAD)
add_subdirectory(Test)
add_subdirectory(Whale)
