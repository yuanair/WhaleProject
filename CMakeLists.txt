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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_CXX_COMPILER_ID}/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_CXX_COMPILER_ID}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_CXX_COMPILER_ID}/${CMAKE_BUILD_TYPE})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR})
#
configure_file(${PROJECT_SOURCE_DIR}/WhaleConfig.cmake.in
        "${PROJECT_SOURCE_DIR}/WhaleConfig.cmake" @ONLY)

# sub
add_subdirectory(GLAD)
add_subdirectory(Test)
add_subdirectory(Whale)
