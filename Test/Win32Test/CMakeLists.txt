
add_executable(Test WIN32 main.cpp)

target_link_libraries(Test
        PUBLIC WhaleCore
        PUBLIC WhaleLanguage
        PUBLIC WhaleRender
        PUBLIC WhaleTool
)

target_include_directories(Test PUBLIC "../../../boost_1_85_0")

target_link_directories(Test PUBLIC "../../../boost_1_85_0/stage/lib")

#add_custom_command(TARGET Test
#        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestData
#        COMMAND ${CMAKE_COMMAND} -E
#        copy_directory
#        ./Resources
#        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestData
#)


