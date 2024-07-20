
file(GLOB WhaleToolHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhaleToolSource "./*.cpp" "./*/*.cpp")

add_library(WhaleTool SHARED ${WhaleToolSource})

target_link_libraries(WhaleTool PUBLIC WhaleCore)
