
file(GLOB WhaleCoreHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhaleCoreSource "./*.cpp" "./*/*.cpp")

add_library(WhaleCore SHARED ${WhaleCoreSource})

target_include_directories(WhaleCore PUBLIC D:/boost_1_85_0)

target_link_directories(WhaleCore PUBLIC D:/boost_1_85_0/stage/lib)

# target_link_libraries(WhaleCore PUBLIC Boost)
