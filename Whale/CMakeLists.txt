cmake_minimum_required(VERSION 3.27)

file(GLOB WhaleHeader "./*/*.h" "./*/*.hpp")
file(GLOB WhaleSource "./*/*.c" "./*/*.cpp" "../GLAD/src/glad.c")

add_library(Whale SHARED ${WhaleSource})

target_include_directories(Whale PUBLIC "../../boost_1_85_0" PRIVATE "../DirectX-Headers-main/include" PRIVATE "../GLAD/include")

target_link_directories(Whale PUBLIC "../../boost_1_85_0/stage/lib/")
