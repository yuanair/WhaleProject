
project(GLAD LANGUAGES C)

add_library(GLAD STATIC "./src/glad.c")

target_include_directories(GLAD PUBLIC "include")
