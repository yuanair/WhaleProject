
file(GLOB WhaleToolHeader "./*/*.hpp")
file(GLOB WhaleToolSource "./*/*.cpp")

add_library(WhaleTool SHARED ${WhaleToolSource})

target_include_directories(WhaleTool PUBLIC "D:/boost_1_85_0")

target_link_directories(WhaleTool PUBLIC "D:/boost_1_85_0/stage/lib/")

target_link_libraries(WhaleTool PRIVATE WhaleCore)
