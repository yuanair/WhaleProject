
file(GLOB WhalePlatformHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhalePlatformSource "./*.cpp" "./*/*.cpp")

add_library(WhalePlatform SHARED ${WhalePlatformSource})

target_include_directories(WhalePlatform PRIVATE ${PROJECT_SOURCE_DIR}/DirectX-Headers-main)

target_link_libraries(WhalePlatform PUBLIC WhaleCore PRIVATE GLAD)
