
file(GLOB WhaleCoreHeader "./*/*.hpp" "./*/*/*.hpp")
file(GLOB WhaleCoreSource "./*/*.cpp" "./*/*/*.cpp")

add_library(WhaleCore SHARED ${WhaleCoreSource})

target_include_directories(WhaleCore PUBLIC ".")

set(BOOST_ROOT "$ENV{BOOST_ROOT}")

message(STATUS "BoostRoot: ${BOOST_ROOT}")
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

    target_include_directories(WhaleCore PUBLIC ${BOOST_ROOT})
    target_link_directories(WhaleCore PUBLIC ${BOOST_ROOT}/stage/lib)

else ()

    find_package(Boost COMPONENTS REQUIRED
            log
            locale
            json
    )

    if (Boost_FOUND)
        target_include_directories(WhaleCore PUBLIC ${Boost_INCLUDE_DIRS})

        MESSAGE(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
        MESSAGE(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
        MESSAGE(STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

        target_link_libraries(WhaleCore PUBLIC ${Boost_LIBRARIES})
    endif ()

endif ()
