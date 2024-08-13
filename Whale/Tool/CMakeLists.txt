
file(GLOB Source "./*/*.cpp" "./*/*/*.cpp" "./*/*.hpp" "./*/*/*.hpp")

add_library(WhaleTool SHARED ${Source})

target_include_directories(WhaleTool PUBLIC ".")

target_link_libraries(WhaleTool PUBLIC WhaleCore)
