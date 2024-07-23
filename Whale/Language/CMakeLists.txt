
file(GLOB WhaleLanguageHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhaleLanguageSource "./*.cpp" "./*/*.cpp")

add_library(WhaleLanguage SHARED ${WhaleLanguageSource})

target_link_libraries(WhaleLanguage PUBLIC WhaleCore)
