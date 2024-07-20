
file(GLOB WhaleLanguageHeader "./*/*.hpp")
file(GLOB WhaleLanguageSource "./*/*.cpp")

add_library(WhaleLanguage SHARED ${WhaleLanguageSource})

target_link_libraries(WhaleLanguage PUBLIC WhaleCore)
