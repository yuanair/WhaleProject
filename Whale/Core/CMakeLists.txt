
file(GLOB WhaleCoreHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhaleCoreSource "./*.cpp" "./*/*.cpp")

add_library(WhaleCore SHARED ${WhaleCoreSource})

target_include_directories(WhaleCore PRIVATE "D:/boost_1_85_0")

target_link_directories(WhaleCore PRIVATE "D:/boost_1_85_0/stage/lib/")
