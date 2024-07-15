cmake_minimum_required(VERSION 3.27)

add_executable(Test WIN32 main.cpp)

add_library(NDKTest SHARED NDKTest.cpp)

target_link_libraries(NDKTest PRIVATE
        android
        log
        EGL
        GLESv2
)

target_link_libraries(Test PUBLIC Whale)

# Resource
add_custom_command(TARGET Test
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/bin/Data
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory
        ${PROJECT_SOURCE_DIR}/Test/Resources
        ${PROJECT_BINARY_DIR}/bin/Data
)
