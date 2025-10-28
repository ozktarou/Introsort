cmake_minimum_required(VERSION 3.21)

option(ENABLE_EXAMPLE "Enable example" OFF)
option(ENABLE_TEST "Enable test" OFF)

set(TARGET_NAME "omoteura-introsort")
set(TARGET_VERSION 1.0.0.0)

project(${TARGET_NAME} VERSION ${TARGET_VERSION})

install(DIRECTORY include/ DESTINATION include)

if(ENABLE_EXAMPLE)
    add_subdirectory(example)
endif()
if (ENABLE_TEST)
    add_subdirectory(test)
endif()
