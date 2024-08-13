project(Win32Test)

file(GLOB ${PROJECT_NAME}Data "./Data/*.*")
add_definitions(-DCMAKE_PROJECT_NAME="${PROJECT_NAME}")

file(GLOB Source "*.cpp" "./Resources/Resources.*")

add_executable(${PROJECT_NAME} WIN32 ${Source})

IF (WIN32)
    SET(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
    SET(CMAKE_STATIC_LINKER_FLAGS /MANIFEST:NO)
    SET(CMAKE_SHARED_LINKER_FLAGS /MANIFEST:NO)
ENDIF (WIN32)
# SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")

target_link_libraries(${PROJECT_NAME}
        PUBLIC WhaleCore
        PUBLIC WhaleLanguage
        PUBLIC WhalePlatform
        PUBLIC WhaleRender
        PUBLIC WhaleTool
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}Data
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${PROJECT_NAME}Data} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}Data
)


