project(ConsoleTest)

SET(CMAKE_ASM_MASM_SOURCE_FILE_EXTENSIONS asm)  # 设置NASM的文件扩展名为asm
ENABLE_LANGUAGE(ASM_MASM)

file(GLOB ${PROJECT_NAME}Data "./Data/*.*")
add_definitions(-DCMAKE_PROJECT_NAME="${PROJECT_NAME}")

add_executable(${PROJECT_NAME} main.cpp CommandManager.cpp Hello.asm)

target_link_libraries(${PROJECT_NAME}
        PUBLIC WhaleCore
        PUBLIC WhaleLanguage
        PUBLIC WhaleTool
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}Data
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${PROJECT_NAME}Data} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}Data
)


