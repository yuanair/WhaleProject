
file(GLOB WhalePlatformHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhalePlatformSource "./*.cpp" "./*/*.cpp")

add_library(WhalePlatform SHARED ${WhalePlatformSource})

target_include_directories(WhalePlatform PRIVATE ${PROJECT_SOURCE_DIR}/DirectX-Headers-main/include)

target_link_libraries(WhalePlatform PUBLIC WhaleCore PRIVATE GLAD)


message(STATUS "EigenRoot: ${EIGEN_ROOT}")
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

find_package(Eigen3 REQUIRED)
message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
target_include_directories(WhalePlatform PUBLIC ${EIGEN3_INCLUDE_DIR})

#if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#
#    target_include_directories(WhaleCore PUBLIC ${EIGEN_ROOT})
#
#else ()
#
#    find_package(Eigen3 REQUIRED)
#    include_directories(${EIGEN3_INCLUDE_DIR})
#
#endif ()
