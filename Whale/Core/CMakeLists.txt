
file(GLOB WhaleCoreHeader "./*.hpp" "./*/*.hpp")
file(GLOB WhaleCoreSource "./*.cpp" "./*/*.cpp")

add_library(WhaleCore SHARED ${WhaleCoreSource})

set(BOOST_ROOT "$ENV{BOOST_ROOT}")

message(STATUS "BoostRoot: ${BOOST_ROOT}")

find_package(Boost COMPONENTS REQUIRED log locale)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

    target_link_libraries(WhaleCore ${Boost_LIBRARIES})
endif ()

# target_link_libraries(WhaleCore PUBLIC Boost)
