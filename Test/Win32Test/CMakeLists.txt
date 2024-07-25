project(Win32Test)

file(GLOB ${PROJECT_NAME}Data "./Data/*.*")
add_definitions(-DCMAKE_PROJECT_NAME="${PROJECT_NAME}")

add_executable(${PROJECT_NAME} WIN32 main.cpp ./Resources/Resources.rc)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")

target_link_libraries(${PROJECT_NAME}
        PUBLIC WhaleCore
        PUBLIC WhaleLanguage
        PUBLIC WhalePlatform
        PUBLIC WhaleTool
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}Data
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${PROJECT_NAME}Data} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}Data
)


