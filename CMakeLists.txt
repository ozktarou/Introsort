cmake_minimum_required(VERSION 3.21)

set(TARGET_NAME "omoteura-introsort")
set(TARGET_VERSION 1.0.0.0)

project(${TARGET_NAME} VERSION ${TARGET_VERSION})

install(DIRECTORY include/ DESTINATION include)

add_subdirectory(example)
