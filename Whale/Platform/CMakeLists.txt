
file(GLOB Source "./*/*.cpp" "./*/*/*.cpp" "./*/*.hpp" "./*/*/*.hpp")

add_library(WhalePlatform SHARED ${Source})


if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

    set(EIGEN3_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../eigen-3.4.0")
    message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
    target_include_directories(WhalePlatform PUBLIC ${EIGEN3_INCLUDE_DIR})

else ()

    find_package(Eigen3 REQUIRED)
    message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
    target_include_directories(WhalePlatform PUBLIC ${EIGEN3_INCLUDE_DIR})

endif ()

target_include_directories(WhalePlatform PUBLIC ".")

target_link_libraries(WhalePlatform PUBLIC WhaleCore)


