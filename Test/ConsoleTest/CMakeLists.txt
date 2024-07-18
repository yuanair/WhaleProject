
add_executable(ConsoleTest main.cpp)

target_link_libraries(ConsoleTest
        PUBLIC WhaleCore
        PUBLIC WhaleLanguage
        PUBLIC WhaleRender
        PUBLIC WhaleTool
)

target_include_directories(ConsoleTest PUBLIC "../../../boost_1_85_0")

target_link_directories(ConsoleTest PUBLIC "../../../boost_1_85_0/stage/lib")

#add_custom_command(TARGET ConsoleTest
#        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConsoleTestData
#        COMMAND ${CMAKE_COMMAND} -E
#        copy_directory
#        ./Resources
#        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConsoleTestData
#)


