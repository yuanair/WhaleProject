
file(GLOB Source "./*/*.cpp" "./*/*/*.cpp" "./*/*.hpp" "./*/*/*.hpp")

add_library(WhaleBuild SHARED ${Source})

target_include_directories(WhaleBuild PUBLIC ".")

target_link_libraries(WhaleBuild PUBLIC WhaleCore PUBLIC WhalePlatform)
