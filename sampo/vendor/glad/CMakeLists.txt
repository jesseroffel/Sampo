# Glad #
cmake_minimum_required(VERSION 3.10...3.21)

MESSAGE(STATUS ${PROJECT_SOURCE_DIR})

project(glad VERSION "1.0.0")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/glad/${outputdir})

include_directories("include/")

add_library(glad STATIC "include/glad/glad.h" "include/KHR/khrplatform.h" "src/glad.c")

target_include_directories(glad PUBLIC "include/")
