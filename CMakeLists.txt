cmake_minimum_required(VERSION 3.16...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# SAMPO PROJECT SOLUTION #
project(Sampo VERSION 0.0.1 DESCRIPTION "Sampo Game Framework" LANGUAGES CXX)

set(outputdir "${CMAKE_SYSTEM_NAME}-${CMAKE_GENERATOR_PLATFORM}-${CMAKE_VS_PLATFORM_NAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Framework Library #
add_subdirectory(framework)
# Demo #
add_subdirectory(demo)