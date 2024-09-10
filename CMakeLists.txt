cmake_minimum_required(VERSION 3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# SAMPO PROJECT SOLUTION #
project(Sampo VERSION 0.1.0 DESCRIPTION "Sampo Game Framework" LANGUAGES CXX)

# Global variable sets #
set(platformname "Win64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${platformname})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${platformname})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${platformname})

if (MSVC)
	MESSAGE(STATUS "Generating a Win32 build")
endif()

# Sampo Library #
add_subdirectory(sampo)
# Framewwork Demo #
add_subdirectory(demo)