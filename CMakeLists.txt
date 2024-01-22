cmake_minimum_required(VERSION 3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# SAMPO PROJECT SOLUTION #
project(Sampo VERSION 0.0.2 DESCRIPTION "Sampo Game Framework" LANGUAGES CXX)

# Global variable sets #
set(outputdir "${CMAKE_SYSTEM_NAME}-${CMAKE_VS_PLATFORM_NAME}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${outputdir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${outputdir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${outputdir})

# Framework Library #
add_subdirectory(framework)
# Framewwork Demo #
add_subdirectory(demo)

# Test projects #
add_subdirectory(tcp_chatclient)
add_subdirectory(tcp_chatserver)