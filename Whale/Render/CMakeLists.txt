
file(GLOB WhaleRenderHeader "./*/*.hpp")
file(GLOB WhaleRenderSource "./*/*.cpp")

add_library(WhaleRender SHARED ${WhaleRenderSource})

target_include_directories(WhaleRender PRIVATE "${PROJECT_SOURCE_DIR}/DirectX-Headers-main/include")

target_link_libraries(WhaleRender PRIVATE WhaleCore PRIVATE GLAD)
