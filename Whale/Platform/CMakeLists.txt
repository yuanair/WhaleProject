
file(GLOB WhalePlatformHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhalePlatformSource "./*.cpp" "./*/*.cpp")

add_library(WhalePlatform SHARED ${WhalePlatformSource})

target_include_directories(WhalePlatform PRIVATE ${PROJECT_SOURCE_DIR}/DirectX-Headers-main/include)

target_link_libraries(WhalePlatform PUBLIC WhaleCore PRIVATE GLAD)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

    set(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../eigen-3.4.0")
    message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
    target_include_directories(WhalePlatform PUBLIC ${EIGEN3_INCLUDE_DIR})

else ()

    find_package(Eigen3 REQUIRED)
    message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
    target_include_directories(WhalePlatform PUBLIC ${EIGEN3_INCLUDE_DIR})

endif ()




