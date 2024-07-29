
file(GLOB WhalePlatformHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhalePlatformSource "./*.cpp" "./*/*.cpp")

add_library(WhalePlatform SHARED ${WhalePlatformSource})

target_include_directories(WhalePlatform PUBLIC ${PROJECT_SOURCE_DIR}/eigen-3.4.0 PRIVATE ${PROJECT_SOURCE_DIR}/DirectX-Headers-main/include)

target_link_libraries(WhalePlatform PUBLIC WhaleCore PRIVATE GLAD)
