
file(GLOB Source "./*/*.cpp" "./*/*/*.cpp" "./*/*.hpp" "./*/*/*.hpp")

add_library(WhaleLanguage SHARED ${Source})

target_include_directories(WhaleLanguage PUBLIC ".")

target_link_libraries(WhaleLanguage PUBLIC WhaleCore)
